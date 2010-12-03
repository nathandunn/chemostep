#ifndef LABELER_HPP_
#  define LABELER_HPP_

class Label ; 
class DataFilter ; 
class LabelSet ; 



class LabelIdentifier {

public:
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter)=0 ; 
    virtual double calculateError(Label* newLabel,DataFilter* newDataFilter)=0 ; 


} ;

#endif /* ifndef LABELER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


