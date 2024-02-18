#include <iostream> 
#include "Player.hpp"

using namespace std;

Player * Player_factory(const string &name, const string &strategy) {
    if(strategy == "Simple"){
        //return new SimplePlayer(name);
    }
    if(strategy == "Human"){
        //return new HumanPlayer(name);
    }
  assert(false);
  return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
  assert(false);
}

//class SimplePlayer : private Player{
//public:
//
//};