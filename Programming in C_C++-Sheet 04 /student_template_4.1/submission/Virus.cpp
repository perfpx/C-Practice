#include "Virus.h"
#include "Food.h"

Virus::Virus(double health_, double power_, double defence_) : Food(health_, power_, defence_, 400.0, 400.0)
// Your Code DONE
{
    // Your Code DONE
    health = health_;
    power = power_;
    defence = defence_;
}

Virus::~Virus() {}

Food *Virus::clone() const {
    // Your Code DONE
    return new Virus(*this);
}