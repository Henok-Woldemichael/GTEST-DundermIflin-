#include "Waitlist.h"
#include "Warehouse.h"
#include "Product.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

TEST(TestWarehouse, WarehouseConstruction) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Product* yam = new Product("Yam", 1.00);

  // returns what? can this be negative quantity?
  wh->changeQuantity(yam, 20);

  EXPECT_EQ(wh->checkQuantity(yam), 20);

  delete yam;
  delete wh;
  delete wl;
}

TEST(TestWarehouse, ChangeValidProductQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Product* yam = new Product("Yam", 1.00);

  // returns what? can this be negative quantity?
  wh->changeQuantity(yam, 20);

  EXPECT_EQ(wh->checkQuantity(yam), 20);

  delete yam;
  delete wh;
  delete wl;
}

TEST(TestWarehouse, ChangeInvalidProductQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  // returns what? can this be negative quantity?
  EXPECT_THROW(wh->changeQuantity(NULL, 20), invalid_parameter_error);

  delete wh;
  delete wl;
}

TEST(TestWarehouse, CheckExistingQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Product* yam = new Product("Yam", 1.00);

  // returns what? can this be negative quantity?
  wh->changeQuantity(yam, 20);

  EXPECT_EQ(wh->checkQuantity(yam), 20);

  delete yam;
  delete wh;
  delete wl;
}

TEST(TestWarehouse, CheckNonExistingQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Product* yam = new Product("Yam", 1.00);

  EXPECT_EQ(wh->checkQuantity(yam), 0);

  delete yam;
  delete wh;
  delete wl;
}
