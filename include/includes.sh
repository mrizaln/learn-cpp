#!/bin/bash

wget https://github.com/SergiusTheBest/plog/archive/refs/tags/1.1.6.zip
unzip 1.1.6.zip
mv plog-1.1.6/include/plog .
rm 1.1.6.zip
rm plog-1.1.6 -r
