/*******************************************************************************
 * Copyright:   Copyright (c) 2011. Hisilicon Technologies, CO., LTD.
 * Version:     V200
 * Filename:    hisi_adc_linux.h
 * Description: hisi_adc_linux.h
 * History:     
*******************************************************************************/

#ifndef __HISI_ADC_LINUX_H
#define __HISI_ADC_LINUX_H

#define ADC_ERR_MSG(printf_msg)		\	do {\		printk(KERN_ERR "%s,%d", __FILE__, __LINE__);\		printk printf_msg ;\	} 		while (0)
#ifdef DEBUG
#define ADC_INF_MSG(printf_msg)				printk printf_msg
#else
#define ADC_INF_MSG(printf_msg)
#endif

#define adc_dbg(_adc, msg...)				dev_dbg(&(_adc)->pdev->dev, msg)

#endif