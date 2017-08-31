//
// Created by kinkou on 17/09/01.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "Para_Struct.h"
#include "Val_Struct.h"
#include "Cons_Struct.h"
#include "Input_Info.h"




int Input_Info(char* filename, struct Para_Struct** para_head_pointer, struct Cons_Struct** cons_info_pointer)
{

    FILE* fp;

    fp = fopen(filename, "r");
    int num = errno;


    if (fp == NULL ) {
        printf("Failed to open: %s\n", strerror(num));
        exit(1);
    }

    char sentence[256] = {0};
    int para_num = 0;

    struct Para_Struct* temp = NULL;
    struct Para_Struct* current_point = *para_head_pointer;
    struct Val_Struct* current_point_val = NULL;
    struct Val_Struct* temp_val = NULL;

    fgets(sentence, 256, fp);


    //***************************************************
    //Construct Parameters Structure and Values Structure
    //***************************************************
    while(sentence[0] == '('){

        int sentence_pointer = 0;

        while(sentence[sentence_pointer] != ':'){

            if(sentence[sentence_pointer] == 'p'){

                para_num++;

                temp = (struct Para_Struct*)malloc(sizeof(struct Para_Struct));
                temp->para = para_num;//1,2,3,...

                temp->next = 0;

                if(para_num == 1){

                    *para_head_pointer = temp;
                    current_point = *para_head_pointer;

                }else{

                    current_point->next = temp;
                    current_point = temp;

                }

            }



            sentence_pointer++;

        }

        fgets(sentence, 256, fp);

    }

    int sentence_pointer = 0;

    while(sentence[0] != '('){

        fgets(sentence, 256, fp);

    }

    current_point = *para_head_pointer;
    current_point->val_sum = 0;

    while(sentence[0] == '('){

        sentence_pointer = 0;

        while(sentence[sentence_pointer] != ')' || sentence[sentence_pointer + 1] != ')'){

            if(sentence[sentence_pointer] == '<' && sentence[sentence_pointer + 1] == '='){

                sentence_pointer += 5;


                while(sentence[sentence_pointer - 1] != ' '){

                    sentence_pointer++;

                }
                int temp_pointer = sentence_pointer;
                while(sentence[sentence_pointer] != ')'){

                    sentence_pointer++;

                }
                while(temp_pointer != sentence_pointer){

                    current_point->val_sum = sentence[temp_pointer] - 48 + current_point->val_sum * 10;
                    temp_pointer++;

                }
            }
            sentence_pointer++;

        }
        fgets(sentence, 256, fp);
        current_point = current_point->next;
        if(current_point != NULL)
            current_point->val_sum = 0;

    }


    //set values
    current_point = *para_head_pointer;
    for(; current_point != NULL; current_point = current_point->next){

        int v_sum = current_point->val_sum;

        for(int i = 1; i <= v_sum; i++){

            temp_val = (struct Val_Struct*)malloc(sizeof(struct Val_Struct));
            temp_val->val = i;
            temp_val->next = NULL;

            if(i == 1){

                current_point->val_head = temp_val;
                current_point_val = temp_val;

            }else{

                current_point_val->next = temp_val;
                current_point_val = temp_val;

            }

        }

    }

    while(sentence[0] != '('){

        if(fgets(sentence, 256, fp) == NULL){

            *cons_info_pointer = NULL;
            return 0;

        }

    }
    //***************************************************
    //Construct Constrains Structure
    //***************************************************

    sentence_pointer = 0;
    struct Cons_Struct* current_cons = NULL;
    char para_name[] = {"c0101"};
    int name_pointer = 4;
    int cons_num = 0;
    int cons_char_pointer = 0;
    int temp_pointer = 0;
    int save_pointer_cons = 0;
    int save_pointer_sentence = 0;

    while(1){

        char* controller = 0;
        if(sentence[0] == '('){

            struct Cons_Struct* temp_cons = (struct Cons_Struct*)malloc(sizeof(struct Cons_Struct));
            temp_cons->next = NULL;
            cons_num++;
            while(sentence[sentence_pointer - 2] != 't')
                sentence_pointer++;

            while(sentence[sentence_pointer + 2] != '\0'){

                temp_cons->cons_num = cons_num;

                if(sentence[sentence_pointer] != 'p')
                    temp_cons->this_cons[cons_char_pointer] = sentence[sentence_pointer];
                else{

                    while(sentence[sentence_pointer + 1] != ' '){

                        sentence_pointer++;

                    }
                    temp_pointer = sentence_pointer;
                    while(sentence[temp_pointer] != 'p'){

                        para_name[name_pointer] = sentence[temp_pointer];
                        name_pointer--;
                        temp_pointer--;

                    }


                    strcat(temp_cons->this_cons, para_name);

                    while(temp_cons->this_cons[cons_char_pointer + 1] != '\0'){

                        cons_char_pointer++;

                    }

                    name_pointer = 4;
                    strcpy(para_name, "c0101");

                }

                cons_char_pointer++;
                sentence_pointer++;

            }

            if(*cons_info_pointer == NULL){

                *cons_info_pointer = temp_cons;
                current_cons = temp_cons;

            }else{

                current_cons->next = temp_cons;
                current_cons = temp_cons;

            }

            save_pointer_cons = cons_char_pointer;
            save_pointer_sentence = sentence_pointer;
            controller = fgets(sentence, 256, fp);
            sentence_pointer = 0;
            name_pointer = 4;
            cons_char_pointer = 0;

        }else{

            break;

        }
        if(controller == NULL){

            break;

        }

    }
    current_cons->this_cons[save_pointer_cons] = sentence[save_pointer_sentence];

    fclose(fp);
    return 0;


}

