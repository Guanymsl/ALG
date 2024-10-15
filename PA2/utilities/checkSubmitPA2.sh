#!/bin/bash

#############################################################################
# File       [ checkSubmitPA2.sh ]
# Author     [ funnymean ]
# Modified   [ 2021/11/14 by Yan-Lin Chen]
# Synopsis   [ simple test for algorithm PA2 homework format program ]
# Date       [ Ver. 2 started 2021/11/14 ]
#############################################################################


if [ "$1" == "" ]; then
    echo "Usage:   ./checkSubmitPA2.sh <fileName>"
    echo "Example: ./checkSubmitPA2.sh b09901000_pa2.tgz"
    echo "This program will build a dir name checkSubmitPA2_$$ env"
    exit
fi

binaryFileName='mps'
fileName=$1

echo "Target file $fileName"
if [ ! -f $fileName ]; then
    echo "Cannot find tgz file $filename!"
    exit
fi
if [ -d check_$$ ]; then
    echo "Directory check_$$ exists"
    echo "Please delete the directory and try again"
    exit
fi

mkdir check_$$
cd check_$$


tar zxvf ../$fileName

stuid=`basename $fileName | sed -e 's/_.*//'`
echo "$fileName"
echo "$stuid"


if [ ! -d ${stuid}_pa2 ]; then
    echo "Cannot find directory <student id>_pa2"
    cd ..
    rm -rf check_$$
    exit
fi

cd ${stuid}_pa2
echo "checking README ..."
if [ ! -f README ]; then
    echo "Cannot find README"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking src/ ..."
if [ ! -d src ]; then
    echo "Cannot find src dir"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking doc/ ..."
if [ ! -d doc ]; then
    echo "Cannot find doc dir"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking report ..."
report_exist=`ls doc | grep report.pdf`
if [ "${report_exist}" = "" ]; then
    echo "Cannot find doc/report.pdf"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking makefile ..."
if [ ! -f makefile ]; then
    echo "Cannot find makefile"
    cd ../../
    rm -rf check_$$
    exit
fi

rm -f bin/$binaryFileName
make clean
make

if [ ! -f bin/$binaryFileName ]; then
    echo "Cannot find bin/$binaryFileName"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "Congratulations!  Passed submission checking!"
cd ../../
rm -rf check_$$

