inp = input().split(';')

s=0
for i in inp:
    t=i.split('-')
    if len(t)==1:
        s+=1
    else:
        s+=int(t[-1])-int(t[0])+1
        
print(s)
