#!/bin/bash

while read line;
do
    echo $line;
    ./basic_selection_mutau_sf.exe $line;
done < basic_selection.txt