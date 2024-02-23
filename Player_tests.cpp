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

    delete human;
    delete simple;
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

    delete simple;
    delete robot;
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

    delete simple;
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

    delete simple;
}

TEST(test_lead_card){
    Player * p1 = Player_factory("Player One", "Simple");
    Suit trump = HEARTS;

    p1->add_card(Card(TEN, HEARTS));
    p1->add_card(Card(ACE, SPADES));
    p1->add_card(Card(JACK, DIAMONDS));
    p1->add_card(Card(KING, SPADES));
    p1->add_card(Card(TEN, SPADES));        
    
    ASSERT_TRUE(p1->lead_card(trump) == Card(ACE, SPADES));

    trump = CLUBS;
    ASSERT_TRUE(p1->lead_card(trump) == Card(ACE, SPADES));

    trump = SPADES;
    p1->add_and_discard(Card(JACK, SPADES));
    p1->add_and_discard(Card(NINE, SPADES));

    ASSERT_TRUE(p1->lead_card(trump) == Card(JACK, SPADES));
    
    delete p1;
}

TEST(test_edge_case_make_trump)
{
    Player * p1 = Player_factory("P1", "Simple");
    Player * p2 = Player_factory("P2", "Simple");
    Player * p3 = Player_factory("P3", "Simple");
    Card upcard = Card(TEN, DIAMONDS);
    Suit OUS;

    p1->add_card(Card(QUEEN, DIAMONDS));
    p1->add_card(Card(KING, DIAMONDS));
    p1->add_card(Card());
    p1->add_card(Card());
    p1->add_card(Card());

    ASSERT_TRUE(p1->make_trump(upcard, false, 1, OUS));
    ASSERT_TRUE(OUS == Suit(DIAMONDS));

    p2->add_card(Card(QUEEN, DIAMONDS));
    p2->add_card(Card(NINE, DIAMONDS));
    p2->add_card(Card());
    p2->add_card(Card());
    p2->add_card(Card());
    OUS = HEARTS;

    ASSERT_FALSE(p2->make_trump(upcard, false, 2, OUS));
    ASSERT_TRUE(OUS == HEARTS);


    p3->add_card(Card(QUEEN, DIAMONDS));
    p3->add_card(Card(JACK, HEARTS));
    p3->add_card(Card());
    p3->add_card(Card());
    p3->add_card(Card());

    ASSERT_TRUE(p3->make_trump(upcard, false, 1, OUS));
    ASSERT_TRUE(OUS == Suit(DIAMONDS));

    delete p1;
    delete p2;
    delete p3;
}
TEST_MAIN()
