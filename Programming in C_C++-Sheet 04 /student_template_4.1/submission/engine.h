#pragma once

// own classes
#include "Amoeba.h"
#include "DeadCell.h"
#include "Bacterium.h"
#include "Food.h"
#include "Virus.h"

// STL classes
#include <vector>


double random_value(double difficulty = 1.0) {
  return (double((std::rand() % 800) + 100) / 1000.0) * difficulty; // [0.1 .. 0.899] * difficulty
}

bool combat(Amoeba *player, Food *enemy) {
  std::cout << "\n+++++++++++++++++++++++++ new round ++++++++++++++++++++++++\n"
            << std::endl; 

  unsigned int turn = 0;
  
  bool player_won{false};

  if (player && enemy) {
    // print enemy and player information
    enemy->print_header();
    enemy->print();
    player->print_header();
    player->print();

    // fight until either player or enemy lost
    while (player->is_alive() && enemy->is_alive()) {
      turn++;
      
      // player attacks first
      enemy->attacked(
        [&player](double &health, double defence) {
          double val = random_value()*player->get_power() - random_value()*defence;
          if(val > 0) {
            health -= val;
          };
        }
      ); // Your Code DONE

      // enemy attacks second
      player->attacked(
        [&enemy](double &health, double defence) {
          double val = random_value()*enemy->get_power() - random_value()*defence;
          if(val > 0) {
            health -= val;
          };
        }
      ); // Your Code DONE

      // print enemy and player information for this turn
      std::cout << "---------- turn: " << turn << " -----------" << std::endl;
      enemy->print_header();
      enemy->print();
      player->print_header();
      player->print();
    }

    player_won = (player->is_alive() && !enemy->is_alive());

    if (player_won)
    {
      player->eat(enemy->get_health_gain(), enemy->get_dna_gain());
    }
  }

  std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
            << std::endl; 

  return player_won;
}

void engine()
{
  std::cout << "Start game!" << std::endl;

  double difficulty{1.0};

  // create the player  
  Amoeba player(1000.0,50.0,50.0,100.0); // <- Your Code here DONE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  // while player is still alive: fight!
  while (player.is_alive()) {
    std::cout << "Difficulty: " << difficulty << std::endl;

    // define a vector with distinct enemies (DeadCell, Bacterium, ...) which are the competitors and available to fight in this round
    std::vector<Food *> all_enemies;

    // <- Your Code here DONE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    double defHealth, defPower,defDefence;

    defHealth = 10.0;
    defPower = 0.0;
    defDefence = 0.0;

    if(difficulty == 1) {
      DeadCell *deadC = new DeadCell(defHealth, defPower, defDefence);
      all_enemies.push_back(deadC);
    } else {
      DeadCell *deadC = new DeadCell(random_value(difficulty) * defHealth,random_value(difficulty) * defPower,random_value(difficulty) * defDefence);
      all_enemies.push_back(deadC);
    }

    defHealth = 200.0;
    defPower = 10.0;
    defDefence = 50.0;

    if(difficulty == 1) {
      Bacterium *bac = new Bacterium(defHealth, defPower, defDefence);
      all_enemies.push_back(bac);
    } else {
      Bacterium *bac = new Bacterium(random_value(difficulty) * defHealth,random_value(difficulty) * defPower,random_value(difficulty) * defDefence);
      all_enemies.push_back(bac);
    }

    defHealth = 500.0;
    defPower = 25.0;
    defDefence = 25.0;

    if(difficulty == 1) {
      Virus *virus = new Virus(defHealth, defPower, defDefence);
      all_enemies.push_back(virus);
    } else {
      Virus *virus = new Virus(random_value(difficulty) * defHealth,random_value(difficulty) * defPower,random_value(difficulty) * defDefence);
      all_enemies.push_back(virus);
    }


    if(all_enemies.empty()) return;

    player.print_header();
    player.print();
    std::cout << "\n";

    // deep copy (one to three) random competitor the player can fight in this round. Duplicates are allowed.
    std::vector<Food *> enemy;
    // <- Your Code here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int random = (std::rand() % 3) + 1;
    int amountEnemies = random;

    for(int i = 0; i < amountEnemies; i++) {
      int index = std::rand() % (all_enemies.size());
      enemy.push_back(all_enemies.at(index)->clone());
    }
    
    // print number of enemies selected for this round
    std::cout << std::setw(10) << "Select" << " : ";
    enemy[0]->print_header(); // only print header of first entry to reduce output in InfoMark
    for (size_t i = 0; i < enemy.size(); i++) {
      std::cout << std::setw(10) << i << " : ";
      enemy[i]->print();
    }
    std::cout << "Choose your enemy (0-" << enemy.size() - 1 << "): ";

    unsigned int selection;
    std::cin >> selection;

    selection = selection % enemy.size();

    combat(&player, enemy[selection]);

    difficulty += 1.0;
    
    // Your Code... don't forget to free dynamically allocated objects

    for(auto ptr: all_enemies) {
      delete ptr;
    }
    for(auto ptr: enemy) {
      delete ptr;
    }
  }
	std::cout << "Player reached difficulty level (round): " << difficulty << std::endl;
}
