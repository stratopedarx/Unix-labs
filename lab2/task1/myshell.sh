#!/bin/bash

if [ ! -f newfile.log ] ;then
    echo "This $0 was used command $*" > newfile.log
fi
date > date.log
case $1 in
    's')
        echo $*;;
    'l')
        ls -la .;;
     '--help')  # my first comment
        echo 'Use arguments as l or s or root';;
    'root')
        ls -la /;;
    'top')
        echo 'Push letter q on your keyboard'
        top > top.log;;
    'del_top')
        rm top.log;;
    *)
        echo 'Hello folks. Use --help';
esac
