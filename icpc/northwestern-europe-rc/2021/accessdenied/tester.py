#!/usr/bin/env python3
#
# Testing tool for the Access Denied problem
#
# Usage:
#
#   python3 testing_tool.py [-p password] <program>
#
# If no password is specified, the sample is used.
#
# You can compile and run your solution as follows.
# - You may have to replace 'python3' by just 'python'.
# - On Windows, you may have to replace '/' by '\'.
#
# If you have a Java solution that you would run using
# "java MyClass", you could invoke the testing tool with:
#
#   python3 testing_tool.py java MyClass
#
# If you have a Python solution that you would run using
# "python solution.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python solution.py
#
# If you have a C++ solution stored in a file called "sol.cpp",
# you must first compile using "g++ sol.cpp -o sol" and then
# invoke the testing tool with:
#
#   python3 testing_tool.py ./sol
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it
# is not guaranteed that a program that passes the testing tool
# will be accepted.
#
import argparse
import subprocess
import sys
import traceback


def write(p, line):
    assert p.poll() is None, 'Program terminated early'
    print('Write: {}'.format(line), flush=True)
    p.stdin.write('{}\n'.format(line))
    p.stdin.flush()


def read(p):
    assert p.poll() is None, 'Program terminated early'
    line = p.stdout.readline().strip()
    assert line != '', 'Read empty line or closed output pipe. Make sure that your program started successfully.'
    print('Read: %s' % line, flush=True)
    return line

def op_if()->int:
    return 1

def op_for()->int:
    return 1

def op_assign()->int:
    return 1

def op_comp()->int:
    return 3

def op_return()->int:
    return 1

def op_init()->int:
    return 1

def delay(user_pw: str, correct_pw: str)-> int:
    assert len(user_pw)>0 and len(user_pw)<21, 'Entered Password has wrong length (0<pw<21)'
    assert len(correct_pw)>0 and len(correct_pw)<21, 'Correct Password has wrong length (0<pw<21)'

    time = op_if()+op_comp()

    if len(user_pw) != len(correct_pw): #Pw length check
        return time+op_return()

    time +=op_init() + op_for() + op_comp() + op_comp() + op_if()
    for i in range(0, common_length(user_pw, correct_pw)):
        time += op_assign() + op_comp() + op_for() + op_comp() + op_if()
    return time + op_return()

def common_length(user_pw: str, correct_pw: str)-> int:
    common = 0
    for i, j in zip(user_pw, correct_pw):
        if i == j:
            common +=1
        else:
            return common
    return common


parser = argparse.ArgumentParser(description='Testing tool for the Access Denied problem')
parser.add_argument('-p', dest='password', metavar='password', default="Hunter2")
parser.add_argument('program', nargs='+', help='Your solution')

args = parser.parse_args()
steps = 0

password = args.password

with subprocess.Popen(" ".join(args.program), shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE,
                          universal_newlines=True) as p:
    try:
        while True:
            guess = read(p)
            assert len(guess)>0 and len(guess)<21, 'Password has wrong length (0<pw<21)'
            steps += 1
            timing=delay(guess, password)
            if guess == password:
                write(p, "ACCESS GRANTED")
                assert p.stdout.readline() == '', 'Printed extra data after finding solution'
                assert p.wait() == 0, 'Did not exit cleanly after finishing'
                break
            else:
                write(p, "ACCESS DENIED ({} ms)".format(timing))
            if steps == 2500:
                sys.stdout.write('Program used too many guesses\n')
                p.kill()
                break
    except:
        traceback.print_exc()
    finally:
        sys.stdout.flush()
        sys.stderr.flush()
        sys.stdout.write('Guessed {} times, exit code: {}\n'.format(steps, p.wait()))
        sys.stdout.flush()
