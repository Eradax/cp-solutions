D=input
G=int(D())
E=[int(A)for A in D().split()]
B=0
A=0
C=0
for F in range(1,366):
    B+=A
    if F in E:A+=1
    if B+A>=20:C+=1;B=0;A=0
if A:C+=1
print(C)
