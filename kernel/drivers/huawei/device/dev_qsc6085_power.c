#include <../drivers/modem/modem_boot_qsc6085.h>
#include <linux/platform_device.h>

/* device to manage power of QSC6085 modem */

static struct modem_qsc6085_platform_data  modem_qsc6085_plat_data = {
    .flashless = false,
    .gpios = {
        [COMM_WAKEUP_SLAVE]        = {GPIO_13_6, GPIOF_OUT_INIT_LOW, "comm_wakeup_slave"},     //GPIO_095_WAKEUP_SLAVE
        [MODEM_BOOT_POWER_ON]      = {GPIO_15_4, GPIOF_OUT_INIT_LOW, "modem_boot_power_on"},   //GPIO_096_M_ON1
        [MODEM_BOOT_PMU_RESET]    = {GPIO_15_6, GPIOF_OUT_INIT_HIGH, "modem_boot_pmu_reset"},  //GPIO_097_M_RESET_PWRDWN_N
        [MODEM_BOOT_POWER_IND]    = {GPIO_14_0, GPIOF_IN, "modem_boot_power_ind"}, //GPIO_094_MODEM_POWER_IND
        [MODEM_BOOT_RESET_IND]    = {GPIO_0_3, GPIOF_IN, "modem_boot_reset_ind"}, //GPIO_098_M_RST_STATE

        [COMM_DOWNLOAD_EN]  = {GPIO_13_5, GPIOF_OUT_INIT_LOW, "comm_download_en"},   //GPIO_114_DOWNLOAD_EN
        [COMM_WAKEUP_HOST]  = {GPIO_0_0, GPIOF_IN, "comm_wakeup_host"},  //GPIO_113_WAKE_H
//        [MODEM_SIM_CARD_SWITCH]   = {GPIO_7_6, GPIOF_OUT_INIT_LOW, "modem_sim_card_switch"},
//        [MODEM_SIM_CARD_DETECT]   = {54, GPIOF_IN, "modem_sim_card_detect"},
        [MODEM_BOOT_PSHOLD]   	  = {GPIO_15_3, GPIOF_OUT_INIT_LOW, "modem_boot_pshold"},
    },
    .block_name = "block_modem",
};

static struct platform_device modem_device_qsc6085_boot = {
    .name       = MODEM_DEVICE_BOOT(MODEM_QSC6085),    //"qsc6085_boot",
    .id = -1,
    .dev = {
        .platform_data = &modem_qsc6085_plat_data,
    },
};

static int __init qsc6085_power_dev_init(void)
{
    int ret = 0;
    pr_info("%s: enter\n",__func__);
    ret = platform_device_register(&modem_device_qsc6085_boot);
    pr_info("%s: ret=%d\n", __func__, ret);
    return ret;
}

arch_initcall(qsc6085_power_dev_init);
