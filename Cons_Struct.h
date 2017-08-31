//
// Created by kinkou on 17/09/01.
//

#ifndef NEWCLA_CONS_STRUCT_H
#define NEWCLA_CONS_STRUCT_H

typedef struct Cons_Struct{

    int cons_num;
    char this_cons[200];

    struct Cons_Struct* next;

}Cons_Struct;

#endif //NEWCLA_CONS_STRUCT_H
