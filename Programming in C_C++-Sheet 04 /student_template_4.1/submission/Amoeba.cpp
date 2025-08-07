#include "Amoeba.h"

Amoeba::Amoeba() 
  : Food(1000.0,50.0,50.0,0.0,0.0) // <- Your code here
                    // <- Your code here
    {
      name = "Amoeba";
    };

Amoeba::Amoeba(double health_, double power_, double defence_, double dna_level_th)
    : Food(health_, power_, defence_, 0, 0)
    // Your code here
    {
      name = "Amoeba";
      health_ = 1000.0;
      power_ = 50.0;
      defence_ = 50.0;
      dna_level_th = 100.0;
    };

Amoeba::~Amoeba(){};

Food *Amoeba::clone() const {
  return new Amoeba(*this); // Your Code here DONE
}
void Amoeba::print_header() {
  std::cout << std::setw(10) << "name" << " | ";
  std::cout << std::setw(10) << "health" << " | ";
  std::cout << std::setw(10) << "power" << " | ";
  std::cout << std::setw(10) << "defence" << " | ";
  std::cout << std::setw(10) << "dna_level_th" << " | ";
  std::cout << std::setw(10) << "dna_level" << std::endl;
}

void Amoeba::print() {
  std::cout << std::setw(10) << name << " | ";
  std::cout << std::setw(10) << health << " | ";
  std::cout << std::setw(10) << power << " | ";
  std::cout << std::setw(10) << defence << " | ";
  std::cout << std::setw(10) << dna_level_th << " | ";
  std::cout << std::setw(10) << dna_level << std::endl;
}

void Amoeba::eat(double health, double dna) {
  // Your Code here DONE
  this->health += health;
  dna_level += dna;

  if(dna_level >= dna_level_th) {
    dna_level_th = dna_level_th * 2;
    dna_level = 0;
  }
}
