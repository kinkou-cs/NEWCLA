//
// Created by kinkou on 17/09/01.
//

#include <stdlib.h>
#include "Interaction_Set.h"
#include "Generate_Set.h"


struct Interaction_Set* Generate_Set(struct Valid_Interaction* valid_head){

    struct Interaction_Set* set_head = NULL;
    struct Interaction_Set* current_set = NULL;
    struct Valid_Interaction* interaction_left = valid_head;
    struct Valid_Interaction* interaction_right = NULL;
    struct Valid_Interaction null_interaction;
    null_interaction.p1 = 0;
    null_interaction.p2 = 0;
    null_interaction.v1 = 0;
    null_interaction.v2 = 0;
    null_interaction.interaction_type = -1;
    null_interaction.next = NULL;

    //d = 1;
    while(interaction_left != NULL){

        if(set_head == NULL){

            set_head = (Interaction_Set*)malloc(sizeof(struct Interaction_Set));
            set_head->Interaction_1 = *interaction_left;
            set_head->Interaction_2 = null_interaction;
            set_head->set_type = 1;

            set_head->next = NULL;

            current_set = set_head;

        }else{

            current_set->next = (Interaction_Set*)malloc(sizeof(struct Interaction_Set));
            current_set->next->Interaction_1 = *interaction_left;
            current_set->next->Interaction_2 = null_interaction;
            current_set->next->set_type = 1;

            current_set->next->next = NULL;

            current_set = current_set->next;

        }

        interaction_left = interaction_left->next;

    }

    //d = 2;
    interaction_left = valid_head;
    while(interaction_left != NULL){

        interaction_right = interaction_left->next;
        while(interaction_right != NULL){

            current_set->next = (Interaction_Set*)malloc(sizeof(struct Interaction_Set));
            current_set->next->Interaction_1 = *interaction_left;
            current_set->next->Interaction_2 = *interaction_right;
            current_set->next->set_type = 2;

            current_set->next->next = NULL;

            current_set = current_set->next;

            interaction_right = interaction_right->next;

        }

        interaction_left = interaction_left->next;

    }

    return set_head;

}