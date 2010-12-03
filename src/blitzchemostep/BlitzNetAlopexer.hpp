#ifndef BLITZNETALOPEXER_HPP_
#  define BLITZNNETALOPEXER_HPP_

#include <fstream>
using std::ofstream ;

#include "NetAlopexer.hpp" 
#include "blitzdefs.hpp" 

class AnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 


class BlitzNetAlopexer : public NetAlopexer {

public:
    BlitzNetAlopexer() ; 
    virtual AnnealingTarget* alopex(ostream *toXML,string netOutFile) ; 
    virtual void setAlopexTarget(AnnealingTarget* alopexTarget) ; 
		void takeStats();
		void resetTimers();
		void initStats();
		void printStep(ostream *stm);
		void dumpXmlStartStep(ostream* s);
		void dumpXmlStopStep(ostream* s);
		void printFinal(ostream* s);
        void dumpNet(string networkFile) ; 
		void dumpXmlAlopexStart(ostream* s);
		void dumpXmlAlopexStop(ostream* s);
		void setOutputPeriod (int period);
		
protected:
			
#ifdef DOMPI
    virtual BlitzNet* syncNet(BlitzNet* origNet) ; 
    Matrix* bcastMatrix ; 
    Matrix* hereWeights ; 
    Vector* hereBias; 
    Vector* hereTau; 
    Vector* hereGain ; 
    Vector* hereInitNeurons; 
    Vector* hereVmem ; 
#endif
			
private:
    BlitzNet *blitzNet; 
    BlitzXmlNetRenderer* renderer; 
		int outputPeriod;
		BlitzNet* bestNet; 
		
		//error
		double bestError, bestSdev, bestCount  ;   
    double currentError, currentSdev, currentCount  ; 
		
		
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
		double deltaError ;
    double initialError ;
		
		
} ;

#endif /* ifndef BLITZNETALOPEXER_H */


