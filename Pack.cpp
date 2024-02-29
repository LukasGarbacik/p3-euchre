#include <iostream>
#include <cassert>
#include "Pack.hpp"
#include "Card.hpp"

using namespace std;


Pack::Pack(){
   int count = 0;
   for(size_t i = SPADES; i <= DIAMONDS; i++){
       for(size_t j = NINE; j <= ACE; j++){
           assert(count < PACK_SIZE);
           cards[count] = Card(static_cast<Rank>(j),static_cast<Suit>(i));
           count++;
       }
   }
   next = 0;
}

Pack::Pack(istream &pack_input){
    int count = 0;
    
   while(pack_input && count < 24){
        pack_input >> cards[count];
        count++;
   }
   next = 0;
}


Card Pack::deal_one(){
   next++;
   return cards[next - 1];
}


void Pack::reset(){
   next = 0;
}

void Pack::shuffle(){
    for(size_t i = 0; i < 7; ++i){
       array<Card, PACK_SIZE/2> Top;
       array<Card, PACK_SIZE/2> Bottom;
       for(size_t j = 0; j < PACK_SIZE/2; ++j){
        Top[j] = cards[j];
       }
       for(size_t k = 0; k < PACK_SIZE/2; ++k){
        Bottom[k] = cards[k + PACK_SIZE/2];
       }
       int topIndex = 0;
       int bottomIndex = 0;
       for(size_t m = 0; m < PACK_SIZE; ++m){
        if(m % 2 == 0){
            cards[m] = Bottom[bottomIndex];
            bottomIndex++;
        }
        else{
            cards[m] = Top[topIndex];
            topIndex++;
        }
       }

    }
} 

bool Pack::empty() const{
   if(next >= 24){
       return true;
   }
   else{
       return false;
   }
}