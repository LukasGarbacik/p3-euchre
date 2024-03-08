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
 int whoPickedIndex = 0; //updated after each trick
 void shuffle();
 void deal(int dealerPosition);
 bool make_trump(Card upcard, Suit &trumpsuit, int round, int playerIndex);
 void play_hand(int &team1, int &team2, int dealerPos, Suit trumpSuit);
 void trick(int &leadPlayer, int &team1tricks, int &team2tricks, Suit trumpSuit);
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
   int team1score = 0, team2score = 0, handsDelt = 0;
   while (team1score < winningScore && team2score < winningScore)
   {
       Card upcard;
       cards.reset();
       if(doesShuffle){
           shuffle(); //shuffle if needed (const throughout game)
       }
  
      deal(handsDelt); //Each player gets five cards
      cout << "Hand " << handsDelt << endl;
      cout << players[handsDelt % 4]->get_name() << " deals" << endl;
      upcard = cards.deal_one();
      cout << upcard << " turned up" << endl;
      Suit trumpSuit;
      if(!make_trump(upcard,trumpSuit, 1, handsDelt)){
        make_trump(upcard, trumpSuit, 2, handsDelt);
      }
      cout << endl;
      play_hand(team1score, team2score, (handsDelt % 4), trumpSuit);
      
      handsDelt++;
   }

    if(team1score >= winningScore){
        cout << players[0]->get_name() << " and " 
        << players[2]->get_name() << " win!" << endl;}
    else{
        cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " win!" << endl;}




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
bool Game::make_trump(Card upcard, Suit &trumpSuit, int round, int handsDelt){
   int index;
   int dealerIndex = handsDelt % 4 ;
   if(dealerIndex == 3){
      index = 0;
   }
   else{
    index = dealerIndex + 1;
   }
    int counter = 0;
   while(counter < 4 && 
         !players[index]->make_trump(upcard, false, round, trumpSuit)){ 
       cout << players[index]->get_name() << " passes" << endl;           
       index++;
       counter++;
       if(index > 3){
        index = 0;
       }
       if(index == dealerIndex && 
       !players[dealerIndex]->make_trump(upcard, true, round, trumpSuit)){
           cout << players[dealerIndex]->get_name() << " passes" << endl; 
           index++;
           counter++;
       }
       else if(index == dealerIndex){
           cout << players[index]->get_name() << " orders up " << trumpSuit << endl; 
           whoPickedIndex = index;
           players[index]->add_and_discard(upcard);
           return true;
       }
   }   
   if(counter != 4){
      cout << players[index]->get_name() << " orders up " << trumpSuit << endl;
      whoPickedIndex = index;
      if(round == 1){
      players[dealerIndex]->add_and_discard(upcard);
      }
      return true;
   }
   return false;
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

void Game::trick(int &leadPlayer, int &team1tricks, int &team2tricks, Suit trumpSuit)
{
    Card leadCard = players[leadPlayer % 4]->lead_card(trumpSuit);
    Card winningCard = leadCard;
    cout << leadCard << " led by " << players[leadPlayer % 4]->get_name() << endl;
    int counter = 2;
    int currentPlayerIndex = leadPlayer;
    int winningPlayerIndex = leadPlayer;
    
    bool followSuit;

    while(counter < 5)
    {
    currentPlayerIndex = ((currentPlayerIndex + 1) % 4);
    Card played = players[currentPlayerIndex]->play_card(leadCard, trumpSuit);
    if(played.get_suit(trumpSuit) == leadCard.get_suit(trumpSuit)){ 
        followSuit = true;
    }
     else{ 
        followSuit = false; 
    }
    cout << played << " played by " << players[currentPlayerIndex]->get_name() << endl;
    if(followSuit && Card_less(winningCard, played, trumpSuit)){
        winningCard = played;
        winningPlayerIndex = currentPlayerIndex;
    }
    else if(!leadCard.is_trump(trumpSuit) && played.is_trump(trumpSuit)){
        if(Card_less(winningCard, played, trumpSuit)){
            winningCard = played;
            winningPlayerIndex = currentPlayerIndex;
        }
    }

        counter++;
    }
    if (winningPlayerIndex == 0 || winningPlayerIndex == 2){team1tricks++;}
    else{team2tricks++;}
    leadPlayer = winningPlayerIndex;
    cout << players[winningPlayerIndex]->get_name() << " takes the trick" << endl << endl;
}


int main (int argc, char **argv){
    
    if (argc != 12)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 2;
    }
    for (int i = 0; i < 12; i++){cout << argv[i] << " ";}
    cout << endl;
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