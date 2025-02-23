#!/bin/bash
read -p 'Enter filename:' filename
if [[ -f $filename ]];
   then
   echo "File exists"
   read -p 'Enter the word you want to search for:' word
   grep $word $filename
   #grep -o "$word" "$filename" |wc -w
else
   echo "File doesn't exist"
fi
