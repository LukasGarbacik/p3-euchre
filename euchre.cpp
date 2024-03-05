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
  std::vector<Player*> players;
  int winningScore;
  bool doesShuffle;
  Pack cards;
  void shuffle();
  void deal(int dealerPosition);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
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
    //int team1score = 0, team2score = 0;
    /*while (team1score < winningScore && team2score < winningScore)
    {

    }*/
}

void Game::shuffle()
{
    cards.shuffle();
}

void Game::deal(int dealerPosition)
{
    int Pos = dealerPosition + 1;
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

void Game::make_trump(/* ... */)
{

}

void Game::play_hand(/* ... */)
{

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


