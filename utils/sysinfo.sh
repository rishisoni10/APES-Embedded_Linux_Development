#!/bin/bash
#@Author: Rishi Soni
#@brief: Stores system information in a text file
#@date: 8 September 2017
#@version: 1.0

OS_TYPE=$(uname -o)
echo "Operating System Type:" ${OS_TYPE} > sysinfo.txt
OS_DISTRIB=$(cat /etc/*-release | grep DISTRIB_DESCRIPTION | cut -d '"' -f 2
)
echo "OS Distribution:" ${OS_DISTRIB} >> sysinfo.txt
echo "Kernel Version:" $(uname -r) >> sysinfo.txt
echo "Kernel Build Information:" $(uname -v) >> sysinfo.txt

test=""
test+="GCC Version used for Kernel Build: $(cat /proc/version | awk '{print $5}') "
test+="$(cat /proc/version | awk '{print $6}') "
test+="$(cat /proc/version | awk '{print $7}') "
test+="$(cat /proc/version | awk '{print $8}') "
test+="$(cat /proc/version | awk '{print $9}') "
test+="$(cat /proc/version | awk '{print $10}') "
test+="$(cat /proc/version | awk '{print $11}')"
echo ${test} >> sysinfo.txt

test=""
test+="Kernel Build Time: $(uname -v | awk '{print $4}') "
test+="$(uname -v | awk '{print $5}') "
test+="$(uname -v | awk '{print $6}') "
test+="$(uname -v | awk '{print $7}') "
test+="$(uname -v | awk '{print $8}')"
echo ${test} >> sysinfo.txt

echo "System Architecture:"$(lscpu | grep Architecture | cut -d ':' -f 2) >> sysinfo.txt
