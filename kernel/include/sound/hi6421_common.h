#ifndef __HI6421_COMMON_H_
#define __HI6421_COMMON_H_

struct hi6421_codec_platform_data {
	/* clock name */
	char *clk_name;
	/* regulator name */
	char *regulator_name;
    /* get pmuspi register base address */
	char *reg_base_name;
    /* gpio reset pin */
    uint32_t gpio_reset;
    /* gpio label */
	char *gpio_label;
#ifdef CONFIG_MFD_HI6421_IRQ
	/* irq for */
	unsigned irq[4];
#endif
};

#endif

struct hi6401_codec_platform_data {
	/* clock name */
	char *clk_name;
	/* regulator name */
	char *regulator_name;
    /* get pmuspi register base address */
	char *reg_base_name;
	/* iomux name */
	char *iomux_name;
    /* gpio reset pin */
    uint32_t gpio_reset;
    /* gpio label */
	char *gpio_label;
    /* gpio ana 1.8v pin */
    uint32_t gpio_avdd_1v8;
    /* gpio digital 1.8v pin */
    uint32_t gpio_dvdd_1v8;
    /* gpio ana 3.15v pin */
    uint32_t gpio_avdd_3v15;
    #ifdef CONFIG_MACH_HI6620OEM
    char* reg_dvdd_1v8;
    char* reg_avdd_1v8;
    char* reg_avdd_3v15;
    #endif
    /* gpio intr pin */
    uint32_t gpio_intr;
};

