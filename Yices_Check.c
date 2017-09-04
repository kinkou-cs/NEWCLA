//
// Created by kinkou on 17/09/01.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <yices.h>
#include <time.h>
#include "Mode_Enum.h"
#include "Para_Struct.h"
#include "Cons_Struct.h"
#include "Valid_Interaction.h"
#include "Interaction_Set.h"
#include "Dis_Pair.h"
#include "Check_Validity.h"
#include "Generate_Set.h"
#include "Check_Dis.h"
#include "Array_Construction.h"
#include "Yices_Check.h"


int Yices_Check(struct Para_Struct* para_head, struct Cons_Struct* cons_info, int case_num, int* para_num_m, enum MODE exec_mode){

    int assertion_num = 0;
    int* assertion_num_pointer = &assertion_num;
    //initialization
    yices_init();

    //define a context with push-pop mode
    term_t f;
    ctx_config_t* config = yices_new_config();
    yices_default_config_for_logic(config, "LIA");
    yices_set_config(config, "arith-fragment", "LIA");
    context_t* ctx = yices_new_context(NULL);

    //define the type of parameters
    type_t int_type = yices_int_type();
    term_t* parameters = NULL;

    struct Para_Struct* para_pointer = para_head;
    int para_num;

    //get the number of the parameters
    while(para_pointer->next != 0){

        para_pointer = para_pointer->next;

    }
    para_num = para_pointer->para;

    parameters = (term_t*)malloc(para_num * sizeof(term_t));

    char name[] = "c0101";
    int name_num = 1;

    //set the type of each parameter as integer
    for(int para_counter = 0; para_counter < para_num; para_counter++){

        parameters[para_counter] = yices_new_uninterpreted_term(int_type);
        yices_set_term_name(parameters[para_counter], name);

        name_num++;

        name[4] = (char)(48 + name_num % 10);
        name[3] = (char)(48 + name_num % 100 / 10);

    }

    //set range
    para_pointer = para_head;
    for(int para_counter = 0; para_counter < para_num; para_counter++){

        f = yices_and2(yices_arith_geq_atom(parameters[para_counter], yices_int32(1)),
                       yices_arith_leq_atom(parameters[para_counter], yices_int32(para_pointer->val_sum)));
        yices_assert_formula(ctx, f);

        para_pointer = para_pointer->next;

    }

    //input constraints
    struct Cons_Struct* cons_pointer = cons_info;
    while(cons_pointer != NULL){

        term_t f_cons;
        f_cons = yices_parse_term(cons_pointer->this_cons);
        yices_assert_formula(ctx, f_cons);
        cons_pointer = cons_pointer->next;

    }

    int cons_flag = 1;
    if(cons_info == NULL){

        cons_flag = 0;              //cons_flag = 0: NO Constraints; cons_flag = 1: HAS Constraints

    }

    //check validity
    struct Valid_Interaction* valid_head = 0;
    int num_valid = 0;
    int* num_valid_point = &num_valid;
    clock_t valid_check_time_start = clock();
    valid_head = Check_Validity(ctx, parameters, para_head, num_valid_point, cons_flag);
    clock_t valid_check_time_stop = clock();
    printf("\n\nValid Check Runtime: %lf[s]\n\n", (double)(valid_check_time_stop - valid_check_time_start)/CLOCKS_PER_SEC);

    //generate valid interaction sets
    struct Interaction_Set* set_head = 0;
    set_head = Generate_Set(valid_head);

    //check distinguishability
    struct Dis_Pair* dis_head;
    clock_t dis_check_time_start = clock();
    dis_head = Check_Dis(ctx, parameters, set_head);
    clock_t dis_check_time_stop = clock();
    printf("\n\nDis Check Runtime: %lf[s]\n\n", (double)(dis_check_time_stop - dis_check_time_start)/CLOCKS_PER_SEC);

    //insert sentences to make up the array
    int test_case_num = case_num;
    term_t** parameters_additional = 0;
    term_t*** parameters_additional_pointer = &parameters_additional;

    //check
    int check_results = Array_Construction(int_type, ctx, parameters, para_head, cons_info,
                                           valid_head, set_head, dis_head, parameters_additional_pointer,
                                           case_num, para_num, name);

    int** test_cases = NULL;

    if(check_results == STATUS_SAT){

        model_t* model = yices_get_model(ctx, 1);
        test_cases = (int **)malloc(sizeof(int*) * test_case_num);

        for(int i = 0; i < test_case_num; i++){

            test_cases[i] = (int *)malloc(sizeof(int) * para_num);

        }

        for(int i = 0; i < test_case_num; i++){

            for(int j = 1; j <= para_num; j++){

                if(i == 0){

                    yices_get_int32_value(model, parameters[j - 1], &test_cases[i][j - 1]);

                }
                else{

                    yices_get_int32_value(model, parameters_additional[i - 1][j - 1], &test_cases[i][j - 1]);

                }

            }

        }

        *para_num_m = para_num;

        printf("\n\n\n(1,2)-Constrained Locating Array is:\n\n\n");

        for(int i = 0; i < test_case_num; i++){

            for(int j = 0; j < para_num; j++){

                printf("%8d", test_cases[i][j] - 1);

            }
            printf("\n");

        }

        printf("The test case size is: %d\n", test_case_num);

        yices_free_config(config);
        return 1;


    }
    if(check_results == STATUS_UNSAT)
    {

        printf("\n\n\nUNSAT!\nThere isn't any valid locating array with %d test cases!\n", test_case_num);

        yices_free_config(config);

        return -1;


    }

    return 0;


}

