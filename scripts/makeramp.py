#!/sw/bin/python


import sys ; 

numArgs = int(len(sys.argv))
if numArgs != 4:
	print "usage:  start stop increment" ;
	sys.exit() ; 



start =  float(sys.argv[1]) 
stop = float(sys.argv[2]  )
increment = float(sys.argv[3])
counter = float(start)

#print "start["+str(start)+"] stop["+str(stop)+"] increment["+str(increment)+"]" ; 
#print "numargs: " +  str(numArgs) ;
    
if increment > 0:
    while  counter < stop: 
         print str(counter)  ; 
         counter = counter + increment ; 
else:
    while  counter > stop: 
         print str(counter)  ; 
         counter = counter + increment ; 



#for(  counter = start ; counter < stop ; counter+= icrement){
#
# print counter +"\n" ; 
#}



