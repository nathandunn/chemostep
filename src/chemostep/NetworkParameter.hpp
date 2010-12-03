#ifndef NETWORKPARAMETER_HPP_
#  define NETWORKPARAMETER_HPP_

class NetworkParameter {

public:
	NetworkParameter(string description,double value) : 
		mDescription(description) ,
		mValue(value) 
	{
		
	} 
	string getDescription() {
		return(mDescription);
	}
	void setDescription(string _mDescription) {
		mDescription = _mDescription;
		return;
	}
	double getValue() {
		return(mValue);
	}
	void setValue(double _mValue) {
		mValue = _mValue;
		return;
	}




protected:
	string mDescription ; 
	double mValue ; 

} ;

#endif /* ifndef NETWORKPARAMETER_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


