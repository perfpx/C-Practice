#include "Bacterium.h"
#include "Food.h"

Bacterium::Bacterium(double health_, double power_, double defence_) : Food(health_, power_, defence_, 10.0, 200.0)
// Your Code DONE

{
  // Your Code DONE
  health = health_;
  power = power_;
  defence = defence_;
}

Bacterium::~Bacterium() {}

Food *Bacterium::clone() const {
  // Your Code DONE
  return new Bacterium(*this);
}