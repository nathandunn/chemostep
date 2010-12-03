## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
#  
#  Separated into the base components, and the clients.
#
#  




SUBDIRS = src 


	%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@


