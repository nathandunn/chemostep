// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--updateminer--1.3.4--base-0/src/networkminerapp/SearchForm2.cpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 18:22:07 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchForm2.cpp,v 1.31 2003/07/21 03:19:29 ndunn Exp $

#include "SearchForm2.hpp"


SearchForm2::SearchForm2(QWidget *newParent, const char *name,SearchDriver *newDriver)  {
    driver = newDriver ; 
    parent = newParent; 
    initGui() ; 
    loadDefaults() ; 
}

void SearchForm2::addMessageGUI(string message) 
{
    QString messageString = QString((char *) &message) ; 
    QMessageBox::warning(this,QString("SearchForm2"), messageString, 0,1) ;
}


void SearchForm2::stopSearchNotify(){
    cout << "SearchForm2:: stopping the search here" << endl ;
}

void SearchForm2::loadDefaults(){
    ifstream defaultFileStream(DEFAULT_FILE.c_str()) ; 

     if(defaultFileStream==0){
        cerr << "unable to open file: " << DEFAULT_FILE << endl ; 
        return ; 
     }else{
        cout << "reading connections: "<< DEFAULT_FILE << endl ; 
     }

  const int INPUT_BUFF = 200 ; 
  char input ;
  int charCount = 0 ; 
  char *buffer = new char[INPUT_BUFF] ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      if(buffer!=NULL && buffer!=""){
         startField->setText(buffer) ; 
      }
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      stopField->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      neuronFileField->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      connectionFileField->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      outputFileField->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      depthSpinBox->setValue(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      cThreshSpinBox->setValue(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      eThreshSpinBox->setValue(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      del1LineEdit->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      del2LineEdit->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      padLineEdit->setText(buffer) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      doPadBox->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      noStatsBox->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      intOutputBox->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      showConnectionBox->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      stopAtTerminusBox->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      edgeLineEdit->setText(buffer ) ;
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      edgeDoTxt->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      edgeDoDot->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      doSelfConnections->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      doRecurrentConnections->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 
      edgeDoLabel->setChecked(atoi(buffer)) ; 
      defaultFileStream.getline(buffer,INPUT_BUFF,'\n') ; 



//      defaultFileStream <<  startField->text() << endl ; 
//      defaultFileStream <<  stopField->text() << endl ; 
//      defaultFileStream <<  neuronFileField->text() << endl ; 
//      defaultFileStream <<  connectionFileField->text() << endl ; 
//      defaultFileStream <<  outputFileField->text() << endl ; 
//      defaultFileStream <<  atoi(depthSpinBox->text())  << endl ; 
//      defaultFileStream <<  atoi(cThreshSpinBox->text())  << endl ; 
//      defaultFileStream <<  atoi(eThreshSpinBox->text())  << endl ; 
//      defaultFileStream <<  del1LineEdit->text() << endl ; 
//      defaultFileStream <<  del2LineEdit->text() << endl ; 
//      defaultFileStream <<  padLineEdit->text() << endl ; 
//      defaultFileStream <<  doPadBox->isChecked() << endl ; 
//      defaultFileStream <<  noStatsBox->isChecked() << endl ; 
//      defaultFileStream <<  intOutputBox->isChecked() << endl ; 
//      defaultFileStream <<  showConnectionBox->isChecked() << endl ; 
//      defaultFileStream <<  stopAtTerminusBox->isChecked() << endl ; 
//      defaultFileStream <<  edgeLineEdit->text() << endl ; 
//      defaultFileStream <<  edgeDoTxt->isChecked() << endl ; 
//      defaultFileStream <<  edgeDoDot->isChecked() << endl ; 
//      defaultFileStream <<  nodeLineEdit->text() << endl ; 
//      defaultFileStream <<  nodeDoTxt->isChecked() << endl ; 
//      defaultFileStream <<  nodeDoDot->isChecked() << endl ; 
//      defaultFileStream <<  edgeDoLabel->isChecked() << endl ; 
    
    
    defaultFileStream.close() ; 
}


int SearchForm2::saveDefaults(){
    ofstream defaultFileStream(DEFAULT_FILE.c_str()) ; 

      defaultFileStream <<  (startField->text()).upper().remove(' ') << endl ; 
      defaultFileStream <<  (stopField->text()).upper().remove(' ') << endl ; 
      defaultFileStream <<  neuronFileField->text() << endl ; 
      defaultFileStream <<  connectionFileField->text() << endl ; 
      defaultFileStream <<  outputFileField->text() << endl ; 
      defaultFileStream <<  atoi(depthSpinBox->text())  << endl ; 
      defaultFileStream <<  atoi(cThreshSpinBox->text())  << endl ; 
      defaultFileStream <<  atoi(eThreshSpinBox->text())  << endl ; 
      defaultFileStream <<  del1LineEdit->text() << endl ; 
      defaultFileStream <<  del2LineEdit->text() << endl ; 
      defaultFileStream <<  padLineEdit->text() << endl ; 
      defaultFileStream <<  doPadBox->isChecked() << endl ; 
      defaultFileStream <<  noStatsBox->isChecked() << endl ; 
      defaultFileStream <<  intOutputBox->isChecked() << endl ; 
      defaultFileStream <<  showConnectionBox->isChecked() << endl ; 
      defaultFileStream <<  stopAtTerminusBox->isChecked() << endl ; 
      defaultFileStream <<  edgeLineEdit->text() << endl ; 
      defaultFileStream <<  edgeDoTxt->isChecked() << endl ; 
      defaultFileStream <<  edgeDoDot->isChecked() << endl ; 
      defaultFileStream <<  doSelfConnections->isChecked() << endl ; 
      defaultFileStream <<  doRecurrentConnections->isChecked() << endl ; 
      defaultFileStream <<  edgeDoLabel->isChecked() << endl ; 
      defaultFileStream.close() ; 

      return true ;
}


int SearchForm2::checkInputs(){
      return true ; 
}



int SearchForm2::startSearchNotify(){

    if(checkInputs()==false){
		return false ; 
    }
    saveDefaults() ; 


    cout << "SearchForm2:: starting the search here" << endl ;
//#ifdef GCC_2

    driver->runSearch() ; 
//        (startField->text()).upper().remove(' '),
//        (stopField->text()).upper().remove(' '),
//        neuronFileField->text(),
//        connectionFileField->text(),
//        outputFileField->text(),
//        atoi(depthSpinBox->text()) ,
//        atoi(cThreshSpinBox->text()) ,
//        atoi(eThreshSpinBox->text()) ,
//        del1LineEdit->text(),
//        del2LineEdit->text(),
//        padLineEdit->text(),
//        doPadBox->isChecked(),
//        noStatsBox->isChecked(),
//        intOutputBox->isChecked(),
//        showConnectionBox->isChecked(),
//        stopAtTerminusBox->isChecked(),
//        edgeLineEdit->text(),
//        edgeDoTxt->isChecked(),
//        edgeDoDot->isChecked(),
//        doSelfConnections->isChecked(),
//        doRecurrentConnections->isChecked(),
//        edgeDoLabel->isChecked()
//        ) ;
//#else
//    driver->startSearch(
//        ((string) startField->text()).upper().remove(' '),
//        ((string) stopField->text()).upper().remove(' '),
//        (string) neuronFileField->text(),
//        (string) connectionFileField->text(),
//        (string) outputFileField->text(),
//        atoi(depthSpinBox->text()) ,
//        atoi(cThreshSpinBox->text()) ,
//        atoi(eThreshSpinBox->text()) ,
//        (string) del1LineEdit->text(),
//        (string) del2LineEdit->text(),
//        (string) padLineEdit->text(),
//        doPadBox->isChecked(),
//        noStatsBox->isChecked(),
//        intOutputBox->isChecked(),
//        showConnectionBox->isChecked(),
//        stopAtTerminusBox->isChecked(),
//        (string) edgeLineEdit->text(),
//        edgeDoTxt->isChecked(),
//        edgeDoDot->isChecked(),
//        doSelfConnections->isChecked(),
//        doRecurrentConnections->isChecked(),
//        edgeDoLabel->isChecked(),
//        ) ;
//#endif

        return true ; 
}


void SearchForm2::initGui() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this,5) ; 


    QVGroupBox *searchBox = new QVGroupBox("Search Parameters",this) ; 
    mainLayout->addWidget(searchBox) ; 
    QFrame *searchFrame = new QFrame(searchBox) ; 

    QVBoxLayout *searchLayout = new QVBoxLayout(searchFrame,5) ; 
    searchLayout->addWidget(searchFrame) ; 

    // add stuff to line 1
    QHBoxLayout *row1 = new QHBoxLayout(searchLayout,5) ; 
    connectionFileField  = new QLineEdit("Connection File", searchFrame) ; 
    row1->addWidget(connectionFileField,5,0) ; 
    chooseConnectionFileButton = new QPushButton("Choose Connection File", searchFrame, "Connection") ; 
    row1->addWidget(chooseConnectionFileButton,1,0) ; 



    // add stuff to line 2
    QHBoxLayout *row2 = new QHBoxLayout(searchLayout,5) ; 
    neuronFileField  = new QLineEdit("Neuron File",searchFrame) ; 
    row2->addWidget(neuronFileField,5,0) ; 
    chooseNeuronFileButton = new QPushButton("Choose Neuron File", searchFrame, "Neuron") ; 
    row2->addWidget(chooseNeuronFileButton,1,0) ; 


    // oops need to insert another line, searchFrame is cake
    QHBoxLayout *row2_1 = new QHBoxLayout(searchLayout,5) ; 
    startLabel = new QLabel("Inputs", searchFrame) ; 
    row2_1->addWidget(startLabel,1,0) ; 
    startField = new QLineEdit("ASE,AFD",searchFrame) ; 
    row2_1->addWidget(startField,5,0) ; 
    stopLabel = new QLabel("Outputs", searchFrame) ; 
    row2_1->addWidget(stopLabel,1,0) ; 
    stopField = new QLineEdit("AVA,AVB,PVC,AVD",searchFrame) ; 
    row2_1->addWidget(stopField,5,0) ; 


    // add stuff to line 2
    QHBoxLayout *row3 = new QHBoxLayout(searchLayout,5) ; 
    depthLabel = new QLabel("Depth",searchFrame) ; 
    row3->addWidget(depthLabel) ; 
    depthSpinBox = new QSpinBox(0,INT_MAX,1,searchFrame,"spin1") ; 
    row3->addWidget(depthSpinBox) ; 

    cThreshLabel = new QLabel("Chem Thresh",searchFrame) ; 
    row3->addWidget(cThreshLabel) ; 
    cThreshSpinBox= new QSpinBox(0,INT_MAX,1,searchFrame,"spin2") ; 
    row3->addWidget(cThreshSpinBox) ; 

    eThreshLabel = new QLabel("Gap Thresh",searchFrame) ; 
    row3->addWidget(eThreshLabel) ; 
    eThreshSpinBox = new QSpinBox(0,INT_MAX,1,searchFrame,"spin3") ; 
    row3->addWidget(eThreshSpinBox) ; 

//    stopAtTerminusBox= new QCheckBox("stopAtTerminus",gb) ; 
    stopAtTerminusBox= new QCheckBox("Stop at Terminus",searchFrame) ; 
    row3->addWidget(stopAtTerminusBox) ; 


    // add the output options
    
    // output file
    QVGroupBox *outputBox = new QVGroupBox("Output Options",this) ; 
    mainLayout->addWidget(outputBox) ; 
    QFrame *gb = new QFrame(outputBox) ; 

    QVBoxLayout *outputLayout = new QVBoxLayout(gb,5) ; 
    outputLayout->addWidget(gb) ; 

    QHBoxLayout *row4 = new QHBoxLayout(outputLayout,5) ; 
    outputFileField  = new QLineEdit("defaultOutput.txt", gb) ; 
    row4->addWidget(outputFileField) ; 
    chooseOutputFileButton = new QPushButton("Choose Output Destination", gb, "Output") ; 
    row4->addWidget(chooseOutputFileButton,0,2) ; 


    // stats
    QHBoxLayout *row5 = new QHBoxLayout(outputLayout,5) ; 
    noStatsBox = new QCheckBox("No Stats",gb) ; 
    row5->addWidget(noStatsBox) ; 
    
    intOutputBox = new QCheckBox("Int Output",gb) ; 
    row5->addWidget(intOutputBox) ; 
    showConnectionBox = new QCheckBox("Show Connections",gb) ; 
    row5->addWidget(showConnectionBox) ; 
    doPadBox = new QCheckBox("Add Padding",gb) ; 
    row5->addWidget(doPadBox) ; 


    QHBoxLayout *row6 = new QHBoxLayout(outputLayout,5) ; 
    padLabel  = new QLabel("Text Padding",gb) ; 
    row6->addWidget(padLabel) ; 
    padLineEdit  = new QLineEdit("#",gb) ; 
    row6->addWidget(padLineEdit) ; 
    del1Label  = new QLabel("Delimiter 1",gb) ; 
    row6->addWidget(del1Label) ; 
    del1LineEdit  = new QLineEdit(",",gb) ; 
    row6->addWidget(del1LineEdit) ; 


    del2Label  = new QLabel("Delimiter 2",gb) ; 
    row6->addWidget(del2Label) ; 
    del2LineEdit  = new QLineEdit("Tab",gb) ; 
    row6->addWidget(del2LineEdit) ; 

    
    // add the report stuff
    //
    QHGroupBox *reportBox = new QHGroupBox("Report options", this,"Control Buttons") ; 
    mainLayout->addWidget(reportBox) ; 

    // set up vertical frame
    QFrame *reportFrame = new QFrame(reportBox) ; 
    QVBoxLayout *reportLayout= new QVBoxLayout(reportFrame,5) ; 
    reportLayout->addWidget(reportFrame) ; 


    // add stuff for row 1
    QHBoxLayout *report_row1 = new QHBoxLayout(reportLayout,5) ; 
    edgeLineEdit = new QLineEdit("Edit Line Output",reportFrame) ; 
    report_row1->addWidget(edgeLineEdit,5,0) ; 
    edgeChooseOutputButton = new QPushButton("Set Report File",reportFrame) ; 
    report_row1->addWidget(edgeChooseOutputButton,5,0) ; 
    edgeDoDot = new QCheckBox(".dot",reportFrame) ; 
    report_row1->addWidget(edgeDoDot,5,0) ; 
    edgeDoTxt = new QCheckBox(".txt",reportFrame) ; 
    report_row1->addWidget(edgeDoTxt,5,0) ; 


    // add stuff for row 2
    QHBoxLayout *report_row2 = new QHBoxLayout(reportLayout,5) ; 
    edgeDoLabel = new QCheckBox("Label Connections",reportFrame) ; 
    report_row2->addWidget(edgeDoLabel,5,0) ; 
    doSelfConnections = new QCheckBox("Map Self-Connections",reportFrame) ; 
    report_row2->addWidget(doSelfConnections,5,0) ; 
    doRecurrentConnections = new QCheckBox("Map Recurrent Connections",reportFrame) ; 
    report_row2->addWidget(doRecurrentConnections,5,0) ; 


//    nodeLineEdit = new QLineEdit("edit neuron output",reportFrame) ; 
//    report_row2->addWidget(nodeLineEdit,5,0) ; 
//    nodeChooseOutputButton = new QPushButton("select neuron output",reportFrame) ; 
//    nodeChooseOutputButton->setFlat(true) ; 
//    report_row2->addWidget(nodeChooseOutputButton,5,0) ; 
//    nodeDoDot = new QCheckBox(".dot",reportFrame) ; 
//    report_row2->addWidget(nodeDoDot,5,0) ; 
//    nodeDoTxt = new QCheckBox(".txt",reportFrame) ; 
//    report_row2->addWidget(nodeDoTxt,5,0) ; 

    

    // add stuff for the control box

    QHGroupBox *buttonGroup = new QHGroupBox("control buttons", this,"controlButtons") ; 
    mainLayout->addWidget(buttonGroup) ; 
    QHBoxLayout *buttonBox = new QHBoxLayout(buttonGroup,10) ; 

    startButton = new QPushButton("Start", buttonGroup, "start") ; 
    startButton->setDefault(true) ; 
    startButton->setAccel(QKeySequence(Key_Return)) ; 
//    startButton->setAutoDefault(true) ; 
    buttonBox->addWidget(startButton,1,2) ; 
    stopButton = new QPushButton("Stop", buttonGroup, "stop") ; 
    buttonBox->addWidget(stopButton,1,2) ; 
    quitButton = new QPushButton("Quit", buttonGroup, "quit") ; 
    buttonBox->addWidget(quitButton,1,2) ; 


    // add a progress label, here


    // connect search boxes
    connect(padLineEdit,SIGNAL(selectionChanged()),this,SLOT(setDoPadBoxTrue())) ;  
    connect(chooseConnectionFileButton,SIGNAL(clicked()),this,SLOT(updateConnectionFile())) ;  
    connect(chooseNeuronFileButton,SIGNAL(clicked()),this,SLOT(updateNeuronFile())) ;  

    // connect output boxes
    connect(chooseOutputFileButton,SIGNAL(clicked()),this,SLOT(updateOutputFile())) ;  

    // connect report boxes
    connect(edgeChooseOutputButton,SIGNAL(clicked()),this,SLOT(updateEdgeReportFile())) ;  
//    connect(nodeChooseOutputButton,SIGNAL(clicked()),this,SLOT(updateNodeReportFile())) ;  

    // connect control box
  connect(startButton,SIGNAL(clicked()),  this, SLOT(startSearchNotify())) ; 
  connect(stopButton,SIGNAL(clicked()),  this, SLOT(stopSearchNotify())) ; 
  connect(quitButton,SIGNAL(clicked()),  qApp, SLOT(quit())) ; 


}

void SearchForm2::setDoPadBoxTrue(){
   doPadBox->setChecked(true) ; 
}


void SearchForm2::updateEdgeReportFile() {
    // set text-file
    QString filename = QFileDialog::getSaveFileName(edgeLineEdit->text(),"*") ; 
    if(filename!=NULL && filename!=""){
        cout << "updateEdgeReportFile: "<< filename << endl ; 
        edgeLineEdit->setText(filename) ;   
    }
}


//void SearchForm2::updateNodeReportFile() {
//    QString filename = QFileDialog::getSaveFileName(nodeLineEdit->text(),"*") ; 
//    if(filename!=NULL && filename!=""){
//        cout << "updateNodeReportFile: "<< filename << endl ; 
//        nodeLineEdit->setText(filename) ;   
//    }
//}



void SearchForm2::updateConnectionFile() {

    // open a text-file
    QString filename = "" ; 
    filename = QFileDialog::getOpenFileName("./DATA","*") ; 
    if(filename!=NULL && filename!=""){
        cout << "updateConnectionFile: "<< filename << endl ; 
        connectionFileField->setText(filename) ;   
    } 
}


void SearchForm2::updateNeuronFile() {

    // open a text-file
    QString filename = QFileDialog::getOpenFileName("./DATA","*") ; 
    if(filename!=NULL && filename!=""){
        cout << "updateNeuronFile: "<< filename << endl ; 
        neuronFileField->setText(filename) ;   
    }
}


void SearchForm2::updateOutputFile() {

    // set text-file
    QString filename = QFileDialog::getSaveFileName(outputFileField->text(),"*") ; 
    if(filename!=NULL && filename!=""){
        cout << "updateOutputFile: "<< filename << endl ; 
        outputFileField->setText(filename) ;   
    }
}


const string SearchForm2::DEFAULT_FILE = "defaults.txt" ;






