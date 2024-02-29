#include <iostream>
#include <cassert>
#include <vector>
#include "Player.hpp"
#include "Card.hpp"
#include <algorithm>

using namespace std;


  //////////////////////////////////////////////////
 /////  Start of Simple Player Implementation //////
//////////////////////////////////////////////////

  //////////////////////////////////////////////////
 /////  Start of Simple Player Implementation //////
//////////////////////////////////////////////////

class SimplePlayer : public Player{
 private:

   string name;
   vector<Card> hand;

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
  assert(round == 1 || round == 2);
  assert(hand.size() == 5);
  int countFaceAce = 0;
  if(round == 1){
    for(size_t i = 0; i < hand.size(); ++i){
      if(hand[i].get_suit(upcard.get_suit()) == upcard.get_suit()
       && hand[i].is_face_or_ace()){
        countFaceAce++;
      }
    }
    if(countFaceAce >= 2){
      order_up_suit = upcard.get_suit();
      return true;
    }
    else{
      return false;
    }
  } 
  if(round == 2){
    if(is_dealer){
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    else{
      for(size_t i = 0; i < hand.size(); ++i){ //too deeply nested here 
        if(hand[i].get_suit() == Suit_next(upcard.get_suit())
         && hand[i].is_face_or_ace()){
          countFaceAce++;
        }
      }  
      if(countFaceAce >= 1){
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      }
    }
  }
  return false;
}

void SimplePlayer::add_and_discard(const Card &upcard) 
{
  assert(hand.size() != 0);
  Suit trump = upcard.get_suit();
  Card *minCard = new Card(hand[0]);
  int minIndex = 0;
  for(size_t i = 1; i < hand.size(); ++i){
    if(!Card_less(*minCard,hand[i], trump)){
      *minCard = hand[i];
      minIndex = i;
    }
  }
  if(Card_less(*minCard, upcard, trump)){
    hand.erase(hand.begin() + minIndex);
    hand.push_back(upcard);
  }
  delete minCard;
}

Card SimplePlayer::lead_card(Suit trump) 
{
  assert(hand.size() != 0);
  Card  returnCard = Card(hand[0]);
  bool allTrump = true;
  int returnIndex = 0;


  for(size_t i = 0; i < hand.size(); ++i){
    if(!hand[i].is_trump(trump)) {
      allTrump = false;
      if (hand[i] > returnCard){
         returnCard = hand[i];
        returnIndex = i;
      }
    }
  }
  if(allTrump){
    for(size_t j = 0; j < hand.size(); ++j){
      if(Card_less(returnCard, hand[j], trump)){
        returnCard = hand[j];
        returnIndex = j;
      }
    }
  }
  hand.erase(hand.begin() + returnIndex);
  return returnCard;
}

Card SimplePlayer::play_card(const Card &led_card, Suit trump) {
  assert(hand.size() != 0);
  bool canFollowSuit = false;
  int returnIndex = 0;
  Card *card = new Card(hand[0]);
  for(size_t i = 0; i < hand.size(); ++i){
    if(hand[i].is_trump(trump)){
      canFollowSuit = true;
    }
    if(canFollowSuit && Card_less(*card, hand[i], trump)){
      *card = hand[i];
      returnIndex = i;
    }
  }  
  if(!canFollowSuit){
    for(size_t j = 1; j < hand.size(); ++j){
      if(Card_less(hand[j], *card, trump)){
        *card = hand[j];
        returnIndex = j;
      }
    }
  }
  Card returnCard = * card;
  hand.erase(hand.begin() + returnIndex);
return returnCard;
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


//Assuming all players will not cheat (SPECS)
//i.e. human will always pick a suit for screw the dealer
bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const {

  string decision;                      

  print_hand(); //Prints hand before decision is made 
  cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
  cin >> decision;

  if (decision != "pass") {
    order_up_suit = string_to_suit(decision);
    return true;
  }
  else {
    return false;
  }
}

//Human will answer with a number corresponding
//to a sorted card in thier hand
void HumanPlayer::add_and_discard(const Card &upcard) {

  string input;
  int handIndex;

  print_hand(); //Prints current hand
  cout << "Discard upcard: [-1]\n"; //has option to discard upcard "-1"
  cout << "Human player " << name << ", please select a card to discard:\n";

  cin >> input;
  handIndex = stoi(input); //index of discard card

  if(handIndex == -1){
    return;
  }
  else{ //Assuming a legit index (SPECS)
    hand.erase(hand.begin() + handIndex);
    add_card(upcard);
    sort(hand.begin(), hand.end());
  }
}

//User still entering index 
//Assuming they know what the trump suit is
Card HumanPlayer::lead_card(Suit trump) {

  string input;
  int handIndex;

  print_hand();
  cout << "Human player " << name << ", please select a card:\n"; 

  cin >> input;
  handIndex = stoi(input);

  Card returnCard = hand[handIndex];
  hand.erase(hand.begin() + handIndex);
  return returnCard;
}

//Exact same implication as lead_card()
Card HumanPlayer::play_card(const Card &led_card, Suit trump){

  string input;
  int handIndex;

  print_hand();
  cout << "Human player " << name << ", please select a card:\n"; 

  cin >> input;
  handIndex = stoi(input);

  Card returnCard = hand[handIndex];
  hand.erase(hand.begin() + handIndex);
  return returnCard;
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