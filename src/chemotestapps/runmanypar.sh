#!/bin/bash

# $Id: runmanypar.sh,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#!/bin/sh
# FILE: "/home/ndunn/cvs/auto3TWOINPUTSTEP/src/chemotestapps/runmanypar.sh"
# LAST MODIFICATION: "Tue, 23 Dec 2003 08:56:39 -0800 (ndunn)"
# (C) 2003 by Nathan Dunn, <ndunn@mac.com>
# $Id: runmanypar.sh,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#mpirun -np 33 time ./kineticanneal > trace1.txt ; 
#mpirun -np 33 time ./kineticanneal > trace2.txt ; 
#mpirun -np 33 time ./kineticanneal > trace3.txt ; 
#mpirun -np 33 time ./kineticanneal > trace4.txt ; 
#mpirun -np 33 time ./kineticanneal > trace5.txt ; 


mpirun -np 11 time ./kineticanneal > trace1.txt ; 
mpirun -np 11 time ./kineticanneal > trace2.txt ; 
mpirun -np 11 time ./kineticanneal > trace3.txt ; 
mpirun -np 11 time ./kineticanneal > trace4.txt ; 
mpirun -np 11 time ./kineticanneal > trace5.txt ; 




