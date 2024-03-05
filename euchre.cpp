#include <iostream>
#include <fstream>
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
  void deal(/* ... */);
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
    int team1score = 0, team2score = 0;
    while (team1score < winningScore && team2score < winningScore)
    {

    }
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


