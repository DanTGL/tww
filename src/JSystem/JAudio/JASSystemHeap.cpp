//
// Generated by dtk
// Translation Unit: JASSystemHeap.cpp
//

#include "JSystem/JAudio/JASSystemHeap.h"
#include "JSystem/JAudio/JASHeapCtrl.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JKernel/JKRStdHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/ar/ar.h"
#include "dolphin/os/OS.h"

u32 JASystem::Kernel::audioDramSize = 0x000C8000;
JKRSolidHeap* JASDram;

/* 8027DB38-8027DB9C       .text sysDramSetup__Q28JASystem6KernelFP12JKRSolidHeap */
void JASystem::Kernel::sysDramSetup(JKRSolidHeap* heap) {
    if (heap) {
        JASDram = heap;
        return;
    }
    OSReport("[JASKernel::sysDramSetup] メモリ指定がありませんので、システムからオーディオヒープを取得します。\n");
    JASDram = JKRSolidHeap::create(audioDramSize, JKRStdHeap::create(audioDramSize + 0x100, NULL, false), false);
}

/* 8027DB9C-8027DC30       .text allocFromSysDram__Q28JASystem6KernelFUl */
void* JASystem::Kernel::allocFromSysDram(u32 size) {
    void* ptr;
    BOOL enable = OSDisableInterrupts();
    ptr = new (JASDram, 0x20) u8[size];
    JUT_ASSERT(79, ptr != NULL);
    OSRestoreInterrupts(enable);
    return ptr;
}

JASystem::Kernel::TSolidHeap JASystem::Kernel::audioAramHeap;
u32 JASystem::Kernel::audioAramSize = 0x00400000;
int JASystem::Kernel::audioAramTop;
int JASystem::Kernel::CARD_SECURITY_BUFFER;

/* 8027DC30-8027DC84       .text sysAramSetup__Q28JASystem6KernelFUl */
void JASystem::Kernel::sysAramSetup(u32 size) {
    if (!size) {
        size = audioAramSize;
    }
    audioAramTop = ARGetBaseAddress();
    CARD_SECURITY_BUFFER = 0x40;
    audioAramHeap.init((u8*)audioAramTop, size - audioAramTop);
}

/* 8027DC84-8027DCDC       .text allocFromSysAramFull__Q28JASystem6KernelFPUl */
void* JASystem::Kernel::allocFromSysAramFull(u32* bufSize) {
    u32 size = audioAramHeap.getRemain();
    void* buf = audioAramHeap.alloc(size - 0x20);
    *bufSize = size - 0x20;
    return buf;
}
