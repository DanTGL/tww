//
// Generated by dtk
// Translation Unit: d_a_mbdoor.cpp
//

#include "f_op/f_op_actor_mng.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "d/actor/d_a_player.h"

class daMbdoor_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    s32 create();
    
    u8 getSwbit();
    u8 getType();
    u8 getShapeType();
    const char* getArcName();
    u32 getFuBdl();
    u32 getLBdl();
    u32 getRBdl();
    u32 getToBdl();
    u32 getDzb();
    f32 getLOffset();
    f32 getROffset();
    f32 getToOffset();
    BOOL CreateHeap();
    void calcMtx();
    BOOL CreateInit();
    s32 getDemoAction();
    void demoProc();
    BOOL checkArea();
    BOOL checkUnlock();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpFuModel;
    /* 0x29C */ J3DModel* mpLModel;
    /* 0x2A0 */ J3DModel* mpRModel;
    /* 0x2A4 */ J3DModel* mpToModel;
    /* 0x2A8 */ dBgW* mpBgW;
    /* 0x2AC */ bool field_0x2ac;
    /* 0x2AD */ u8 field_0x2ad;
    /* 0x2AE */ u8 mCurActionIdx;
    /* 0x2AF */ u8 field_0x2AF[0x2B0 - 0x2AF];
    /* 0x2B0 */ s16 field_0x2b0;
    /* 0x2B2 */ s16 field_0x2b2;
    /* 0x2B4 */ s16 field_0x2b4;
    /* 0x2B6 */ u8 field_0x2b6;
    /* 0x2B7 */ u8 field_0x2B7[0x2B8 - 0x2B7];
    /* 0x2B8 */ s16 field_0x2b8;
    /* 0x2BA */ u8 field_0x2BA[0x2BC - 0x2BA];
    /* 0x2BC */ s32 field_0x2bc;
    /* 0x2C0 */ s32 mEvtStaffId;
    /* 0x2C4 */ cXyz field_0x2c4;
    /* 0x2D0 */ cXyz field_0x2d0;
    /* 0x2DC */ cXyz field_0x2dc;
};

typedef BOOL (daMbdoor_c_ActionFunc)(daMbdoor_c*);

/* 00000078-00000084       .text getSwbit__10daMbdoor_cFv */
u8 daMbdoor_c::getSwbit() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 00000084-00000090       .text getType__10daMbdoor_cFv */
u8 daMbdoor_c::getType() {
    return orig.angle.z & 0x3F;
}

/* 00000090-0000009C       .text getShapeType__10daMbdoor_cFv */
u8 daMbdoor_c::getShapeType() {
    return (fopAcM_GetParam(this) & 0x00000F00) >> 0x08;
}

/* 0000009C-000000E4       .text getArcName__10daMbdoor_cFv */
const char* daMbdoor_c::getArcName() {
    switch (getShapeType()) {
    case 1:
        return "Gbdoor";
    default:
        return "Mbdoor";
    }
}

/* 000000E4-00000120       .text getFuBdl__10daMbdoor_cFv */
u32 daMbdoor_c::getFuBdl() {
    switch (getShapeType()) {
    case 1:
        return 6; // v_gbdfu.bdl
    default:
        return 6; // s_mbdfu.bdl
    }
}

/* 00000120-0000015C       .text getLBdl__10daMbdoor_cFv */
u32 daMbdoor_c::getLBdl() {
    switch (getShapeType()) {
    case 1:
        return 4; // v_gbd_l.bdl
    default:
        return 4; // s_mbd_l.bdl
    }
}

/* 0000015C-00000198       .text getRBdl__10daMbdoor_cFv */
u32 daMbdoor_c::getRBdl() {
    switch (getShapeType()) {
    case 1:
        return 5; // v_gbd_r.bdl
    default:
        return 5; // s_mbd_r.bdl
    }
}

/* 00000198-000001D4       .text getToBdl__10daMbdoor_cFv */
u32 daMbdoor_c::getToBdl() {
    switch (getShapeType()) {
    case 1:
        return 7; // v_gbdto.bdl
    default:
        return 7; // s_mbdto.bdl
    }
}

/* 000001D4-00000210       .text getDzb__10daMbdoor_cFv */
u32 daMbdoor_c::getDzb() {
    switch (getShapeType()) {
    case 1:
        return 0xA; // gbd.dzb
    default:
        return 0xA; // s_mbdfu.dzb
    }
}

/* 00000210-00000254       .text getLOffset__10daMbdoor_cFv */
f32 daMbdoor_c::getLOffset() {
    switch (getShapeType()) {
    case 1:
        return -300.0f;
    default:
        return -255.0f;
    }
}

/* 00000254-00000298       .text getROffset__10daMbdoor_cFv */
f32 daMbdoor_c::getROffset() {
    switch (getShapeType()) {
    case 1:
        return 300.0f;
    default:
        return 277.0f;
    }
}

/* 00000298-000002DC       .text getToOffset__10daMbdoor_cFv */
f32 daMbdoor_c::getToOffset() {
    switch (getShapeType()) {
    case 1:
        return 335.0f;
    default:
        return 300.0f;
    }
}

/* 000002DC-000002FC       .text CheckCreateHeap__FP10fopAc_ac_c */
BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daMbdoor_c*)i_this)->CreateHeap();
}

/* 000002FC-0000060C       .text CreateHeap__10daMbdoor_cFv */
BOOL daMbdoor_c::CreateHeap() {
    void* modelData = dComIfG_getObjectRes(getArcName(), getFuBdl());
    JUT_ASSERT(198, modelData != 0)
    mpFuModel = mDoExt_J3DModel__create((J3DModelData*)modelData, 0x80000, 0x11000022);
    if (!mpFuModel) { return FALSE; }
    
    modelData = dComIfG_getObjectRes(getArcName(), getLBdl());
    JUT_ASSERT(209, modelData != 0)
    mpLModel = mDoExt_J3DModel__create((J3DModelData*)modelData, 0x80000, 0x11000022);
    if (!mpLModel) { return FALSE; }
    
    modelData = dComIfG_getObjectRes(getArcName(), getRBdl());
    JUT_ASSERT(220, modelData != 0)
    mpRModel = mDoExt_J3DModel__create((J3DModelData*)modelData, 0x80000, 0x11000022);
    if (!mpRModel) { return FALSE; }
    
    modelData = dComIfG_getObjectRes(getArcName(), getToBdl());
    JUT_ASSERT(231, modelData != 0)
    mpToModel = mDoExt_J3DModel__create((J3DModelData*)modelData, 0x80000, 0x11000022);
    if (!mpToModel) { return FALSE; }
    
    mpBgW = new dBgW();
    if (!mpBgW) { return FALSE; }
    cBgD_t* dzbData = (cBgD_t*)dComIfG_getObjectRes(getArcName(), getDzb());
    if (!dzbData) { return FALSE; }
    calcMtx();
    bool error = mpBgW->Set(dzbData, 1, &mpFuModel->getBaseTRMtx());
    return error != true ? TRUE : FALSE;
}

/* 0000060C-00000898       .text calcMtx__10daMbdoor_cFv */
void daMbdoor_c::calcMtx() {
    // Transform the door's frame.
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(orig.angle.y);
    mpFuModel->setBaseTRMtx(mDoMtx_stack_c::now);
    
    cXyz offset;
    offset.set(0.0f, 0.0f, -150.0f);
    mDoMtx_stack_c::multVec(&offset, &field_0x2d0);
    offset.set(0.0f, 0.0f, -400.0f);
    mDoMtx_stack_c::multVec(&offset, &field_0x2dc);
    
    // Transform door's right half.
    if (field_0x2ad == 0) {
        mpLModel->setBaseTRMtx(mDoMtx_stack_c::now);
        if (field_0x2b2) {
            mDoMtx_stack_c::transM(getROffset(), 0.0f, 0.0f);
            mDoMtx_stack_c::YrotM(field_0x2b2);
            mDoMtx_stack_c::transM(-getROffset(), 0.0f, 0.0f);
        }
        offset.set(80.0f, 0.0f, 75.0f);
        mDoMtx_stack_c::multVec(&offset, &field_0x2c4);
    }
    mpRModel->setBaseTRMtx(mDoMtx_stack_c::now);
    
    // Transform door's left half.
    if (field_0x2ad == 1) {
        if (field_0x2b2) {
            mDoMtx_stack_c::transM(getLOffset(), 0.0f, 0.0f);
            mDoMtx_stack_c::YrotM(-field_0x2b2);
            mDoMtx_stack_c::transM(-getLOffset(), 0.0f, 0.0f);
        }
        offset.set(-80.0f, 0.0f, 75.0f);
        mDoMtx_stack_c::multVec(&offset, &field_0x2c4);
        mpLModel->setBaseTRMtx(mDoMtx_stack_c::now);
    }
    
    // Transform door's bar.
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(orig.angle.y);
    if (field_0x2b0) {
        mDoMtx_stack_c::transM(getToOffset(), 231.0f, 0.0f);
        mDoMtx_stack_c::ZrotM(field_0x2b0);
        mDoMtx_stack_c::transM(-getToOffset(), -231.0f, 0.0f);
    }
    mpToModel->setBaseTRMtx(mDoMtx_stack_c::now);
}

/* 00000898-00000A44       .text CreateInit__10daMbdoor_cFv */
BOOL daMbdoor_c::CreateInit() {
    s32 swbit = getSwbit();
    s32 type = getType();
    
    if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
        JUT_ASSERT(334, 0);
    }
    field_0x2ac = true;
    mTevStr.mRoomNo = current.roomNo;
    
    if (type == 2) {
        mCurActionIdx = 1;
        field_0x2b0 = 0;
        field_0x2b2 = 0;
    } else if ((type == 0 && (swbit != 0xFF && !dComIfGs_isSwitch(swbit, fopAcM_GetRoomNo(this))))
            || (type == 1 && (swbit == 0xFF || dComIfGs_isSwitch(swbit, fopAcM_GetRoomNo(this))))) {
        mCurActionIdx = 1;
        field_0x2b0 = 0;
        field_0x2b2 = 0;
    } else {
        mCurActionIdx = 4;
        field_0x2b0 = -0x3F65;
        field_0x2b2 = 0;
    }
    
    field_0x2bc = 30;
    mAttentionInfo.mPosition.y += 250.0f;
    mEyePos.y += 250.0f;
    mAttentionInfo.mFlags = 0x20;
    calcMtx();
    mpBgW->Move();
    mStatus = mStatus & ~0x3F | 0x2B;
    
    return TRUE;
}

/* 00000A44-00000AF4       .text create__10daMbdoor_cFv */
s32 daMbdoor_c::create() {
    s32 phase_state = dComIfG_resLoad(&mPhs, getArcName());
    
    fopAcM_SetupActor(this, daMbdoor_c);
    
    if (phase_state != cPhs_COMPLEATE_e) {
        return phase_state;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x8200)) {
        return cPhs_ERROR_e;
    }
    
    CreateInit();
    
    return cPhs_COMPLEATE_e;
}

/* 00000AF4-00000B3C       .text getDemoAction__10daMbdoor_cFv */
s32 daMbdoor_c::getDemoAction() {
    static char* action_table[] = {
        "WAIT",
        "SET_START",
        "SET_ANGLE",
        "END",
        "OPEN",
        "STOP_OPEN",
        "SET_GOAL",
        "SET_GOAL2",
        "ADJUSTMENT",
    };
    
    return dComIfGp_evmng_getMyActIdx(mEvtStaffId, action_table, 9, 0, 0);
}

/* 00000B3C-00000F78       .text demoProc__10daMbdoor_cFv */
void daMbdoor_c::demoProc() {
    // Explicit cast from daPy_py_c to daPy_py_c necessary for matching regalloc.
    daPy_py_c* player = (daPy_py_c*)daPy_getPlayerActorClass();
    s32 actIdx = getDemoAction();
    cXyz goal;
    s16 angle;
    
    if (dComIfGp_evmng_getIsAddvance(mEvtStaffId)) {
        switch (actIdx) {
        case 1:
            calcMtx();
            goal = field_0x2c4;
            dComIfGp_evmng_setGoal(&goal);
            break;
        case 2:
            angle = current.angle.y + 0x7FFF;
            player->changeDemoMoveAngle(angle);
            break;
        case 4:
            fopAcM_seStart(this, JA_SE_OBJ_MJ_GATE_OPEN, 0);
            field_0x2b4 = 0;
            break;
        case 5:
            fopAcM_seStart(this, JA_SE_OBJ_MJ_GATE_BAR_OPEN, 0);
            field_0x2b4 = 0;
            field_0x2b6 = 1;
            break;
        case 6:
            goal = field_0x2d0;
            dComIfGp_evmng_setGoal(&goal);
            break;
        case 7:
            goal = field_0x2dc;
            dComIfGp_evmng_setGoal(&goal);
            break;
        case 8:
            calcMtx();
            field_0x2b8 = 0;
            u32* timerP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Timer");
            if (timerP) {
                field_0x2b8 = *timerP;
            }
            break;
        }
    }
    
    switch (actIdx) {
    case 3:
        break;
    case 4:
        if (field_0x2b4 < 250) {
            field_0x2b4 += 50;
        }
        s32 temp = field_0x2b2 - field_0x2b4;
        if (temp < -0x1C71) {
            field_0x2b2 = -0x1C71;
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        } else {
            field_0x2b2 = temp;
        }
        calcMtx();
        if (field_0x2ad) {
            angle = current.angle.y + 0x7FFF - field_0x2b2;
        } else {
            angle = current.angle.y + 0x7FFF + field_0x2b2;
        }
        player->setPlayerPosAndAngle(&field_0x2c4, angle);
        break;
    case 5:
        if (field_0x2b6) {
            if (field_0x2b4 < 400) {
                field_0x2b4 += 40;
            }
            temp = field_0x2b0 - field_0x2b4;
            if (temp < -0x3F65) {
                field_0x2b0 = -0x3F65;
                dComIfGp_evmng_cutEnd(mEvtStaffId);
                field_0x2b6 = 0;
                fopAcM_seStart(this, JA_SE_OBJ_MJ_GATE_BAR_STOP, 0);
            } else {
                field_0x2b0 = temp;
            }
            calcMtx();
        } else {
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        break;
    case 8:
        angle = player->shape_angle.y;
        cLib_addCalcAngleS2(&angle, current.angle.y + 0x7FFF, 10, 0x800);
        goal = player->current.pos;
        goal.x = goal.x*0.9f + field_0x2c4.x*0.1f;
        goal.z = goal.z*0.9f + field_0x2c4.z*0.1f;
        player->setPlayerPosAndAngle(&goal, angle);
        if (field_0x2b8 > 0) {
            field_0x2b8--;
        } else {
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        break;
    default:
        dComIfGp_evmng_cutEnd(mEvtStaffId);
        break;
    }
}

/* 00000F78-000010CC       .text checkArea__10daMbdoor_cFv */
BOOL daMbdoor_c::checkArea() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz relPos1 = player->current.pos - orig.pos;
    cXyz relPos2 = relPos1;
    relPos2.x = relPos1.z * cM_ssin(current.angle.y) - relPos1.x * cM_scos(current.angle.y);
    relPos2.z = relPos1.z * cM_scos(current.angle.y) + relPos1.x * cM_ssin(current.angle.y);
    
    if (relPos2.z > 160.0f) {
        return FALSE;
    }
    if (relPos2.x > 200.0f || relPos2.x < -200.0f) {
        return FALSE;
    }
    if (fopAcM_seenActorAngleY(player, this) > 0x2000) {
        return FALSE;
    }
    
    if (relPos2.x > 0.0f) {
        field_0x2ad = 1;
    } else {
        field_0x2ad = 0;
    }
    
    return TRUE;
}

/* 000010CC-00001198       .text checkUnlock__10daMbdoor_cFv */
BOOL daMbdoor_c::checkUnlock() {
    s32 swbit = getSwbit();
    switch (getType()) {
    case 0:
        return dComIfGs_isSwitch(swbit, fopAcM_GetRoomNo(this));
    case 1:
        if (!fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this))) {
            if (field_0x2bc > 0) {
                field_0x2bc--;
            } else {
                if (swbit != 0xFF) {
                    dComIfGs_onSwitch(swbit, fopAcM_GetRoomNo(this));
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 00001198-000011BC       .text daMbdoor_actionWait__FP10daMbdoor_c */
BOOL daMbdoor_actionWait(daMbdoor_c* i_this) {
    i_this->calcMtx();
    return TRUE;
}

/* 000011BC-0000121C       .text daMbdoor_actionLockWait__FP10daMbdoor_c */
BOOL daMbdoor_actionLockWait(daMbdoor_c* i_this) {
    if (i_this->checkUnlock()) {
        i_this->mCurActionIdx = 2;
        fopAcM_orderOtherEvent2(i_this, "MBDOOR_STOP_OPEN", 1, -1);
    }
    return TRUE;
}

/* 0000121C-000012AC       .text daMbdoor_actionLockOff__FP10daMbdoor_c */
BOOL daMbdoor_actionLockOff(daMbdoor_c* i_this) {
    if (i_this->mEvtInfo.checkCommandDemoAccrpt()) {
        i_this->mEvtStaffId = dComIfGp_evmng_getMyStaffId("MBDOOR", NULL, 0);
        i_this->demoProc();
        i_this->mCurActionIdx = 3;
    } else {
        fopAcM_orderOtherEvent2(i_this, "MBDOOR_STOP_OPEN", 1, -1);
    }
    return TRUE;
}

/* 000012AC-00001324       .text daMbdoor_actionLockDemo__FP10daMbdoor_c */
BOOL daMbdoor_actionLockDemo(daMbdoor_c* i_this) {
    if (dComIfGp_evmng_endCheck("MBDOOR_STOP_OPEN")) {
        dComIfGp_event_reset();
        i_this->mCurActionIdx = 4;
    } else {
        i_this->demoProc();
    }
    return TRUE;
}

/* 00001324-000013E4       .text daMbdoor_actionCloseWait__FP10daMbdoor_c */
BOOL daMbdoor_actionCloseWait(daMbdoor_c* i_this) {
    if (i_this->mEvtInfo.checkCommandDoor()) {
        i_this->mEvtStaffId = dComIfGp_evmng_getMyStaffId("MBDOOR", NULL, 0);
        i_this->demoProc();
        i_this->mCurActionIdx = 5;
        dComIfG_Bgsp()->Release(i_this->mpBgW);
        i_this->field_0x2ac = false;
    } else {
        if (i_this->checkArea()) {
            i_this->mEvtInfo.setEventName("MBDOOR_OPEN");
            i_this->mEvtInfo.onCondition(dEvtCnd_CANDOOR_e);
        }
    }
    return TRUE;
}

/* 000013E4-00001408       .text daMbdoor_actionOpen__FP10daMbdoor_c */
BOOL daMbdoor_actionOpen(daMbdoor_c* i_this) {
    i_this->demoProc();
    return TRUE;
}

BOOL daMbdoor_c::draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &mTevStr);
    
    g_env_light.setLightTevColorType(mpFuModel, &mTevStr);
    mDoExt_modelUpdateDL(mpFuModel);
    
    g_env_light.setLightTevColorType(mpLModel, &mTevStr);
    mDoExt_modelUpdateDL(mpLModel);
    
    g_env_light.setLightTevColorType(mpRModel, &mTevStr);
    mDoExt_modelUpdateDL(mpRModel);
    
    g_env_light.setLightTevColorType(mpToModel, &mTevStr);
    mDoExt_modelUpdateDL(mpToModel);
    
    return TRUE;
}

/* 00001408-000014BC       .text daMbdoor_Draw__FP10daMbdoor_c */
BOOL daMbdoor_Draw(daMbdoor_c* i_this) {
    return i_this->draw();
}

BOOL daMbdoor_c::execute() {
    static daMbdoor_c_ActionFunc* l_action[] = {
        &daMbdoor_actionWait,
        &daMbdoor_actionLockWait,
        &daMbdoor_actionLockOff,
        &daMbdoor_actionLockDemo,
        &daMbdoor_actionCloseWait,
        &daMbdoor_actionOpen,
    };
    
    dDemo_actor_c* demoActor = dComIfGp_demo_getActor(mDemoActorId);
    if (demoActor) {
        field_0x2ad = 0;
        if (demoActor->checkEnable(0x8)) {
            field_0x2b2 = demoActor->getRatate()->y;
            field_0x2b0 = demoActor->getRatate()->z;
        }
        calcMtx();
    } else {
        (l_action[mCurActionIdx])(this);
    }
    return TRUE;
}

/* 000014BC-00001558       .text daMbdoor_Execute__FP10daMbdoor_c */
BOOL daMbdoor_Execute(daMbdoor_c* i_this) {
    return i_this->execute();
}

/* 00001558-00001560       .text daMbdoor_IsDelete__FP10daMbdoor_c */
BOOL daMbdoor_IsDelete(daMbdoor_c* i_this) {
    return TRUE;
}

/* 00001560-000015D4       .text daMbdoor_Delete__FP10daMbdoor_c */
BOOL daMbdoor_Delete(daMbdoor_c* i_this) {
    if (i_this->heap) {
        dComIfG_Bgsp()->Release(i_this->mpBgW);
    }
    dComIfG_resDelete(&i_this->mPhs, i_this->getArcName());
    i_this->~daMbdoor_c();
    return TRUE;
}

/* 000015D4-000015F4       .text daMbdoor_Create__FP10fopAc_ac_c */
s32 daMbdoor_Create(fopAc_ac_c* i_this) {
    return ((daMbdoor_c*)i_this)->create();
}

static actor_method_class l_daMbdoor_Method = {
    (process_method_func)daMbdoor_Create,
    (process_method_func)daMbdoor_Delete,
    (process_method_func)daMbdoor_Execute,
    (process_method_func)daMbdoor_IsDelete,
    (process_method_func)daMbdoor_Draw,
};

extern actor_process_profile_definition g_profile_MBDOOR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 3,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MBDOOR,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daMbdoor_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0132,
    /* Actor SubMtd */ &l_daMbdoor_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
