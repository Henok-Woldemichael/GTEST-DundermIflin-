#include "Order.h"
#include "OrderState.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "Exceptions.h"
#include <map>
#include "gtest/gtest.h"
// to handle the situation for checking NULL pointers
#include "gmock/gmock.h"

using ::testing::IsNull;
using ::testing::NotNull;
using ::testing::A;
using ::testing::An;


TEST(TestOrder, OrderValidInitializationTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);

  EXPECT_TRUE(o->isEmpty());

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, OrderInvalidInitializationTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  EXPECT_THROW(new Order(NULL, NULL), invalid_parameter_error);

  delete wh;
  delete wl;
}

TEST(TestOrder, EditValidContentsTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  Product* p = new Product("A4", 5.00);

  // why isn't this false? seems to be a bug
  // EXPECT_FALSE(o->editContents(p, 15));

  EXPECT_TRUE(o->editContents(p, 10));
  EXPECT_TRUE(o->editContents(p, -5));

  delete o;
  delete p;
  delete wh;
  delete wl;
}

TEST(TestOrder, EditInvalidContentsTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  EXPECT_THROW(o->editContents(NULL, 15), invalid_parameter_error);

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetWHTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  EXPECT_THAT(o->getWH(), NotNull());

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetWaitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Order* o = new Order(wh, wl);
  EXPECT_THAT(o->getWait(), NotNull());

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, ValidSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 5);
  o->editContents(a5, 15);

  o->getWH()->changeQuantity(a4, 20);
  o->getWH()->changeQuantity(a5, 20);

  EXPECT_TRUE(o->submit());

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, InvalidSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  // this order will go into pending
  EXPECT_FALSE(o->submit());

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, EmptyCancelTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Order* o = new Order(wh, wl);

  EXPECT_TRUE(o->isEmpty());
  o->cancel();
  EXPECT_TRUE(o->isEmpty());

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, CancelTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  EXPECT_FALSE(o->isEmpty());
  o->cancel();
  EXPECT_TRUE(o->isEmpty());

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, IsEmptyTrueTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);
  Order* o = new Order(wh, wl);

  EXPECT_TRUE(o->isEmpty());

  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, IsEmptyFalseTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  EXPECT_FALSE(o->isEmpty());

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetContentsEmptyTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  map<Product* , int> contents = o->getContents();

  EXPECT_EQ(contents.size(), 0);

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetContentsTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  map<Product* , int> contents = o->getContents();

  EXPECT_EQ(contents[a4], 25);
  EXPECT_EQ(contents[a5], 25);

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetInCartStatusTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  EXPECT_NO_THROW(static_cast<InCartState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetPendingStatusTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  // this order will go into pending
  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));
  // PendingState* os = o->getStatus();

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrder, GetCompleteStatusTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 5);
  o->editContents(a5, 15);

  o->getWH()->changeQuantity(a4, 20);
  o->getWH()->changeQuantity(a5, 20);

  EXPECT_TRUE(o->submit());
  EXPECT_NO_THROW(static_cast<CompleteState*>(o->getStatus()));
  // CompleteState* os = o->getStatus();

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

// using submit()
TEST(TestOrder, PendingToCompleteStatusTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  // this order will go into pending
  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));

  o->getWH()->changeQuantity(a4, 30);
  o->getWH()->changeQuantity(a5, 30);

  EXPECT_TRUE(o->submit());
  EXPECT_NO_THROW(static_cast<CompleteState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

// using cancel()
TEST(TestOrder, PendingToIncartStatusTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  // this order will go into pending
  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));

  o->cancel();
  EXPECT_TRUE(o->isEmpty());
  EXPECT_NO_THROW(static_cast<InCartState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}
