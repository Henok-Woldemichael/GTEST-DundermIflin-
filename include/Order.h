#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include "OrderState.h"
#include "ShippingMethod.h"
#include "ShippingMethodFactory.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "Exceptions.h"
#include <map>
#include <string>
using namespace std;

/**
* Contains all informations related to an order. Allows manipulation of
* the contents of an order before it is shipped. Uses OrderState to determine
* behaviour for submit, cancel, and view, making use of a state pattern.
*/

class Order {
 public:
  /**
  * Class constructor, sets the status pointer to a new InCartState,
  * and the shipType to a null pointer.
  * @param[in] w Pointer to a Warehouse where all Products are stored
  * @param[in] wl Pointer to a Wailist for all orders which cannot be
  *  processed on submit
  * @throws invalid_parameter_error If either parameter is null.
  */
  Order(Warehouse* w, Waitlist* wl);

  /**
  * Class destructor
  */
  virtual ~Order();

  /**
  * Changes the quantity of an item in an order.
  * @param[in] item The type of item to update
  * @param[in] quantity Quantity to be changed, can be + or -
  * @return true if the item is found in the order, false otherwise
  * @throws invalid_parameter_error If either parameter is null.
  */
  bool editContents(Product* item, int quantity);

  /**
  * Attempts to submit the order by using the OrderState submit. If the
  * submit is successful the status is changed to CompleteState. If the submit
  * is unsuccessful the the status is changed to PendingState.
  * @return true if the status was sucessfully updated to CompleteState, false
  *  otherwise.
  */
  bool submit();

  /**
  * Returns true if there are no contents in the order.
  * @return true if there are no contents, false otherwise
  */
  bool isEmpty();

  /**
  * Attempts to cancel an order by using the OrderState submit.
  */
  void cancel();

  /**
  * Attempts to view an order, behaviour dependant on OrderState
  */
  void view();

  /**
  * Returns a copy of all contents and their quantities.
  * @return the contents of the order
  */
  map<Product* , int> &getContents();

  /**
  * Displays all contents of an order in a numbered list.
  */
  void displayContent();

  /**
  * returns a pointer to the order's warehouse. Used in OrderState.
  * @return a pointer to the Warehouse
  */
  Warehouse* getWH();

  /**
  * returns a pointer to the order's waitlist. Used in OrderState.
  * @return a pointer to the Waitlist
  */
  Waitlist* getWait();

  /**
  * returns a pointer to the order's state. Used in OrderState.
  * @return a pointer to the status of the order
  */
  OrderState* getStatus();

  /**
  * Returns a pointer to the order's shipping method. It is possible
  * this a null pointer will be returned.
  * @return a pointer to the ShippingMethod
  */
  ShippingMethod* getShipping();

  /**
  * returns a pointer to the order's warehouse. Used in OrderState.
  * @param[in] weight The type of item to update
  */
  void setShipping(double weight);

 private:
  map<Product* , int> contents;
  OrderState* status;
  ShippingMethod* shipType;
  Warehouse* from;
  Waitlist* in;
};

#endif // ORDER_H_INCLUDED
