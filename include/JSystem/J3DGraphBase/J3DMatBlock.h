#ifndef J3DMATBLOCK_H
#define J3DMATBLOCK_H

#include "JSystem/J3DGraphBase/J3DGD.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/J3DGraphBase/J3DTevs.h"
#include "JSystem/J3DGraphBase/J3DTexture.h"
#include "dolphin/gx/GXEnum.h"

struct J3DGXColorS10 : public GXColorS10 {
    J3DGXColorS10() {}
};

struct J3DGXColor : public GXColor {
    J3DGXColor() {}
};

class J3DTexGenBlock {
public:
    virtual void reset(J3DTexGenBlock*);
    virtual void calc(f32 const (*)[4]) = 0;
    virtual void load() = 0;
    virtual void patch() = 0;
    virtual void diff(u32) = 0;
    virtual void diffTexMtx() = 0;
    virtual void diffTexGen() = 0;
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setTexGenNum(u32 const*);
    virtual void setTexGenNum(u32);
    virtual u32 getTexGenNum() const;
    virtual void setTexCoord(u32, J3DTexCoord const*);
    virtual J3DTexCoord* getTexCoord(u32);
    virtual void setTexMtx(u32, J3DTexMtx*);
    virtual J3DTexMtx* getTexMtx(u32);
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual u32 getTexMtxOffset() const;
    virtual void setTexMtxOffset(u32);
    virtual ~J3DTexGenBlock() {}
};

class J3DTexGenBlockPatched : public J3DTexGenBlock {
public:
    J3DTexGenBlockPatched() { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void calc(f32 const (*)[4]);
    virtual void calcWithoutViewMtx(f32 const (*)[4]);
    virtual void calcPostTexMtx(f32 const (*)[4]);
    virtual void calcPostTexMtxWithoutViewMtx(f32 const (*)[4]);
    virtual void load();
    virtual void patch();
    virtual void diff(u32);
    virtual void diffTexMtx();
    virtual void diffTexGen();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setTexGenNum(u32 const*);
    virtual void setTexGenNum(u32);
    virtual u32 getTexGenNum() const;
    virtual void setTexCoord(u32, J3DTexCoord const*);
    virtual J3DTexCoord* getTexCoord(u32);
    virtual void setTexMtx(u32, J3DTexMtx*);
    virtual J3DTexMtx* getTexMtx(u32);
    virtual u32 getTexMtxOffset() const;
    virtual void setTexMtxOffset(u32);
    virtual ~J3DTexGenBlockPatched() {}

protected:
    /* 0x04 */ u32 mTexGenNum;
    /* 0x08 */ J3DTexCoord mTexCoord[8];
    /* 0x28 */ J3DTexMtx* mTexMtx[8];
    /* 0x48 */ u32 mTexMtxOffset;
};  // Size: 0x4C

class J3DTexGenBlockBasic : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlockBasic() : mNBTScale(j3dDefaultNBTScaleInfo) { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual ~J3DTexGenBlockBasic() {}

private:
    /* 0x4C */ J3DNBTScale mNBTScale;
};  // Size: 0x5C

class J3DTexGenBlock4 : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlock4() : mNBTScale(j3dDefaultNBTScaleInfo) { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual ~J3DTexGenBlock4() {}

private:
    /* 0x4C */ J3DNBTScale mNBTScale;
};  // Size: 0x5C

class J3DTevBlock {
public:
    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diff(u32);
    virtual void diffTexNo() {}
    virtual void diffTevReg() {}
    virtual void diffTexCoordScale() {}
    virtual void diffTevStage() {}
    virtual void diffTevStageIndirect() {}
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex() = 0;
    virtual void indexToPtr() = 0;
    virtual u32 getType() = 0;
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual _GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual _GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32 i, const u8* pNum) {}
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevKAlphaSel(u32 i, const u8* pNum) {}
    virtual void setTevKAlphaSel(u32, u8);
    virtual u8 getTevKAlphaSel(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage* getTevStage(u32);
    virtual void setTevSwapModeInfo(u32 i, const J3DTevSwapModeInfo* pInfo) {}
    virtual void setTevSwapModeInfo(u32 i, J3DTevSwapModeInfo info) {}
    virtual void setTevSwapModeTable(u32 i, const J3DTevSwapModeTable* pTable) {}
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable);
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage* getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const { return 0; }
    virtual void setTexNoOffset(u32 offs) { mTexNoOffset = offs; }
    virtual void setTevRegOffset(u32 offs) {}
    virtual ~J3DTevBlock() {}

protected:
    void indexToPtr_private(u32);

    /* 0x4 */ u32 mTexNoOffset;
};

class J3DTevBlockPatched : public J3DTevBlock {
public:
    J3DTevBlockPatched() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load() {}
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr() { return indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVPT'; }
    virtual s32 countDLSize();
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTexNo(u32 i, const u16* pNo) { mTexNo[i] = *pNo; }
    virtual void setTexNo(u32 i, u16 no) { mTexNo[i] = no; }
    virtual u16 getTexNo(u32 i) const { return mTexNo[i]; }
    virtual void setTevOrder(u32 i, const J3DTevOrder* pOrder) { mTevOrder[i] = *pOrder; }
    virtual void setTevOrder(u32 i, J3DTevOrder order) { mTevOrder[i] = order; }
    virtual J3DTevOrder* getTevOrder(u32 i) { return &mTevOrder[i]; }
    virtual void setTevStage(u32 i, const J3DTevStage* pStage) { mTevStage[i] = *pStage; }
    virtual void setTevStage(u32 i, J3DTevStage stage) { mTevStage[i] = stage; }
    virtual J3DTevStage* getTevStage(u32 i) { return &mTevStage[i]; }
    virtual void setIndTevStage(u32 i, const J3DIndTevStage* pStage) { mIndTevStage[i] = *pStage; }
    virtual void setIndTevStage(u32 i, J3DIndTevStage stage) { mIndTevStage[i] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 i) { return &mIndTevStage[i]; }
    virtual void setTevColor(u32 i, const J3DGXColorS10* pColor) { mTevColor[i] = *pColor; }
    virtual void setTevColor(u32 i, J3DGXColorS10 color) { mTevColor[i] = color; }
    virtual GXColorS10* getTevColor(u32 i) { return &mTevColor[i]; }
    virtual void setTevKColor(u32 i, const J3DGXColor* pColor) { mTevKColor[i] = *pColor; }
    virtual void setTevKColor(u32 i, J3DGXColor color) { mTevKColor[i] = color; }
    virtual GXColor* getTevKColor(u32 i) { return &mTevKColor[i]; }
    virtual void setTevKColorSel(u32 i, const u8* pSel) { mTevKColorSel[i] = *pSel; }
    virtual void setTevKColorSel(u32 i, u8 sel) { mTevKColorSel[i] = sel; }
    virtual u8 getTevKColorSel(u32 i) { return mTevKColorSel[i]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }

    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlockPatched() {}

private:
    /* 0x08 */ u16 mTexNo[8];
    /* 0x18 */ J3DTevOrder mTevOrder[8];
    /* 0x38 */ J3DTevStage mTevStage[8];
    /* 0x78 */ J3DIndTevStage mIndTevStage[8];
    /* 0x98 */ GXColorS10 mTevColor[4];
    /* 0xB8 */ GXColor mTevKColor[4];
    /* 0xC8 */ u8 mTevKColorSel[8];
    /* 0xD0 */ u8 mTevStageNum;
    /* 0xD4 */ u32 mTevRegOffset;
};  // Size: 0xD8

class J3DTevBlockNull : public J3DTevBlock {
    void initialize();
};

class J3DTevBlock4 : public J3DTevBlock {
public:
    J3DTevBlock4() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { return indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB4'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 i, const u16* pNo) { mTexNo[i] = *pNo; }
    virtual void setTexNo(u32 i, u16 no) { mTexNo[i] = no; }
    virtual u16 getTexNo(u32 i) const { return mTexNo[i]; }
    virtual void setTevOrder(u32 i, const J3DTevOrder* pOrder) { mTevOrder[i] = *pOrder; }
    virtual void setTevOrder(u32 i, J3DTevOrder order) { mTevOrder[i] = order; }
    virtual J3DTevOrder* getTevOrder(u32 i) { return &mTevOrder[i]; }
    virtual void setTevColor(u32 i, const J3DGXColorS10* pColor) { mTevColor[i] = *pColor; }
    virtual void setTevColor(u32 i, J3DGXColorS10 color) { mTevColor[i] = color; }
    virtual GXColorS10* getTevColor(u32 i) { return &mTevColor[i]; }
    virtual void setTevKColor(u32 i, const J3DGXColor* pColor) { mTevKColor[i] = *pColor; }
    virtual void setTevKColor(u32 i, J3DGXColor color) { mTevKColor[i] = color; }
    virtual GXColor* getTevKColor(u32 i) { return &mTevKColor[i]; }
    virtual void setTevKColorSel(u32 i, const u8* pNum) { mTevKColorSel[i] = *pNum; }
    virtual void setTevKColorSel(u32 i, u8 num) { mTevKColorSel[i] = num; }
    virtual u8 getTevKColorSel(u32 i) { return mTevKColorSel[i]; }
    virtual void setTevKAlphaSel(u32 i, const u8* pNum) { mTevKAlphaSel[i] = *pNum; }
    virtual void setTevKAlphaSel(u32 i, u8 num) { mTevKAlphaSel[i] = num; }
    virtual u8 getTevKAlphaSel(u32 i) { return mTevKAlphaSel[i]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 i, const J3DTevStage* pStage) { mTevStage[i] = *pStage; }
    virtual void setTevStage(u32 i, J3DTevStage stage) { mTevStage[i] = stage; }
    virtual J3DTevStage* getTevStage(u32 i) { return &mTevStage[i]; }
    virtual void setTevSwapModeInfo(u32 i, const J3DTevSwapModeInfo*) { /* Nonmatching */
    }
    virtual void setTevSwapModeInfo(u32 i, J3DTevSwapModeInfo) { /* Nonmatching */
    }
    virtual void setTevSwapModeTable(u32 i, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[i] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 i, J3DTevSwapModeTable table) {
        mTevSwapModeTable[i] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 i) { return &mTevSwapModeTable[i]; }
    virtual void setIndTevStage(u32 i, const J3DIndTevStage* pStage) { mIndTevStage[i] = *pStage; }
    virtual void setIndTevStage(u32 i, J3DIndTevStage stage) { mIndTevStage[i] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 i) { return &mIndTevStage[i]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock4() {}

private:
    /* 0x08 */ u16 mTexNo[4];
    /* 0x10 */ J3DTevOrder mTevOrder[4];
    /* 0x20 */ u8 mTevStageNum;
    /* 0x21 */ J3DTevStage mTevStage[4];
    /* 0x42 */ GXColorS10 mTevColor[4];
    /* 0x62 */ GXColor mTevKColor[4];
    /* 0x72 */ u8 mTevKColorSel[4];
    /* 0x76 */ u8 mTevKAlphaSel[4];
    /* 0x7A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x80 */ J3DIndTevStage mIndTevStage[4];
    /* 0x90 */ u32 mTevRegOffset;
};  // Size: 0x94

class J3DTevBlock2 : public J3DTevBlock {
public:
    J3DTevBlock2() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { return indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB2'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 i, const u16* pNo) { mTexNo[i] = *pNo; }
    virtual void setTexNo(u32 i, u16 no) { mTexNo[i] = no; }
    virtual u16 getTexNo(u32 i) const { return mTexNo[i]; }
    virtual void setTevOrder(u32 i, const J3DTevOrder* pOrder) { mTevOrder[i] = *pOrder; }
    virtual void setTevOrder(u32 i, J3DTevOrder order) { mTevOrder[i] = order; }
    virtual J3DTevOrder* getTevOrder(u32 i) { return &mTevOrder[i]; }
    virtual void setTevColor(u32 i, const J3DGXColorS10* pColor) { mTevColor[i] = *pColor; }
    virtual void setTevColor(u32 i, J3DGXColorS10 color) { mTevColor[i] = color; }
    virtual GXColorS10* getTevColor(u32 i) { return &mTevColor[i]; }
    virtual void setTevKColor(u32 i, const J3DGXColor* pColor) { mTevKColor[i] = *pColor; }
    virtual void setTevKColor(u32 i, J3DGXColor color) { mTevKColor[i] = color; }
    virtual GXColor* getTevKColor(u32 i) { return &mTevKColor[i]; }
    virtual void setTevKColorSel(u32 i, const u8* pNum) { mTevKColorSel[i] = *pNum; }
    virtual void setTevKColorSel(u32 i, u8 num) { mTevKColorSel[i] = num; }
    virtual u8 getTevKColorSel(u32 i) { return mTevKColorSel[i]; }
    virtual void setTevKAlphaSel(u32 i, const u8* pNum) { mTevKAlphaSel[i] = *pNum; }
    virtual void setTevKAlphaSel(u32 i, u8 num) { mTevKAlphaSel[i] = num; }
    virtual u8 getTevKAlphaSel(u32 i) { return mTevKAlphaSel[i]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 i, const J3DTevStage* pStage) { mTevStage[i] = *pStage; }
    virtual void setTevStage(u32 i, J3DTevStage stage) { mTevStage[i] = stage; }
    virtual J3DTevStage* getTevStage(u32 i) { return &mTevStage[i]; }
    virtual void setTevSwapModeInfo(u32 i, const J3DTevSwapModeInfo*) { /* Nonmatching */
    }
    virtual void setTevSwapModeInfo(u32 i, J3DTevSwapModeInfo) { /* Nonmatching */
    }
    virtual void setTevSwapModeTable(u32 i, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[i] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 i, J3DTevSwapModeTable table) {
        mTevSwapModeTable[i] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 i) { return &mTevSwapModeTable[i]; }
    virtual void setIndTevStage(u32 i, const J3DIndTevStage* pStage) { mIndTevStage[i] = *pStage; }
    virtual void setIndTevStage(u32 i, J3DIndTevStage stage) { mIndTevStage[i] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 i) { return &mIndTevStage[i]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock2() {}

private:
    /* 0x08 */ u16 mTexNo[2];
    /* 0x0C */ J3DTevOrder mTevOrder[2];
    /* 0x14 */ GXColorS10 mTevColor[4];
    /* 0x34 */ u8 mTevStageNum;
    /* 0x35 */ J3DTevStage mTevStage[2];
    /* 0x45 */ GXColor mTevKColor[4];
    /* 0x55 */ u8 mTevKColorSel[2];
    /* 0x57 */ u8 mTevKAlphaSel[2];
    /* 0x59 */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x60 */ J3DIndTevStage mIndTevStage[2];
    /* 0x68 */ u32 mTevRegOffset;
};  // Size: 0x6C

class J3DTevBlock16 : public J3DTevBlock {
public:
    J3DTevBlock16() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr() { return indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TV16'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 i, const u16* pNo) { mTexNo[i] = *pNo; }
    virtual void setTexNo(u32 i, u16 no) { mTexNo[i] = no; }
    virtual u16 getTexNo(u32 i) const { return mTexNo[i]; }
    virtual void setTevOrder(u32 i, const J3DTevOrder* pOrder) { mTevOrder[i] = *pOrder; }
    virtual void setTevOrder(u32 i, J3DTevOrder order) { mTevOrder[i] = order; }
    virtual J3DTevOrder* getTevOrder(u32 i) { return &mTevOrder[i]; }
    virtual void setTevColor(u32 i, const J3DGXColorS10* pColor) { mTevColor[i] = *pColor; }
    virtual void setTevColor(u32 i, J3DGXColorS10 color) { mTevColor[i] = color; }
    virtual GXColorS10* getTevColor(u32 i) { return &mTevColor[i]; }
    virtual void setTevKColor(u32 i, const J3DGXColor* pColor) { mTevKColor[i] = *pColor; }
    virtual void setTevKColor(u32 i, J3DGXColor color) { mTevKColor[i] = color; }
    virtual GXColor* getTevKColor(u32 i) { return &mTevKColor[i]; }
    virtual void setTevKColorSel(u32 i, const u8* pNum) { mTevKColorSel[i] = *pNum; }
    virtual void setTevKColorSel(u32 i, u8 num) { mTevKColorSel[i] = num; }
    virtual u8 getTevKColorSel(u32 i) { return mTevKColorSel[i]; }
    virtual void setTevKAlphaSel(u32 i, const u8* pNum) { mTevKAlphaSel[i] = *pNum; }
    virtual void setTevKAlphaSel(u32 i, u8 num) { mTevKAlphaSel[i] = num; }
    virtual u8 getTevKAlphaSel(u32 i) { return mTevKAlphaSel[i]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 i, const J3DTevStage* pStage) { mTevStage[i] = *pStage; }
    virtual void setTevStage(u32 i, J3DTevStage stage) { mTevStage[i] = stage; }
    virtual J3DTevStage* getTevStage(u32 i) { return &mTevStage[i]; }
    virtual void setTevSwapModeInfo(u32 i, const J3DTevSwapModeInfo* pInfo) {
        J3DTevStageTevSwapModeInfo& out = mTevStage[i].mTevSwapModeInfo;
        out.field_0x0_29 = pInfo->field_0x0 + 1;
        out.field_0x0_31 = pInfo->field_0x0;
    }
    virtual void setTevSwapModeInfo(u32 i, J3DTevSwapModeInfo info) {
        mTevStage[i].mTevSwapModeInfo.field_0x0_29 = info.field_0x0 + 1;
        mTevStage[i].mTevSwapModeInfo.field_0x0_31 = info.field_0x0;
    }
    virtual void setTevSwapModeTable(u32 i, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[i] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 i, J3DTevSwapModeTable table) {
        mTevSwapModeTable[i] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 i) { return &mTevSwapModeTable[i]; }
    virtual void setIndTevStage(u32 i, const J3DIndTevStage* pStage) { mIndTevStage[i] = *pStage; }
    virtual void setIndTevStage(u32 i, J3DIndTevStage stage) { mIndTevStage[i] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 i) { return &mIndTevStage[i]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock16() {}

    // private:
    /* 0x008 */ u16 mTexNo[8];
    /* 0x018 */ J3DTevOrder mTevOrder[16];
    /* 0x058 */ u8 mTevStageNum;
    /* 0x059 */ J3DTevStage mTevStage[16];
    /* 0x0DA */ GXColorS10 mTevColor[4];
    /* 0x0FA */ GXColor mTevKColor[4];
    /* 0x10A */ u8 mTevKColorSel[16];
    /* 0x11A */ u8 mTevKAlphaSel[16];
    /* 0x12A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x130 */ J3DIndTevStage mIndTevStage[16];
    /* 0x170 */ u32 mTevRegOffset;
};  // Size: 0x174

STATIC_ASSERT(offsetof(J3DTevBlock16, mTexNo) == 0x008);
STATIC_ASSERT(offsetof(J3DTevBlock16, mTevStage) == 0x059);

class J3DTevBlock1 : public J3DTevBlock {
public:
    J3DTevBlock1() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { return indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB1'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 i, const u16* pNo) { mTexNo[i] = *pNo; }
    virtual void setTexNo(u32 i, u16 no) { mTexNo[i] = no; }
    virtual u16 getTexNo(u32 i) const { return mTexNo[i]; }
    virtual void setTevOrder(u32 i, const J3DTevOrder* pOrder) { mTevOrder[i] = *pOrder; }
    virtual void setTevOrder(u32 i, J3DTevOrder order) { mTevOrder[i] = order; }
    virtual J3DTevOrder* getTevOrder(u32 i) { return &mTevOrder[i]; }
    virtual void setTevStageNum(const u8* pNum) {}
    virtual void setTevStageNum(u8 num) {}
    virtual u8 getTevStageNum() const { return 1; }
    virtual void setTevStage(u32 i, const J3DTevStage* pStage) { mTevStage[i] = *pStage; }
    virtual void setTevStage(u32 i, J3DTevStage stage) { mTevStage[i] = stage; }
    virtual J3DTevStage* getTevStage(u32 i) { return &mTevStage[i]; }
    virtual void setIndTevStage(u32 i, const J3DIndTevStage* pStage) { mIndTevStage[i] = *pStage; }
    virtual void setIndTevStage(u32 i, J3DIndTevStage stage) { mIndTevStage[i] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 i) { return &mIndTevStage[i]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual ~J3DTevBlock1() {}

private:
    /* 0x08 */ u16 mTexNo[1];
    /* 0x0A */ J3DTevOrder mTevOrder[1];
    /* 0x0E */ J3DTevStage mTevStage[1];
    /* 0x18 */ J3DIndTevStage mIndTevStage[1];
};  // Size: 0x1C

inline u16 calcZModeID(u8 param_0, u8 param_1, u8 param_2) {
    return ((param_1 * 2) & 0x1FE) + (param_0 * 0x10) + param_2;
}

extern u8 j3dZModeTable[96];

struct J3DZMode {
    J3DZMode() { mZModeID = j3dDefaultZModeID; }

    u8 getCompareEnaable() const { return j3dZModeTable[mZModeID * 3]; }
    u8 getFunc() const { return j3dZModeTable[mZModeID * 3 + 1]; }
    u8 getUpdateEnable() const { return j3dZModeTable[mZModeID * 3 + 2]; }

    void setZModeInfo(const J3DZModeInfo& info) {
        mZModeID = calcZModeID(info.mCompareEnable, info.mFunc, info.mUpdateEnable);
    }

    void load() {
        J3DGDSetZMode(getCompareEnaable(), GXCompare(getFunc()), getUpdateEnable());
    }

    /* 0x0 */ u16 mZModeID;
};

struct J3DBlend : public J3DBlendInfo {
    J3DBlend() { *(J3DBlendInfo*)this = j3dDefaultBlendInfo; }

    GXBlendMode getBlendMode() const { return (GXBlendMode)mBlendMode; }
    GXBlendFactor getSrcFactor() const { return (GXBlendFactor)mSrcFactor; }
    GXBlendFactor getDstFactor() const { return (GXBlendFactor)mDstFactor; }
    GXLogicOp getLogicOp() const { return (GXLogicOp)mLogicOp; }

    void load(u8 ditherEnable) {
        J3DGDSetBlendMode(getBlendMode(), getSrcFactor(), getDstFactor(), getLogicOp(), ditherEnable);
    }
};

extern const J3DFogInfo j3dDefaultFogInfo;

struct J3DFog : public J3DFogInfo {
    J3DFog() { *getFogInfo() = j3dDefaultFogInfo; }
    J3DFogInfo* getFogInfo() { return (J3DFogInfo*)this; }

    void load() {
        J3DGDSetFog(GXFogType(mType), mStartZ, mEndZ, mNearZ, mFarZ, mColor);
        J3DGDSetFogRangeAdj(mAdjEnable, mCenter, (GXFogAdjTable*)mFogAdjTable);
    }
};

struct J3DAlphaCompInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 mRef0;
    /* 0x3 */ u8 mRef1;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
};

inline u32 calcAlphaCmpID(u32 param_1, u32 param_2, u32 param_3) {
    return ((param_1 & 0xff) << 5) + ((param_2 & 0xff) << 3) + (param_3 & 0xff);
}

extern u8 j3dAlphaCmpTable[768];

struct J3DAlphaComp {
    J3DAlphaComp() {
        mAlphaCmpID = j3dDefaultAlphaCmpID;
        mRef0 = 0;
        mRef1 = 0;
    }

    GXCompare getComp0() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3]); }
    GXAlphaOp getOp() const { return GXAlphaOp(j3dAlphaCmpTable[mAlphaCmpID * 3 + 1]); }
    GXCompare getComp1() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3 + 2]); }
    u8 getRef0() const { return mRef0; }
    u8 getRef1() const { return mRef1; }

    void setAlphaCompInfo(const J3DAlphaCompInfo& info) {
        // mAlphaCmpID = calcAlphaCmpID(param_1, param_1.mRef0, param_1.mRef1);
    }

    void load() {
        J3DGDSetAlphaCompare(getComp0(), getRef0(), getOp(), getComp1(), getRef1());
    }

    /* 0x00 */ u16 mAlphaCmpID;
    /* 0x02 */ u8 mRef0;
    /* 0x03 */ u8 mRef1;
};  // Size: 0x4

class J3DPEBlock {
public:
    virtual void reset(J3DPEBlock*);
    virtual void load() = 0;
    virtual void patch();
    virtual void diff(u32);
    virtual void diffFog();
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setFog(J3DFog*);
    virtual J3DFog* getFog();
    virtual void setAlphaComp(J3DAlphaComp const*);
    virtual void setAlphaComp(J3DAlphaComp) {}
    virtual J3DAlphaComp* getAlphaComp();
    virtual void setBlend(J3DBlend const*);
    virtual void setBlend(J3DBlend) {}
    virtual J3DBlend* getBlend();
    virtual void setZMode(J3DZMode const*);
    virtual void setZMode(J3DZMode) {}
    virtual J3DZMode* getZMode();
    virtual void setZCompLoc(u8 const*);
    virtual void setZCompLoc(u8) {}
    virtual u8 getZCompLoc() const;
    virtual void setDither(u8 const*);
    virtual void setDither(u8);
    virtual u8 getDither() const;
    virtual u32 getFogOffset() const;
    virtual void setFogOffset(u32);
    virtual ~J3DPEBlock() {}
};

class J3DPEBlockXlu : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockXlu();
};

class J3DPEBlockTexEdge : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockTexEdge();
};

class J3DPEBlockOpa : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockOpa();
};

class J3DPEBlockFull : public J3DPEBlock {
public:
    J3DPEBlockFull() { initialize(); }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void patch();
    virtual void diff(u32);
    virtual void diffFog();
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEFL'; }
    virtual void setFog(J3DFog* pFog) { mFog = pFog; }
    virtual J3DFog* getFog() { return mFog; }
    virtual void setAlphaComp(const J3DAlphaComp* pAlphaComp) { mAlphaComp = *pAlphaComp; }
    virtual void setAlphaComp(J3DAlphaComp alphaComp) { mAlphaComp = alphaComp; }
    virtual J3DAlphaComp* getAlphaComp() { return &mAlphaComp; }
    virtual void setBlend(const J3DBlend* pBlend) { mBlend = *pBlend; }
    virtual void setBlend(J3DBlend blend) { mBlend = blend; }
    virtual J3DBlend* getBlend() { return &mBlend; }
    virtual void setZMode(const J3DZMode* pZMode) { mZMode = *pZMode; }
    virtual void setZMode(J3DZMode zMode) { mZMode = zMode; }
    virtual J3DZMode* getZMode() { return &mZMode; }
    virtual void setZCompLoc(const u8* pZCompLoc) { mZCompLoc = *pZCompLoc; }
    virtual void setZCompLoc(u8 zCompLoc) { mZCompLoc = zCompLoc; }
    virtual u8 getZCompLoc() const { return mZCompLoc; }
    virtual void setDither(const u8* pDither) { mDither = *pDither; }
    virtual void setDither(u8 dither) { mDither = dither; }
    virtual u8 getDither() const { return mDither; }
    virtual u32 getFogOffset() const { return mFogOffset; }
    virtual void setFogOffset(u32 offs) { mFogOffset = offs; }
    virtual ~J3DPEBlockFull() {}

private:
    /* 0x04 */ J3DFog* mFog;
    /* 0x08 */ J3DAlphaComp mAlphaComp;
    /* 0x0C */ J3DBlend mBlend;
    /* 0x10 */ J3DZMode mZMode;
    /* 0x14 */ u8 mZCompLoc;
    /* 0x15 */ u8 mDither;
    /* 0x18 */ u32 mFogOffset;
};  // Size: 0x1C

class J3DPEBlockFogOff : public J3DPEBlock {
public:
    J3DPEBlockFogOff() { initialize(); }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void diff(u32 flag) {
        if ((flag & 0x20000000) != 0)
            diffBlend();
    }
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEFG'; }
    virtual void setAlphaComp(const J3DAlphaComp* pAlphaComp) { mAlphaComp = *pAlphaComp; }
    virtual void setAlphaComp(J3DAlphaComp alphaComp) { mAlphaComp = alphaComp; }
    virtual J3DAlphaComp* getAlphaComp() { return &mAlphaComp; }
    virtual void setBlend(const J3DBlend* pBlend) { mBlend = *pBlend; }
    virtual void setBlend(J3DBlend blend) { mBlend = blend; }
    virtual J3DBlend* getBlend() { return &mBlend; }
    virtual void setZMode(const J3DZMode* pZMode) { mZMode = *pZMode; }
    virtual void setZMode(J3DZMode zMode) { mZMode = zMode; }
    virtual J3DZMode* getZMode() { return &mZMode; }
    virtual void setZCompLoc(const u8* pZCompLoc) { mZCompLoc = *pZCompLoc; }
    virtual void setZCompLoc(u8 zCompLoc) { mZCompLoc = zCompLoc; }
    virtual u8 getZCompLoc() const { return mZCompLoc; }
    virtual void setDither(const u8* pDither) { mDither = *pDither; }
    virtual void setDither(u8 dither) { mDither = dither; }
    virtual u8 getDither() const { return mDither; }
    virtual ~J3DPEBlockFogOff() {}

private:
    /* 0x04 */ J3DAlphaComp mAlphaComp;
    /* 0x08 */ J3DBlend mBlend;
    /* 0x0C */ J3DZMode mZMode;
    /* 0x0E */ u8 mZCompLoc;
    /* 0x0F */ u8 mDither;
};  // Size: 0x10

struct J3DIndTexCoordScale {
    J3DIndTexCoordScale();
    ~J3DIndTexCoordScale() {}

    u8 getScaleS() { return mScaleS; }
    u8 getScaleT() { return mScaleT; }

    /* 0x0 */ u8 mScaleS __attribute__((aligned(4)));
    /* 0x1 */ u8 mScaleT;
};

struct J3DIndTexMtx {
    J3DIndTexMtx();
    ~J3DIndTexMtx() {}

    void load(u32 param_1) {
        J3DGDSetIndTexMtx(GXIndTexMtxID(param_1 + 1), mOffsetMtx, mScaleExp);
    }

    /* 0x00 */ Mtx23 mOffsetMtx;
    /* 0x18 */ u8 mScaleExp;
};  // Size: 0x1C

struct J3DIndTexOrder {
    J3DIndTexOrder();

    u8 getCoord() const { return mCoord; }
    u8 getMap() const { return mMap; }

    /* 0x0 */ u8 mCoord;
    /* 0x1 */ u8 mMap;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
};

class J3DIndBlock {
public:
    virtual void reset(J3DIndBlock*);
    virtual void diff(u32) = 0;
    virtual void load() = 0;
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setIndTexStageNum(u8);
    virtual u8 getIndTexStageNum() const;
    virtual void setIndTexOrder(u32, J3DIndTexOrder);
    virtual void setIndTexOrder(u32, J3DIndTexOrder const*);
    virtual J3DIndTexOrder* getIndTexOrder(u32);
    virtual void setIndTexMtx(u32, J3DIndTexMtx const*);
    virtual void setIndTexMtx(u32, J3DIndTexMtx) {}
    virtual J3DIndTexMtx* getIndTexMtx(u32);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale) {}
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale const*);
    virtual J3DIndTexCoordScale* getIndTexCoordScale(u32);
    virtual ~J3DIndBlock() {}
};

class J3DIndBlockFull : public J3DIndBlock {
public:
    J3DIndBlockFull() { initialize(); }
    void initialize();

    virtual void reset(J3DIndBlock*);
    virtual void diff(u32);
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setIndTexStageNum(u8);
    virtual u8 getIndTexStageNum() const;
    virtual void setIndTexOrder(u32, J3DIndTexOrder);
    virtual void setIndTexOrder(u32, J3DIndTexOrder const*);
    virtual J3DIndTexOrder* getIndTexOrder(u32);
    virtual void setIndTexMtx(u32, J3DIndTexMtx const*);
    virtual void setIndTexMtx(u32, J3DIndTexMtx);
    virtual J3DIndTexMtx* getIndTexMtx(u32);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale const*);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale);
    virtual J3DIndTexCoordScale* getIndTexCoordScale(u32);
    virtual ~J3DIndBlockFull();

private:
    /* 0x04 */ u8 mIndTexStageNum;
    /* 0x05 */ J3DIndTexOrder mIndTexOrder[4];
    /* 0x18 */ J3DIndTexMtx mIndTexMtx[3];
    /* 0x6C */ J3DIndTexCoordScale mIndTexCoordScale[4];
};  // Size: 0x7C

class J3DIndBlockNull : public J3DIndBlock {
public:
    virtual void reset(J3DIndBlock*);
    virtual void diff(u32);
    virtual void load();
    virtual u32 getType();
    virtual ~J3DIndBlockNull();
};

inline u32 setChanCtrlMacro(u8 enable, GXColorSrc ambSrc, GXColorSrc matSrc, u32 lightMask, GXDiffuseFn diffuseFn, GXAttnFn attnFn) {
    return
        matSrc |
        enable << 1 |
        (lightMask & 0x0f) << 2 |
        ambSrc << 6 |
        ((attnFn == GX_AF_SPEC) ? GX_DF_NONE : diffuseFn) << 7 |
        (attnFn != GX_AF_NONE) << 9 |
        (attnFn != GX_AF_SPEC) << 10 |
        (lightMask >> 4 & 0x0f) << 11;
}

struct J3DColorChan {
    J3DColorChan();
    GXAttnFn getAttnFn();
    GXDiffuseFn getDiffuseFn() { return GXDiffuseFn(mChanCtrl >> 7 & 3); }
    u8 getLightMask() { return ((mChanCtrl >> 2 & 0x0f) | (mChanCtrl >> 11 & 0x0f) << 4); }
    void setLightMask(u8 param_1) {
        mChanCtrl = (mChanCtrl & ~0x3c) | ((param_1 & 0x0f) << 2);
        mChanCtrl = (mChanCtrl & ~0x7800) | ((param_1 & 0xf0) << 7);
    }
    GXColorSrc getMatSrc() { return GXColorSrc(mChanCtrl >> 0 & 0x01); }
    GXColorSrc getAmbSrc() { return GXColorSrc(mChanCtrl >> 6 & 0x01); }
    u8 getEnable() { return !!(mChanCtrl & 0x02); }
    void load() {
        J3DGDWrite_u32(setChanCtrlMacro(getEnable(), getAmbSrc(), getMatSrc(), getLightMask(), getDiffuseFn(), getAttnFn()));
    }

    /* 0x0 */ u16 mChanCtrl;
};

class J3DColorBlock {
public:
    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setLight(u32, J3DLightObj*);
    virtual J3DLightObj* getLight(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlock() {}
};

class J3DColorBlockLightOn : public J3DColorBlock {
public:
    J3DColorBlockLightOn() { initialize(); }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setLight(u32, J3DLightObj*);
    virtual J3DLightObj* getLight(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlockLightOn() {}

private:
    /* 0x04 */ GXColor mMatColor[2];
    /* 0x0C */ GXColor mAmbColor[2];
    /* 0x14 */ u8 mColorChanNum;
    /* 0x16 */ J3DColorChan mColorChan[4];
    /* 0x20 */ J3DLightObj* mLight[8];
    /* 0x40 */ u8 mCullMode;
    /* 0x44 */ u32 mMatColorOffset;
    /* 0x48 */ u32 mColorChanOffset;
};  // Size: 0x4C

class J3DColorBlockLightOff : public J3DColorBlock {
public:
    J3DColorBlockLightOff() { initialize(); }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlockLightOff() {}

protected:
    /* 0x04 */ GXColor mMatColor[2];
    /* 0x0C */ u8 mColorChanNum;
    /* 0x0E */ J3DColorChan mColorChan[4];
    /* 0x16 */ u8 mCullMode;
    /* 0x18 */ u32 mMatColorOffset;
    /* 0x1C */ u32 mColorChanOffset;
};  // Size: 0x20

extern int SizeOfJ3DColorBlockLightOffLoad;

class J3DColorBlockAmbientOn : public J3DColorBlockLightOff {
public:
    J3DColorBlockAmbientOn() { initialize(); }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual ~J3DColorBlockAmbientOn() {}

protected:
    /* 0x20 */ GXColor mAmbColor[2];
};  // Size: 0x28

extern int SizeOfJ3DColorBlockAmbientOnLoad;

#endif /* J3DMATBLOCK_H */
