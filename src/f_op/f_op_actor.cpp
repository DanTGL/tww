//
// Generated by dtk
// Translation Unit: f_op_actor.cpp
//

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_tag.h"
#include "f_op/f_op_draw_tag.h"
#include "f_pc/f_pc_leaf.h"
#include "d/d_demo.h"
#include "d/d_map.h"
#include "d/d_meter.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"

/* 8002330C-800233C4       .text __ct__10fopAc_ac_cFv */
fopAc_ac_c::fopAc_ac_c() {
}

int g_fopAc_type;
u32 fopAc_ac_c::stopStatus;

/* 80023514-80023540       .text fopAc_IsActor__FPv */
s32 fopAc_IsActor(void* pProc) {
    return fpcBs_Is_JustOfType(g_fopAc_type, ((fopAc_ac_c*)pProc)->mAcType);
}

/* 80023540-8002362C       .text fopAc_Draw__FPv */
s32 fopAc_Draw(void* pProc) {
    fopAc_ac_c * actor = (fopAc_ac_c *)pProc;
    s32 ret = TRUE;

    if (!dMenu_flag()) {
        s32 moveApproval = dComIfGp_event_moveApproval(actor);

        if ((moveApproval == 2 || !fopAcM_checkStatus(actor, fopAc_ac_c::stopStatus)) && (!(fopAcM_checkStatus(actor, fopAcStts_CULL_e) && !fopAcM_cullingCheck(actor)) || !fopAcM_checkStatus(actor, fopAcStts_NODRAW_e))) {
            fopAcM_OffCondition(actor, fopAcCnd_NODRAW_e);
            ret = fpcLf_DrawMethod((leafdraw_method_class*)actor->mSubMtd, actor);
        } else {
            fopAcM_OnCondition(actor, fopAcCnd_NODRAW_e);
        }

        fopAcM_OffStatus(actor, fopAcStts_NODRAW_e);

        if (dComIfGp_roomControl_getStayNo() >= 0 && fopAcM_checkStatus(actor, fopAcStts_SHOWMAP_e))
            dMap_c::drawActorPointMiniMap(actor);
    }

    return ret;
}

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)

/* 8002362C-80023BDC       .text fopAc_Execute__FPv */
s32 fopAc_Execute(void* pProc) {
    fopAc_ac_c * actor = (fopAc_ac_c *)pProc;
    s32 ret = TRUE;

    CHECK_FLOAT_CLASS(0x27d, actor->current.pos.x);
    CHECK_FLOAT_CLASS(0x27e, actor->current.pos.y);
    CHECK_FLOAT_CLASS(0x27f, actor->current.pos.z);
    CHECK_VEC3_RANGE(0x286, actor->current.pos);

    if (fopAcM_checkStatus(actor, fopAcStts_NOPAUSE_e) || (!dMenu_flag() && !dScnPly_ply_c::isPause())) {
        actor->mEvtInfo.setCondition(dEvtCnd_NONE_e);

        s32 moveApproval = dComIfGp_event_moveApproval(actor);

        if ((moveApproval == 2 || moveApproval != 0 || !fopAcM_checkStatus(actor, fopAc_ac_c::stopStatus)) && (!fopAcM_checkStatus(actor, fopAcStts_NOCULLEXEC_e) || !fopAcM_CheckCondition(actor, fopAcCnd_NODRAW_e))) {
            fopAcM_OffCondition(actor, fopAcCnd_NOEXEC_e);
            actor->next = actor->current;
            ret = fpcMtd_Execute((process_method_class*)actor->mSubMtd, actor);
        } else {
            fopAcM_OnCondition(actor, fopAcCnd_NOEXEC_e);
        }

        CHECK_FLOAT_CLASS(0x2b4, actor->current.pos.x);
        CHECK_FLOAT_CLASS(0x2b5, actor->current.pos.y);
        CHECK_FLOAT_CLASS(0x2b6, actor->current.pos.z);
        CHECK_VEC3_RANGE(0x2bd, actor->current.pos);
    }

    return ret;
}

/* 80023BDC-80023C30       .text fopAc_IsDelete__FPv */
s32 fopAc_IsDelete(void* pProc) {
    fopAc_ac_c * actor = (fopAc_ac_c *)pProc;
    s32 ret = fpcMtd_IsDelete((process_method_class*)actor->mSubMtd, actor);
    if (ret == 1)
        fopDwTg_DrawQTo(&actor->mDwTg);
    return ret;
}

/* 80023C30-80023CD4       .text fopAc_Delete__FPv */
s32 fopAc_Delete(void* pProc) {
    fopAc_ac_c * actor = (fopAc_ac_c *)pProc;
    s32 ret = fpcMtd_Delete((process_method_class*)actor->mSubMtd, actor);
    if (ret == 1) {
        fopAcTg_ActorQTo(&actor->mAcTg);
        fopDwTg_DrawQTo(&actor->mDwTg);
        fopAcM_DeleteHeap(actor);
        dDemo_actor_c *pDemoActor = dComIfGp_demo_getActor(actor->mDemoActorId);
        if (pDemoActor != NULL)
            pDemoActor->setActor(NULL);
        mDoAud_seDeleteObject(&actor->mEyePos);
        mDoAud_seDeleteObject(&actor->current.pos);
    }
    return ret;
}

/* 80023CD4-80023F78       .text fopAc_Create__FPv */
s32 fopAc_Create(void* pProc) {
    fopAc_ac_c* actor = (fopAc_ac_c*)pProc;

    if (fpcM_IsFirstCreating(actor)) {
        actor_process_profile_definition* profile = (actor_process_profile_definition*)fpcM_GetProfile(pProc);
        actor->mAcType = fpcBs_MakeOfType(&g_fopAc_type);
        actor->mSubMtd = profile->mSubMtd;
        fopAcTg_Init(&actor->mAcTg, actor);
        fopAcTg_ToActorQ(&actor->mAcTg);
        fopDwTg_Init(&actor->mDwTg, actor);
        actor->mStatus = profile->mStatus;
        actor->mGroup = profile->mGroup;
        actor->mCullType = profile->mCullType;

        fopAcM_prm_class* prm = fopAcM_GetAppend(actor);
        if (prm != NULL) {
            fopAcM_SetParam(actor, prm->mParameter);
            actor->orig.pos = prm->mPos;
            actor->orig.angle = prm->mAngle;
            actor->shape_angle = prm->mAngle;
            actor->mParentPcId = prm->mParentPcId;
            actor->mSubtype = prm->mSubtype;
            actor->mGbaName = prm->mGbaName;
            actor->mScale.set(prm->mScale[0] * 0.1f, prm->mScale[1] * 0.1f, prm->mScale[2] * 0.1f);
            actor->mSetId = prm->mSetId;
            actor->orig.roomNo = prm->mRoomNo;
        }

        actor->next = actor->orig;
        actor->current = actor->orig;
        actor->mEyePos = actor->orig.pos;
        actor->mMaxFallSpeed = -100.0f;
        actor->mAttentionInfo.mDistances[0] = 1;
        actor->mAttentionInfo.mDistances[1] = 2;
        actor->mAttentionInfo.mDistances[2] = 3;
        actor->mAttentionInfo.mDistances[3] = 7;
        actor->mAttentionInfo.mDistances[4] = 8;
        actor->mAttentionInfo.mDistances[7] = 15;
        actor->mAttentionInfo.mDistances[5] = 16;
        actor->mAttentionInfo.mDistances[6] = 16;
        actor->mAttentionInfo.mPosition = actor->orig.pos;
        dKy_tevstr_init(&actor->mTevStr, actor->orig.roomNo, 0xFF);
    }

    s32 status = fpcMtd_Create((process_method_class*)actor->mSubMtd, actor);
    if (status == cPhs_COMPLEATE_e) {
        s32 priority = fpcLf_GetPriority(actor);
        fopDwTg_ToDrawQ(&actor->mDwTg, priority);
    }

    return status;
}

actor_method_class g_fopAc_Method = {
    (process_method_func)fopAc_Create,
    (process_method_func)fopAc_Delete,
    (process_method_func)fopAc_Execute,
    (process_method_func)fopAc_IsDelete,
    (process_method_func)fopAc_Draw,
};
