#include "Order.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "PaperCompany.h"
#include "gtest/gtest.h"
// to handle the situation for checking NULL pointers
#include "gmock/gmock.h"

using ::testing::IsNull;
using ::testing::NotNull;


TEST(TestPapercompany, AddNewProductTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->addProduct("A2", 5.00));
  EXPECT_TRUE(pc->addProduct("A3", 5.00));
  EXPECT_TRUE(pc->addProduct("A4", 5.00));

  delete pc;
}

TEST(TestPapercompany, AddExistingProductTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->addProduct("A2", 5.00));
  EXPECT_FALSE(pc->addProduct("A1", 5.00));
  EXPECT_FALSE(pc->addProduct("A2", 5.00));

  delete pc;
}

TEST(TestPapercompany, FindExistingProductTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->addProduct("A2", 5.00));

  Product* A1 = pc->findProduct("A1");
  Product* A2 = pc->findProduct("A2");

  EXPECT_EQ(A1->getName(), "A1");
  EXPECT_EQ(A1->getWeight(), 5.00);

  EXPECT_EQ(A2->getName(), "A2");
  EXPECT_EQ(A2->getWeight(), 5.00);

  delete pc;
}

TEST(TestPapercompany, FindNonExistingProductTest) {
  PaperCompany* pc = new PaperCompany();
  Product* result = pc->findProduct("A1");

  EXPECT_THAT(result, IsNull());

  delete pc;
}

TEST(TestPapercompany, AdjustingExistingProductTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->adjustInventory("A1", 10));

  delete pc;
}

TEST(TestPapercompany, AdjustingNonExistingProductTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_FALSE(pc->adjustInventory("A2", 10));

  delete pc;
}

TEST(TestPapercompany, AdjustingValidQuantityTest) {
  PaperCompany *pc = new PaperCompany();

  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->addProduct("A2", 5.00));
  EXPECT_TRUE(pc->adjustInventory("A2", 10));

  delete pc;
}

TEST(TestPapercompany, AdjustingInvalidQuantityTest) {
  PaperCompany *pc = new PaperCompany();
  EXPECT_TRUE(pc->addProduct("A1", 5.00));
  EXPECT_TRUE(pc->addProduct("A2", 5.00));
  EXPECT_TRUE(pc->adjustInventory("A2", 10));
  EXPECT_FALSE(pc->adjustInventory("A2", -20));

  delete pc;
}

TEST(TestPapercompany, CreateOrderTest) {
  PaperCompany *pc = new PaperCompany();

  Order* o = pc->createOrder();
  EXPECT_THAT(o, NotNull());

  delete  pc;
}
