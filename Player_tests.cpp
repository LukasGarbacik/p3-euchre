#include "Player.hpp"
#include "unit_test_framework.hpp"
#include "Card.hpp"

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
    
}


TEST(test_simple_player)
{
    Player * simple = Player_factory("simp", "Simple");
    Player * robot = Player_factory("robot", "Simple");
    ASSERT_EQUAL("simp", simple->get_name());
    ASSERT_EQUAL("robot", robot->get_name());
    for(size_t j = TEN; j <= ACE; j++){
        simple->add_card(Card(static_cast<Rank>(j), SPADES));
        robot->add_card(Card(static_cast<Rank>(j), SPADES));
    }
    simple->add_and_discard(Card(NINE, SPADES));
    for(int i = 0; i < 5; i++){
        ASSERT_TRUE( simple->play_card(Card(NINE, SPADES), SPADES) == robot->play_card(Card(NINE, SPADES), SPADES) );
    }
}


TEST(test_sp_make_trump)
{
    Player * simple = Player_factory("simp", "Simple");
    simple->add_card(Card(TEN, HEARTS));
    simple->add_card(Card(NINE, SPADES));
    simple->add_card(Card(ACE, SPADES));
    simple->add_card(Card(JACK, HEARTS));
    simple->add_card(Card(KING, HEARTS));
    Card upcard = Card(NINE, HEARTS);

    Suit orderedUp;
    ASSERT_TRUE(simple->make_trump(upcard, false, 1, orderedUp));
    ASSERT_TRUE(orderedUp == HEARTS);
    upcard = Card(TEN, DIAMONDS);
    ASSERT_FALSE(simple->make_trump(upcard, false, 1, orderedUp));
    ASSERT_TRUE(orderedUp != DIAMONDS);

    ASSERT_TRUE(simple->make_trump(Card(TEN, DIAMONDS), false, 2, orderedUp));
    ASSERT_TRUE(orderedUp == HEARTS);

    ASSERT_TRUE(simple->make_trump(Card(NINE, CLUBS), true, 2, orderedUp));
    ASSERT_TRUE(orderedUp == SPADES);

    ASSERT_FALSE(simple->make_trump(upcard, true, 1, orderedUp));
    ASSERT_TRUE(orderedUp != DIAMONDS);

    ASSERT_TRUE(simple->make_trump(Card(NINE, HEARTS), true, 1, orderedUp));
    ASSERT_TRUE(orderedUp == HEARTS);
}


TEST(add_and_discard){
    Player * simple = Player_factory("simp", "Simple");
    simple->add_card(Card(TEN, HEARTS));
    simple->add_card(Card(NINE, SPADES));
    simple->add_card(Card(ACE, SPADES));
    simple->add_card(Card(JACK, HEARTS));
    simple->add_card(Card(KING, HEARTS));
    Card upcard = Card(NINE, HEARTS);

    Player * match = Player_factory("simp", "Simple");
    match->add_card(Card(TEN, HEARTS));
    match->add_card(Card(ACE, SPADES));
    match->add_card(Card(JACK, HEARTS));
    match->add_card(Card(KING, HEARTS));
    match->add_card(Card(NINE, HEARTS));

    simple->add_and_discard(upcard);

    for(int i = 0; i < 5; i++){
        ASSERT_TRUE( simple->play_card(Card(NINE, SPADES), HEARTS) == match->play_card(Card(NINE, SPADES), HEARTS) );
    }
}

TEST_MAIN()
