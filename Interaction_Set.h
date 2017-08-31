//
// Created by kinkou on 17/09/01.
//

#ifndef NEWCLA_INTERACTION_SET_H
#define NEWCLA_INTERACTION_SET_H

#include "Valid_Interaction.h"

typedef struct Interaction_Set{

    struct Valid_Interaction Interaction_1;
    struct Valid_Interaction Interaction_2;

    int set_type;                               //1: d = 1; 2: d = 2;
    struct Interaction_Set* next;


}Interaction_Set;

#endif //NEWCLA_INTERACTION_SET_H
