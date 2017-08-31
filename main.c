#include <stdio.h>
#include <string.h>
#include <time.h>
#include <yices.h>
#include <getopt.h>
#include <stdlib.h>
#include "Mode_Enum.h"
#include "Para_Struct.h"
#include "Cons_Struct.h"
#include "Input_Info.h"
#include "Yices_Check.h"


int main (int argc, char *argv[]){

    clock_t start, stop;

    const char* optstring = "o:m:vs:h";
    int opt_char = 0;
    int arg_file_num =0;
    enum MODE this_mode = EXEC_ONCE;
    int test_case_num = 0;

    if(argc <= 3){

        printf("\nPlease invoke an input file!\n\n");

    }

    while((opt_char = getopt(argc, argv, optstring)) != -1){

        switch(opt_char){

            case 'o':
                this_mode = EXEC_ONCE;
                test_case_num = atoi(optarg);
                break;
            case 'm':
                this_mode = EXEC_MULTI;
                test_case_num = atoi(optarg);

                break;
            case 's':
                this_mode = EXEC_ONCE_SHOW;
                test_case_num = atoi(optarg);
                break;
            case 'v':
                printf("Yices Version: %s\nCLA Version 1.0\n", yices_version);
                return 1;
            case 'h':
                printf("Usage: ./CLA [option] <input file>\nOptions:\n");
                printf("%4s%-15s%s", " ", "-o <size>","Input the test case number and check if there exists a constrained locating array in that size.\n");
                printf("%4s%-15s%s", " ", "-m <size>","Input the test case number and arrange the size to find smallest constrained locating array.\n");
                printf("%4s%-15s%s", " ", "-s <size>","Input the test case number and check if there exists a constrained locating array in that size. And show the consists of SMT Language.\n");
                printf("%4s%-15s%s", " ", "-v",       "Show the version.\n");
                printf("%4s%-15s%s", " ", "-h",       "Show the usage.\n");
                return 0;
            default:
                printf("Invalid option, use -h option for help.");
                return 7;

        }

    }
    arg_file_num = optind;

    start = clock();

    char filename[100];
    struct Para_Struct* para_head = NULL;
    struct Cons_Struct* cons_info = NULL;

    strcpy(filename, argv[arg_file_num]);

    struct Para_Struct** para_head_pointer = &para_head;
    struct Cons_Struct** cons_info_pointer = &cons_info;
    Input_Info(filename, para_head_pointer, cons_info_pointer);

    int parameters_num =0;

    int* para_num = & parameters_num;

    int check_result;
    check_result = Yices_Check(para_head, cons_info, test_case_num, para_num, this_mode);

    stop = clock();

    if(check_result == 1){

        printf("Total Runtime: %lf[s]\n",(double)(stop - start)/CLOCKS_PER_SEC);
        return 255;

    }
    if(check_result == -1){

        printf("Total Runtime: %lf[s]\n",(double)(stop - start)/CLOCKS_PER_SEC);
        return 127;

    }


}
