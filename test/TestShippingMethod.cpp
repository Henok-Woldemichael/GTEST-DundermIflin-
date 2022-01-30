#include "ShippingMethod.h"
#include "gtest/gtest.h"

TEST(TestShippingMethod, AirShippingNameTest) {
  Air* s = new Air();

  EXPECT_EQ(s->name(), "Air");

  delete s;
}

TEST(TestShippingMethod, TruckShippingNameTest) {
  Truck* s = new Truck();

  EXPECT_EQ(s->name(), "Truck");

  delete s;
}

TEST(TestShippingMethod, TrainShippingNameTest) {
  Train* s = new Train();

  EXPECT_EQ(s->name(), "Train");

  delete s;
}

TEST(TestShippingMethod, ShipShippingNameTest) {
  Ship* s = new Ship();

  EXPECT_EQ(s->name(), "Ship");

  delete s;
}
