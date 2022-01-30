#ifndef WAREHOUSE_H_INCLUDED
#define WAREHOUSE_H_INCLUDED

#include "Product.h"
#include "Waitlist.h"
#include "Exceptions.h"
#include <map>
#include <utility>

using namespace std;

/**
* Contains all the inventory for a company
*/
class Warehouse {
 public:
  /**
  * Constructor
  * @param[in] w Pointer to the waitlist
  */
  Warehouse(Waitlist* w);

  /**
  * Changes the quantity of an item to the Warehouse
  * @param[in] type Pointer to the Product to change
  * @param[in] quantity Amount of the Product to ajust
  * @throws invalid_parameter_error if product is null.
  */
  bool changeQuantity(Product* type, int quantity);

  /**
  * Checks how much of a product is in the Warehouse
  * @param[in] type Pointer to the product to check
  * @return The total amount of that Product in the Warehouse
  * @throws invalid_parameter_error if product is null.
  */
  int checkQuantity(Product* type);

 private:
  Waitlist* pending;
  map<Product*, int> inventory;
};

#endif // WAREHOUSE_H_INCLUDED
