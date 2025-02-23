#!/bin/bash

# Print the input arguments
echo "Start: $1, End: $2"

# Function to check if a number is a palindrome
palin() {
    n=$1
    rev=0
    temp=$n

    while [ $temp -ne 0 ]
    do
        rem=$(($temp % 10))
        rev=$(($rev * 10 + $rem))
        temp=$(($temp / 10))
    done

    if [ $rev -eq $n ]; then
        echo "$n"
    fi
}

# Assign start and end values from command-line arguments
start=$1
end=$2

echo "Palindrome numbers between $start and $end:"

# Loop through the range and check for palindrome numbers
while [ $start -le $end ]
do
    palin $start
    start=$(($start + 1))
done
