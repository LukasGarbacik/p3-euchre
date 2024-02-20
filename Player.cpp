#include <iostream> 
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"

using namespace std;

Player * Player_factory(const string &name, const string &strategy) {
    if(strategy == "Simple"){
        //return new SimplePlayer(name);
    }
    else if(strategy == "Human"){
        //return new HumanPlayer(name);
    }
  assert(false);
  return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
  return os << p.get_name();
}




SimplePlayer::Simple(string nameInput){ //not right, coudnt figure out as of 2/18
      name = nameInput;
}

class SimplePlayer : private Player{
  private:

    string name;
    array<Card, MAX_HAND_SIZE> hand;

  public:

    const string get_name(){
      return name;
    }

    void add_card(const Card &c){
      assert(hand.size() < MAX_HAND_SIZE);
      hand.push_back(c);
    }
};