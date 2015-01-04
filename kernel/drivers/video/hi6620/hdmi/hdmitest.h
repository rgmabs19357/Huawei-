#include "si_drv_mhl_tx.h"

//LDI 寄存器取值
/*******************************************************************************
** 所有寄存器
*/

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_PLR_CTRL_HIGH = 0,
    LDI_PLR_CTRL_LOW

} LDI_PLR_CTRL_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_DISABLE = 0,
    LDI_ENABLE

} LDI_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_CTRL_DISP_MODE_DEFAULT = 0,
    LDI_CTRL_DISP_MODE_3D_FBF

} LDI_CTRL_DISP_MODE_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_CTRL_DATA_GATE_DISABLE = 0,
    LDI_CTRL_DATA_GATE_ENABLE

} LDI_CTRL_DATA_GATE_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_CTRL_BPP_RGB565 = 0,
    LDI_CTRL_BPP_RGB666,
    LDI_CTRL_BPP_RGB888

} LDI_CTRL_BPP_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_CTRL_WAIT_VSYNC_DISABLE = 0,
    LDI_CTRL_WAIT_VSYNC_ENABLE

} LDI_CTRL_WAIT_VSYNC_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_CTRL_RGB = 0,
    LDI_CTRL_BGR

} LDI_CTRL_BGR_e;


/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_WORK_MODE_TEST = 0,
    LDI_WORK_MODE_WORK

} LDI_WORK_MODE_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_WBACK_DISABLE = 0,
    LDI_WBACK_ENABLE

} LDI_WORK_MODE_WBACK_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_COLORBAR_DISABLE = 0,
    LDI_COLORBAR_ENABLE

} LDI_WORK_MODE_COLORBAR_EN_e;




/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_INT_DISABLE = 0,
    LDI_INT_ENABLE

} LDI_INT_EN_e;


/**
 * @enum
 * @brief
 */
typedef enum
{
    LDI_INT_CLR_DISABLE = 0,
    LDI_INT_CLR_ENABLE

} LDI_INT_CLR_EN_e;

/*******************************************************************************
** DC:Display Control DIS:disable EN:enable
*/

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH_DISABLE = 0,
    EDC_CH_ENABLE

} EDC_CH_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH_PIX_FMT_ARGB1555 = 0,
    EDC_CH_PIX_FMT_RGB565,
    EDC_CH_PIX_FMT_RGB888,
    EDC_CH_PIX_FMT_ARGB8888,
    EDC_CH_PIX_FMT_YUYV,
    EDC_CH_PIX_FMT_UYVY,
    EDC_CH_PIX_FMT_YVYU,
    EDC_CH_PIX_FMT_VYUY,

    EDC_CH_PIX_FMT_BUTT

} EDC_CH_PIX_FMT_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH_RGB = 0,
    EDC_CH_BGR

} EDC_CH_BGR_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH_COLORK_DISABLE = 0,
    EDC_CH_COLORK_ENABLE

} EDC_CH_COLORK_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH1_SUB_DISABLE = 0,
    EDC_CH1_SUB_ENABLE

} EDC_CH1_SUB_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH1_LINEAR_ENABLE = 0,
    EDC_CH1_TILE_ENABLE

} EDC_CH1_TILE_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH1_YFLIP_DISABLE = 0,
    EDC_CH1_YFLIP_ENABLE

} EDC_CH1_YFLIP_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH1_TILE = 0,
    EDC_CH1_SUPPER_TILE,
    EDC_CH1_MULTI_TILE,
    EDC_CH1_SUPPERMULTI_TILE

} EDC_CH1_TILE_FMT_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH1_ROT_0 = 0,
    EDC_CH1_ROT_180,
    EDC_CH1_ROT_90,
    EDC_CH1_ROT_270

} EDC_CH1_ROT_e;

/**
 * @enum
 * @brief CH12 OVLY 子项使能
 */
typedef enum
{
    EDC_CH12_OVLY_SUB_DISABLE = 0,
    EDC_CH12_OVLY_SUB_ENABLE

} EDC_CH12_OVLY_SUB_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH12_ALP_SEL_0 = 0,
    EDC_CH12_ALP_SEL_1,
    EDC_CH12_ALP_SEL_2,
    EDC_CH12_ALP_SEL_3

} EDC_CH12_ALP_SEL_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH12_MSKC_CH1 = 0,
    EDC_CH12_MSKC_CH2

} EDC_CH12_MSKC_SRC_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH12_PIX_ALP_CH2 = 0,
    EDC_CH12_PIX_ALP_CH1

} EDC_CH12_PIX_ALP_SRC_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH12_ALP_GLOBAL = 0,
    EDC_CH12_ALP_PIXEL

} EDC_CH12_ALP_SRC_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CH12_CH2_BOTTOM = 0,
    EDC_CH12_CH2_TOP

} EDC_CH12_CH2_TOP_e;


/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_ALP_SEL_0 = 0,
    EDC_CRS_ALP_SEL_1,
    EDC_CRS_ALP_SEL_2,
    EDC_CRS_ALP_SEL_3

} EDC_CRS_ALP_SEL_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_UNDER_ALP_SEL_0 = 0,
    EDC_CRS_UNDER_ALP_SEL_1,
    EDC_CRS_UNDER_ALP_SEL_2,
    EDC_CRS_UNDER_ALP_SEL_3

} EDC_CRS_UNDER_ALP_SEL_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_PIX_FMT_ARGB1555 = 0,
    EDC_CRS_PIX_FMT_RGB565,
    EDC_CRS_PIX_FMT_RGB888,
    EDC_CRS_PIX_FMT_ARGB8888

} EDC_CRS_PIX_FMT_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_RGB = 0,
    EDC_CRS_BGR

} EDC_CRS_BGR_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_COLORK_DISABLE = 0,
    EDC_CRS_COLORK_ENABLE

} EDC_CRS_COLORK_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_ALP_GLOBAL = 0,
    EDC_CRS_ALP_PIXEL

} EDC_CRS_ALP_SRC_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_ALP_BLEND_DISABLE = 0,
    EDC_CRS_ALP_BLEND_ENABLE,

} EDC_CRS_ALP_BLEND_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_CRS_DISABLE = 0,
    EDC_CRS_ENABLE,

} EDC_CRS_EN_e;


/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_CFG_OK_NO = 0,
    EDC_DC_CFG_OK_YES

} EDC_CFG_OK_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_CFG_OK_EDC2 = 0,
    EDC_DC_CFG_OK_EDC1

} EDC_CFG_OK_SEL_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_D3D_LF = 0,
    EDC_DC_D3D_RF

} EDC_DC_D3D_RF_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_FRM_FMT_2D = 0,
    EDC_DC_FRM_FMT_3D_SBS,
    EDC_DC_FRM_FMT_3D_TTB,
    EDC_DC_FRM_FMT_3D_CBC,
    EDC_DC_FRM_FMT_3D_LBL,
    EDC_DC_FRM_FMT_3D_QUINCUNX,
    EDC_DC_FRM_FMT_3D_FBF

} EDC_DC_FRM_FMT_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_PIX_FMT_RGB565 = 0,
    EDC_DC_PIX_FMT_RGB666,
    EDC_DC_PIX_FMT_RGB888

} EDC_DC_PIX_FMT_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_DITHER_DISABLE = 0,
    EDC_DC_DITHER_ENABLE

} EDC_DC_DITHER_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_ENDIAN_LITTLE = 0,
    EDC_DC_ENDIAN_BIG

} EDC_DC_ENDIAN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DISABLE = 0,
    EDC_ENABLE

} EDC_EN_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_GAMMA_DISABLE = 0,
    EDC_DC_GAMMA_ENABLE

} EDC_DC_GAMMA_EN_e;

/**
 * @enum
 * @brief EDC2的Channel1替换EDC1的Channel2
 */
typedef enum
{
    EDC_DC_CH_CHG_DISABLE = 0,
    EDC_DC_CH_CHG_ENABLE

} EDC_DC_CH_CHG_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_NROT_BURST8 = 0,
    EDC_DC_NROT_BURST16

} EDC_DC_NROT_BURST_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_DC_CRG_GT_DISABLE = 0,
    EDC_DC_CRG_GT_ENABLE

} EDC_DC_CRG_GT_EN_e;



/**
 * @enum
 * @brief
 */
typedef enum
{
    EDC_INTS_RESET = 0,
    EDC_INTS_SET

} EDC_INTS_e;

/**
 * @enum
 * @brief 中断使能
 */
typedef enum
{
    EDC_INT_ENABLE = 0,
    EDC_INT_DISABLE

} EDC_INTE_e;

/**
 * @enum
 * @brief CSC使能
 */
typedef enum
{
    EDC_CSC_DISABLE = 0,
    EDC_CSC_ENABLE

} EDC_CSC_EN_e;

/**
 * @enum
 * @brief 水平缩放位置
 */
typedef enum
{
    EDC_CH1_SCL_HSP_HFIR = 0,
    EDC_CH1_SCL_HSP_VFIR

} EDC_CH1_SCL_HSP_ORDER_e;

/**
 * @enum
 * @brief Scaler 水平、垂直子项的共用使能状态
 */
typedef enum
{
    EDC_CH1_SCL_HVSP_SUB_DISABLE = 0,
    EDC_CH1_SCL_HVSP_SUB_ENABLE

} EDC_CH1_SCL_HVSP_SUB_EN_e;

/**
 * @fn
 * @brief 垂直缩放阶数
 */
typedef enum
{
    EDC_CH1_SCL_VSR_VSC_LUMA_TAP_4 = 0,
    EDC_CH1_SCL_VSR_VSC_LUMA_TAP_2

} EDC_CH1_SCL_VSR_VSC_LUMA_TAP_e;

typedef enum
{
CHANNEL_TX2 = 0,
CHANNEL_TX3
} AUDIO_CHANNEL_TYPE;
typedef enum
{
DATA_PCM = 0,
DATA_AC3,
DATA_TYPE_NUM
} AUDIO_DATA_TYPE;
typedef enum
{
IF_HDMI = 0,
IF_SPDIF
} AUDIO_IF_TYPE;

typedef enum
{
TX_NORMAL = 0,
TX_TRANSPARENT = 0x08,
} AUDIO_TX_TYPE;


void rpt(AUDIO_CHANNEL_TYPE chn, int count);
void configEDC_3DFBF();
void asp_load_file_to_memory_regions(char *filename, u32 addr, u32 size);
void cfg_asp(AUDIO_CHANNEL_TYPE chann_typ, AUDIO_IF_TYPE if_typ,
                   u32 audioFormat, u32 SampleFreq, u32 samplesize, char *file_name);
void cfg_asp_init( u32 filesize, u32 count);
void cfg_asp_clk(u32 SampleFreq);
void K3TestAudio(inAudioTypes_t K3_AudioType);
void cfg_mhl(int sample_freq, u32 samplesize, bool bsio, u32 layout, u32 audiotype);
void TestAudioAll(int sample_freq, u32 samplesize, u32 bsio, u32 chan_num, u32 audioformat, char* file_name);

#if 0  /* si_mhl_main.h has the same definition */
#define LOG_TAG                    "[MHL]"
#define DEBUG_VERSION              1   /* 1:msgs printed; 0:no msgs */

#if DEBUG_VERSION
#define logi(fmt, ...)             pr_info(LOG_TAG"[I]%s L%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define logd(fmt, ...)             pr_info(LOG_TAG"[D]%s L%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define loge(fmt, ...)             pr_info(LOG_TAG"[E]%s L%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logi
#define logd
#endif

#define IN_FUNCTION                logi ("Begin\n")
#define OUT_FUNCTION               logi ("End\n")
#endif
