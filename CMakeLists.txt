cmake_minimum_required(VERSION 3.8)
project(NEWCLA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Check_Dis.c
        Check_Dis.h
        Check_Validity.c
        Check_Validity.h
        Cons_Struct.h
        Dis_Pair.h
        Generate_Set.c
        Generate_Set.h
        Input_Info.c
        Input_Info.h
        Interaction_Set.h
        main.c
        Mode_Enum.h
        Para_Struct.h
        Val_Struct.h
        Valid_Interaction.h
        Yices_Check.c
        Yices_Check.h Array_Construction.c Array_Construction.h)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(NEWCLA ${SOURCE_FILES})
target_link_libraries(NEWCLA yices m)