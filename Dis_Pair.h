//
// Created by kinkou on 17/09/01.
//

#ifndef NEWCLA_DIS_PAIR_H
#define NEWCLA_DIS_PAIR_H

typedef struct Dis_Pair{

    Interaction_Set domain_set;
    Interaction_Set codomain_set;

    Valid_Interaction dis_interaction;//dis between dis_interaction and codomain_set;
    int Type_Set_Domain;
    int Type_Set_Codomain;

    struct Dis_Pair* next;

}Dis_Pair;

#endif //NEWCLA_DIS_PAIR_H
