#!/bin/bash

while read line;
do
    echo $line;
    #./basic_selection_tautau_sf.exe $line;
    .//basic_selection_tautau.exe $line;
done < basic_selection_data.txt
#done < basic_selection.txt