#ifndef D_A_OBJ_ROTEN_H
#define D_A_OBJ_ROTEN_H

#include "f_op/f_op_actor.h"

class daObj_Roten_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}

    void set_mtx();
    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_ROTEN_H */