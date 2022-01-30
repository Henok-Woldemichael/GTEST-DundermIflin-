#ifndef ORDERSTATE_H_INCLUDED
#define ORDERSTATE_H_INCLUDED

class Order;

/**
* Implementation of a state pattern. OrderState is an abstract base
* class for the other states. They determine the behaviour for functions
* within the Order Class. The functions are view, submit, and cancel. Each
* will have different behaviour if the state has been set differently.
*/

/**
* \class OrderState OrderState.h "OrderState.h"
*/
class OrderState {
 public:
  /**
  *
  * Destructor.
  */
  virtual ~OrderState() {}
  /**
  * virtual function for view.
  */
  virtual void view(Order* in) = 0;
  /**
  * virtual function for submit.
  */
  virtual bool submit(Order* in) = 0;
  /**
  * virtual function for cancel.
  */
  virtual void cancel(Order* in) = 0;
};

/**
* State of an order that is not pending or completed
*/

/**
* \class InCartState OrderState.h "OrderState.h"
*/
class InCartState : public OrderState {
 public:
  /**
  * Outputs the current contents of the order and the status.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void view(Order* in);

  /**
  * Attempts to submit the order, if it is successful returns true.
  * If one or more item are not in stock, the order is sent to the waitlist.
  * If all items are in stock, the items are removed from the warehouse.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  * @return true if the order is succesfully submitted, false if the order is
  * pending.
  */
  bool submit(Order* in);

  /**
  * Clears the contents of the order.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void cancel(Order* in);
};

/**
*
* State of an order that does not have the required inventory to be
* submitted yet.
*
*/

/**
* \class PendingState OrderState.h "OrderState.h"
*/
class PendingState : public OrderState {
 public:
  /**
  * Outputs the current contents of the order and the status.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void view(Order* in);

  /**
  * Checks the warehouse to see if all items on the order are in stock.
  * If they are it removes the items from the warehouse.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  * @return true if the order is succesfully submitted, false if the order
  * remains pending.
  */
  bool submit(Order* in);

  /**
  * Clears the contents of the order and removes the order from the
  * waitlist.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void cancel(Order* in);
};

/**
*
* State of an order that has been completed and shipped.
*
*/

/**
* \class CompleteState OrderState.h "OrderState.h"
*/
class CompleteState : public OrderState {
 public:
  /**
  * Outputs the current contents of the order and the status.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void view(Order* in);

  /**
  * Outputs an error message since this order is already submitted.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  * @return always returns true, because the submit has already been succesful
  */
  bool submit(Order* in);

  /**
  * Outputs an error message since this order is already submitted.
  * @param[in] in Pointer to the order to call the appropriate functions on.
  */
  void cancel(Order* in);
};

#endif // ORDERSTATE_H_INCLUDED
