#ifndef RES_YM_H
#define RES_YM_H

#include "global.h"

enum YM_RES_FILE_ID {
    /* BCKS */
    YM_BCK_WAIT01=0x0,
    YM_BCK_YM_KARI01=0x1,
    YM_BCK_YM_KARI2WAIT=0x2,
    YM_BCK_YM_KTALK=0x3,
    YM_BCK_YM_KTALK02=0x4,
    YM_BCK_YM_KWAIT=0x5,
    YM_BCK_YM_NBTLOOK=0x6,
    YM_BCK_YM_NBTTALK=0x7,
    YM_BCK_YM_NBTWAIT=0x8,
    YM_BCK_YM_SIT=0x10,
    YM_BCK_YM_SITTALK=0x11,
    YM_BCK_YM_TALK01=0x12,
    YM_BCK_YM_WAIT02=0x13,
    
    /* BDL */
    YM_BDL_YMKAMA=0x9,
    
    /* BDLM */
    YM_BDL_YM=0xA,
    YM_BDL_YMHEAD01=0xB,
    YM_BDL_YMHEAD02=0xC,
    
    /* BMT */
    YM_BMT_YM2=0xD,
    
    /* BTP */
    YM_BTP_YMHEAD01=0xE,
    YM_BTP_YMHEAD02=0xF,
};

enum YM_RES_FILE_INDEX {
    /* BCKS */
    YM_INDEX_BCK_WAIT01=0x7,
    YM_INDEX_BCK_YM_KARI01=0x8,
    YM_INDEX_BCK_YM_KARI2WAIT=0x9,
    YM_INDEX_BCK_YM_KTALK=0xA,
    YM_INDEX_BCK_YM_KTALK02=0xB,
    YM_INDEX_BCK_YM_KWAIT=0xC,
    YM_INDEX_BCK_YM_NBTLOOK=0xD,
    YM_INDEX_BCK_YM_NBTTALK=0xE,
    YM_INDEX_BCK_YM_NBTWAIT=0xF,
    YM_INDEX_BCK_YM_SIT=0x10,
    YM_INDEX_BCK_YM_SITTALK=0x11,
    YM_INDEX_BCK_YM_TALK01=0x12,
    YM_INDEX_BCK_YM_WAIT02=0x13,
    
    /* BDL */
    YM_INDEX_BDL_YMKAMA=0x16,
    
    /* BDLM */
    YM_INDEX_BDL_YM=0x19,
    YM_INDEX_BDL_YMHEAD01=0x1A,
    YM_INDEX_BDL_YMHEAD02=0x1B,
    
    /* BMT */
    YM_INDEX_BMT_YM2=0x1E,
    
    /* BTP */
    YM_INDEX_BTP_YMHEAD01=0x21,
    YM_INDEX_BTP_YMHEAD02=0x22,
};

#endif /* RES_YM_H */