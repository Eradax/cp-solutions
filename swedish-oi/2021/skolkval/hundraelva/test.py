import os
for i in range(1000):
    if os.system(f"echo {i} | python hundraelva.py > /dev/null"):
        print(i)
