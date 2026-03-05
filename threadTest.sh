#!/bin/bash

rounds=50

make all

./datagen -s 20

rm outputs.txt
rm diff.txt

touch diff.txt
touch outputs.txt

./main 1
cp data_output temp.txt

for i in {1..50}
do
    ./main 1
    diff temp.txt data_output >> diff.txt
    cat data_output >> outputs.txt
    rm temp.txt
    cp data_output temp.txt
done
