#!/bin/bash

while read line;
do
    echo $line;
    ./DataMCcom_estbkg.exe $line;
done < DataMCcom.txt