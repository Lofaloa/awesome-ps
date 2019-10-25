#!/bin/bash

echo "========= MOCK PROCESS ========="
echo "My PID is $$"

echo "Active infinite loop..."

count=0
while true; do
    count=$[count+1]
done
