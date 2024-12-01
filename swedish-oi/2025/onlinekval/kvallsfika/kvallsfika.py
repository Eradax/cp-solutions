n,p,k,*A=map(int,open(0).read().split())
i,*r=[0]*9**6
for(a,b)in sorted(zip(A[:n],A[n:])):
 if(a>p)|(r[b-1]>=k)<1:r[b-1]+=1;p-=a;i+=1
print(i)
