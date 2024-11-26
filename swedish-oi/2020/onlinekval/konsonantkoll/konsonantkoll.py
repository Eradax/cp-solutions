#!/usr/bin/env python3
i=input()
print(''.join(a for a,b,c in zip(i,i[1:],i[2:])if(a==b==c)*(a in"bcdfghjklmnpqrstvwxz")-1)+i[-2:])

