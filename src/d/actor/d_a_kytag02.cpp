//
// Generated by dtk
// Translation Unit: d_a_kytag02.cpp
//

#include "d/actor/d_a_kytag02.h"
#include "d/d_procname.h"

/* 00000078-000000C0       .text set_path_info__FP10fopAc_ac_c */
void set_path_info(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000C0-000000F0       .text set_next_path_info__FP13kytag02_classP5dPath */
void set_next_path_info(kytag02_class*, dPath*) {
    /* Nonmatching */
}

/* 000000F0-0000017C       .text get_railwind_vec__FP5dPathi */
void get_railwind_vec(dPath*, int) {
    /* Nonmatching */
}

/* 0000017C-000002E8       .text get_nearpos_rail__FP13kytag02_classP5dPathP4cXyzPi */
void get_nearpos_rail(kytag02_class*, dPath*, cXyz*, int*) {
    /* Nonmatching */
}

/* 000002E8-000003D4       .text windtag_move__FP13kytag02_class */
void windtag_move(kytag02_class*) {
    /* Nonmatching */
}

/* 000003D4-000003DC       .text daKytag02_Draw__FP13kytag02_class */
static BOOL daKytag02_Draw(kytag02_class*) {
    /* Nonmatching */
}

/* 000003DC-00000400       .text daKytag02_Execute__FP13kytag02_class */
static BOOL daKytag02_Execute(kytag02_class*) {
    /* Nonmatching */
}

/* 00000400-00000408       .text daKytag02_IsDelete__FP13kytag02_class */
static BOOL daKytag02_IsDelete(kytag02_class*) {
    /* Nonmatching */
}

/* 00000408-00000420       .text daKytag02_Delete__FP13kytag02_class */
static BOOL daKytag02_Delete(kytag02_class*) {
    /* Nonmatching */
}

/* 00000420-0000047C       .text daKytag02_Create__FP10fopAc_ac_c */
static s32 daKytag02_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daKytag02_Method = {
    (process_method_func)daKytag02_Create,
    (process_method_func)daKytag02_Delete,
    (process_method_func)daKytag02_Execute,
    (process_method_func)daKytag02_IsDelete,
    (process_method_func)daKytag02_Draw,
};

actor_process_profile_definition g_profile_KYTAG02 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KYTAG02,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kytag02_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00A2,
    /* Actor SubMtd */ &l_daKytag02_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
