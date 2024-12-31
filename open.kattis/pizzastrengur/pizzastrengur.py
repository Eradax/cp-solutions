#!/usr/bin/env python3

import random

n = int(input())
choices = {'P', 'I', 'Z', 'A'}

def fun():
    known = ""
    for _ in range(n):
        #print(f'known: {known}')
        curr_choices = choices
        while True:
            if len(curr_choices) == 1:
                known += "".join(curr_choices)
                break

            choice = random.choice(list(curr_choices))
            
            print(known+choice, flush=True)
            ans = int(input())

            if ans == 1:
                #print('yay')
                known += choice
                break
            if ans == 2:
                known += choice
                return
                break
            curr_choices = curr_choices - {choice}

    print(known)
fun()
