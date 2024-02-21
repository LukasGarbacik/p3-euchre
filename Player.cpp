#include <iostream>
#include <cassert>
#include <vector>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"

using namespace std;


  //////////////////////////////////////////////////
 /////  Start of Simple Player Implementation //////
//////////////////////////////////////////////////

class SimplePlayer : public Player{
 private:

   string name;
   vector<Card> hand; //Changed to vector as push_back doesnt work with arrays
   //Shouldn't need a vector with max hand size as that can be handled separately

 public:
   SimplePlayer(string nameInput) : Player() {
    name = nameInput;
    }
   const string& get_name() const override{
     return name;
   }


   void add_card(const Card &c) override {
     assert(hand.size() < MAX_HAND_SIZE);
     hand.push_back(c);
   }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override;
    void add_and_discard(const Card &upcard) override;
    Card lead_card(Suit trump) override;
    Card play_card(const Card &led_card, Suit trump) override;
};




bool SimplePlayer::make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const 
{
  assert(false);
}

void SimplePlayer::add_and_discard(const Card &upcard) 
{
  assert(false);
}

Card SimplePlayer::lead_card(Suit trump) 
{
  assert(false);
}

Card SimplePlayer::play_card(const Card &led_card, Suit trump) {
  assert(false);
}





  //////////////////////////////////////////////////
 /////  Start of Human Player Implementation //////
//////////////////////////////////////////////////

class HumanPlayer : public Player{
 private:


   string name;
   vector<Card> hand;


 public:
   HumanPlayer(string nameInput) : Player() {
    name = nameInput;
  }
   const string& get_name() const override{
     return name;
   }


   void add_card(const Card &c) override{
     assert(hand.size() < MAX_HAND_SIZE);
     hand.push_back(c);
   }

   void print_hand() const {
      for (size_t i=0; i < hand.size(); ++i)
      cout << "Human player " << name << "'s hand: "
        << "[" << i << "] " << hand[i] << "\n";
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override;
    void add_and_discard(const Card &upcard) override ;
    Card lead_card(Suit trump) override;
    Card play_card(const Card &led_card, Suit trump) override;
};

bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                int round, Suit &order_up_suit) const {
    assert(false);
}

void HumanPlayer::add_and_discard(const Card &upcard) {
    assert(false);
}

Card HumanPlayer::lead_card(Suit trump) {
    assert(false);
}

Card HumanPlayer::play_card(const Card &led_card, Suit trump){
    assert(false);
}




  /////////////////////////////////////////////
 ///////   funciton implementations   ////////
/////////////////////////////////////////////


Player * Player_factory(const string &name, const string &strategy) {
   if(strategy == "Simple"){
    return new SimplePlayer(name);
   }
   else if(strategy == "Human"){
      return new HumanPlayer(name);
   }
  assert(false);
  return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
 return os << p.get_name();
}