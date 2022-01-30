#ifndef PAPER_H_INCLUDED
#define PAPER_H_INCLUDED

#include <map>
#include <string>
using namespace std;

/**
* Represents a specific product that can be sold
*/
class Product {
 public:
  /**
  * Constructor
  * @param[in] name String that represents the Product
  * @param[in] pWeight The weight of the Product
  */
  Product(string name, double pWeight);

  /**
  * Destructor
  */
  virtual ~Product() {}

  /**
  * Gets the weight of the product
  * @return double representing the weight of the Product in kg
  */
  double getWeight();

  /**
  * Gets the name of the Product
  * @return The name of the Product as a string
  */
  string getName();

 private:
  string id;
  /**< in Kg */
  double weight;
};

#endif // PAPER_H_INCLUDED
