//
// Created by kinkou on 17/09/01.
//

#include <stdlib.h>
#include <yices.h>
#include "Interaction_Set.h"
#include "Dis_Pair.h"
#include "Check_Dis.h"

struct Dis_Pair* Check_Dis(context_t* ctx, term_t* parameters, struct Interaction_Set* set_head, int cons_flag){

    struct Dis_Pair* dis_head = NULL;
    struct Dis_Pair* current_dis = NULL;

    struct Interaction_Set* set_left = set_head;
    struct Interaction_Set* set_right = NULL;

    int flag = 0;//show indistinguishable pairs

    while(set_left != NULL){

        set_right = set_left->next;
        while(set_right != NULL){


            set_right = set_right->next;

        }

        set_left = set_left->next;

    }




}
