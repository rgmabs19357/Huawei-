#ifndef _HISILICON_EFUSE_H_
#define _HISILICON_EFUSE_H_

#define OK      			              (0)
#define ERROR  				       (-1)
#define ERROR_EXIT_PD			(-2)	/* 不能退出power down模式 */
#define ERROR_ENTER_PD			(-3)	/* 不能退出power down模式 */
#define ERROR_APB_PGM_DIS		(-4)	/* 当前eFusec不允许烧写 */
#define ERROR_EFUSEC_READ		(-5)	/* 不能完成一次eFuse读操作 */
#define ERROR_PRE_WRITE		(-6)	/* 未完成预烧写置位 */
#define ERROR_PG_OPERATION	(-7)	/* 不能完成一次eFuse写操作 */
#define ERROR_SECURE_OS              (-8)	/* 安全OS执行错误 */

#define HISI_EFUSE_READ_CHIPID		       0x1000
#define HISI_EFUSE_READ_DIEID			0x2000
#define HISI_EFUSE_WRITE_CHIPID		0x3000
#define HISI_EFUSE_READ_AUTHKEY		0x4000
#define HISI_EFUSE_WRITE_AUTHKEY		0x5000
#define HISI_EFUSE_READ_CHIPIDLEN		0x6000
#define HISI_EFUSE_WRITE_DEBUGMODE    0x7000
#define HISI_EFUSE_READ_DEBUGMODE	0x8000

#define BIT_64   64
#define BYTE_8    8
#define BYTE_20  20
#define EFUSE_BUF_SIZE  256

#endif
