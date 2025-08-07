#include "DeadCell.h"
#include "Food.h"

DeadCell::DeadCell(double health_, double power_, double defence_)
: Food(health_, power_, defence_,  10.0,  100.0)
// Your Code DONE
{
  // Your Code DONE
  health = health_;
  power = power_;
  defence = defence_;
}

DeadCell::~DeadCell() {}

Food *DeadCell::clone() const {
  // Your Code DONE
  return new DeadCell(*this);
}
