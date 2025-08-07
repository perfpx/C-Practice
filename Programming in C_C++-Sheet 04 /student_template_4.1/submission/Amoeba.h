#pragma once

#include "Food.h"

class Amoeba : public Food {
public:
  Amoeba();

  Amoeba(double health_, double power_, double defence_, double dna_level_th);

  ~Amoeba();

  virtual Food *clone() const override;

  void eat(double health, double dna);

  void print_header() override;
  void print() override;

protected:
  double dna_level{};
  // <-- Your code here DONE
  double dna_level_th = 100.0;
};
