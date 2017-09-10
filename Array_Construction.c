//
// Created by kinkou on 17/09/05.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <yices.h>

#include "Para_Struct.h"
#include "Cons_Struct.h"
#include "Valid_Interaction.h"
#include "Interaction_Set.h"
#include "Dis_Pair.h"
#include "Array_Construction.h"

int Array_Construction(type_t int_type, context_t* ctx, term_t* parameters, struct Para_Struct* para_head, struct Cons_Struct* cons_info,
                       struct Valid_Interaction* valid_head, struct Interaction_Set* set_head, struct Dis_Pair* dis_head, term_t*** parameters_additional_pointer,
                       int case_num, int para_num, char* name){

    term_t f;
    struct Para_Struct* para_pointer = 0;

    //insert sentences to make up the array
    int test_case_num = case_num;

    //*****************************************
    //term insert -> additional parameters which are parts of test cases No.2 to No.(case_num - 1)
    //*****************************************

    (*parameters_additional_pointer) = (term_t**)malloc((test_case_num - 1) * sizeof(term_t*));
    for(int i = 0; i < test_case_num - 1; i++){

        (*parameters_additional_pointer)[i] = (term_t*)malloc(para_num * sizeof(term_t));
        for(int j = 0; j < para_num; j++){

            (*parameters_additional_pointer)[i][j] = yices_new_uninterpreted_term(int_type);


            name[1] = (char)((i + 2) % 100 / 10 + 48);
            name[2] = (char)((i + 2) % 10 + 48);
            name[3] = (char)((j + 1) % 100 / 10 + 48);
            name[4] = (char)((j + 1) % 10 + 48);

            yices_set_term_name((*parameters_additional_pointer)[i][j], name);

        }

    }

    //range insert
    for(int i = 0; i < test_case_num - 1; i++){

        para_pointer = para_head;
        for(int j = 0; j < para_num; j++){

            f = yices_and2(yices_arith_geq_atom((*parameters_additional_pointer)[i][j], yices_int32(1)),
                           yices_arith_leq_atom((*parameters_additional_pointer)[i][j], yices_int32(para_pointer->val_sum)));
            yices_assert_formula(ctx, f);
            para_pointer = para_pointer->next;

        }

    }

    //constraint insert
    struct Cons_Struct* current_cons = 0;

    if(cons_info != NULL){

        for(int i = 0; i < test_case_num - 1; i++){

            current_cons = cons_info;
            while(current_cons != NULL){

                char temp_cons[200] = {0};
                int cons_pointer_num = 0;
                strcpy(temp_cons, current_cons->this_cons);

                while(temp_cons[cons_pointer_num] != '\0'){

                    if(temp_cons[cons_pointer_num - 1] != 'c')
                        cons_pointer_num++;
                    else{

                        temp_cons[cons_pointer_num++] = (char)((i + 2) / 10 + 48);
                        temp_cons[cons_pointer_num++] = (char)((i + 2) % 10 + 48);

                    }

                }
                term_t f_var = yices_parse_term(temp_cons);
                yices_assert_formula(ctx, f_var);
                current_cons = current_cons->next;

            }

        }

    }

    //**************************************************************************************
    //From HERE
    //**************************************************************************************

    //appears at least once
//    struct Valid_Interaction* current_interaction = valid_head;
//    term_t and_phrase_once = 0;
//    term_t or_phrase_once = 0;
//
//    while(current_interaction != NULL){
//
//        for(int i = 0; i < test_case_num; i++){
//
//            if(i == 0){
//
//                and_phrase_once = yices_and2(yices_arith_eq_atom(parameters[current_interaction->p1 - 1], yices_int32(current_interaction->v1)),
//                                             yices_arith_eq_atom(parameters[current_interaction->p2 - 1], yices_int32(current_interaction->v2)));
//                or_phrase_once = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)), and_phrase_once);
//
//            }else{
//
//                and_phrase_once = yices_and2(yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_interaction->p1 - 1], yices_int32(current_interaction->v1)),
//                                             yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_interaction->p2 - 1], yices_int32(current_interaction->v2)));
//                or_phrase_once = yices_or2(or_phrase_once, and_phrase_once);
//
//            }
//
//        }
//        yices_assert_formula(ctx, or_phrase_once);
//
//        current_interaction = current_interaction->next;
//
//    }
    struct Valid_Interaction* current_interaction = valid_head;
    term_t and_phrase_once = 0;
    term_t or_phrase_once = 0;

    while(current_interaction != NULL){

        for(int i = 0; i < test_case_num; i++){

            if(i == 0){

                if(current_interaction->interaction_type == 1){

                    and_phrase_once = yices_arith_eq_atom(parameters[current_interaction->p1 - 1], yices_int32(current_interaction->v1));
                    or_phrase_once = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)), and_phrase_once);

                }else{//current_interaction->interaction_type == 2

                    and_phrase_once = yices_and2(yices_arith_eq_atom(parameters[current_interaction->p1 - 1], yices_int32(current_interaction->v1)),
                                                 yices_arith_eq_atom(parameters[current_interaction->p2 - 1], yices_int32(current_interaction->v2)));
                    or_phrase_once = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)), and_phrase_once);

                }

            }else{

                if(current_interaction->interaction_type == 1){

                    and_phrase_once = yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_interaction->p1 - 1], yices_int32(current_interaction->v1));
                    or_phrase_once = yices_or2(or_phrase_once, and_phrase_once);

                }else{//current_interaction->interaction_type == 2

                    and_phrase_once = yices_and2(yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_interaction->p1 - 1], yices_int32(current_interaction->v1)),
                                                 yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_interaction->p2 - 1], yices_int32(current_interaction->v2)));
                    or_phrase_once = yices_or2(or_phrase_once, and_phrase_once);

                }

            }

        }
        yices_assert_formula(ctx, or_phrase_once);

        current_interaction = current_interaction->next;

    }


    //**********************************

    //XOR insert
//    while(current_pair != NULL){
//
//        for(int i = 0; i < test_case_num; i++){
//
//            if(i == 0){
//
//                xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(parameters[current_pair->p1 - 1], yices_int32(current_pair->v1)),
//                                                       yices_arith_eq_atom(parameters[current_pair->p2 - 1], yices_int32(current_pair->v2))),
//                                            yices_and2(yices_arith_eq_atom(parameters[current_pair->p3 - 1], yices_int32(current_pair->v3)),
//                                                       yices_arith_eq_atom(parameters[current_pair->p4 - 1], yices_int32(current_pair->v4))));
//                or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)), xor_phrase_dis);
//
//            }else{
//
//                xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_pair->p1 - 1], yices_int32(current_pair->v1)),
//                                                       yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_pair->p2 - 1], yices_int32(current_pair->v2))),
//                                            yices_and2(yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_pair->p3 - 1], yices_int32(current_pair->v3)),
//                                                       yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][current_pair->p4 - 1], yices_int32(current_pair->v4))));
//                or_phrase_dis = yices_or2(or_phrase_dis, xor_phrase_dis);
//
//            }
//
//        }
//        yices_assert_formula(ctx, or_phrase_dis);
//
//        current_pair = current_pair->next;
//
//    }
    struct Dis_Pair* current_pair = dis_head;
    term_t xor_phrase_dis = 0;
    term_t and_phrase_dis = 0;
    term_t or_phrase_dis = 0;

    while(current_pair != NULL){

        for(int i = 0; i < test_case_num; i++) {

            if (i == 0) {

                if (current_pair->Ttpe_Set_Codomain == 1) {//d == 1

                    if (current_pair->codomain_set.Interaction_1.interaction_type == 1) {//d == 1 && t == 1

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_1.v1)));
                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      xor_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_1.v1)));
                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      xor_phrase_dis);

                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2) {//d == 1 && t == 2

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));
                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      xor_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));
                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      xor_phrase_dis);

                        }

                    }

                } else if (current_pair->Ttpe_Set_Codomain == 2) {//d == 2

                    if (current_pair->codomain_set.Interaction_1.interaction_type == 1 &&
                        current_pair->codomain_set.Interaction_2.interaction_type == 1) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_1.v1)));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_1.v1)));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2 &&
                               current_pair->codomain_set.Interaction_2.interaction_type == 1) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_arith_eq_atom(parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                                        yices_int32(current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2 &&
                               current_pair->codomain_set.Interaction_2.interaction_type == 2) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                        yices_int32(current_pair->dis_interaction.v1)),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_2.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_2.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_2.v2))));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_1.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_1.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_1.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(
                                    yices_and2(yices_arith_eq_atom(parameters[current_pair->dis_interaction.p1 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v1)),
                                               yices_arith_eq_atom(parameters[current_pair->dis_interaction.p2 - 1],
                                                                   yices_int32(current_pair->dis_interaction.v2))),
                                    yices_and2(yices_arith_eq_atom(
                                            parameters[current_pair->codomain_set.Interaction_2.p1 - 1],
                                            yices_int32(current_pair->codomain_set.Interaction_2.v1)),
                                               yices_arith_eq_atom(
                                                       parameters[current_pair->codomain_set.Interaction_2.p2 - 1],
                                                       yices_int32(current_pair->codomain_set.Interaction_2.v2))));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(yices_arith_eq_atom(yices_int32(1), yices_int32(0)),
                                                      and_phrase_dis);

                        }

                    }

                }

            } else {//i != 0

                if (current_pair->Ttpe_Set_Codomain == 1) {

                    if (current_pair->codomain_set.Interaction_1.interaction_type == 1) {//d == 1 && t == 1

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_1.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_1.v1)));
                            or_phrase_dis = yices_or2(or_phrase_dis, xor_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_1.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_1.v1)));
                            or_phrase_dis = yices_or2(or_phrase_dis, xor_phrase_dis);

                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2) {//d == 1 && t == 2

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));
                            or_phrase_dis = yices_or2(or_phrase_dis, xor_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));
                            or_phrase_dis = yices_or2(or_phrase_dis, xor_phrase_dis);

                        }

                    }

                } else if (current_pair->Ttpe_Set_Codomain == 2) {

                    if (current_pair->codomain_set.Interaction_1.interaction_type == 1 &&
                        current_pair->codomain_set.Interaction_2.interaction_type == 1) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_1.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_1.v1)));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_2.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_1.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_1.v1)));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_2.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);
                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2 &&
                               current_pair->codomain_set.Interaction_2.interaction_type == 1) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_2.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_arith_eq_atom((*parameters_additional_pointer)[i - 1][
                                                                                    current_pair->codomain_set.Interaction_2.p1 -
                                                                                    1],
                                                                            yices_int32(
                                                                                    current_pair->codomain_set.Interaction_2.v1)));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);

                        }

                    } else if (current_pair->codomain_set.Interaction_1.interaction_type == 2 &&
                               current_pair->codomain_set.Interaction_2.interaction_type == 2) {

                        if (current_pair->dis_interaction.interaction_type == 1) {

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_2.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_2.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_2.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_2.v2))));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);

                        } else if (current_pair->dis_interaction.interaction_type == 2) {

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_1.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_1.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_1.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_1.v2))));

                            and_phrase_dis = yices_and2(yices_arith_eq_atom(yices_int32(0), yices_int32(0)),
                                                        xor_phrase_dis);

                            xor_phrase_dis = yices_xor2(yices_and2(yices_arith_eq_atom(
                                    (*parameters_additional_pointer)[i - 1][current_pair->dis_interaction.p1 - 1],
                                    yices_int32(current_pair->dis_interaction.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->dis_interaction.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->dis_interaction.v2))),
                                                        yices_and2(yices_arith_eq_atom(
                                                                (*parameters_additional_pointer)[i - 1][
                                                                        current_pair->codomain_set.Interaction_2.p1 -
                                                                        1],
                                                                yices_int32(
                                                                        current_pair->codomain_set.Interaction_2.v1)),
                                                                   yices_arith_eq_atom(
                                                                           (*parameters_additional_pointer)[i - 1][
                                                                                   current_pair->codomain_set.Interaction_2.p2 -
                                                                                   1],
                                                                           yices_int32(
                                                                                   current_pair->codomain_set.Interaction_2.v2))));

                            and_phrase_dis = yices_and2(and_phrase_dis, xor_phrase_dis);

                            or_phrase_dis = yices_or2(or_phrase_dis, and_phrase_dis);

                        }

                    }

                }

            }

        }
        yices_assert_formula(ctx, or_phrase_dis);

        current_pair = current_pair->next;

    }


    //symmetry breaking
//    term_t sb_dash = yices_and2(yices_arith_eq_atom(parameters[dis_head->dis_interaction.p1 - 1], yices_int32(dis_head->dis_interaction.v1)),
//                                yices_arith_eq_atom(parameters[dis_head->dis_interaction.p2 - 1], yices_int32(dis_head->dis_interaction.v2)));
//    yices_assert_formula(ctx, sb_dash);

//    term_t sb_dash_second = yices_and2(yices_arith_eq_atom((*parameters_additional_pointer)[0][dis_head->codomain_set.Interaction_1.p1 - 1], yices_int32(dis_head->codomain_set.Interaction_1.v1)),
//                                       yices_arith_eq_atom((*parameters_additional_pointer)[0][dis_head->codomain_set.Interaction_1.p2 - 1], yices_int32(dis_head->codomain_set.Interaction_1.v2)));
//    yices_assert_formula(ctx, sb_dash_second);

    term_t* sb = (term_t*)malloc(sizeof(term_t) * (test_case_num - 1));
    term_t sum1 = 0;
    term_t sum2 = 0;
    for(int i = 0; i < test_case_num - 1; i++){

        for(int j = 0; j < para_num; j++){

            int v = (int)pow(4, para_num - j);
            if(i == 0){

                if(j == 0) {

                    sum1 = yices_add(yices_int32(0), yices_mul(parameters[j], yices_int32(v)));
                    sum2 = yices_add(yices_int32(0), yices_mul((*parameters_additional_pointer)[0][j], yices_int32(v)));

                }else{

                    sum1 = yices_add(sum1, yices_mul(parameters[j], yices_int32(v)));
                    sum2 = yices_add(sum2, yices_mul((*parameters_additional_pointer)[0][j], yices_int32(v)));

                }

            }else{

                if(j == 0){

                    sum1 = yices_add(yices_int32(0), yices_mul((*parameters_additional_pointer)[i - 1][j], yices_int32(v)));
                    sum2 = yices_add(yices_int32(0), yices_mul((*parameters_additional_pointer)[i][j], yices_int32(v)));

                }else{

                    sum1 = yices_add(sum1, yices_mul((*parameters_additional_pointer)[i - 1][j], yices_int32(v)));
                    sum2 = yices_add(sum2, yices_mul((*parameters_additional_pointer)[i][j], yices_int32(v)));

                }

            }

        }
        sb[i] = yices_arith_leq0_atom(yices_sub(sum1, sum2));

        yices_assert_formula(ctx, sb[i]);

    }


    //Check Result
    int check_results = yices_check_context(ctx, NULL);

    return check_results;


}