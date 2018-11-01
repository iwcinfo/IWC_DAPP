#!/bin/sh

DIR="/home/eos/contracts/IWC_DEV"

#alias cleos=/home/eos/ibctprivate/cleos.sh
date="2018-11-24"
time="11:16:00"
cleos wallet unlock -n 79wallet < ./walletpassword.txt
$DIR/program/program $date $time #first run program with default start time

date=$(<$DIR/log/start_date.txt)
time=$(<$DIR/log/start_time.txt)
echo $date
echo $time
while :
do
    cleos wallet unlock -n 79wallet < ./walletpassword.txt
    sleep 2s
    $DIR/program/program $date $time
    date=$(<$DIR/log/start_date.txt)
    time=$(<$DIR/log/start_time.txt)
done
