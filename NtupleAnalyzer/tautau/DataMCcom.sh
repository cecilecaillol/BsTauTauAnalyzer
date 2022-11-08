#!/bin/bash

while read line;
do
    echo $line;
    ./DataMCcom_sf_addSSQCD.exe $line;
done < DataMCcom.txt