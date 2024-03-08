#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_right_left_bower)
{
    Card left = {JACK, SPADES};
    Card right = {JACK, CLUBS};
    Card ace = {ACE, CLUBS};
    Suit trump = CLUBS;
    ASSERT_TRUE(Card_less(left, right, trump));
    ASSERT_FALSE(Card_less(right, left, trump));
    ASSERT_FALSE(Card_less(left, ace, trump));
    ASSERT_FALSE(Card_less(right, ace, trump));
    ASSERT_FALSE(Card_less(left, left, trump));
    ASSERT_FALSE(Card_less(right, right, trump));
    
    Card aceSpades = {ACE, SPADES};
    Card tenSpades = {TEN, SPADES};
    Card nineHearts = {NINE, HEARTS};
    Card tenHearts = {TEN, HEARTS};

    ASSERT_TRUE(Card_less(tenSpades, nineHearts, tenHearts, tenHearts.get_suit()));
    ASSERT_TRUE(Card_less(tenSpades,aceSpades, nineHearts, nineHearts.get_suit()));
    ASSERT_TRUE(Card_less(tenSpades, tenHearts, HEARTS));
    ASSERT_TRUE(Card_less(tenSpades,tenHearts, CLUBS));
}

TEST(test_greater_less_equal_to)
{
    Card aceSpades = {ACE, SPADES};
    Card tenSpades = {TEN, SPADES};
    Card nineHearts = {NINE, HEARTS};
    Card tenHearts = {TEN, HEARTS};

    ASSERT_TRUE(tenSpades > nineHearts);
    ASSERT_FALSE(tenSpades > tenHearts);

    ASSERT_TRUE(tenHearts < aceSpades);
    ASSERT_FALSE(tenHearts < tenSpades);

    ASSERT_TRUE(tenHearts >= tenSpades);
    ASSERT_FALSE(tenHearts >= aceSpades);
    
    ASSERT_TRUE(tenHearts <= aceSpades);
    ASSERT_FALSE(aceSpades <= nineHearts);
}

TEST(test_left_bower){   
    Card jackHearts(JACK, HEARTS);
    Card aceDiamonds(ACE, DIAMONDS);
    Suit trump = DIAMONDS;

    ASSERT_TRUE(jackHearts.is_trump(trump));
    ASSERT_FALSE(Card_less(jackHearts,aceDiamonds, trump));
    ASSERT_TRUE(jackHearts.is_left_bower(trump));
    ASSERT_TRUE(jackHearts.is_face_or_ace() && aceDiamonds.is_face_or_ace());
    ASSERT_FALSE(jackHearts.get_suit() == jackHearts.get_suit(trump));

}

TEST(test_card_print){
    Card nineSpades(NINE, SPADES);
    Card jackDiamonds(JACK, DIAMONDS);
    Card kingHearts(KING, HEARTS);

    stringstream card1;
    stringstream card2;
    stringstream card3;

    card1 << nineSpades;
    card2 << jackDiamonds;
    card3 << kingHearts;
    ASSERT_TRUE(card1.str() == "Nine of Spades");
    ASSERT_TRUE(card2.str() == "Jack of Diamonds");
    ASSERT_TRUE(card3.str() == "King of Hearts");

}

TEST(test_suit_next){
    Card nineSpades(NINE, SPADES);
    Card jackDiamonds(JACK, DIAMONDS);
    Card kingHearts(KING, HEARTS);
    Card tenClubs(TEN, CLUBS);

    Suit trump = HEARTS;

    ASSERT_TRUE(Suit_next(nineSpades.get_suit()) == CLUBS);
    ASSERT_TRUE(Suit_next(jackDiamonds.get_suit()) == trump);
    ASSERT_TRUE(Suit_next(kingHearts.get_suit()) == DIAMONDS);
    ASSERT_TRUE(Suit_next(tenClubs.get_suit()) == SPADES);
}

TEST(test_low_val_trump){
    Card nineSpades(NINE, SPADES);
    Card jackDiamonds(JACK, DIAMONDS);
    Card kingHearts(KING, HEARTS);
    Card tenClubs(TEN, CLUBS);
    Card nineClubs(NINE, CLUBS);
    Card aceSpades(ACE, SPADES);

    Suit trump = CLUBS;

    ASSERT_TRUE(Card_less(kingHearts, nineClubs, trump));
    ASSERT_TRUE(Card_less(kingHearts, tenClubs, trump));
    ASSERT_FALSE(Card_less(nineClubs, aceSpades, trump));
    ASSERT_FALSE(Card_less(tenClubs, jackDiamonds, trump ));
}

TEST_MAIN()
