//
// Created by kinkou on 17/09/01.
//

#include <stdlib.h>
#include <yices.h>
#include "Interaction_Set.h"
#include "Dis_Pair.h"
#include "Check_Dis.h"

struct Dis_Pair* Check_Dis(context_t* ctx, term_t* parameters, struct Interaction_Set* set_head){

    struct Dis_Pair* dis_head = NULL;
    struct Dis_Pair* current_dis = NULL;

    struct Interaction_Set* set_left = set_head;
    struct Interaction_Set* set_right = NULL;

    int check_11 = 0,
        check_12 = 0,
        check_21 = 0,
        check_22 = 0;

    int flag_of_set = 0;
    int flag = 0;

    term_t check_assert;

    while(set_left != NULL){

        set_right = set_left->next;
        while(set_right != NULL){

            //*******************************************************************************
            //set: d == 1 && d == 1
            //*******************************************************************************
            if(set_left->set_type == 1 && set_right->set_type == 1) {

                if(set_left->Interaction_1.interaction_type == 2 && set_right->Interaction_1.interaction_type == 2) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT){

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_left;
                            dis_head->codomain_set = *set_right;
                            dis_head->dis_interaction = set_left->Interaction_1;

                            dis_head->Type_Set_Domain = 1;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_left;
                            current_dis->next->codomain_set = *set_right;
                            current_dis->next->dis_interaction = set_left->Interaction_1;

                            current_dis->next->Type_Set_Domain = 1;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_right->Interaction_1.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT){

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_left;
                            dis_head->codomain_set = *set_right;
                            dis_head->dis_interaction = set_left->Interaction_1;

                            dis_head->Type_Set_Domain = 1;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_left;
                            current_dis->next->codomain_set = *set_right;
                            current_dis->next->dis_interaction = set_left->Interaction_1;

                            current_dis->next->Type_Set_Domain = 1;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 1 && set_right->Interaction_1.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT){

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_left;
                            dis_head->codomain_set = *set_right;
                            dis_head->dis_interaction = set_left->Interaction_1;

                            dis_head->Type_Set_Domain = 1;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_left;
                            current_dis->next->codomain_set = *set_right;
                            current_dis->next->dis_interaction = set_left->Interaction_1;

                            current_dis->next->Type_Set_Domain = 1;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }

            }

            //*******************************************************************************
            //set: d == 1 && d == 2
            //*******************************************************************************
            if(set_left->set_type == 1 && set_right->set_type == 2) {

                if(set_left->Interaction_1.interaction_type == 2 && set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 2) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_2.p2 - 1], yices_int32(set_right->Interaction_2.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_right->Interaction_1.interaction_type == 1 && set_right->Interaction_2.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 1 && set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 2) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_2.p2 - 1], yices_int32(set_right->Interaction_2.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 1 && set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 1 && set_right->Interaction_1.interaction_type == 1 && set_right->Interaction_2.interaction_type == 1) {

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_1;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_1;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    } else if(check_12 == STATUS_SAT) {

                        if(dis_head == NULL){

                            dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            dis_head->domain_set = *set_right;
                            dis_head->codomain_set = *set_left;
                            dis_head->dis_interaction = set_right->Interaction_2;

                            dis_head->Type_Set_Domain = 2;
                            dis_head->Ttpe_Set_Codomain = 1;

                            dis_head->next = NULL;

                            current_dis = dis_head;

                        }else{

                            current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                            current_dis->next->domain_set = *set_right;
                            current_dis->next->codomain_set = *set_left;
                            current_dis->next->dis_interaction = set_right->Interaction_2;

                            current_dis->next->Type_Set_Domain = 2;
                            current_dis->next->Ttpe_Set_Codomain = 1;

                            current_dis->next->next = NULL;

                            current_dis = current_dis->next;

                        }

                    }

                }

            }

            //*******************************************************************************
            //set: d == 2 && d == 2
            //*******************************************************************************
            if(set_left->set_type == 2 && set_right->set_type == 2) {

                if(set_left->Interaction_1.interaction_type == 2 && set_left->Interaction_2.interaction_type == 2 &&
                   set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 2) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_2.p2 - 1], yices_int32(set_right->Interaction_2.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_2.p2 - 1], yices_int32(set_right->Interaction_2.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_left->Interaction_2.interaction_type == 2 &&
                   set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type == 1) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_left->Interaction_2.interaction_type == 2 &&
                   set_right->Interaction_1.interaction_type == 1 && set_right->Interaction_2.interaction_type == 1) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_2.p2 - 1], yices_int32(set_left->Interaction_2.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_left->Interaction_2.interaction_type == 1 &&
                   set_right->Interaction_1.interaction_type == 2 && set_right->Interaction_2.interaction_type ==1) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_and2(yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_right->Interaction_1.p2 - 1], yices_int32(set_right->Interaction_1.v2))));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 2 && set_left->Interaction_2.interaction_type == 1 &&
                   set_right->Interaction_1.interaction_type == 1 && set_right->Interaction_2.interaction_type == 1) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                                         yices_arith_eq_atom(parameters[set_left->Interaction_1.p2 - 1], yices_int32(set_left->Interaction_1.v2))),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }
                if(set_left->Interaction_1.interaction_type == 1 && set_left->Interaction_2.interaction_type == 1 &&
                   set_right->Interaction_1.interaction_type == 1 && set_right->Interaction_2.interaction_type == 1) {

                    flag = 0;

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_11 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_1.p1 - 1], yices_int32(set_left->Interaction_1.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_12 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_1.p1 - 1], yices_int32(set_right->Interaction_1.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_21 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    yices_push(ctx);
                    check_assert = yices_xor2(yices_arith_eq_atom(parameters[set_left->Interaction_2.p1 - 1], yices_int32(set_left->Interaction_2.v1)),
                                              yices_arith_eq_atom(parameters[set_right->Interaction_2.p1 - 1], yices_int32(set_right->Interaction_2.v1)));
                    yices_assert_formula(ctx, check_assert);
                    check_22 = yices_check_context(ctx, NULL);
                    yices_pop(ctx);

                    if(check_11 == STATUS_SAT && flag == 0){

                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }


                        }
                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 1
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_1;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_1;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }
                    if(check_22 == STATUS_SAT && flag == 0){

                        if(check_21 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_left->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_left;
                                dis_head->codomain_set = *set_right;
                                dis_head->dis_interaction = set_left->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_left;
                                current_dis->next->codomain_set = *set_right;
                                current_dis->next->dis_interaction = set_left->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }
                        if(check_12 == STATUS_SAT && flag == 0){

                            //Set_left ~ Set_right; Set_right->Interaction 2
                            flag = 1;
                            if(dis_head == NULL){

                                dis_head = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                dis_head->domain_set = *set_right;
                                dis_head->codomain_set = *set_left;
                                dis_head->dis_interaction = set_right->Interaction_2;

                                dis_head->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = dis_head;

                            }else{

                                current_dis->next = (Dis_Pair*)malloc(sizeof(Dis_Pair));
                                current_dis->next->domain_set = *set_right;
                                current_dis->next->codomain_set = *set_left;
                                current_dis->next->dis_interaction = set_right->Interaction_2;

                                current_dis->next->next = NULL;

                                dis_head->Type_Set_Domain = 2;
                                dis_head->Ttpe_Set_Codomain = 2;

                                current_dis = current_dis->next;

                            }

                        }

                    }

                }

            }


            set_right = set_right->next;

        }

        set_left = set_left->next;

    }

    return dis_head;


}
