#!/bin/bash

# $Id: $

#!/bin/sh

# (C) 2006 by Nathan Dunn, <ndunn@mac.com>

./distributionapp -network /Users/nathandunn//svn/mypapers/adaptivebehavior/type1Net_2005_05_12_b29_2.xml   -time 3600 -runs 200 -space 0 -height 14 -width 10 -target 5 -lowv -0.5 -highv 1.5 -output type1noablation.txt #-plot
./distributionapp -network /Users/nathandunn//svn/mypapers/adaptivebehavior/type1Net_cryo0ablate_2005_05_12_b29_2.xml   -time 3600 -runs 200 -space 0 -height 14 -width 10 -target 5 -lowv -0.5 -highv 1.5 -output type1cryoablate.txt #-plot
./distributionapp -network /Users/nathandunn//svn/mypapers/adaptivebehavior/type1Net_thermo1ablate_2005_05_12_b29_2.xml   -time 3600 -runs 200 -space 0 -height 14 -width 10 -target 5 -lowv -0.5 -highv 1.5 -output type1thermoablate.txt #-plot
#./distributionapp -network /Users/nathandunn//svn/wormruns/2005_02/bestnet_2005_02_24_net4_b29_1.xml   -time 3600 -runs 1 -space 0 -height 10 -width 14 -target 7 -lowv -0.9 -highv 1.9 -output noablation.txt -plot

