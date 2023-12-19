//
// Generated by dtk
// Translation Unit: d_a_ghostship.cpp
//

#include "d/actor/d_a_ghostship.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "SSystem/SComponent/c_math.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_kankyo_wether.h"

enum AYUSH_RES_FILE_ID { // IDs and indexes are synced
    /* BDLM */
    AYUSH_BDL_AYUSH=0x5,
    
    /* BTK */
    AYUSH_BTK_AYUSH=0x8,
    
    /* TEX */
    AYUSH_BTI_B_GSHIP_HATA=0xB,
    AYUSH_BTI_B_GSHIP_HO=0xC,
};

// Needed for .data to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

const u32 daGhostship_c::m_heapsize = 0x1EA0;
const char daGhostship_c::m_arc_name[] = "Ayush";
const char daGhostship_c::m_cloth_arc_name[] = "Cloth";

static daGhostship_HIO_c l_HIO;

/* 000000EC-000000F8 .text daGhostship_SailVtxFactorCB__FP15dCloth_packet_cii */
static int daGhostship_SailVtxFactorCB(dCloth_packet_c*, int, int param_3) {
    return param_3 ? 0 : 1;
}

/* 000000F8-00000118 .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daGhostship_c*>(i_this)->_createHeap();
}

/* 00000118-0000032C .text _createHeap__13daGhostship_cFv */
BOOL daGhostship_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, AYUSH_BDL_AYUSH));
    JUT_ASSERT(88, modelData != 0);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if(!mpModel) {
        return false;
    }

    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, AYUSH_BTK_AYUSH));
    JUT_ASSERT(95, btk != 0);

    if(!mBtk.init(modelData, btk, true, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0)) {
        return false;
    }

    ResTIMG* res1 = static_cast<ResTIMG*>(dComIfG_getObjectRes(m_arc_name, AYUSH_BTI_B_GSHIP_HATA));
    ResTIMG* res2 = static_cast<ResTIMG*>(dComIfG_getObjectRes(m_arc_name, AYUSH_BTI_B_GSHIP_HO));
    ResTIMG* res3 = static_cast<ResTIMG*>(dComIfG_getObjectRes(m_cloth_arc_name, CLOTH_BTI_CLOTHTOON));

    mpCloth = dCloth_packetXlu_create(res1, res3, 5, 5, 700.0f, 350.0f, &mTevStr, 0);
    mpCloth2 = dCloth_packetXlu_create(res2, res3, 6, 6, 1800.0f, 1000.0f, &mTevStr, 0);
    if(!mpCloth || !mpCloth2) {
        return false;
    }

    mpCloth2->setFactorCheckCB(&daGhostship_SailVtxFactorCB);

    return true;
}

/* 0000032C-00000368 .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
static BOOL pathMove_CB(cXyz* curPos, cXyz* curPntPos, cXyz* nextPntPos, void* i_this) {
    return static_cast<daGhostship_c*>(i_this)->_pathMove(curPos, curPntPos, nextPntPos);
}

/* 00000368-000003B8 .text __ct__17daGhostship_HIO_cFv */
daGhostship_HIO_c::daGhostship_HIO_c() {
    field_0x04 = 0;
    hideShip = false;
    shipAlpha = 0.51f;
    field_0x0C = 5.0f;
    shipHideDist = 3000.0f;
    shipEnterDist = 1500.0f;
}

/* 00000400-000004CC .text pathMove__13daGhostship_cFv */
void daGhostship_c::pathMove() {
    cLib_addCalc2(&speedF, mPathSpeed, 0.1f, 2.0f);
    dLib_pathMove(&mPathPos, &mPathPntNo, mPath, speedF, &pathMove_CB, this);
    cLib_addCalcPosXZ2(&current.pos, mPathPos, g_regHIO.mChild[12].mFloatRegs[0] + 0.01f, speedF);
    if(speedF != 0.0f && mPathSpeed != 0.0f) {
        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mPathPos), 8, 0x100);
    }
}

/* 000004CC-000004D8 .text modeWaitInit__13daGhostship_cFv */
void daGhostship_c::modeWaitInit() {
    mMode = 0;
}

/* 000004D8-000004DC .text modeWait__13daGhostship_cFv */
void daGhostship_c::modeWait() {
    return;
}

/* 000004DC-000004E0 .text modeRealize__13daGhostship_cFv */
void daGhostship_c::modeRealize() {
    return;
}

/* 000004E0-00000770 .text _pathMove__13daGhostship_cFP4cXyzP4cXyzP4cXyz */
BOOL daGhostship_c::_pathMove(cXyz* curPos, cXyz* p_curPntPos, cXyz* p_nextPntPos) {
    mCurPntPos = *p_curPntPos;
    mCurPntPos.y = current.pos.y;
    mNextPntPos = *p_nextPntPos;
    mNextPntPos.y = current.pos.y;

    cXyz delta = mNextPntPos - mCurPntPos;
    if(!delta.normalizeRS()) {
        return TRUE;
    }

    s16 targetAngleY = cM_atan2s(delta.x, delta.z);
    s16 angleLeftToTarget = cLib_addCalcAngleS(&current.angle.y, targetAngleY, 8, 0x200, 8);
    f32 step = speedF * fabsf(cM_scos(angleLeftToTarget));
    cLib_chasePosXZ(curPos, mNextPntPos, step);
    if((*curPos - mNextPntPos).absXZ() < step * (g_regHIO.mChild[12].mFloatRegs[5] + 1.0f) || (*curPos - mNextPntPos).absXZ() == 0.0f) {
        return TRUE;
    }

    return FALSE;
}

/* 00000770-0000077C .text modePathMoveInit__13daGhostship_cFv */
void daGhostship_c::modePathMoveInit() {
    mMode = 2;
}

/* 0000077C-000007D0       .text modePathMove__13daGhostship_cFv */
void daGhostship_c::modePathMove() {
    if(pathId != 0xFF) {
        mPathSpeed = 10.0f;
        pathMove();
    }

    current.pos.y = dLib_getWaterY(current.pos, mAcch);
}

/* 000007D0-00000874 .text modeProcCall__13daGhostship_cFv */
void daGhostship_c::modeProcCall() {
    typedef void(daGhostship_c::*ProcFunc)(void);
    static const ProcFunc mode_proc[] = {
        &daGhostship_c::modeWait,
        &daGhostship_c::modeRealize,
        &daGhostship_c::modePathMove
    };

    (this->*mode_proc[mMode])();
}

// probably unused/debug colors or something
static const u32 dummy[] = {
    0x0000FF80,
    0xFF000080,
    0xFF000080,
    0xFF000080,
    0x00FF0080,
    0x0000FF80,
    0x0000FF80,
    0x0000FF80,
};
static u32 dummyFunc() {
    return dummy[0];
}

/* 00000874-00000C78 .text createInit__13daGhostship_cFv */
void daGhostship_c::createInit() {
    mPathPos = current.pos;

    for(int i = 0; i < 0xC; i++) {
        mPaths[i].mAngle = 0x2000 * i;

        s32 temp2 = 1;
        f32 temp3 = 600.0f * cM_scos(mPaths[i].mAngle + mPaths[i].mAngleSpeed);
        if(i % 2 == 1) {
            temp2 = -1;
            temp3 = 600.0f * cM_ssin(mPaths[i].mAngle + mPaths[i].mAngleSpeed);
        }

        mPaths[i].mRadius = 100.0f * i;

        f32 temp4 = 500.0f + g_regHIO.mChild[12].mFloatRegs[10];
        mPaths[i].mWobbleAmplitude = 300.0f + g_regHIO.mChild[12].mFloatRegs[1];
        mPaths[i].mAngleSpeed = temp2 * (0x100 + g_regHIO.mChild[12].mShortRegs[0] + 0x10 * i + cM_rndF(100.0f));
        mPaths[i].mTranslation.x = current.pos.x + temp4 * cM_ssin(shape_angle.y);
        mPaths[i].mTranslation.y = 600.0f + current.pos.y + temp3 + cM_rndF(100.0f);
        mPaths[i].mTranslation.z = current.pos.z + temp4 * cM_scos(shape_angle.y);

        dLib_setCirclePath(&mPaths[i]);
    }

    if(pathId != 0xFF) {
        mPath = dPath_GetRoomPath(pathId, fopAcM_GetRoomNo(this));
        modePathMoveInit();
    }
    else {
        modeWaitInit();
    }

    mCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&fopAcM_GetPosition_p(this), &fopAcM_GetOldPosition_p(this), this, 1, &mCir, &fopAcM_GetSpeed_p(this));
    mAcch.SetWallNone();
    mAcch.SetRoofNone();
    dLib_waveRot(&current.pos, 0.0f, &mWave);

    shape_angle.x = mWave.mRotX;
    shape_angle.z = mWave.mRotZ;

    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());

    mDoMtx_stack_c::push();
    mDoMtx_stack_c::transM(0.0f, 3200.0f, 75.0f);
    mpCloth->setMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::pop();
    mDoMtx_stack_c::transM(-900.0f, 2080.0f, 85.0f);
    mDoMtx_stack_c::YrotM(0x4000);
    mpCloth2->setMtx(mDoMtx_stack_c::get());
}

/* 00000C78-00000C8C .text getArg__13daGhostship_cFv */
void daGhostship_c::getArg() {
    u32 param = fopAcM_GetParam(this);
    pathId = fopAcM_GetParamBit(param, 0x10, 8);
    moonPhase = fopAcM_GetParamBit(param, 0, 8);
}

/* 00000C8C-00000DFC .text daGhostshipCreate__FPv */
static s32 daGhostshipCreate(void* i_actor) {
    daGhostship_c* i_this = static_cast<daGhostship_c*>(i_actor);
    fopAcM_SetupActor(i_this, daGhostship_c);

    s32 result = dComIfG_resLoad(&i_this->mPhs, daGhostship_c::m_arc_name);
    if(result != cPhs_COMPLEATE_e) {
        return result;
    }

    result = dComIfG_resLoad(&i_this->mClothPhs, daGhostship_c::m_cloth_arc_name);
    if(result != cPhs_COMPLEATE_e) {
        return result;
    }

    i_this->getArg();
    if((s32)dComIfGs_getEventReg(0x8803) == 3) {
        return cPhs_ERROR_e;
    }

    if (!fopAcM_entrySolidHeap(i_this, createHeap_CB, 0x1EA0)) {
        return cPhs_ERROR_e;
    }

    i_this->createInit();

    return cPhs_COMPLEATE_e;
}

/* 00000FD8-00001024 .text daGhostshipDelete__FPv */
static BOOL daGhostshipDelete(void* i_actor) {
    daGhostship_c* i_this = static_cast<daGhostship_c*>(i_actor);

    dComIfG_resDelete(&i_this->mPhs, daGhostship_c::m_arc_name);
    dComIfG_resDelete(&i_this->mClothPhs, daGhostship_c::m_cloth_arc_name);

    return true;
}

/* 00001024-00001048 .text daGhostshipExecute__FPv */
static BOOL daGhostshipExecute(void* i_this) {
    return static_cast<daGhostship_c*>(i_this)->_execute();
}

/* 00001048-0000182C .text _execute__13daGhostship_cFv */
bool daGhostship_c::_execute() {
    f32 time = dComIfGs_getTime();
    f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));

    mbCanEnterShip = false;
    if(moonPhase != dKy_moon_type_chk() || (time > 90.0f && time < 285.0f)) {
        dKy_pship_existense_cut();
        mAlpha = 0.0f;
    }
    else {
        dKy_pship_existense_set();
        f32 targetAlpha;
        if(dist < l_HIO.shipHideDist) {
            targetAlpha = 0.0f;
        }
        else {
            targetAlpha = l_HIO.shipAlpha;
        }

        if(dComIfGs_isOpenCollectMap(0x24) && dComIfGs_isGetCollectMap(0x24)) {
            mbCanEnterShip = 1;
            targetAlpha = l_HIO.shipAlpha;
        }

        cLib_chaseF(&mAlpha, targetAlpha, 0.02f);
    }

    if(mAlpha == 0.0f) {
        fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e | 0x3);
    }
    else {
        fopAcM_seStart(this, JA_SE_CV_YUUREISEN_SONG, 0);
        fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e | 0x3);
    }

    for(int i = 0; i < 0xC; i++) {
        if(mPaths[i].mRadius < 900.0f) {
            field_0x6C4[i] = i * 100.0f + 1500.0f;
        }
        else {
            if(mPaths[i].mRadius > i * 100.0f + 1400.0f) {
                field_0x6C4[i] = 800.0f;
            }
        }

        s32 temp2 = 1;
        f32 temp3 = 600.0f * cM_scos((mPaths[i].mAngle + mPaths[i].mAngleSpeed) * 2 & 0xFFFE);
        if(i % 2 == 1) {
            temp2 = -1;
            temp3 = 600.0f * cM_ssin((mPaths[i].mAngle + mPaths[i].mAngleSpeed) * 2 & 0xFFFE);
        }

        cLib_addCalc2(&mPaths[i].mRadius, field_0x6C4[i], 0.1f, 10.0f);

        f32 temp = (500.0f + g_regHIO.mChild[12].mFloatRegs[10]);

        mPaths[i].mWobbleAmplitude = 300.0f + g_regHIO.mChild[12].mFloatRegs[1];
        mPaths[i].mAngleSpeed = (5 + g_regHIO.mChild[12].mShortRegs[0] + i * 2 + cM_rndF(20.0f)) * temp2;

        mPaths[i].mTranslation.x = current.pos.x + temp * cM_ssin(shape_angle.y);
        mPaths[i].mTranslation.y = 600.0f + current.pos.y + temp3;
        mPaths[i].mTranslation.z = current.pos.z + temp * cM_scos(shape_angle.y);

        dLib_setCirclePath(&mPaths[i]);
        if(mAlpha != 0.0f) {
            dComIfGp_particle_setSimple(0x8306, &mPaths[i].mPos, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
    }

    if(mAlpha == l_HIO.shipAlpha && dist < l_HIO.shipEnterDist && dComIfGs_getEventReg(0x8803) < 3 && !mbEnteredShip) {
        mDoAud_seStart(JA_SE_LK_WARP_TO_G_SHIP);
        stage_scls_info_class* scls_data = dComIfGd_getMeshSceneList(current.pos);
        JUT_ASSERT(463, scls_data != 0)

        u8 startCode = scls_data->mStart;
        dComIfGs_setEventReg(0xC3FF, scls_data->mRoom);
        dComIfGs_setEventReg(0x85FF, startCode);
        dComIfGp_setNextStage("PShip", 0, 2);
        mbEnteredShip = true;
    }

    modeProcCall();
    mBtk.play();

    dLib_waveRot(&current.pos, 0.0f, &mWave);
    shape_angle.x = mWave.mRotX;
    shape_angle.z = mWave.mRotZ;

    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());

    mDoMtx_stack_c::push();
    mDoMtx_stack_c::transM(0.0f, 3200.0f, 75.0f);
    mpCloth->setMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::pop();
    mDoMtx_stack_c::transM(-900.0f, 2080.0f, 85.0f);
    mDoMtx_stack_c::YrotM(0x4000);
    mpCloth2->setMtx(mDoMtx_stack_c::get());

    mpCloth->setParam(0.45f, -1.5f, 0.875f, 1.0f, 1.0f, 0x100, 0, 900, -800, 7.0f, 6.0f);
    mpCloth->setGlobalWind(dKyw_get_wind_vec());
    mpCloth->cloth_move();

    mpCloth2->setParam(0.45f, -0.25f, 0.875f, 1.0f, 1.0f, 0x100, 0, 900, -800, 7.0f, 6.0f);
    cXyz wind2 = *dKyw_get_wind_vec();
    wind2 *= 0.548f;
    wind2.y = -0.83f;
    mpCloth2->setGlobalWind(&wind2);
    mpCloth2->cloth_move();

    return false;
}

/* 0000182C-00001850 .text daGhostshipDraw__FPv */
static BOOL daGhostshipDraw(void* i_this) {
    return static_cast<daGhostship_c*>(i_this)->_draw();
}

/* 00001850-000019A4 .text _draw__13daGhostship_cFv */
bool daGhostship_c::_draw() {
    if(mAlpha == 0.0f) {
        return true;
    }

    if(!l_HIO.hideShip) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
        g_env_light.setLightTevColorType(mpModel, &mTevStr);

        J3DModelData* modelData = mpModel->getModelData();
        u8 i;
        u32 alpha = (u8)(mAlpha * 255.5f);
        for(i = 0; i < modelData->getMaterialNum(); i++) {
            modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = alpha;
        }

        mBtk.entry(modelData, mBtk.getFrame());
        mDoExt_modelUpdateDL(mpModel);
        mBtk.remove(modelData);

        mTevStr.mColorC0.a = alpha;
        mpCloth->cloth_draw();
        mTevStr.mColorC0.a = alpha;
        mpCloth2->cloth_draw();
    }

    return true;
}

/* 000019A4-000019AC .text daGhostshipIsDelete__FPv */
static BOOL daGhostshipIsDelete(void*) {
    return true;
}

static actor_method_class daGhostshipMethodTable = {
    (process_method_func)daGhostshipCreate,
    (process_method_func)daGhostshipDelete,
    (process_method_func)daGhostshipExecute,
    (process_method_func)daGhostshipIsDelete,
    (process_method_func)daGhostshipDraw,
};

actor_process_profile_definition g_profile_AYUSH = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_AYUSH,
    &g_fpcLf_Method.mBase,
    sizeof(daGhostship_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x009E,
    &daGhostshipMethodTable,
    fopAcStts_UNK40000_e | fopAcStts_SHOWMAP_e | 0x3,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_4_e,
};
