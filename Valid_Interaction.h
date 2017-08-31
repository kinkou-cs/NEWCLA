//
// Created by kinkou on 17/09/01.
//

#ifndef NEWCLA_VALID_INTERACTION_H
#define NEWCLA_VALID_INTERACTION_H

typedef struct Valid_Interaction{

    int p1,v1;                          //Parameter 1 and its value;
    int p2,v2;                          //Parameter 2 and its value;

    int interaction_type;               //strength of this interaction;
    struct Valid_Interaction* next;     //pointer to next interaction;

}Valid_Interaction;

#endif //NEWCLA_VALID_INTERACTION_H
