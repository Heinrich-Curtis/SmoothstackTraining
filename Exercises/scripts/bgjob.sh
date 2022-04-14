#!/bin/bash
#bg process I can kill
val=1
#echo "val is $val"
FREEFILENAME=file.txt
CPUIFILENAME=cpuinfo.txt
INITINFODIR=InitInfo
MEMIFILENAME=meminfo.txt
TOPFILENAME=topdata.txt
#make an init info directory
mkdir $INITINFODIR
cd $INITINFODIR
#get the cpu info
cat /proc/cpuinfo > $CPUIFILENAME
#get the meminfo
cat /proc/meminfo > $MEMIFILENAME
#back to the main dir
cd ..
TIMESTAMP=$(date | awk '{print $4 "-" $3 "-"$2}') #sorta works, might just wantto use date on its own and get its fields (man date)
echo $TIMESTAMP
#let's also find the pid for this process so we can try and kill it
#TODO getting 2 pids here, I assume one of them is the one that ps | awk is running in?
THISPID=$(ps | awk '$4 == "awk"{print $1}')
echo $THISPID > pid.txt
#start tracking free's output
#also get output from top corresponding to this process, YEP
rm $FREEFILENAME
while [ "$val" -le  10 ] #the spaces around the brackets are necessary
do
	top -b -n 1 | awk '$12 == "bgjob.sh"{print}' >> $TOPFILENAME #only print the whole row if the 12th element is the name of this program
	free | awk 'NR==2{print $2}' >> $FREEFILENAME # this says "get the second entry from every line and put it in the file. We want all these entries in one file
	val=$((val + 1))
done

