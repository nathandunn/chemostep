// -*- C++ -*-
//
//
//
// PASSED TESTS:
// addGuiOption
// addGuiCommand
// clearGui
// setGuiOption
// 1 - addGuiType // should add a sleu of options/commands in a batch
// (need to add signals/clots connected from TextField (changed) and CommandButton (pushed) to commands
// 6 - doCommandButton
//QtFlatRenderer:
// 3 - getOptionFromGui (should be triggered during updateOptionsFromGui)
// 4 - optionSetInGui
// 2 - loadAppToMap
// 5 - renderAppToGui
// transmitXmlOptions
// transmitXmlCommand
// transmitXml
// updateOptionsFromGui
//
// 


#include "rendertest.hpp" 
#include <AppInterface.hpp>
#include <Option.hpp>
#include <Command.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <testclasses>
#include <Renderer.hpp>
#include <QtFlatRenderer.h>
#include <TiAppParser.hpp>

#include <iostream>
#include <string>
using namespace std ; 

#include <qapplication.h>

rendertest::rendertest() 
{
  app = NULL ; 
  renderer = NULL ; 
}

Type* rendertest::generateType()   
{
    theType = NULL ; 
    theType = new Type("interfaceA",NULL,"typeA")  ; 
    Option *opA = new Option("optionA","STRING","dog",true) ; 
    theType->addOptionToMap(opA) ; 
    Option *opB = new Option("optionB","STRING","cat",true) ; 
    theType->addOptionToMap(opB) ; 
    Option *opC = new Option("optionC","STRING","monkey",true) ; 
    theType->addOptionToMap(opC) ; 
    Option *opD = new Option("optionD","STRING","shark",true) ; 
    theType->addOptionToMap(opD) ; 
    Option *opE = new Option("optionE","STRING","mackerel",true) ; 
    theType->addOptionToMap(opE) ; 
    Command *commA = new Command("donkey","BOOL","3") ; 
    theType->addCommandToMap(commA) ; 
    Command *commB = new Command("stormy","STRING","5") ; 
    theType->addCommandToMap(commB) ; 

    return theType ; 
}



string rendertest::transmitXml(string xmlString)   
{
    cout << "transimiting xml:  " << xmlString << endl ; 
    return "yeah" ; 
}

void rendertest::setRenderer(Renderer* newRenderer)   
{
    renderer = newRenderer ; 
}

void rendertest::setApp(AppInterface* newApp)   
{
    app = newApp ; 
}


bool rendertest::runTest(int argc,char **argv)   
{


    return true ; 
}



string getAppString(){

    // 1. create app 
    //
    // 2. convert to string
    //
    AppInterface* test = new TestAnnealer("APP",TestAnnealer::TEST_ANNEALER,NULL) ; 
    AppInterfaceXmlEngine* xmlRenderer = new TinyAppInterfaceXmlEngine(test) ; 

    test->createLocalMaps() ; 
    cout << "A" << endl ; 
    test->setType(TestAnnealer::ANNEALER_OBJECT+"/"+TestAnnealer::TEST_NEURAL_NETWORK) ;
    cout << "B" << endl ; 
    test->setType(TestAnnealer::FILE_READER+"/"+TestNN::FILE_FEEDER) ;
    cout << "C" << endl ; 
    test->createMaps(TestAnnealer::ANNEALER_OBJECT) ; 
    cout << "C1" << endl ; 
    test->setType(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER+"/"+TestNN::RANDOM_FEEDER) ; 
    cout << "D" << endl ; 
    test->setType(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER+"/"+TestNN::FILE_FEEDER) ; 
    cout << "E" << endl ; 
    test->createMaps(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::TARGET_FEEDER) ; 
    cout << "F" << endl ; 
    test->createMaps(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER) ; 
    cout << "G" << endl ; 
    test->setOption(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER,TestRandomFeeder::RANDOM_CENTER,"0.1111") ; 
    cout << "H" << endl ; 
    test->setOption(TestAnnealer::ANNEALER_OBJECT,TestNN::TEMPERATURE_DATA,"0.1234") ; 
    cout << "I" << endl ; 
    cout << test->setOption("",TestAnnealer::HIGH_TEMP,"75") << endl ; 
    cout << "I1" << endl ; 
    cout << test->setOption("",TestAnnealer::LOW_TEMP,"0.2") << endl ; 
    cout << "I2" << endl ; 
    cout << test->getOption(TestAnnealer::ANNEALER_OBJECT+"."+TestNN::STIM_FEEDER,TestRandomFeeder::RANDOM_CENTER) << endl ; 
    cout << "J" << endl ; 

    return xmlRenderer->toXml(test) ; 
}


int main(int argc,char **argv){

    cout << "render test BEGIN" << endl ; 


    rendertest *tester = new rendertest() ; 
    QApplication qapp( argc, argv ) ;
    QtFlatRenderer *testRenderer = new QtFlatRenderer(tester,new TiAppParser()) ; 


    // add options
    // add commands
//    testRenderer->addGuiType("pathToType",tester->generateType()) ; 

    string appString = getAppString() ; 
    cout << "appString: " << appString << endl ; 
	testRenderer->loadAppToMap(appString) ; 
	testRenderer->renderAppToGui() ; 
    string optionName = "APP.ANNEALER_OBJECT/TEST_NEURAL_NETWORK" ; 
    testRenderer->setGuiOption(optionName,new Option("NETWORK_DATA","STRING","change post show",true)) ; 
    testRenderer->setMinimumSize(600,300) ; 
    testRenderer->show() ; 

	qapp.setMainWidget(testRenderer) ; 
    qapp.connect( &qapp, SIGNAL( lastWindowClosed() ), &qapp, SLOT( quit() ) );



    cout << "render test END" << endl ; 

    return qapp.exec();

}


