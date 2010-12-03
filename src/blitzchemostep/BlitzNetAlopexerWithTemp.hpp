#ifndef BLITZNETALOPEXERWITHTEMP_HPP_
#  define BLITZNNETALOPEXERWITHTEMP_HPP_

#include <fstream>
using std::ofstream ;

#include "NetAlopexer.hpp" 
#include "blitzdefs.hpp" 

class AnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 


class BlitzNetAlopexerWithTemp : public NetAlopexer {

public:
    BlitzNetAlopexerWithTemp() ; 
    virtual AnnealingTarget* alopex(ostream *toXML) ; 
    virtual void setAlopexTarget(AnnealingTarget* alopexTarget) ; 
		void takeStats();
		void resetTimers();
		void initStats();
		void printStep(ostream *stm);
		void dumpXmlStartStep(ostream* s);
		void dumpXmlStopStep(ostream* s);
		void printFinal(ostream* s);
		void dumpXmlAlopexStart(ostream* s);
		void dumpXmlAlopexStop(ostream* s);
		void setOutputPeriod (int period);
		
protected:
			
#ifdef DOMPI
    Matrix* bcastMatrix ; 
    Matrix* hereWeights ; 
    Vector* hereTau; 
    Vector* hereBias; 
    Vector* hereInitNeurons; 
    Vector* hereVmem ; 
#endif
			
private:
    BlitzNet *blitzNet; 
    BlitzXmlNetRenderer* renderer; 
		int outputPeriod;
		BlitzNet* bestNet; 
		
		//error
		double deltaError ;
		double bestError ; 
    double currentError ; 
    double initialError ;
		
		// clock stats
    clock_t initClock   ; 
    double deltaClock ; 
    time_t initTime ; 
    double deltaTime  ; 
    double wallTime ; 
    double clockTime ; 
    clock_t currentClock  ; 
    clock_t nextClock     ; 
    time_t currentTime  ; 
    time_t nextTime     ; 
		
		//other stats
		int iterCount ; 
		
		
} ;

#endif /* ifndef BLITZNETALOPEXERWITHTEMP_H */


