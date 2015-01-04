#ifndef _XT_PORT_H
#define _XT_PORT_H

#include <linux/types.h>

/* Port matching stuff */
struct xt_port_info {
    __u16 tcp_port_using[2];        /* Port range. */
    __u8 invflags;                  /* Inverse flags */
};

/* Values for "inv" field in struct xt_port_info. */
#define XT_PORT_INV_TCP_PORT_USING     0x01 /* Invert the sense of ports. */
#define XT_PORT_INV_MASK               0x01 /* All possible flags. */

#endif /*_XT_PORT_H*/

