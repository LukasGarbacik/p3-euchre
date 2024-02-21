#include <iostream>
#include <cassert>
#include <vector>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"

using namespace std;

const int MAX_HAND_SIZE = 5; //Global constant to keep player hand sizes in check

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
                    int round, Suit &order_up_suit) const override {
        // Implement the make_trump function logic here
        // Return true or false based on the player's decision
    }

    void add_and_discard(const Card &upcard) override {
        // Implement the add_and_discard function logic here
    }

    Card lead_card(Suit trump) override {
        // Implement the lead_card function logic here
        // Return the card to be led
    }

    Card play_card(const Card &led_card, Suit trump) override {
        // Implement the play_card function logic here
        // Return the card to be played
    }
};





////////////////////////////////////////////////////
/////  Start of Human Player Implementation ////////
////////////////////////////////////////////////////

class HumanPlayer : public Player{
 private:


   string name;
   vector<Card> hand;


 public:
   HumanPlayer(string nameInput);
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
                    int round, Suit &order_up_suit) const override {
        // Implement the make_trump function logic here
        // Return true or false based on the player's decision
    }

    void add_and_discard(const Card &upcard) override {
        // Implement the add_and_discard function logic here
    }

    Card lead_card(Suit trump) override {
        // Implement the lead_card function logic here
        // Return the card to be led
    }

    Card play_card(const Card &led_card, Suit trump) override {
        // Implement the play_card function logic here
        // Return the card to be played
    }
};


HumanPlayer::HumanPlayer(string nameInput) : Player() {
    name = nameInput;
}



  /////////////////////////////////////////////
 ///////   funciton implementations   ////////
/////////////////////////////////////////////


Player * Player_factory(const string &name, const string &strategy) {
   if(strategy == "Simple"){
    SimplePlayer sPlayer = SimplePlayer(name);
    Player * spPtr = & sPlayer;
    return spPtr;
   }
   else if(strategy == "Human"){
      HumanPlayer hPlayer = HumanPlayer(name);
      Player * hpPtr = &hPlayer;
      return hpPtr;
   }
   else{
    return nullptr;
   }
}

ostream & operator<<(ostream &os, const Player &p) {
 return os << p.get_name();
}