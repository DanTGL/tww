//
// Generated by dtk
// Translation Unit: d_s_title.cpp
//

#include "f_op/f_op_scene.h"
#include "f_op/f_op_draw_iter.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_op/f_op_msg_mng.h"
#include "f_op/f_op_scene_mng.h"
#include "f_pc/f_pc_leaf.h"
#include "f_pc/f_pc_manager.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/actor/d_a_movie_player.h"

namespace JAInter {
    class BankWave {
    public:
        static bool checkAllWaveLoadStatus();
    };
};

#if VERSION == VERSION_PAL
    #define title_of_scene_class dScnTitle_c
#endif

struct title_of_scene_class : public scene_class {
public:
    /* 0x1C4 */ u32 pad[0x97];
    /* 0x420 */ u32 mMoviePId;

#if VERSION == VERSION_PAL
    static daMP_c* mMp;
#endif
};

#if VERSION == VERSION_PAL
daMP_c* dScnTitle_c::mMp;
#endif

/* 802372F4-80237344       .text dScnTitle_Draw__FP20title_of_scene_class */
BOOL dScnTitle_Draw(title_of_scene_class* i_this) {  
    for (create_tag_class* pTag = fopDwIt_Begin(); pTag != NULL; pTag = fopDwIt_Next(pTag))
        fpcM_Draw(pTag->mpTagData);
    return TRUE;
}

/* 80237344-802374C8       .text dScnTitle_Execute__FP20title_of_scene_class */
BOOL dScnTitle_Execute(title_of_scene_class* i_this) {
    if (!fopOvlpM_IsPeek() && !dComIfG_resetToOpening(i_this)) {
#if VERSION == VERSION_PAL
        daMP_c *movie = dScnTitle_c::mMp;
        if (movie == NULL) {
            s32 rt = fopAcM_SearchByID(i_this->mMoviePId, (fopAc_ac_c**)&movie);
            JUT_ASSERT(0x8a, rt);

            if (movie == NULL)
                return TRUE;

            dScnTitle_c::mMp = movie;
        }
#else
        daMP_c *movie;
        s32 rt = fopAcM_SearchByID(i_this->mMoviePId, (fopAc_ac_c**)&movie);
        JUT_ASSERT(0x83, rt);

        if (movie == NULL)
            return TRUE;
#endif

        if (movie->mpCallBack1 == NULL || movie->mpCallBack2 == NULL)
            return TRUE;

        if (fpcM_GetName(i_this) == PROC_ENDING_SCENE) {
            if (movie->mpCallBack1() == 0) {
                if (dComIfGs_getClearCount() == 0) {
                    fopScnM_ChangeReq(i_this, PROC_NAMEEX_SCENE, 0, 5);
                } else {
                    dComIfG_changeOpeningScene(i_this, PROC_OPENING_SCENE);
                }
                movie->mpCallBack2(0.0f);
            }
        } else {
            if (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_START(0) || movie->mpCallBack1() == 0) {
                dComIfG_changeOpeningScene(i_this, PROC_OPENING_SCENE);
                movie->mpCallBack2(0.0f);
            }
        }
    }
    return TRUE;
}

/* 802374C8-802374D0       .text dScnTitle_IsDelete__FP20title_of_scene_class */
BOOL dScnTitle_IsDelete(title_of_scene_class* i_this) {
    return TRUE;
}

/* 802374D0-802374D8       .text dScnTitle_Delete__FP20title_of_scene_class */
BOOL dScnTitle_Delete(title_of_scene_class* i_this) {
#if VERSION == VERSION_PAL
    dComIfGp_event_remove();
#endif
    return TRUE;
}

/* 802374D8-80237568       .text dScnTitle_Create__FP11scene_class */
s32 dScnTitle_Create(scene_class* i_scn) {
    title_of_scene_class * i_this = (title_of_scene_class*) i_scn;

    if (JAInter::BankWave::checkAllWaveLoadStatus())
        return cPhs_INIT_e;

    dMenu_flagSet(0);
    fopAc_ac_c::setStopStatus(0);
    dComIfGp_offEnableNextStage();
    u32 parameter = fpcM_GetName(i_this) == PROC_TITLE_SCENE ? 0 : 1;

    i_this->mMoviePId = fopAcM_create(PROC_MP, parameter, NULL, -1, NULL, NULL, 0xFF, NULL);

#if VERSION == VERSION_PAL
    dScnTitle_c::mMp = NULL;
    if (fpcM_GetName(i_this) == PROC_ENDING_SCENE) {
        fopMsgM_Create(PROC_MESG, 0, 0);
    }
#endif

    return cPhs_COMPLEATE_e;
}

static scene_method_class l_dScnTitle_Method = {
    (process_method_func)dScnTitle_Create,
    (process_method_func)dScnTitle_Delete,
    (process_method_func)dScnTitle_Execute,
    (process_method_func)dScnTitle_IsDelete,
    (process_method_func)dScnTitle_Draw,
};

extern scene_process_profile_definition g_profile_TITLE_SCENE = {
	fpcLy_ROOT_e,
    1,
    fpcPi_CURRENT_e,
    PROC_TITLE_SCENE,
	&g_fpcNd_Method.mBase,
    sizeof(title_of_scene_class),
    0,
    0,
    &g_fopScn_Method.mBase,
    &l_dScnTitle_Method,
};

extern scene_process_profile_definition g_profile_ENDING_SCENE = {
	fpcLy_ROOT_e,
    1,
    fpcPi_CURRENT_e,
    PROC_ENDING_SCENE,
	&g_fpcNd_Method.mBase,
    sizeof(title_of_scene_class),
    0,
    0,
    &g_fopScn_Method.mBase,
    &l_dScnTitle_Method,
};
