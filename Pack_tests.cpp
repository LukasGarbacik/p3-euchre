#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here

TEST(test_make_pack)
{
    Pack pack;
    Card first = Card(NINE, SPADES);
    ASSERT_EQUAL(pack.deal_one(), first);
    pack.reset();
    Card test;
    for(size_t i = SPADES; i <= DIAMONDS; i++){
       for(size_t j = NINE; j <= ACE; j++){
        ASSERT_EQUAL(pack.deal_one(), Card(static_cast<Rank>(j),static_cast<Suit>(i)));
       }
   }

    Card first = Card(NINE, SPADES);
    ASSERT_EQUAL(pack.deal_one(), first);
    pack.reset();
}

TEST_MAIN()
