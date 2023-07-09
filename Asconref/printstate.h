#ifndef PRINTSTATE_H_
#define PRINTSTATE_H_


#include "ascon.h"
#include "word.h"
#include "stdio.h"

void printword(const char* text, const uint64_t x);
//void printstate(const char* text, const ascon_state_t* s);
//
//void printstate(const char* text, const ascon_state_t* s){
//      printf("%s\n", text);
//      for (int i = 0; i < 5; i++) {
//        printf("%lX\n",s->x[i]);
//    }
//    printf("\n");
//  }



#endif /* PRINTSTATE_H_ */
