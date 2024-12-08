#!/usr/bin/env python3

a=max(map(int,open(0).read().split()))
print(("Trubbig","Ratvinklig","Spetsig")[(a<=90)+(a<90)]+" Triangel")
