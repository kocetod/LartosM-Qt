#!/bin/bash
cd /home/pi/LartosMG
rm MakeFile
rm LartosQT
rm .qmake.stash

qmake-qt5 ../LartosM-Qt/LartosQT.pro
make
