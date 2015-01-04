

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __DRX_OM_DEF_H__
#define __DRX_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



typedef enum
{
     LPHY_DEBUG_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DEBUG, 0x1),

}LPHY_DEBUG_DRX_ENUM;

typedef enum
{
     LPHY_ERR_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_ERROR, 0x1),

}LPHY_ERR_DRX_ENUM;

/* BEGIN: Added by h00130263, 2013/10/6   PN:tds_debug*/
typedef struct __TDS_DEBUG_INFO_STRU__
{
    UINT32 ulTdsTraceHead;              /*107*/
    UINT16 usLastSfn;
	UINT16 usLastSlot;                  /*108*/
	UINT16 usLastIntFuncIdx;
	UINT16 usLastTrigFuncIdx;           /*109*/
    UINT16 usLastTaskFuncIdx;
    UINT16 usRsv;                       /*110*/
    UINT32 ulProcessCnt[32];            /*142*/
    UINT32 ulDmaTraceCnt;               /*143*/
    UINT32 ulDmaTraceInfo[16][4];       /*207*/
}TDS_DRX_DEBUG_INFO_STRU;
/* END:   Added by h00130263, 2013/10/6 */

typedef struct
{
    UINT32 ulLteTraceHead;             /*/1*/
    UINT32 ulAllResetCnt;               /*/2*/
    UINT32 ulInitPowUpCnt;              /*/3*/
    UINT32 ulLpcResetCnt;               /*/4*/
    UINT32 ulTaskLoopCnt[16];           /*20*/
    UINT32 epc[4];                      /*24*/
    UINT32 eps[4];                      /*28*/
    /*UINT32 ulWakeTimer;*/
    /*UINT32 ulSlwwpTimer;*/
    /*UINT32 ulMeasResult;*/
    UINT32 ulWakeResumeFunc;            /*29*/
    UINT32 ulTaskInfo;                  /*30*/
    UINT32 ulDrxCurStatus;              /*31*/
    UINT32 ulExcLoc;                    /*32*/
    UINT16 usExcID;
    UINT16 usSysFrame;                  /*33*/
    UINT16 usSubFrame;
    UINT16 usMeasCalcCnt;               /*34*/
    UINT16 usWakeCnt;
    UINT16 usSleepCnt;                  /*35*/
    UINT16 usCdrxSleepCnt;
    UINT16 usCdrxWakeCnt;               /*36*/
    /*UINT16 usWakeValid;*/
    UINT16 usSlaveWakeUpCnt;
    UINT16 usSlaveSleepCnt;             /*37*/
    UINT16 usCdrxOnlyRfSleepCnt;
    UINT16 usCdrxOnlyRfWakeCnt;         /*38*/
    UINT16 usRsvd[6];                   /*41*/
    UINT32 usMailTraceCnt;              /*42*/
    UINT32 usMailTraceInfo[16][4];      /*106*/
}LTE_DRX_DEBUG_INFO_STRU;

typedef struct
{
    LTE_DRX_DEBUG_INFO_STRU stLteDrxDebugInfo;
    TDS_DRX_DEBUG_INFO_STRU stTdsDrxDebugInfo;
}TL_DRX_DEBUG_STRU;

/* BEGIN: Added by xueqiuyan, 2012/9/18   PN:CMCC_DT*/
typedef enum
{
     LPHY_DT_DRX_STATUS_INFO_REQ        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x1),

}LPHY_DT_DRX_REQ_ENUM;

typedef enum
{
     LPHY_DT_DRX_STATUS_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_SG, 0x1),

}LPHY_DT_DRX_IND_ENUM;


typedef enum
{
    DRX_TIMER_INACTIVE = 0,
    DRX_TIMER_ACTIVE
}DRX_TIMER_STATUS_ENUM;

typedef UINT16 DRX_TIMER_STATUS_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16          usRsv;
} LPHY_DT_DRX_STATUS_INFO_REQ_STRU;


typedef struct
{
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRttTimer[15];
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRetranTimer[15];
} DRX_DL_HARQ_TIMER_INFO_STRU;
typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    UINT16  usDrxCycleType;
    UINT16  usActiveState;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;
    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    DRX_TIMER_STATUS_ENUM_UINT16  enShortTimer;
    UINT16  usRsv;
    DRX_DL_HARQ_TIMER_INFO_STRU   stDlHarqTimer;
} LPHY_DT_DRX_STATUS_INFO_IND_STRU;



/* END:   Added by xueqiuyan, 2012/9/18 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRX_OM_DEF_H__ */

