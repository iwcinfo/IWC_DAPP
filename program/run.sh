#!/bin/sh

DIR="/home/eos/contracts/IWC_DEV"

#alias cleos=/home/eos/ibctprivate/cleos.sh
date="2018-11-20"
time="16:20:00"
cleos wallet unlock < ./walletpassword.txt &> /dev/null
$DIR/program/program $date $time #first run program with default start time

date=$(<$DIR/log/start_date.txt)
time=$(<$DIR/log/start_time.txt)

while :
do
    cleos wallet unlock < ./walletpassword.txt &> /dev/null
    sleep 2s
    $DIR/program/program $date $time
    date=$(<$DIR/log/start_date.txt)
    time=$(<$DIR/log/start_time.txt)
done
