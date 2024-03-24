#!/bin/bash

set -e

rm -rf `pwd`/build/*
cd `pwd`/build && cmake .. && make
cd ..
cp -r `pwd`/include `pwd`/lib

# 把头文件拷贝到 /usr/include/mymuduo  so库拷贝到 /usr/lib    PATH
if [ ! -d /usr/include/rpc ]; then 
    mkdir /usr/include/rpc
fi

cd `pwd`/include

# 拷贝hpp文件
for header in `ls *.h`
do
    cp $header /usr/include/rpc
done

cd ..
cp `pwd`/lib/librpc.a /usr/lib

ldconfig