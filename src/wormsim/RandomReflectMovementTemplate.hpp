#ifndef RANDOMREFLECTMOVEMENTTEMPLATE_HPP_
#  define RANDOMREFLECTMOVEMENTTEMPLATE_HPP_

#include "MovementModelTemplate.hpp"

/** Description:  Class RandomReflectMovementTemplate where a worm is reflected at its incoming angle.
 *
 */
template <class T> 
class RandomReflectMovementTemplate : public MovementModelTemplate<T> {

public:
    RandomReflectMovementTemplate( float newVelocity) ;
    virtual void move(T* aWorm)   ;
    virtual void toXML(ostream *s)  ; 

} ;


#include "RandomReflectMovementTemplate.cpp"

#endif /* ifndef RANDOMREFLECTMOVEMENTTEMPLATE_H */

