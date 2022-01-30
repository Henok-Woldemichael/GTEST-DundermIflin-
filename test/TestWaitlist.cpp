#include "Waitlist.h"
#include "Warehouse.h"
#include "Order.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

TEST(TestWaitlist, AddValidOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  Order* o2 = new Order(wh, wl);

  wl->addOrder(o);
  wl->addOrder(o2);
  EXPECT_EQ(wl->size(), 2);

  delete o;
  delete o2;
  delete wh;
  delete wl;
}

TEST(TestWaitlist, AddInvalidOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  EXPECT_THROW(wl->addOrder(NULL), invalid_parameter_error);

  delete wh;
  delete wl;
}

// REPORTED BUG
TEST(TestWaitlist, RemoveValidOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  Order* o2 = new Order(wh, wl);

  wl->addOrder(o);
  wl->addOrder(o2);
  EXPECT_EQ(wl->size(), 2);

  wl->removeOrder(o2);
  EXPECT_EQ(wl->size(), 1);

  delete o;
  delete o2;
  delete wh;
  delete wl;
}

TEST(TestWaitlist, RemoveInvalidOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  EXPECT_THROW(wl->addOrder(NULL), invalid_parameter_error);

  delete wh;
  delete wl;
}
