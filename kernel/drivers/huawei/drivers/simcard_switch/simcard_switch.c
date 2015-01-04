#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <hsad/config_mgr.h>
#include <linux/printk.h>

#define CG_BOARDID_VIRT                     "cdma_gsm/boardid_virtual"
#define CG_MODE_ENABLE                       "cdma_gsm/cg_mode"
#define CG_CDMA_SELECT                       "cdma_gsm/cdma_select"
#define CG_CTR_GPIO                             "cdma_gsm/ctr_gpio"

struct simcard_switch_platform_data{
	unsigned int cdma_sw_cfg;
	unsigned int sw_gpio;
};

static struct simcard_switch_platform_data simcard_switch_pdata;

static ssize_t mode_cfg_swicth_set(struct device *dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
	int ret = -1;
	unsigned long state = 0;
	int gpio_flag = 0;
	if (!strict_strtol(buf, 10, &state)){
		gpio_flag = !!state;
		if (simcard_switch_pdata.cdma_sw_cfg)
			gpio_flag = !state;
		else
			gpio_flag = !!state;

		gpio_direction_output(simcard_switch_pdata.sw_gpio, gpio_flag);
		ret = count;
	}

    return ret;
}

static ssize_t mode_cfg_swicth_get(struct device *dev,
                 struct device_attribute *attr,
                 char *buf)
{
	if (__gpio_get_value(simcard_switch_pdata.sw_gpio))
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "0\n");
}

static DEVICE_ATTR(mode_cfg, 0660, mode_cfg_swicth_get, mode_cfg_swicth_set);

static int sim_card_switch_probe(struct platform_device *pdev)
{
	int ret = -1;

	ret = gpio_request(simcard_switch_pdata.sw_gpio, "sim_card_switch");
	if (ret) {
		pr_err("[sim card switch][gpio:%d] request err !\n", simcard_switch_pdata.sw_gpio);
		goto out;
	}

	ret = device_create_file(&(pdev->dev), &dev_attr_mode_cfg);
	if (ret) {
		pr_err("[sim card switch]create file err !\n");
		goto free_gpio;
	}

	pr_err("[sim card switch][probe success !]\n");
	return ret;

free_gpio:
	gpio_free(simcard_switch_pdata.sw_gpio);
out:
	return ret;
}

static int sim_card_switch_remove(struct platform_device *pdev)
{
	gpio_free(simcard_switch_pdata.sw_gpio);
	return 0;
}

static struct platform_device simcard_switch_device = {
	.name = "sim_card_switch",
	.id = -1,
};

static struct platform_driver simcard_switch_driver = {
	.probe     = sim_card_switch_probe,
	.remove    = sim_card_switch_remove,
	.driver    = {
		.name  = "sim_card_switch",
		.owner = THIS_MODULE,
	},
};

static int __init sim_card_switch_init(void)
{
	int ret = -1;
	unsigned int cg_mode;
	unsigned int cdma_slect;
	unsigned int ctr_gpio;
	if (get_hw_config_int(CG_MODE_ENABLE, &cg_mode,  NULL) &&
		get_hw_config_int(CG_CDMA_SELECT, &cdma_slect, NULL) &&
		get_hw_config_int(CG_CTR_GPIO, &ctr_gpio, NULL)){
		if (!ctr_gpio || !cg_mode) {
			pr_err("[sim card switch][mode/gpio config do not support][ctr_gpio:%d][cg_mode:%d]\n", ctr_gpio, cg_mode);
			return ret;
		}

		simcard_switch_pdata.cdma_sw_cfg = cdma_slect;
		simcard_switch_pdata.sw_gpio = ctr_gpio;
		platform_device_register(&simcard_switch_device);
		ret = platform_driver_register(&simcard_switch_driver);
	} else {
		pr_err("[sim card switch][mode/cdma_select/ctr_gpio config do not exist]\n");
	}
	pr_info("[sim card switch][gpio:%d][sw_cfg:%d]\n", simcard_switch_pdata.sw_gpio, simcard_switch_pdata.cdma_sw_cfg);

	return ret;
}

static void __exit sim_card_switch_exit(void)
{
	platform_device_unregister(&simcard_switch_device);
	platform_driver_unregister(&simcard_switch_driver);
}

module_init(sim_card_switch_init);
module_exit(sim_card_switch_exit);
MODULE_LICENSE("GPL");
