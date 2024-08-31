n=int(input())
print(' '*(n+1)+'x')
for i in range(n):
    print(' '*(n-i)+'/'+' '*(2*i+1)+'\\')
print('x'+' '*(2*n+1)+'x')
for i in range(n)[::-1]:
    print(' '*(n-i)+'\\'+' '*(2*i+1)+'/')
print(' '*(n+1)+'x')