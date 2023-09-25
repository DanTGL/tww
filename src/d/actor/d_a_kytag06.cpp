/**
* d_a_kytag06.cpp
*/
#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_kankyo_wether.h"
#include "d/d_npc.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

struct kytag06_class : fopAc_ac_c {
public:
    /* 0x290 */ int field_0x290;
    /* 0x294 */ float field_0x294;
};

static const float[] unk = {1.0f, 0.1f, 0.001f, 0.0001};

/* 00000078-00000080       .text daKytag06_Draw__FP13kytag06_class */
static bool daKytag06_Draw(kytag06_class*) {
    return true;
}

/* 00000080-00000194       .text daKytag06_Execute__FP13kytag06_class */
BOOL daKytag06_Execute(kytag06_class* i_this) {
    f32 time;
    int date;

    if (g_dComIfG_gameInfo.play.mEvtCtrl.mMode == 0) {
        return 1;
    }
    if(dComIfGp_evmng_startCheck("ARRIVAL_BRK") == 0) {
        return 1;
    }

    time = dComIfGs_getTime();
    date = dComIfGs_getDate();
    if (time >= 90.0f && time < 345) {
        time += 0.05f;
    }
    dComIfGs_setTime(time);
    dComIfGs_setDate(date);

    dKy_change_colpat(1);
    date = i_this->field_0x294 * 250.0f;
    if (date > g_env_light.mRainCount) {
        dKyw_rain_set(date);
    }
    g_env_light.mThunderEff.mMode = 1;
    cLib_addCalc(&i_this->field_0x294, 1.0f, 0.1f, 0.001f, 0.0001);
    return 1;
}

/* 00000194-0000019C       .text daKytag06_IsDelete__FP13kytag06_class */
static bool daKytag06_IsDelete(kytag06_class*) {
    return true;
}

/* 0000019C-000001A4       .text daKytag06_Delete__FP13kytag06_class */
static bool daKytag06_Delete(kytag06_class*) {
    return true;
}

/* 000001A4-00000224       .text daKytag06_Create__FP10fopAc_ac_c */
static int daKytag06_Create(fopAc_ac_c* i_this) {
    kytag06_class* tag = (kytag06_class*)i_this;
    int var;

    fopAcM_SetupActor(tag, kytag06_class);

    if(dComIfGs_isSymbol(0) != 0) {
        var = 5;
    } else {
        tag->field_0x294 = 0;
        var = 4;
    }

    return var;
}

static actor_method_class l_kytag06__Method = {
    (process_method_func)daKytag06_Execute,
    (process_method_func)daKytag06_Draw,
    (process_method_func)daKytag06_IsDelete,
    (process_method_func)daKytag06_Delete,
    (process_method_func)daKytag06_Create,
};

extern actor_process_profile_definition g_profile_KYTAG06 = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_KYTAG06,
    &g_fpcLf_Method.mBase,
    sizeof(kytag06_class),
    0,
    0,
    &g_fopAc_Method.base,
    0xA6,
    &l_kytag06__Method,
    0x00044000,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};