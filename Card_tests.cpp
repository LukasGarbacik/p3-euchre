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
    ASSERT_FALSE(Card_less(tenSpades,tenHearts, CLUBS));
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

TEST_MAIN()
