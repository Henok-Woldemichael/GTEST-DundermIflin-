#include "Product.h"
#include "gtest/gtest.h"

TEST(TestProduct, ProductConstructionTest) {
    Product* prod = new Product("Yellow Potato Bag", 25.00);
    Product* prod2 = new Product("Rice", 12.00);

    EXPECT_EQ(prod->getWeight(), 25.00);
    EXPECT_EQ(prod->getName(), "Yellow Potato Bag");

    EXPECT_EQ(prod2->getWeight(), 12.00);
    EXPECT_EQ(prod2->getName(), "Rice");

    delete prod;
    delete prod2;
}
