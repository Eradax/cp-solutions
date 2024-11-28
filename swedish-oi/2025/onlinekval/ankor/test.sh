#!/usr/bin/env bash

ans='1'
res=''
res2=''

counter=0

while [ "$ans" == '1' ]
do
    res=$(timeout 3 ./gen.py) 
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for gen.py"
        break
    fi

    res2=$(echo -n "$res" | timeout 3 ./ankor)
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for ankor"
        break
    fi

    ans=$(echo -n "$res $res2" | timeout 3 ./ankor-test)
    if [ $? -eq 124 ]; then
        echo "Timeout exceeded for ankor-test"
        break
    fi

    ((counter++))
    if [ $counter -gt 100 ]; then
        echo "100 done"
        counter=0
    fi
done

echo "$res"
echo "$res2"
echo "$ans"
