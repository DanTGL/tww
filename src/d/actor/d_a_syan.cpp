//
// Generated by dtk
// Translation Unit: d_a_syan.cpp
//

#include "d/actor/d_a_syan.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"

/* 000000EC-000002D4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000310-00000440       .text syan_draw__FP10syan_class */
void syan_draw(syan_class*) {
    /* Nonmatching */
}

/* 00000440-000004AC       .text daSyan_Draw__FP10syan_class */
static BOOL daSyan_Draw(syan_class*) {
    /* Nonmatching */
}

/* 000004AC-00000CA0       .text daSyan_Execute__FP10syan_class */
static BOOL daSyan_Execute(syan_class*) {
    /* Nonmatching */
}

/* 00000CA0-00000CA8       .text daSyan_IsDelete__FP10syan_class */
static BOOL daSyan_IsDelete(syan_class*) {
    /* Nonmatching */
}

/* 00000CA8-00000D1C       .text daSyan_Delete__FP10syan_class */
static BOOL daSyan_Delete(syan_class*) {
    /* Nonmatching */
}

/* 00000D1C-00000E10       .text daSyan_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSyan_solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000E10-00000FE0       .text daSyan_Create__FP10fopAc_ac_c */
static s32 daSyan_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daSyan_Method = {
    (process_method_func)daSyan_Create,
    (process_method_func)daSyan_Delete,
    (process_method_func)daSyan_Execute,
    (process_method_func)daSyan_IsDelete,
    (process_method_func)daSyan_Draw,
};

actor_process_profile_definition g_profile_SYAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SYAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(syan_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00EF,
    /* Actor SubMtd */ &l_daSyan_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
