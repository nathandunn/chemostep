#!/bin/bash

# $Id: $

#!/bin/sh

# (C) 2006 by Nathan Dunn, <ndunn@mac.com>

#./distributionapp -network ~/svn/mypapers/adaptivebehavior/analysis/ttxdistributions/noablate_2005_02_24_b29_1.xml  -time 3600 -runs 200 -space 0 -height 14 -width 10 -target 5 -lowv -0.5 -highv 1.5 -plot
./distributionapp -network $1  -time 3600 -runs 20 -space 0 -height 10 -width 14 -target 7 -lowv -0.9 -highv 1.9 -startx 7 -opts -plot -loop 


