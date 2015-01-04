#include "msp_errno.h"
#include "msp_nvim.h"
#include "msp_cfg.h"

VOS_UINT32 nvim_GetImei(VOS_CHAR szImei[16])
{
    VOS_UINT32 ulRst;
    VOS_UINT16 usLen = 0;
    VOS_UINT32 i = 0;
    VOS_UINT8 ucCheckData = 0;
    VOS_UINT8 aucTmp[NVM_IMEI_LENTH+1] = {0};

    usLen = NVM_IMEI_LENTH+1;

    ulRst = NVM_Read(EN_NV_ID_IMEI, aucTmp, usLen);

    if(ulRst != ERR_MSP_SUCCESS)
    {
        return ulRst;
    }
    else
    {
        for (i = 0; i < (NVM_IMEI_LENTH - 1); i += 2)
        {
            ucCheckData += (VOS_UINT8)(((aucTmp[i])
                           +((aucTmp[i + 1] * 2) / 10))
                           +((aucTmp[i + 1] * 2) % 10));
        }
        ucCheckData = (10 - (ucCheckData%10)) % 10;

        for (i = 0; i < usLen; i++)
        {
            *(szImei + i) = *(aucTmp + i) + 0x30;
        }

        szImei[NVM_IMEI_LENTH - 1] = ucCheckData + 0x30;
        szImei[NVM_IMEI_LENTH] = 0;
    }

    return ulRst;
}



