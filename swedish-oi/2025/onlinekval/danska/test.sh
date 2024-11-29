#!/usr/bin/env bash

ans='1'
res=''
res2=''

counter=0

while true
do
    res=$(timeout 3 ./gen.py) 
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for gen.py"
        break
    fi

    ans=$(echo -n "$res" | timeout 3 ./danska-brute.py)
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for brute"
        ((counter++))
        ans='1'
        continue
    fi

    ans2=$(echo -n "$res" | timeout 3 ./danska)
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for fast"
        break
    fi

    ((counter++))
    if [ $counter -gt 100 ]; then
        echo "100 done"
        counter=0
    fi

    if [ "$(echo "$ans" "$ans2" | ./eq.py)" != '1' ]; then
        break
    fi
done

echo "$res"
echo "$ans"
echo "$ans2"
