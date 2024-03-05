#include <iostream>
#include <fstream>
#include <cstring>
#include "Player.hpp"
#include "Pack.hpp"


using namespace std;






class Game {


public:


 Game(Pack cards, Player* playerArray[], int score, bool shuffle);
 void play();


private:


 vector<Player*> players; //Player vector
 Pack cards; // Card pack


 int winningScore; // argv[3] const througout
 bool doesShuffle; // const througout
 int trickNum; // updated after each trick
 int whoPickedIndex = 0; //updated after each trick




 void shuffle();
 void deal(int dealerPosition);
 void make_trump(Card upcard, Suit &trumpsuit, int &pickIndex, int round, int playerIndex);
 void play_hand(/* ... */);
 void trick(/* ..... */);


};




Game::Game(Pack p, Player* playerArray[], int score, bool shuffle)
{
   for(int i =0; i < 4; i++){players.push_back(playerArray[i]);}
   winningScore = score;
   doesShuffle = shuffle;
   cards = p;
}




void Game::play()
{
   int team1score = 0, team2score = 0;
   trickNum = 0;
   while (team1score < winningScore && team2score < winningScore)
   {
       Card upcard;


       if(doesShuffle){
           shuffle(); //shuffle if needed (const throughout game)
       }
  


      deal(trickNum); //Each player gets five cards


      cout << "Hand " << trickNum % 4 << endl;
      cout << players[trickNum % 4]->get_name() << " deals" << endl;
      upcard = cards.deal_one();
      cout << upcard << " turned up" << endl;


      Suit trumpSuit;
      int decisionRound = 1;
      make_trump(upcard,trumpSuit, whoPickedIndex, decisionRound, 0);
     
   team1score++;
   }
   for (size_t i = 0; i < players.size(); ++i) {
       delete players[i];
   }
}


void Game::shuffle()
{
   cards.shuffle();
}


void Game::deal(int dealerPosition)
{
   int Pos = dealerPosition + 1;
   if(dealerPosition == 3){
       Pos = 0;
   }
   int counter = 0;
   while (counter < 4)
   {
       if (counter % 2 == 0)
       {
           for (int i = 0; i < 3; i++)
           {
               players[Pos]->add_card(cards.deal_one());
           }
       }
       else
       {
           for (int i = 0; i < 2; i++)
           {
               players[Pos]->add_card(cards.deal_one());
           }
       }
       counter++;
       if(Pos == 3){Pos = 0;}
       else{Pos++;}
   }




   while (counter < 8)
   {
       if (counter % 2 == 0)
       {
           for (int i = 0; i < 2; i++)
           {
               players[Pos]->add_card(cards.deal_one());
           }
       }
       else
       {
           for (int i = 0; i < 3; i++)
           {
               players[Pos]->add_card(cards.deal_one());
           }
       }
       counter++;
       if(Pos == 3){Pos = 0;}
       else{Pos++;}
   }
}


void Game::make_trump(Card upcard, Suit &trumpSuit, int &pickIndex, int round, int playerIndex){
   int i = 1;
   bool isDealer = false;
   Suit makeTrumpSuit;
   if(abs(trickNum - playerIndex) % 4 == 0){ isDealer = true; }
   while(i < 4 && !players[i]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
       cout << players[i]->get_name() << " passes" << endl;
       i++;
       if(i == 4 && !players[0]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
           cout << players[0]->get_name() << " passes" << endl;
       }
       else if(i == 4){
           cout << players[i]->get_name() << " orders up " << makeTrumpSuit << endl;
       }
   }   
   if(i != 4){
      cout << players[i]->get_name() << " orders up " << makeTrumpSuit << endl;    
      return;
   }
  
   round++;
   i = 1;
   while(i < 4 && !players[i]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
       cout << players[i]->get_name() << " passes" << endl;
       i++;
       if(i == 4 && !players[0]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
           cout << players[0]->get_name() << " passes" << endl;
       }
       else if(i == 4){
           cout << players[i]->get_name() << " orders up " << makeTrumpSuit << endl;
       }
   }
   if(i != 4){
      cout << players[i]->get_name() << " orders up " << makeTrumpSuit << endl;    
      return;
   }




   trumpSuit = makeTrumpSuit;
}


void Game::play_hand(/* ... */)
{


}


void Game::trick(/* . . . */){


}




int main (int argc, char **argv){
   if (argc != 12)
   {
       cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
    return 2;
   }
   ifstream inPack(argv[1]);
   if(!inPack.is_open())
   {
       cout << "Error opening " << argv[1] << endl;
       return 3;
   }
   bool doShuffle = false;
   if (strcmp(argv[2], "shuffle") == 0){
       doShuffle = true;
   } 
   Player* playerArray[4];
   for (int i = 4; i < 12; i += 2){
       playerArray[(i-4)/2] = Player_factory(argv[i], argv[i+1]);
   }
   Pack gameCards = Pack(inPack);
   Game game(gameCards, playerArray, atoi(argv[3]), doShuffle);
   game.play();
}
