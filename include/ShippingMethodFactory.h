#ifndef SHIPPINGMETHODFACTORY_H_INCLUDED
#define SHIPPINGMETHODFACTORY_H_INCLUDED

#include "ShippingMethod.h"

/**
* Implementation of a strategy pattern. Determines the appropriate
* shipping method for an orderbased on an input @parameter, in this case
* weight.
*/
class ShippingMethodFactory {
 public:
  /**
  * Returns a pointer to an appropriate shipping method strategy.
  * @param[in] weight used to determine correct shipping strategy
  * @return a pointer to a ShippingMethod
  */
  ShippingMethod* getShippingMethod(const double weight);
};

#endif // SHIPPINGMETHODFACTORY_H_INCLUDED
