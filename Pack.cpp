#include <iostream>
#include "Pack.hpp"




using namespace std;


Pack::Pack(){
   int count = 0;
   for(size_t i = SPADES; i <= DIAMONDS; ++i){
       for(size_t j = TWO; j <= ACE; ++j){
           assert(count < PACK_SIZE);
           cards[count] = new Card(j, i);
           count++;
       }
   }
   next = 0;
}


Pack::Pack(istream &pack_input){
   string garbage;
   for(size_t i = 0; i < PACK_SIZE; ++i){
       //further implimentation to come
   }


}


Card deal_one(){
   next++;
   return cards[next - 1];
}


void reset(){
   next = 0;
}


void shuffle(){
   int localIndex;
   for(size_t i = 0; i < 7; ++i){
       localIndex = 0;
       Card newDeck [PACK_SIZE];
       for(size_t j = 0; j < PACK_SIZE/2; ++j){
           newDeck[localIndex] = cards[localIndex + PACK_SIZE/2]
           localIndex++;
           newDeck[j] = cards[localIndex];
           localIndex++;
       }
       cards = newDeck;
       delete newDeck;
   }
}


bool empty() const{
   if(next >= 24){
       return true;
   }
   else{
       return false;
   }
}
