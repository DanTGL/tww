//
// Generated by dtk
// Translation Unit: d_a_sea.cpp
//

#include "d/actor/d_a_sea.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_stage.h"
#include "m_Do/m_Do_lib.h"
#include "d/actor/d_a_daiocta.h"
#include "SSystem/SComponent/c_m2d_g_box.h"

daSea_packet_c l_cloth;

f32 daSea_packet_c::BASE_HEIGHT = 1.0f;

daSea_WaveInfoDat wi_prm_ocean[4] = {
    {
        2.5f,           // mHeight
        7.352941E-5f,   // mKm
        0,              // mPhase
        0.98f,          // mScaleX
        0.2f,           // mScaleZ
        200,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        8.928571E-5f,   // mKm
        4000,           // mPhase
        0.2f,           // mScaleX
        0.98f,          // mScaleZ
        190,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        1.13636364E-4f, // mKm
        8000,           // mPhase
        -0.98f,         // mScaleX
        0.2f,           // mScaleZ
        210,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        1.5625E-4f,     // mKm
        12000,          // mPhase
        0.2f,           // mScaleX
        -0.98f,         // mScaleZ
        180,            // mCounterMax
    },
};

s8 pos_around[16] = {
    -1, -1,  0, -1,
     1, -1,  1,  0,
     1,  1,  0,  1,
    -1,  1, -1,  0,
};

extern void dKy_usonami_set(f32 param_0);

/* 8015B0A4-8015B0FC       .text Pos2Index__25daSea_WaterHeightInfo_MngFfPf */
int daSea_WaterHeightInfo_Mng::Pos2Index(f32 v, f32* dst) {
    f32 f = 450000.0f;
    int idx = (v + f) / 100000.0f;
    if (dst != NULL)
        *dst = (v + f) - idx * 100000.0f;
    return idx;
}

/* 8015B0FC-8015B164       .text GetHeight__25daSea_WaterHeightInfo_MngFff */
int daSea_WaterHeightInfo_Mng::GetHeight(f32 x, f32 z) {
    int xi = Pos2Index(x, NULL);
    int zi = Pos2Index(z, NULL);
    return GetHeight(xi, zi);
}

/* 8015B164-8015B1E8       .text get_wave_max__Fi */
int get_wave_max(int roomNo) {
    dStage_Multi_c * multi = dComIfGp_getStage().getMulti();
    if (multi == NULL)
        return 10;

    dStage_Mult_info* entry = multi->m_entries;
    for (int i = 0; i < multi->num; i++, entry++)
        if (roomNo == entry->mRoomNo)
            return entry->mWaveMax;

    return 10;
}

/* 8015B1E8-8015B288       .text GetHeight__25daSea_WaterHeightInfo_MngFii */
int daSea_WaterHeightInfo_Mng::GetHeight(int x, int z) {
    if (x < 0 || 9 <= x || z < 0 || 9 <= z)
        return 10;

    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e) {
        return mHeight[z][x];
    } else {
        return get_wave_max(dComIfGp_roomControl_getStayNo());
    }
}

/* 8015B288-8015B2D0       .text calcMinMax__FiPfPf */
void calcMinMax(int v, f32* min, f32* max) {
    *min = v * 100000.0f - 450000.0f;
    *max = *min + 100000.0f;
}

/* 8015B2D0-8015B328       .text GetArea__25daSea_WaterHeightInfo_MngFiiPfPfPfPf */
void daSea_WaterHeightInfo_Mng::GetArea(int x, int z, f32* minX, f32* minZ, f32* maxX, f32* maxZ) {
    calcMinMax(x, minX, maxX);
    calcMinMax(z, minZ, maxZ);
}

/* 8015B328-8015B3FC       .text SetInf__25daSea_WaterHeightInfo_MngFv */
void daSea_WaterHeightInfo_Mng::SetInf() {
    dStage_Multi_c * multi = dComIfGp_getStage().getMulti();

    for (s32 i = 0; i < 9; i++)
        for (s32 j = 0; j < 9; j++)
            mHeight[i][j] = 10;

    if (multi != NULL) {
        s32 roomNo = 1;
        for (s32 i = 1; i < 8; i++) {
            for (s32 j = 1; j < 8; j++) {
                mHeight[i][j] = get_wave_max(roomNo);
                roomNo++;
            }
        }
    }
}

/* 8015B3FC-8015B43C       .text __ct__14daSea_WaveInfoFv */
daSea_WaveInfo::daSea_WaveInfo() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mCounters); i++) {
        m04[i] = 0.0f;
        mCounters[i] = 0;
    }
    mCurScale = 1.0f;
}

/* 8015B43C-8015B484       .text __dt__14daSea_WaveInfoFv */
daSea_WaveInfo::~daSea_WaveInfo() {
    /* Nonmatching */
}

/* 8015B484-8015B4D4       .text AddCounter__14daSea_WaveInfoFv */
void daSea_WaveInfo::AddCounter() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mCounters); i++) {
        mCounters[i]++;
        if (mCounters[i] >= mWaveInfoTable[i].mCounterMax)
            mCounters[i] = 0;
    }
}

/* 8015B4D4-8015B530       .text GetRatio__14daSea_WaveInfoFi */
f32 daSea_WaveInfo::GetRatio(int idx) {
    return (f32)mCounters[idx] / (f32)mWaveInfoTable[idx].mCounterMax;
}

/* 8015B530-8015B54C       .text GetKm__14daSea_WaveInfoFi */
f32 daSea_WaveInfo::GetKm(int idx) {
    return mWaveInfoTable[idx].mKm * 6.28f;
}

/* 8015B54C-8015B56C       .text GetScale__14daSea_WaveInfoFf */
f32 daSea_WaveInfo::GetScale(f32 v) {
    mCurScale += (v - mCurScale) / 100.0f;
    return mCurScale;
}

/* 8015B56C-8015B7A0       .text create__14daSea_packet_cFR4cXyz */
bool daSea_packet_c::create(cXyz& pos) {
    BASE_HEIGHT = 1.0f;
    BASE_HEIGHT = pos.y + 1.0f;

    mFlatInter = 0.0f;
    mpHeightTable = new f32[65 * 65];
    if (mpHeightTable == NULL)
        return false;

    mWaterHeightMgr.SetInf();
    mWaveInfo.SetDat(wi_prm_ocean);
    CleanUp();
    mInitFlag = true;
    mRoomNo = -1;
    mFlags = 0;
    mAnimCounter = 0;

    ResTIMG* timg = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_B_SEA_TEX0AND2);
    
    GXBool mipmap = timg->mipmapCount > 1;
    GXInitTexObj(&mTexSea0, (char*)timg + timg->imageOffset, timg->width, timg->height,
        (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
        mipmap);
    GXInitTexObjLOD(&mTexSea0, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
        timg->minLOD * 0.125f, timg->maxLOD * 0.125f, -0.9f,
        (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
        (GXAnisotropy)timg->maxAnisotropy);

    mipmap = timg->mipmapCount > 1;
    GXInitTexObj(&mTexSea1, (char*)timg + timg->imageOffset, timg->width, timg->height,
        (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
        mipmap);
    GXInitTexObjLOD(&mTexSea1, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
        timg->minLOD * 0.125f, timg->maxLOD * 0.125f, 1.0f,
        (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
        (GXAnisotropy)timg->maxAnisotropy);

    timg = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_B_WYURAYURA_TEX1);
    mDoLib_setResTimgObj(timg, &mTexYura, 0, NULL);

    return true;
}

/* 8015B7A0-8015B7E4       .text CleanUp__14daSea_packet_cFv */
void daSea_packet_c::CleanUp() {
    s32 idx = 0;
    for (s32 i = 0; i < 65; i++)
        for (s32 j = 0; j < 65; j++)
            mpHeightTable[idx++] = BASE_HEIGHT;
    mCurPos.zero();
}

/* 8015B7E4-8015B84C       .text __ct__14daSea_packet_cFv */
daSea_packet_c::daSea_packet_c() {}

/* 8015B84C-8015B86C       .text SetFlat__14daSea_packet_cFv */
void daSea_packet_c::SetFlat() {
    mFlags |= 0x01;
    mFlatTarget = 0.0f;
    mFlatInterCounter = 150.0f;
}

/* 8015B86C-8015B884       .text ClrFlat__14daSea_packet_cFv */
void daSea_packet_c::ClrFlat() {
    mFlags &= ~0x01;
    mFlatInterCounter = 150.0f;
}

/* 8015B884-8015BA18       .text CalcFlatInterTarget__14daSea_packet_cFR4cXyz */
f32 daSea_packet_c::CalcFlatInterTarget(cXyz& pos) {
    cM2dGBox box;
    cXy xzPos;
    xzPos.x = pos.x;
    xzPos.y = pos.z;

    if (mWaterHeightMgr.GetHeight(mIdxX, mIdxZ) == 0) {
        return 0.0f;
    }

    f32 result = 1.0f;

    for (int i = 0; i < 8; i++) {
        int ix = mIdxX + pos_around[2 * i];
        int iz = mIdxZ + pos_around[(2 * i) + 1];

        if (mWaterHeightMgr.GetHeight(ix, iz) == 0) {
            cXy min;
            cXy max;

            mWaterHeightMgr.GetArea(ix, iz, &min.x, &min.y, &max.x, &max.y);

            min.x -= 12800.0f;
            min.y -= 12800.0f;
            max.x += 12800.0f;
            max.y += 12800.0f;

            box.Set(min, max);

            f32 len = box.GetLen(xzPos);

            if (len > 12800.0f) {
                len = 12800.0f;
            }

            len /= 12800.0f;
            if (result > len) {
                result = len;
            }
        }
    }

    return result;
}

/* 8015BA18-8015BAD8       .text CalcFlatInter__14daSea_packet_cFv */
void daSea_packet_c::CalcFlatInter() {
    if (mFlags & 1) {
        if (mFlatInterCounter != 0.0f) {
            mFlatInter = mFlatInter + (mFlatTarget - mFlatInter) / mFlatInterCounter;
            mFlatInterCounter--;
        } else {
            mFlatInter = mFlatTarget;
        }
    } else {
        f32 target = CalcFlatInterTarget(mPlayerPos);
        if (mFlatInterCounter != 0.0f) {
            mFlatInter = mFlatInter + (target - mFlatInter) / mFlatInterCounter;
            mFlatInterCounter--;
        } else {
            mFlatInter = target;
        }
    }
}

/* 8015BAD8-8015BAF8       .text daSea_Init__Fv */
void daSea_Init() {
    l_cloth.mInitFlag = false;
    l_cloth.mCullStopFlag = true;
    l_cloth.m13A = true;
}

/* 8015BAF8-8015BB60       .text daSea_ChkAreaBeforePos__Fff */
bool daSea_ChkAreaBeforePos(f32 x, f32 z) {
    if (l_cloth.mInitFlag == 0) {
        return false;
    }

    if (l_cloth.mWaterHeightMgr.GetHeight(x, z) == 0 && l_cloth.mCullStopFlag != 0) {
        return false;
    }

    return true;
}

/* 8015BB60-8015BBFC       .text daSea_ChkArea__Fff */
bool daSea_ChkArea(f32 x, f32 z) {
    if (!daSea_ChkAreaBeforePos(x, z)) {
        return false;
    }

    if (l_cloth.getMinX() < x && x < l_cloth.getMaxX() && l_cloth.getMinZ() < z && z < l_cloth.getMaxZ()) {
        return true;
    }

    return false;
}

// Fakematch
#pragma opt_dead_assignments off
/* 8015BBFC-8015BDB0       .text daSea_calcWave__Fff */
f32 daSea_calcWave(f32 x, f32 z) {
    if (!daSea_ChkArea(x, z)) {
        return daSea_packet_c::BASE_HEIGHT;
    }

    f32 frac = 1.0f / 800.0f;

    int x0 = (x - l_cloth.getMinX()) * frac;
    int z0 = (z - l_cloth.getMinZ()) * frac;

    f32* pY = l_cloth.mpHeightTable;
    pY += x0;
    pY += z0 * 65;

    //f32 minX = (x0 * 800) + l_cloth.getMinX();
    //f32 maxX = minX + 800.0f;
    //f32 minZ = (z0 * 800) + l_cloth.getMinZ();
    //f32 maxZ = minZ + 800.0f;
    
    Vec v00, v01, v10, v11;

    v00.x = (x0 * 800) + l_cloth.getMinX();
    v00.y = pY[0];
    v00.z = (z0 * 800) + l_cloth.getMinZ();

    v01.x = (x0 * 800) + l_cloth.getMinX();
    v01.y = pY[65];
    v01.z = v00.z + 800.0f;

    v10.x = v01.x + 800.0f;
    v10.y = pY[1];
    v10.z = (z0 * 800) + l_cloth.getMinZ();

    v11.x = v10.x;
    v11.y = pY[66];
    v11.z = v01.z;

    Vec norm;
    f32 baseY;

    f32 f0, f1;
    f1 = x - v01.x;
    f0 = z - v10.z;
    f1 *= frac;
    f0 *= frac;

    if (f1 + f0 >= 1.0f) {
        cM3d_CalcPla(&v01, &v10, &v11, &norm, &baseY);
    } else {
        cM3d_CalcPla(&v00, &v01, &v10, &norm, &baseY);
    }

    return -((norm.x * x) + (norm.z * z) + baseY) / norm.y;
}

#pragma opt_dead_assignments reset

/* 8015BDB0-8015C010       .text daSea_GetPoly__FPvPFPvR4cXyzR4cXyzR4cXyz_vRC4cXyzRC4cXyz */
void daSea_GetPoly(void* param_1, void (*callback)(void*, cXyz&, cXyz&, cXyz&), const cXyz& param_3, const cXyz& param_4) {
    if (!daSea_ChkArea(param_3.x, param_3.z) || !daSea_ChkArea(param_4.x, param_4.z)) return;

    f32 frac = 1.0f / 800.0f;
    int x0 = (param_3.x - l_cloth.getMinX()) * frac;
    int z0 = (param_3.z - l_cloth.getMinZ()) * frac;
    int x1 = (param_4.x - l_cloth.getMinX()) * frac;
    int z1 = (param_4.z - l_cloth.getMinZ()) * frac;

    if (!(x0 >= 0 && x0 <= 0x3F && z0 >= 0 && z0 <= 0x3F && x1 >= 0 && x1 <= 0x3F && z1 >= 0 && z1 <= 0x3F)) {
        return;
    }

    for (int z = z0; z < z1 + 1; z++) {
        for (int x = x0; x < x1 + 1; x++) {
            f32* pY = l_cloth.mpHeightTable;
            pY += x;
            pY += z * 65;
            cXyz v00, v01, v10, v11;

            v00.x = (x * 800) + l_cloth.getMinX();
            v00.y = pY[0];
            v00.z = (z * 800) + l_cloth.getMinZ();

            v01.x = v00.x;
            v01.y = pY[65];
            v01.z = v00.z + 800.0f;

            v10.x = v00.x + 800.0f;
            v10.y = pY[1];
            v10.z = v00.z;

            v11.x = v10.x;
            v11.y = pY[66];
            v11.z = v01.z;

            callback(param_1, v00, v01, v11);
            callback(param_1, v00, v11, v10);
        }
    }
}

/* 8015C010-8015C11C       .text SetCullStopFlag__14daSea_packet_cFv */
void daSea_packet_c::SetCullStopFlag() {
    if (strcmp(dComIfGp_getStartStageName(), "A_umikz") == 0) {
        mCullStopFlag = false;
        return;
    }

    if (mWaterHeightMgr.GetHeight(mIdxX, mIdxZ) != 0) {
        mCullStopFlag = false;
        return;
    }

    f32 minX, minZ, maxX, maxZ;
    mWaterHeightMgr.GetArea(mIdxX, mIdxZ, &minX, &minZ, &maxX, &maxZ);

    minX += 25600.0f;
    minZ += 25600.0f;
    maxX -= 25600.0f;
    maxZ -= 25600.0f;

    if ((minX < mPlayerPos.x) && (mPlayerPos.x < maxX) && (minZ < mPlayerPos.z) && (mPlayerPos.z < maxZ)) {
        mCullStopFlag = true;
        return;
    }

    mCullStopFlag = false;
}

/* 8015C11C-8015C1DC       .text CheckRoomChange__14daSea_packet_cFv */
void daSea_packet_c::CheckRoomChange() {
    dStage_roomDt_c * room = dComIfGp_roomControl_getStatusRoomDt(dComIfGp_roomControl_getStayNo());
    if (room != NULL) {
        mRoomNo = dComIfGp_roomControl_getStayNo();
        u32 procName = PROC_DAIOCTA;
        daDaiocta_c* octa = (daDaiocta_c *)fopAcM_SearchByName(PROC_DAIOCTA);
        if (octa == NULL) {
            if (mFlags & 0x01) {
                ClrFlat();
            }
        } else {
            if (!dComIfGs_isSwitch(octa->getSw(), fopAcM_GetHomeRoomNo(octa))) {
                SetFlat();
            } else {
                ClrFlat();
            }
        }
    }
}

/* 8015C1DC-8015C214       .text daSea_execute__FR4cXyz */
void daSea_execute(cXyz& pos) {
    if (l_cloth.mInitFlag)
        l_cloth.execute(pos);
}

/* 8015C214-8015C75C       .text execute__14daSea_packet_cFR4cXyz */
void daSea_packet_c::execute(cXyz& pos) {
    mPlayerPos = pos;
    mIdxX = mWaterHeightMgr.Pos2Index(mPlayerPos.x, NULL);
    mIdxZ = mWaterHeightMgr.Pos2Index(mPlayerPos.z, NULL);

    if (strcmp(dComIfGp_getStartStageName(), "ADMumi") == 0) {
        mFlatInter = 0.0f;
    }

    if (mRoomNo != dComIfGp_roomControl_getStayNo() && dComIfGp_roomControl_getStayNo() != 0) {
        CheckRoomChange();
    }

    CalcFlatInter();
    dKy_usonami_set(mFlatInter);
    mDrawMinX = pos.x - 25600.0f;
    mDrawMaxX = pos.x + 25600.0f;
    mDrawMinZ = pos.z - 25600.0f;
    mDrawMaxZ = pos.z + 25600.0f;
    SetCullStopFlag();

    if (mCullStopFlag == 1) {
        return;
    }

    int h = mWaterHeightMgr.GetHeight(pos.x, pos.z);

    f32 scale = mFlatInter * mWaveInfo.GetScale(h);

    // Vectorization?
    s16 aOffsAnimTable [4];
    f32 aThetaXTable [4];
    f32 aThetaZTable [4];
    f32 aHeightTable [4];

    for (int i = 0; i < 4; i++) {
        aThetaXTable[i] = mWaveInfo.GetKm(i) * mWaveInfo.GetVx(i);
        aThetaZTable[i] = mWaveInfo.GetKm(i) * mWaveInfo.GetVz(i);

        aOffsAnimTable[i] = 65536.0f * (mWaveInfo.GetRatio(i) - 0.5f);
        aHeightTable[i] = mWaveInfo.GetBaseHeight(i) * scale;
    }

    scale = mDrawMinZ + 800.0f;

    // Unrolled loops?

    s16 iVar[4];
    // Split up to prevent integer promotion
    iVar[0] = cM_rad2s(aThetaZTable[0] * scale);
    iVar[1] = cM_rad2s(aThetaZTable[1] * scale);
    iVar[2] = cM_rad2s(aThetaZTable[2] * scale);
    iVar[3] = cM_rad2s(aThetaZTable[3] * scale);

    iVar[0] -= aOffsAnimTable[0];
    iVar[1] -= aOffsAnimTable[1];
    iVar[2] -= aOffsAnimTable[2];
    iVar[3] -= aOffsAnimTable[3];

    iVar[0] += mWaveInfo.GetPhai(0);
    iVar[1] += mWaveInfo.GetPhai(1);
    iVar[2] += mWaveInfo.GetPhai(2);
    iVar[3] += mWaveInfo.GetPhai(3);

    s16 waveTheta_DeltaZ[4];
    waveTheta_DeltaZ[0] = cM_rad2s(aThetaZTable[0] * 800.0f);
    waveTheta_DeltaZ[1] = cM_rad2s(aThetaZTable[1] * 800.0f);
    waveTheta_DeltaZ[2] = cM_rad2s(aThetaZTable[2] * 800.0f);
    waveTheta_DeltaZ[3] = cM_rad2s(aThetaZTable[3] * 800.0f);

    s16 waveTheta_DeltaX[4];
    waveTheta_DeltaX[0] = cM_rad2s(aThetaXTable[0] * 800.0f);
    waveTheta_DeltaX[1] = cM_rad2s(aThetaXTable[1] * 800.0f);
    waveTheta_DeltaX[2] = cM_rad2s(aThetaXTable[2] * 800.0f);
    waveTheta_DeltaX[3] = cM_rad2s(aThetaXTable[3] * 800.0f);

    scale = mDrawMinX + 800.0f;

    s16 waveTheta_Phase[4];
    waveTheta_Phase[0] = cM_rad2s(aThetaXTable[0] * scale);
    waveTheta_Phase[1] = cM_rad2s(aThetaXTable[1] * scale);
    waveTheta_Phase[2] = cM_rad2s(aThetaXTable[2] * scale);
    waveTheta_Phase[3] = cM_rad2s(aThetaXTable[3] * scale);

    f32 aFadeTable [65];

    for (int fadeZ = 0; fadeZ < 65; fadeZ++) {
        aFadeTable[fadeZ] = 1.0f;
    }

    // Probably unrolled loop
    f32 frac = 1.0f / 6;
    aFadeTable[64] = frac * 0;
    aFadeTable[0]  = frac * 0;
    aFadeTable[63] = frac * 1;
    aFadeTable[1]  = frac * 1;
    aFadeTable[62] = frac * 2;
    aFadeTable[2]  = frac * 2;
    aFadeTable[61] = frac * 3;
    aFadeTable[3]  = frac * 3;
    aFadeTable[60] = frac * 4;
    aFadeTable[4]  = frac * 4;
    aFadeTable[59] = frac * 5;
    aFadeTable[5]  = frac * 5;

    for (int z = 1; z < 0x40; z++) {
        f32* pHeight = mpHeightTable + 65 * z + 1;
        s16 waveTheta0 = waveTheta_Phase[0];
        waveTheta0 += iVar[0];
        s16 waveTheta1 = waveTheta_Phase[1];
        waveTheta1 += iVar[1];
        s16 waveTheta2 = waveTheta_Phase[2];
        waveTheta2 += iVar[2];
        s16 waveTheta3 = waveTheta_Phase[3];
        waveTheta3 += iVar[3];

        for (int x = 1; x < 0x40; x++) {
            *pHeight = aHeightTable[0] * cM_scos(waveTheta0)
                     + aHeightTable[1] * cM_scos(waveTheta1)
                     + aHeightTable[2] * cM_scos(waveTheta2)
                     + aHeightTable[3] * cM_scos(waveTheta3)
                     + BASE_HEIGHT;

            *pHeight *= aFadeTable[z] * aFadeTable[x];
            waveTheta0 += waveTheta_DeltaX[0];
            waveTheta1 += waveTheta_DeltaX[1];
            waveTheta2 += waveTheta_DeltaX[2];
            waveTheta3 += waveTheta_DeltaX[3];

            pHeight++;
        }

        iVar[0] += waveTheta_DeltaZ[0];
        iVar[1] += waveTheta_DeltaZ[1];
        iVar[2] += waveTheta_DeltaZ[2];
        iVar[3] += waveTheta_DeltaZ[3];
    }

    mWaveInfo.AddCounter();
    mCurPos = pos;
}

/* 8015C75C-8015D80C       .text draw__14daSea_packet_cFv */
void daSea_packet_c::draw() {
    /* Nonmatching */
}

/* 8015D80C-8015D87C       .text daSea_Draw__FP9sea_class */
static BOOL daSea_Draw(sea_class* i_this) {
    dComIfGd_setListSky();
    j3dSys.getDrawBuffer(1)->entryImm(&l_cloth, 31);
    dComIfGd_setList();
    return TRUE;
}

/* 8015D87C-8015D8D0       .text daSea_Execute__FP9sea_class */
static BOOL daSea_Execute(sea_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz pos = player->current.pos;
    l_cloth.execute(pos);
    return TRUE;
}

/* 8015D8D0-8015D8E8       .text daSea_IsDelete__FP9sea_class */
static BOOL daSea_IsDelete(sea_class*) {
    l_cloth.mInitFlag = false;
    return TRUE;
}

/* 8015D8E8-8015D8F0       .text daSea_Delete__FP9sea_class */
static BOOL daSea_Delete(sea_class*) {
    return TRUE;
}

/* 8015D8F0-8015D924       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return l_cloth.create(i_this->current.pos);
}

/* 8015D924-8015D99C       .text daSea_Create__FP10fopAc_ac_c */
static s32 daSea_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, sea_class);
    if (!fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0xA000))
        return cPhs_ERROR_e;
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daSea_Method = {
    (process_method_func)daSea_Create,
    (process_method_func)daSea_Delete,
    (process_method_func)daSea_Execute,
    (process_method_func)daSea_IsDelete,
    (process_method_func)daSea_Draw,
};

actor_process_profile_definition g_profile_SEA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SEA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sea_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x009A,
    /* Actor SubMtd */ &l_daSea_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
