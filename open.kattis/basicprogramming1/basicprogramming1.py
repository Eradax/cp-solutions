P=print
I=lambda:[*map(int,input().split())]
q=("P(7)","P('BSEimqgauglaellre  r '[(A[0]<=A[1])+(A[0]==A[1])::3])","P(sorted(A[:3])[1])","P(sum(A))","P(sum(x for x in A if x%2-1))","P(''.join(chr(97+x%26)for x in A))","i=0;v=[0]*n;a='Out'\nwhile 0<=i<n:\n	if v[i]:a='Cyclic';break\n	if i==n-1:a='Done';break\n	v[i]=1;i=A[i]\nP(a)")
n,t=I()
A=I()
exec(q[t-1])