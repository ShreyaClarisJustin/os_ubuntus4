#!/bin/bash
echo "enter file name"
read fn
echo "enter the word to be searched"
read str
if [ -f $fn ]
then
        echo "no of occurences"
        grep -o "$str" "$fn" | wc -w
else
        echo "word not found"
fi
