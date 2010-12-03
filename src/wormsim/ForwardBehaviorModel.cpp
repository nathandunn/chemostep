
#include "ForwardBehaviorModel.hpp"


int ForwardBehaviorModel::getBehavior(){
	currentBehavior = FORWARD ; 
	return currentBehavior ; 
}

ForwardBehaviorModel::ForwardBehaviorModel(){
   currentBehavior = FORWARD ;  
}

char* ForwardBehaviorModel::getBehaviorModel(){
    return "FORWARD" ; 
}

void ForwardBehaviorModel::toXML(ostream *s) 
{
  addSpacer(s) ; 
  *s << "\t<behaviormodel type=\"forwardbehaviormodel\">" << endl ;
  addSpacer(s) ; 
  *s << "\t</behaviormodel>" << endl ;

}



