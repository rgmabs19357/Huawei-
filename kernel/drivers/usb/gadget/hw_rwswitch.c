/*
 * huawei rework switch code.
 *
 */

/* #define DEBUG */
/* #define VERBOSE_DEBUG */


/* 0: no usb port switch request has been sent
 * 1: one usb port switch request has already been sent at least
 */
static int switch_request = 0;

/*
 *  * usb_port_switch_request: submit usb switch request by sending uevent
 *  * Return value: void
 *  * Side effect : none
 *  */
static void usb_port_switch_request(int usb_switch_index)
{
	char event_buf[32];
	char *envp[2] = {event_buf, NULL};
	int ret;

	snprintf(event_buf, sizeof(event_buf),"USB_PORT_SWITCH=%d", usb_switch_index);
	ret= kobject_uevent_env(&_android_dev->dev->kobj, KOBJ_CHANGE, envp);
	if (ret < 0){
		pr_err("%s: uevent sending failed with ret = %d\n", __func__, ret);
	}else{
		pr_info("%s: uevent USB_PORT_SWITCH=%d send OK %d", __func__, usb_switch_index, ret);
	}
	switch_request = usb_switch_index + 1;
	return;
}

static ssize_t switch_request_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%d\n", switch_request);
}

static DEVICE_ATTR(switch_request, S_IRUGO, switch_request_show, NULL);

