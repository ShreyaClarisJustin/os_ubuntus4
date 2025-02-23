#!/bin/sh
palin () {
	n=$1
	k=$n
	l=$n
	rem=0
	rev=0
	while [ $l -ne 0 ]
	do
		rem=$(($l%10))
		rev=$(($rev*10))
		rev=$(($rev+$rem))
		l=$(($l/10))
	done
	if [ $rev -eq $n ]
	then
		echo "$n"
	fi
}

start=$1
end=$2
echo " "
while [ $start -lt $end ]
do
	palin $start
	start=$(($start+1))
done
