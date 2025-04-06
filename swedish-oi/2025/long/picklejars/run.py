# PYTHON_ARGCOMPLETE_OK
import collections
import dataclasses
import subprocess
import time
import os
import shlex
import argparse
from typing import DefaultDict


# TODO: dont crash when using -w and the solution crashes
# NOTE: This run script is borrowed from upidapi


@dataclasses.dataclass
class Script:
    name: str
    script: str
    compile: str | None = None


def run_cmd(cmd: str) -> str:
    return subprocess.check_output(cmd, shell=True).decode()


def run_script(name: str, data: str) -> str:
    return subprocess.check_output(f"{name}", input=data.encode(), shell=True).decode()


# kinda cant do that
# you need a lot of control and i don't think there's some nice
# interface
# def run_interactive(solution: Script, interactor: Script):


def run_solution_timed(name: str, data: str) -> (str, float):
    start = time.time_ns()

    count = 0

    # for one sec
    while time.time_ns() - start < 10**9:
        res = run_script(name, data)
        count += 1

    return res, ((time.time_ns() - start) / 10**9) / count  # seconds


def wait_for_file_change(file: str, init_time: int) -> str:
    while True:
        if (mod_time := os.path.getmtime(file)) != init_time:
            return mod_time

        time.sleep(0.1)


def print_diff(a_name, a, b_name, b):
    cmd = (
        "delta "
        "--word-diff-regex . "
        "--features side-by-side "
        "--diff-args=-U99999 "
        "--width 100 "
        # passing the strings through process substitution
        f"<(echo {shlex.quote(a)}) <(echo {shlex.quote(b)}) "
        # remove the file names
        "| tail +8"
    )
    print(f">>> {a_name} | {b_name}")
    # print(cmd)
    print(run_cmd(cmd))


def run_solutions(
    solution: Script,
    compare: Script | None = None,
    generator: Script | None = None,
    validator: Script | None = None,
    # interactor: Script | None = None,
    inp_file: str = "inp.txt",
    compile: bool = True,
    # only run them once
    once: bool = False,
    # time the solutions
    time_solution: bool = False,
    # run until it finds a case where the outputs don't match
    exit_on_missmatch: bool = True,
    # only rerun once the inp file changes
    watch_inp_update: bool = True,
    # print total, fail, fail% for each iteration
    print_fail_count: bool = False,
):
    mtime = -1

    total = 0
    fails = 0

    if compile:
        print("Compiling:")
        for script in [solution, compare, generator, validator]:
            if script is None or script.compile is None:
                continue

            print(f"{script.name:-^60}")
            print(script.compile)
            print()
            try:
                print(run_cmd(script.compile))
            except subprocess.CalledProcessError:
                print()
                print("Compilation failed")
                exit()

            print()

    def run(data: str, script: Script):
        print(f"{script.name:-^60}")

        if time_solution:
            res, t = run_solution_timed(script.script, data)
            print(res)
            print(f"run time: {t}")
        else:
            res = run_script(script.script, data)
            print(res)

        if validator is not None:
            print(f"{'validating with ' + validator.name:-^60}")
            print(data + "\n" + res)
            print("---")
            run_script(validator.script, data + "\n" + res)

        print()

        return res

    while True:
        # generate data
        if generator is not None:
            inp_data = run_cmd(generator.script)
            with open(inp_file, "w") as f:
                f.write(inp_data)

        # make sure we have new data
        if watch_inp_update:
            mtime = wait_for_file_change(inp_file, mtime)

        with open(inp_file) as f:
            data = f.read()

        print("-" * 100)
        print(data)
        print()

        if compare is not None:
            b = run(data, compare)

            a = run(data, solution)

            total += 1

            if a != b:
                fails += 1
                print_diff(solution.name, a, compare.name, b)

                if exit_on_missmatch:
                    return

            if once:
                return

            print()
            print()

            if print_fail_count:
                print(f"{total} | {fails} | {fails / total}")

            continue

        run(data, solution)

        if once:
            return


def cpp_script(file):
    output_name = f"./test-{file[: -len('.cpp')]}.out"

    return Script(
        name=file,
        script=output_name,
        compile=(
            "g++ "
            # maybe add a kattis profile since that doesnt have
            # -fsanitize=undefined,address
            "-fsanitize=undefined,address "
            # remove the dbg printing stuff
            # "-DLOCAL "
            # "-g "
            "-O3 "
            "-Wall "
            f"{file} "
            f"-o {output_name}"
        ),
    )


def py_script(file):
    return Script(name=file, script=f"python {file}")


def txt_script(file):
    return Script(name=file, script=f"cat {file}")


def to_script(file):
    file_handler = {
        "py": py_script,
        "cpp": cpp_script,
        "txt": txt_script,
    }.get(file.split(".")[-1])

    if file_handler is None:
        raise Exception("file is not py nor cpp file")

    return file_handler(file)


# run_solutions(
#     solution=cpp_script("main-v2.cpp"),
#     compare=py_script("main-old.py"),
#     generator=py_script("gen.py"),
#     # once=True,
#     # time_solution=True,
#     compile=False,
#     print_fail_count=True,
# )


def get_args():
    parser = argparse.ArgumentParser(description="Process some files and flags.")

    # parser.add_argument(
    #     "-D",
    #     "--directory",
    #     type=str,
    #     help="Specify the directory.",
    #     required=False,
    #     default=".",
    # )

    parser.add_argument(
        "-s",
        "--solution",
        type=str,
        help="Specify the solution",
        required=False,
    )

    # Files
    parser.add_argument(
        "-c",
        "--compare",
        type=str,
        help="Specify the solution to compare with",
        required=False,
    )

    parser.add_argument(
        "-v",
        "--validator",
        type=str,
        help="Specify the validator",
        required=False,
    )

    # group = parser.add_mutually_exclusive_group(required=True)
    parser.add_argument(
        "-g",
        "--generator",
        type=str,
        help="A generator to create new test data",
        required=False,
    )
    parser.add_argument(
        "-d",
        "--inp-file",
        type=str,
        help="Input data file, will be overwriten if a generator is provided",
        default="inp.txt",
    )

    # parser.add_argument(
    #     "-i",
    #     "--interactor",
    #     type=argparse.FileType("r"),
    #     help="Specify the interactor file",
    #     required=False,
    # )

    # Flags
    parser.add_argument(
        "-w",
        "--watch-inp",
        action="store_true",
        help="Rerun when input file changes",
    )
    parser.add_argument(
        "-1",
        "-o",
        "--once",
        action="store_true",
        help="Run once",
    )
    parser.add_argument(
        "-N",
        "--no-compile",
        action="store_true",
        help="Dont recompile files",
        default=False,
    )
    parser.add_argument(
        "-e",
        "--find-error",
        action="store_true",
        help="Terminate on missmatch",
        # default=True,
    )
    parser.add_argument(
        "-f",
        "--print-fail-count",
        action="store_true",
        help="Print the fail count",
    )
    parser.add_argument("-t", "--time", action="store_true", help="Time solutions")

    args = parser.parse_args()

    if args.find_error and not args.compare:
        parser.error("--find-error requires --compare to be set.")

    return args


def main():
    args = get_args()

    solution, compare, generator, validator = map(
        lambda file: None if file is None else to_script(file),
        [
            args.solution,
            args.compare,
            args.generator,
            args.validator,
        ],
    )

    run_solutions(
        solution=solution,
        compare=compare,
        generator=generator,
        validator=validator,
        # interactor: Script | None = None,
        inp_file=args.inp_file,
        compile=not args.no_compile,
        # only run them once
        once=args.once,
        # time the solutions
        time_solution=args.time,
        # run until it finds a case where the outputs don't match
        exit_on_missmatch=args.find_error,
        # only rerun once the inp file changes
        watch_inp_update=args.watch_inp,
        # print total, fail, fail% for each iteration
        print_fail_count=args.print_fail_count,
    )


if __name__ == "__main__":
    main()


"""
-d --directory

# all folowing are files
-c --compare  

# one of
-g --generator 
-d --inp-file

-i --interactor

# flags
-o --once 
-w --watch-inp  # rerun when inp file changes
-e --find-error  # terminate when 
-t --time
-f --print-fail-count
"""
