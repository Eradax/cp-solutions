#!/usr/bin/env python3
n=".***..|*.....|*.*...|**....|**.*..|*..*..|***...|****..|*.**..|.**...".split('|')
print('\n'.join(' '.join(l)for l in zip(*[[n[int(i)][j:j+2]for j in(0,2,4)]for i in str(sum((input(),int(''.join(str(n.index(''.join(i)))for i in zip(*[input().split()for _ in'   ']))))[1]for _ in'  '))])))

