

#include <iostream>
using std::cout ; 
using std::endl ; 


#include <TestAnnealer.hpp>
#include <testclasses>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <AppInterface.hpp>


AppInterface *test1(){

    AppInterface* test = new TestAnnealer("APP",TestAnnealer::TEST_ANNEALER,NULL) ; 
    AppInterfaceXmlEngine* xmlRenderer = new TinyAppInterfaceXmlEngine(test) ; 

//    AppInterface* test = NULL ; 

    cout << "----" << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "aaaa" << endl ; 
    test->createLocalMaps() ; 
    cout << "bbbb" << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 

    cout << "cccc" << endl ; 
    cout << test->setType(TestAnnealer::ANNEALER_OBJECT+"/"+TestAnnealer::TEST_NEURAL_NETWORK) << endl ;
    cout << test->setType(TestAnnealer::FILE_READER+"/"+TestNN::FILE_FEEDER) << endl ;
    cout << "dddd" << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "eeee" << endl ; 
    AppInterface* annealerInterface = test->getLocalTypeForInterface(TestAnnealer::ANNEALER_OBJECT) ; 
    cout << "ffff" << endl ; 
//    cout << xmlRenderer->toXml(annealerInterface) << endl ; 
    cout << "gggg" << endl ; 
    annealerInterface->createLocalMaps() ; 
    cout << "hhhh" << endl ; 
//    cout << xmlRenderer->toXml(annealerInterface) << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "iiii" << endl ; 

//    // 
//    // need to get these two lines to work
//    // if it contains a dot, find a component named ANNEALER_OBJECT
//    // and pass the argument to the right of the dot to that component 
//    // returning the same
//    // 
    cout << test->setType(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"/"+TestNN::RANDOM_FEEDER) << endl ; 
    cout << "jjjj" << endl ;  
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "kkkk" << endl ; 
    cout << test->setType(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER+"/"+TestNN::FILE_FEEDER) << endl ; 
    cout << "llll" << endl ; 
    cout << test->createMaps(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER) ; 
    cout << test->createMaps(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER) ; 
    cout << "mmmm" << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "nnnn" << endl ; 
    cout << test->setOption(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER,TestRandomFeeder::RANDOM_CENTER,"0.7777") << endl ; 
    cout << test->setOption(TestAnnealer::ANNEALER_OBJECT,TestNN::TEMPERATURE_DATA,"0.1234") << endl ; 
    cout << test->setLocalOption(TestAnnealer::HIGH_TEMP,"77") << endl ; 
    cout << test->setLocalOption(TestAnnealer::LOW_TEMP,"0.2") << endl ; 
    cout << "oooo" << endl ;
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "pppp" << endl ;
    cout << test->getOption(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER,TestRandomFeeder::RANDOM_CENTER) << endl ; 
    cout << "qqqq" << endl ;
    cout << test->doLocalCommand(TestAnnealer::START_ANNEALER) << endl ; 
    cout << "rrrr" << endl ;
    cout << test->doCommand(TestAnnealer::ANNEALER_OBJECT,TestNN::PERTURB_NET) << endl ; 
    cout << "ssss" << endl ;
    cout << test->doCommand(TestAnnealer::ANNEALER_OBJECT,new Command(TestNN::PERTURB_NET)) << endl ; 
    cout << "tttt" << endl ;
    cout << test->doCommand(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER,TestFileFeeder::GET_NEXT_POINT) << endl ; 
    cout << "uuuu" << endl ;
    cout << xmlRenderer->doXmlCommand("<commandbatch><command id=\"12\"><doCommand name=\"START_ANNEALER\" type=\"BOOL\"/></command></commandbatch>",test) << endl ; 
    cout << "vvvv" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"13\"><doCommand path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER+"\" name=\"GET_NEXT_POINT\"  /></command>",test) << endl ; 
    cout << "wwww" << endl ;
//    cout << xmlRenderer->doXmlCommand("<command id=\"14\"><doCommand path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER+"\" name=\"GET_POINT_AT\" > <argument name=\"theName\" value=\"444.888\" type=\"OPT_DOUBLE\" /> </doCommand></command>") << endl ; 
//    cout << "xxxx" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"15\"><setOption name=\"HIGH_TEMP\" value=\"98.6\" /></command>",test) << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "xxxx" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"16\"><getOption name=\"HIGH_TEMP\" /></command>",test) << endl ; 
    cout << "yyyy" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"18\"><setOption path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\" name=\""+TestRandomFeeder::RANDOM_CENTER+"\" value=\"0.4444\" /></command>") << endl ; 
    cout << "zzzz" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"19\"><getOption path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\" name=\""+TestRandomFeeder::RANDOM_CENTER+"\"  /></command>") << endl ; 
    cout << "AAAAAAAA" << endl ;
//    cout << "FINISHED UP TO HERE" << endl ; 
//    cout << xmlRenderer->doXmlCommand("<command id=\"19\"><disposeMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\"  /></command>") << endl ;  // this one also works
    cout << xmlRenderer->doXmlCommand("<command id=\"20\"><disposeMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"\"  /></command>") << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "BBBBBBBB" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"21\"><setType path=\""+TestAnnealer::ANNEALER_OBJECT+"/"+TestAnnealer::TEST_NEURAL_NETWORK+"\"  /></command>") << endl ; 
    cout << xmlRenderer->doXmlCommand("<command id=\"22\"><createMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"\"  /></command>") << endl ; 
//    cout << test->setType(TestAnnealer::ANNEALER_OBJECT+"/"+TestAnnealer::TEST_NEURAL_NETWORK) << endl ;
    cout << "CCCCCCCC" << endl ;
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << xmlRenderer->doXmlCommand("<command id=\"23\"><createMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\"  /></command>") << endl ; 
    cout << xmlRenderer->doXmlCommand("<command id=\"24\"><createMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER+"\"  /></command>") << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "DDDDDDD" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"25\"><setType path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"/"+TestNN::FILE_FEEDER+"\"  /></command>") << endl ; 
//    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "EEEEEE" << endl ;
    cout << xmlRenderer->doXmlCommand("<command id=\"26\"><createMaps path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\" /></command>") << endl ; 
    cout << xmlRenderer->doXmlCommand("<command id=\"27\"><setOption path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\" name=\""+TestFileFeeder::FILE_FILENAME+"\" value=\"missingfile\" /></command>") << endl ; 
    cout << xmlRenderer->doXmlCommand("<command id=\"28\"><doCommand path=\""+TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"\" name=\"GET_NEXT_POINT\"  /></command>",test) << endl ; 
    cout << "FFFFFF" << endl ;
    cout << xmlRenderer->toXml(test) << endl ; 
    cout << "GGGGGG" << endl ;

    return  test ; 
}



AppInterface *app ; 

int main( int argc, char ** argv )
{
    app = test1() ; 
    
    return NULL ; 
}



