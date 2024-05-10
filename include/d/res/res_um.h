#ifndef RES_UM_H
#define RES_UM_H

#include "global.h"

enum UM_RES_FILE_ID {
    /* BCKS */
    UM_BCK_UM_TALK01=0x4,
    UM_BCK_UM_WAIT01=0x5,
    UM_BCK_UM_WALK=0x6,
    UM_BCK_UM_HAPPY=0xD,
    UM_BCK_UM_SHOBON=0xE,
    UM_BCK_UM_TALK02=0xF,
    UM_BCK_UM_TALK03=0x10,
    UM_BCK_UM_TALK04=0x11,
    UM_BCK_UM_TAMEIKI=0x12,
    UM_BCK_UM_WAIT02=0x13,
    UM_BCK_UM_WAIT03=0x14,
    UM_BCK_UM_WAIT04=0x15,
    UM_BCK_UM_HAPPY02=0x17,
    
    /* BDL */
    UM_BDL_UM=0x1,
    UM_BDL_UM_SCOPE=0x16,
    
    /* BDLM */
    UM_BDL_UM01_HEAD=0x2,
    UM_BDL_UM02_HEAD=0x7,
    UM_BDL_UM03_HEAD=0x8,
    
    /* BTP */
    UM_BTP_UM01_MABA=0x3,
    UM_BTP_UM02_MABA=0x9,
    UM_BTP_UM03_MABA=0xA,
    
    /* BMT */
    UM_BMT_UM02=0xB,
    UM_BMT_UM03=0xC,
};

enum UM_RES_FILE_INDEX {
    /* BCKS */
    UM_INDEX_BCK_UM_TALK01=0x7,
    UM_INDEX_BCK_UM_WAIT01=0x8,
    UM_INDEX_BCK_UM_WALK=0x9,
    UM_INDEX_BCK_UM_HAPPY=0xA,
    UM_INDEX_BCK_UM_SHOBON=0xB,
    UM_INDEX_BCK_UM_TALK02=0xC,
    UM_INDEX_BCK_UM_TALK03=0xD,
    UM_INDEX_BCK_UM_TALK04=0xE,
    UM_INDEX_BCK_UM_TAMEIKI=0xF,
    UM_INDEX_BCK_UM_WAIT02=0x10,
    UM_INDEX_BCK_UM_WAIT03=0x11,
    UM_INDEX_BCK_UM_WAIT04=0x12,
    UM_INDEX_BCK_UM_HAPPY02=0x13,
    
    /* BDL */
    UM_INDEX_BDL_UM=0x16,
    UM_INDEX_BDL_UM_SCOPE=0x17,
    
    /* BDLM */
    UM_INDEX_BDL_UM01_HEAD=0x1A,
    UM_INDEX_BDL_UM02_HEAD=0x1B,
    UM_INDEX_BDL_UM03_HEAD=0x1C,
    
    /* BTP */
    UM_INDEX_BTP_UM01_MABA=0x1F,
    UM_INDEX_BTP_UM02_MABA=0x20,
    UM_INDEX_BTP_UM03_MABA=0x21,
    
    /* BMT */
    UM_INDEX_BMT_UM02=0x24,
    UM_INDEX_BMT_UM03=0x25,
};

#endif /* RES_UM_H */