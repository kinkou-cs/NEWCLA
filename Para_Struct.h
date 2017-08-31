//
// Created by kinkou on 17/09/01.
//

#ifndef NEWCLA_PARA_STRUCT_H
#define NEWCLA_PARA_STRUCT_H

typedef struct Para_Struct{

    int para;
    int val_sum;

    struct Val_Struct* val_head;
    struct Para_Struct* next;

}Para_Struct;

#endif //NEWCLA_PARA_STRUCT_H
