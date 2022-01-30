#ifndef SHIPPINGMETHOD_H_INCLUDED
#define SHIPPINGMETHOD_H_INCLUDED

#include <string>
using namespace std;

/**
* Implementation of a strategy pattern. Determines the appropriate
* shipping method for an orderbased on an input @parameter, in this case
* weight.
*/
class ShippingMethod {
 public:
  /**
  *Virtual Decontructor
  */
  virtual ~ShippingMethod() {}

  /**
  * Returns the name of the shipping method for outputting
  * @return a string representing the shipping method
  */
  string name();

 protected:
  string shipName;
};

/**
* strategy for shipping by Air
*/
class Air : public ShippingMethod {
 public:
  /**
  * Default constructor, sets the shipName to "Air".
  */
  Air();
};

/**
* strategy for shipping by Truck
*/
class Truck : public ShippingMethod {
 public:
  /**
  * Default constructor, sets the shipName to "Truck".
  */
  Truck();
};

/**
* strategy for shipping by Train
*/
class Train : public ShippingMethod {
 public:
  /**
  * Default constructor, sets the shipName to "Train".
  */
  Train();
};

/**
* strategy for shipping by Ship
*/
class Ship : public ShippingMethod {
 public:
  /**
  * Default constructor, sets the shipName to "Ship".
  */
  Ship();
};

#endif // SHIPPINGMETHOD_H_INCLUDED
