#include <iostream>
#include <cassert>
#include "Pack.hpp"




using namespace std;


Pack::Pack(){
   int count = 0;
   for(size_t i = 0; i <= 3; i++){
       for(size_t j = 7; j <= 12; j++){
           assert(count < PACK_SIZE);
           cards[count] = Card(static_cast<Rank>(j),static_cast<Suit>(i));
           count++;
       }
   }
   next = 0;
}


Pack::Pack(istream &pack_input){
    int count = 0;
   while(pack_input){
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
   int localIndex;
   for(size_t i = 0; i < 7; ++i){
       localIndex = 0;
       Card newDeck [PACK_SIZE];
       for(size_t j = 0; j < PACK_SIZE/2; ++j){
           newDeck[localIndex] = cards[localIndex + PACK_SIZE/2];
           localIndex++;
           newDeck[j] = cards[localIndex];
           localIndex++;
       }
       for(int k = 0; k < PACK_SIZE; ++k)
       {
        cards[k] = newDeck[k];
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
