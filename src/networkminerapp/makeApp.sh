#!/bin/bash

# $Id: $

#!/bin/sh
rm -rf NetMiner
mkdir  -p NetMiner/NetMiner.app/Contents/MacOS
cp -f autonetminer NetMiner/NetMiner.app/Contents/MacOS/NetMiner
mkdir  -p NetMiner/libs
cp $QTDIR/lib/libqt-mt.3.dylib NetMiner/libs
#cp -rf ../../DATA/NETDATA NetMiner
mkdir NetMiner/scripts
cp postflight NetMiner/scripts

# (C) 2006 by Nathan Dunn, <ndunn@mac.com>


