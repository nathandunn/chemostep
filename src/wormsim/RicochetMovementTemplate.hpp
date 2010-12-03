#ifndef RICOCHETMOVEMENTTEMPLATE_HPP_
#  define RICOCHETMOVEMENTTEMPLATE_HPP_

#include "MovementModelTemplate.hpp"

/** Description:  Class RicochetMovementTemplate where a worm is reflected at its incoming angle.
 *
 */
template <class T> 
class RicochetMovementTemplate : public MovementModelTemplate<T> {

public:
    RicochetMovementTemplate( float newVelocity) ;
    virtual void move(T* aWorm)   ;
    virtual void toXML(ostream *s)  ; 

} ;


#include "RicochetMovementTemplate.cpp"

#endif /* ifndef RICOCHETMOVEMENTTEMPLATE_H */

