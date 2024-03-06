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
 void make_trump(Card upcard, Suit &trumpsuit, int round, int playerIndex);
 void play_hand(int &team1, int &team2, int dealerPos, Suit trumpSuit);
 void trick(int &leadPlayer, int team1tricks, int team2tricks, Suit trumpSuit);
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
       cards.reset();
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
      make_trump(upcard,trumpSuit, decisionRound, 0);
      cout << endl;
      play_hand(team1score, team2score, (trickNum % 4), trumpSuit);
      
      trickNum++;
   }

    if(team1score >= winningScore){
        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!";}
    else{
        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!";}




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
    int counter = 0;
    if(Pos >=4){Pos%=4;}
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
void Game::make_trump(Card upcard, Suit &trumpSuit, int round, int playerIndex){
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
           whoPickedIndex = 4;
       }
   }   
   if(i != 4){
      cout << players[i]->get_name() << " orders up " << makeTrumpSuit << endl;    
      whoPickedIndex = i;
      return;
   }
  
   round++;
   i = 5;
   while(i < 8 && !players[i-4]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
       cout << players[i-4]->get_name() << " passes" << endl;
       i++;
       if(i == 4 && !players[0]->make_trump(upcard, isDealer, round, makeTrumpSuit)){
           cout << players[0]->get_name() << " passes" << endl;
       }
       else if(i == 8){
           cout << players[i-4]->get_name() << " orders up " << makeTrumpSuit << endl;
           whoPickedIndex = 4;
       }
   }
   if(i != 8){
      cout << players[i-4]->get_name() << " orders up " << makeTrumpSuit << endl;  
      whoPickedIndex = i-4;  
      return;
   }
   trumpSuit = makeTrumpSuit;
}
void Game::play_hand(int &team1, int &team2, int dealerPos, Suit trumpSuit )
{
    int team1tricks = 0, team2tricks = 0, leadPlayer = dealerPos+1, winningTeam;
    bool takeAll = false;
    for (int i = 0; i < 5; i++)
    {
        trick(leadPlayer, team1tricks, team2tricks, trumpSuit);
    }
    if(team1tricks >= 3){winningTeam = 1;
    cout << players[0]->get_name() << " and " 
    << players[2]->get_name() << " win the hand" << endl;}
    else{winningTeam = 2;
    cout << players[1]->get_name() << " and " 
    << players[3]->get_name() << " win the hand" << endl;}




    if(team1tricks == 5 || team2tricks == 5){takeAll = true;}
    if(whoPickedIndex == 0 || whoPickedIndex == 2)
    {
        if(winningTeam == 1 && takeAll){team1 += 2;
        cout << "march!" << endl;}
        else if(winningTeam == 1){team1 += 1;}
        else{team2 += 2;
        cout << "euchred!" << endl;}
    }
    else
    {
        if(winningTeam == 2 && takeAll){team2 += 2;
        cout << "march!" << endl;}
        else if(winningTeam == 2){team2 += 1;}
        else{team1 += 2;
        cout << "euchred!" << endl;}
    }

    cout << players[0]->get_name() << " and " << players[2]->get_name() 
    << " have " << team1 << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name() 
    << " have " << team2 << " points" << endl << endl;
}

void Game::trick(int &leadPlayer, int team1tricks, int team2tricks, Suit trumpSuit)
{
    Card leadCard = players[leadPlayer]->lead_card(trumpSuit);
    Card winningCard = leadCard;
    cout << leadCard << " led by " << players[leadPlayer]->get_name() << endl;
    int counter = 2;
    int currentPlayer = leadPlayer;
    int winningPlayer = leadPlayer;
    
    while(counter < 5)
    {
        currentPlayer = ((currentPlayer + 1) % 4);
        Card played = players[currentPlayer]->play_card(leadCard, trumpSuit);
        cout << played << " played by " << players[currentPlayer]->get_name() << endl;
        if(Card_less(winningCard, played, trumpSuit)){winningCard = played;
        winningPlayer = currentPlayer;}

        counter++;
    }
    if (winningPlayer == 0 || winningPlayer == 2){team1tricks++;}
    else{team2tricks++;}
    leadPlayer = winningPlayer;
    cout << players[winningPlayer]->get_name() << " takes the trick" << endl << endl;
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
    if(!inPack)
    {
        cout << "Error opening " << argv[1] << endl;
        return 3;
    }
    bool doShuffle = false;
    if (strcmp(argv[2], "shuffle") == 0){
        doShuffle = true;
    }  
    Player* playerArray[4];
    for (int i = 4; i < 12; i += 2)
    {
        playerArray[(i-4)/2] = Player_factory(argv[i], argv[i+1]);
    }
    Pack gameCards = Pack(inPack);
    Game game(gameCards, playerArray, atoi(argv[3]), doShuffle);
    game.play();
}