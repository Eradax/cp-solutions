#!/usr/bin/env python3

print(max([(-len(i),i)for i in open(0).read().split()[1:]if len(i)==len({*i})>4]or((1,'Neibb')))[1])