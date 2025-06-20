input()
a = sum(map(int,input().split()))
b = sum(map(int,input().split()))
if a == b:
    print("Oh no")
else:
    print(f"Button {1 + (b > a)}")
