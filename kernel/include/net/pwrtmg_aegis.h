/*
 *  include/net/pwrtmg_aegis.h
 *
 *  Copyright (C) 2013 Huawei Device Co.,Ltd.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 */
#ifndef _PWRTMG_AEGIS_H_
#define _PWRTMG_AEGIS_H_
extern void aegis_tcp4_discard_pkt_increase(void);
extern void aegis_udp4_discard_pkt_increase(void);
extern void aegis_listen_port_add(uint16_t port);
extern void aegis_listen_port_delete(uint16_t port);
#endif  //_PWRTMG_AEGIS_H_
