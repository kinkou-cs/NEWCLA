//
// Created by kinkou on 17/09/01.
//

#include <stdio.h>
#include <stdlib.h>
#include "Interaction_Set.h"
#include "Generate_Set.h"


struct Interaction_Set* Generate_Set(struct Valid_Interaction* valid_head){

    struct Interaction_Set* set_head = NULL;
    struct Interaction_Set* current_set = NULL;
    struct Valid_Interaction* interaction_left = valid_head;
    struct Valid_Interaction* interaction_right = NULL;
    struct Valid_Interaction null_interaction;
    null_interaction.p1 = 6;
    null_interaction.p2 = 6;
    null_interaction.v1 = 6;
    null_interaction.v2 = 6;
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

            int check_type = interaction_left->interaction_type == 2 && interaction_right->interaction_type == 1;
            int check_value = (interaction_left->p1 == interaction_right->p1 && interaction_left->v1 == interaction_right->v1) ||
                              (interaction_left->p2 == interaction_right->p1 && interaction_left->v2 == interaction_right->v1);
            int check_total = check_type && check_value;

            if(!check_total){   //check for dependency->independent

                current_set->next = (Interaction_Set*)malloc(sizeof(struct Interaction_Set));
                current_set->next->Interaction_1 = *interaction_left;
                current_set->next->Interaction_2 = *interaction_right;
                current_set->next->set_type = 2;

                current_set->next->next = NULL;

                current_set = current_set->next;

            }
            else{

                printf("##################################################\n");
                printf("T1.p1=%d, T1.v1=%d\n", interaction_left->p1, interaction_left->v1);
                printf("T1.p2=%d, T1.v2=%d\n", interaction_left->p2, interaction_left->v2);
                printf("\n");
                printf("T2.p1=%d, T2.v1=%d\n", interaction_right->p1, interaction_right->v1);
                printf("\nare dependent\n");
                printf("##################################################\n");

            }

            interaction_right = interaction_right->next;

        }

        interaction_left = interaction_left->next;

    }

    return set_head;

}