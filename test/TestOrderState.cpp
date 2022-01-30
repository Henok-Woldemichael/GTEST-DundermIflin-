#include "Order.h"
#include "OrderState.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "gtest/gtest.h"

TEST(TestOrderState, InCartStateValidSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 5);
  o->editContents(a5, 15);

  o->getWH()->changeQuantity(a4, 20);
  o->getWH()->changeQuantity(a5, 20);
  InCartState* ics = new InCartState();
  EXPECT_TRUE(ics->submit(o));
  EXPECT_NO_THROW(static_cast<CompleteState*>(o->getStatus()));

  delete ics;
  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrderState, InCartStateInvalidSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 5);
  o->editContents(a5, 15);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);
  InCartState* ics = new InCartState();
  EXPECT_FALSE(ics->submit(o));
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));

  delete ics;
  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrderState, InCartStateCancelTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 5);
  o->editContents(a5, 15);
  EXPECT_FALSE(o->isEmpty());

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  InCartState* ics = new InCartState();
  ics->cancel(o);
  EXPECT_TRUE(o->isEmpty());
  EXPECT_NO_THROW(static_cast<InCartState*>(o->getStatus()));

  delete ics;
  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrderState, PendingStateValidSubmitTest) {
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

TEST(TestOrderState, PendingStateInvalidSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);

  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));

  o->getWH()->changeQuantity(a4, 3);
  o->getWH()->changeQuantity(a5, 3);

  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}


TEST(TestOrderState, PendingStateCancelTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 1);
  o->getWH()->changeQuantity(a5, 1);
  EXPECT_FALSE(o->isEmpty());

  // this order will go into pending
  EXPECT_FALSE(o->submit());
  EXPECT_NO_THROW(static_cast<PendingState*>(o->getStatus()));
  // PendingState* os = o->getStatus();

  o->cancel();
  EXPECT_TRUE(o->isEmpty());
  EXPECT_NO_THROW(static_cast<InCartState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrderState, CompleteStateSubmitTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 30);
  o->getWH()->changeQuantity(a5, 30);
  EXPECT_FALSE(o->isEmpty());

  EXPECT_TRUE(o->submit());
  EXPECT_TRUE(o->submit());
  EXPECT_TRUE(o->submit());
  EXPECT_TRUE(o->submit());
  EXPECT_NO_THROW(static_cast<CompleteState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}

TEST(TestOrderState, CompleteStateCancelTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* wh = new Warehouse(wl);

  Product* a4 = new Product("A4", 5.00);
  Product* a5 = new Product("A5", 5.00);

  Order* o = new Order(wh, wl);
  o->editContents(a4, 25);
  o->editContents(a5, 25);

  o->getWH()->changeQuantity(a4, 30);
  o->getWH()->changeQuantity(a5, 30);
  EXPECT_FALSE(o->isEmpty());

  EXPECT_TRUE(o->submit());
  o->cancel();
  EXPECT_TRUE(o->submit());
  EXPECT_NO_THROW(static_cast<CompleteState*>(o->getStatus()));

  delete a4;
  delete a5;
  delete o;
  delete wh;
  delete wl;
}
