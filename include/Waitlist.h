#ifndef WAITLIST_H_INCLUDED
#define WAITLIST_H_INCLUDED

#include <list>
using namespace std;

class Order;

/**
* Represents a waitlist for incompleted orders
*/
class Waitlist {
 public:
  /**
  * Checks all the orders in the Waitlist if they can be completed
  */
  void checkAll();

  /**
  * Adds an order to the Waitlist
  * @param[in] order Pointer to the Order to be added
  * @throws invalid_parameter_error if order is null.
  */
  void addOrder(Order* order);

  /**
  * Removes an order from the Waitlist
  * @param[in] order Pointer to the Order to be removed
  * @throws invalid_parameter_error if order is null.
  */
  void removeOrder(Order* order);

  /**
  * Gets the size of the Waitlist
  * @return The total number of Orders in the Waitlist
  */
  int size();

 private:
  list<Order*> pendingOrders;
};

#endif // WAITLIST_H_INCLUDED
