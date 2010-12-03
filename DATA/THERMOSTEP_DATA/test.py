#!/usr/bin/env python

# (C) 2005 by Nathan Dunn, <ndunn@mac.com>

import sys

startPoint = int(sys.argv[1]) ; 
numPoints = int(sys.argv[2]) ; 
mult = float(sys.argv[3]) ; 
shift = float(sys.argv[4]) ; 


for i in range(startPoint,numPoints):
	print i*mult + shift ;  


