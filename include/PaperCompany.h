#ifndef PAPERCOMPANY_H_INCLUDED
#define PAPERCOMPANY_H_INCLUDED

#include "Order.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

/**
* Represents a Paper Company and its components
*/
class PaperCompany {
 public:
  /**
  * Default constructor
  */
  PaperCompany();
  /**
  * Destructor
  */
  virtual ~PaperCompany();

  /**
  * Adds a new product type to the company
  * @param[in] name The unique name of the new Product
  * @param[in] weight The weight of the Product in kg
  * @return False if a Product with that name already exists, true otherwise
  */
  bool addProduct(string name, double weight);

  /**
  * Gets a pointer to the product with a specific name
  * @param[in] name The unique name of the product to find
  * @return Pointer to the product with the given name. If no Product has the
  * given name, returns nullptr.
  */
  Product* findProduct(string name);

  /**
  * Displays each Product's name and their quantities in the Warehouse.
  */
  void listInventory();

  /**
  * Adds or Removes an amount of a Product.
  * @param[in] name The unique name of the Product to be adjusted
  * @param[in] quantity Amount to add or remove from the Warehouse. Positive to
  * add, negative to remove.
  * @return True if successfull. If false, Product may not exist or has too
  * low a quantity to remove that many items.
  */
  bool adjustInventory(string name, int quantity);

  /**
  * Displays recipts for all created orders.
  */
  void viewOrders();

  /**
  * Creates a new Order.
  * @return Pointer to the created order.
  */
  Order* createOrder();

  /**
  * Adds an Order to the list of all orders
  * @param[in] input Pointer to the Order to be added
  * @throws invalid_parameter_error if order is null.
  */
  void addToOrders(Order* input);

 private:
  map<string, Product*> products;
  Warehouse* wh;
  Waitlist* wl;
  vector<Order*> orders;
};

#endif // PAPERCOMPANY_H_INCLUDED
