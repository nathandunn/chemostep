
#ifndef _Dimension_h
#define _Dimension_h

class Dimension{

	public:
		Dimension() ; 
		Dimension(double x, double y) ; 
		void setDimension(double newX, double newY){
			xDim = newX ; 
			yDim = newY ; 
		}; 
		double getX(){ return xDim ; } ; 
		double getY(){ return yDim ; } ; 

	private:
		double xDim ;
		double yDim ;
} ;

#endif 
