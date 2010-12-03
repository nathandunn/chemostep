#ifndef REFLECTMOVEMENTTEMPLATE_HPP_
#  define REFLECTMOVEMENTTEMPLATE_HPP_

#include "MovementModelTemplate.hpp"

/** Description:  Class ReflectMovementTemplate where a worm is reflected at its incoming angle.
 *
 */
template <class T> 
class ReflectMovementTemplate : public MovementModelTemplate<T> {

public:
    ReflectMovementTemplate( float newVelocity) ;
    virtual void move(T* aWorm)   ;
    virtual void toXML(ostream *s)  ; 

} ;


#include "ReflectMovementTemplate.cpp"

#endif /* ifndef REFLECTMOVEMENTTEMPLATE_H */

