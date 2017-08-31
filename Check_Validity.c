//
// Created by kinkou on 17/09/01.
//

#include <stdlib.h>
#include <yices.h>
#include "Para_Struct.h"
#include "Val_Struct.h"
#include "Valid_Interaction.h"
#include "Check_Validity.h"

struct Valid_Interaction* Check_Validity(context_t* ctx, term_t* parameters, struct Para_Struct* para_head, int* num_valid, int cons_flag){

    struct Para_Struct* para_point_left = para_head;
    struct Para_Struct* para_point_right = para_point_left->next;
    struct Val_Struct* val_point_left = para_point_left->val_head;
    struct Val_Struct* val_point_right = para_point_right->val_head;
    struct Valid_Interaction* valid_head = NULL;
    struct Valid_Interaction* valid_current = NULL;

    int flag = 0;


    //add 2-way interactions
    while(para_point_right != NULL){

        while(para_point_right != NULL){

            while(val_point_left != NULL){

                while(val_point_right != NULL){

                    if(cons_flag == 1){									// HAS Constraints

                        yices_push(ctx);
                        term_t check_assert;
                        check_assert = yices_and2(yices_arith_eq_atom(parameters[para_point_left->para - 1],yices_int32(val_point_left->val)),
                                                  yices_arith_eq_atom(parameters[para_point_right->para - 1],yices_int32(val_point_right->val)));
                        yices_assert_formula(ctx, check_assert);
                        if(yices_check_context(ctx, NULL) == STATUS_SAT){

                            (*num_valid)++;
                            if(valid_head == NULL){

                                valid_head = (struct Valid_Interaction*)malloc(sizeof(struct Valid_Interaction));
                                valid_head->p1 = para_point_left->para;
                                valid_head->p2 = para_point_right->para;
                                valid_head->v1 = val_point_left->val;
                                valid_head->v2 = val_point_right->val;
                                valid_head->next = NULL;

                                valid_head->interaction_type = 2;//it is a 2-way interaction

                                valid_current = valid_head;

                            }else{

                                valid_current->next = (struct Valid_Interaction*)malloc(sizeof(struct Valid_Interaction));
                                valid_current->next->p1 = para_point_left->para;
                                valid_current->next->p2 = para_point_right->para;
                                valid_current->next->v1 = val_point_left->val;
                                valid_current->next->v2 = val_point_right->val;
                                valid_current->next->next = NULL;

                                valid_current->next->interaction_type = 2;

                                valid_current = valid_current->next;

                            }

                        }else{

                            if(flag == 0){

                                printf("\n\nInvalid Interactions are:\n\n\n");
                                flag = 1;
                            }
                            //if UNSAT
                            printf("*******************************************\n");
                            printf("sigma(%d, %d)\n", para_point_left->para, val_point_left->val - 1);
                            printf("sigma(%d, %d)\n", para_point_right->para, val_point_right->val - 1);
                            printf("                                is invalid!\n");
                            printf("*******************************************\n");

                        }

                        val_point_right = val_point_right->next;
                        yices_pop(ctx);

                    }else if(cons_flag == 0){							//NO Constraints

                        (*num_valid)++;
                        if(valid_head == NULL){

                            valid_head = (struct Valid_Interaction*)malloc(sizeof(struct Valid_Interaction));
                            valid_head->p1 = para_point_left->para;
                            valid_head->p2 = para_point_right->para;
                            valid_head->v1 = val_point_left->val;
                            valid_head->v2 = val_point_right->val;
                            valid_head->next = NULL;

                            valid_head->interaction_type = 2;

                            valid_current = valid_head;

                        }else{

                            valid_current->next = (struct Valid_Interaction*)malloc(sizeof(struct Valid_Interaction));
                            valid_current->next->p1 = para_point_left->para;
                            valid_current->next->p2 = para_point_right->para;
                            valid_current->next->v1 = val_point_left->val;
                            valid_current->next->v2 = val_point_right->val;
                            valid_current->next->next = NULL;

                            valid_current->next->interaction_type = 2;

                            valid_current = valid_current->next;

                        }
                        val_point_right = val_point_right->next;

                    }

                }

                val_point_left = val_point_left->next;
                val_point_right = para_point_right->val_head;

            }

            para_point_right = para_point_right->next;
            val_point_left = para_point_left->val_head;
            if(para_point_right != NULL)
                val_point_right = para_point_right->val_head;
            else
                val_point_right = NULL;

        }

        para_point_left = para_point_left->next;
        para_point_right = para_point_left->next;
        if(para_point_left != NULL)
            val_point_left = para_point_left->val_head;
        else
            val_point_left = NULL;
        if(para_point_right != NULL)
            val_point_right = para_point_right->val_head;
        else
            val_point_left = NULL;

    }

    //add 1-way interactions
    para_point_left = para_head;

    while(para_point_left != NULL){

        val_point_left = para_point_left->val_head;

        while(val_point_left != NULL){

            valid_current->next = (struct Valid_Interaction*)malloc(sizeof(struct Valid_Interaction));
            valid_current->next->p1 = para_point_left->para;
            valid_current->next->v1 = val_point_left->val;
            valid_current->next->p2 = 0;
            valid_current->next->v2 = 0;
            valid_current->next->next = NULL;

            valid_current->interaction_type = 1;

            valid_current = valid_current->next;

            val_point_left = val_point_left->next;

        }
        para_point_left = para_point_left->next;

    }

    return valid_head;

}

