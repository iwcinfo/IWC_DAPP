#!/bin/sh
DIR="/home/eos/contracts/IWC_DEV"

url=$(<$DIR/log/output.txt)
rm -rf $DIR/log/api_out.json
curl -s $url |\
  jq '.' > $DIR/log/api_out.json

echo "$url" >> $DIR/log/api_archive.json
curl -s $url |\
  jq '.' >> $DIR/log/api_archive.json
