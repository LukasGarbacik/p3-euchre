#include "Player.hpp"
#include "unit_test_framework.hpp"
#include "Card.hpp"
#include "Pack.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_player_factory)
{
    Player * human = Player_factory("Human", "Human");
    ASSERT_EQUAL("Human", human->get_name());
    Player * simple = Player_factory("robot", "Simple");
    ASSERT_EQUAL("robot", simple->get_name());
    Pack pack;
    Card first = Card(NINE, SPADES);
    ASSERT_EQUAL(pack.deal_one(), first);
    pack.reset();
    
}


/*TEST(test_make_trump)
{
}*/

TEST_MAIN()
