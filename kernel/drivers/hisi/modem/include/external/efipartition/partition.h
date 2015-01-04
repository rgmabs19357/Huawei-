#ifndef _PARTITION_H_
#define _PARTITION_H_

struct partition {
	const char *name;
	unsigned size_kb;
};

#ifdef CONFIG_MACH_K3V2OEM1
static struct partition partitions[] = {
	{ "-",              128 },	/* ptable       128K */
	{ "xloader",        256 },	/* xloader      256K */
	{ "round",         3712 },	/* round 4M    3712K */
	{ "nvme",        4*1024 },	/* NV             4M */
	{ "misc",        4*1024 },	/* misc           4M */
	{ "splash",      8*1024 },	/* apanic         8M */
	{ "oeminfo",    32*1024 },	/* oeminfo       32M */
	{ "reserved1",   8*1024 },	/* reserved1      8M */
	{ "reserved2",   8*1024 },	/* reserved2      8M */
	{ "recovery2",   8*1024 },	/* recovery2      8M */
	{ "recovery",    8*1024 },	/* recovery       8M */
	{ "boot",        8*1024 },	/* boot           8M */
	{ "modemimage", 32*1024 },	/* modemimage    32M */
	{ "modemnvm1",   8*1024 },	/* modemnvm1      8M */
	{ "modemnvm2",   8*1024 },	/* modemnvm2      8M */
	{ "system",    512*1024 },	/* system       512M */
	{ "cache",     256*1024 },	/* cache        256M */
	{ "cust",      256*1024 },	/* cust         256M */
	{ "userdata", 6292*1024 },	/* userdata    6292M */
	{ 0, 0 },
};
#elif CONFIG_MACH_HI6620SFT
/* !!! warning !!! when partitions changed,please change  vendor\hisi\build\scripts\gen_img_vrl_tbl.py  accordingly */
static struct partition partitions[] = {
	{ "-", 512 }, /* 0 ptable 512K */
	{ "mcuimage", 256 }, /* 1 mcuimage 256K */
	{ "teeos", 512 }, /* 2 teeos 512K */
	{ "log", 256 }, /* 3 log 256K */
	{ "round", 512 }, /* 4 round 2M 512K */
	/*fix me, when move fastboot2 from boot partition to here */
	{ "fastboot2", 2*1024 }, /* 5 fastboot2 2M */
	{ "misc", 2*1024 }, /* 6 misc 4M */
	{ "modemnvbkup", 2*1024 }, /* 7 modemnvbkup 2M */
	{ "nvme", 4*1024 }, /* 8 NV 4M */
	{ "oeminfo", 32*1024 }, /* 9 oeminfo 32M */
	{ "splash", 8*1024 }, /* 10 android use 8M */
	{ "modemnvm1", 8*1024 }, /* 11 modemnvm1 8M */
	{ "modemnvm2", 8*1024 }, /* 12 modemnvm2 8M */
	{ "modemimage", 64*1024 },/* 13 modemimage 64M */
	{ "dsp", 8*1024 }, /* 14 bbe16 8M */
	{ "hifi", 4*1024 }, /* 15 hifi 2M */
	{ "modemlog", 16*1024 }, /* 16 modemlog 16M */
	{ "boot", 16*1024 }, /* 17 boot 16M */
	{ "recovery", 16*1024 }, /* 18 recovery 16M */
	{ "recovery2", 16*1024 }, /* 19 recovery2 16M */
	{ "splash2", 64*1024 }, /* 20 recovery log 64M */
	{ "cache", 256*1024 }, /* 21 cache 256M */
	{ "3rdmodem", 128*1024 }, /* 22 3rdmodem/dump 128M */
	{ "hisitest0", 2*1024 }, /* 23 reserved0 2M */
	{ "hisitest1", 2*1024 }, /* 24 reserved1 2M */
	{ "hisitest2", 4*1024 }, /* 25 reserved2 4M */
	{ "system", 1536*1024 }, /* 26 system 1536M */
	{ "cust", 512*1024 }, /* 27 customer 512M */
	{ "userdata", 4920*1024 }, /* 28 userdata 4920M */
	{ 0, 0 }, /* total 7632M*/
};


#else /*CONFIG_MACH_HI6620OEM*/
/* !!! warning !!! when partitions changed,please change  vendor\hisi\build\scripts\gen_img_vrl_tbl.py  accordingly */
static struct partition partitions[] = {
	{ "-", 512 }, /* 0 ptable 512K */
	{ "mcuimage", 256 }, /* 1 mcuimage 256K */
	{ "teeos", 512 }, /* 2 teeos 512K */
	{ "log", 256 }, /* 3 log 256K */
	{ "round", 512 }, /* 4 round 2M 512K */
	/*fix me, when move fastboot2 from boot partition to here */
	{ "fastboot2", 2*1024 }, /* 5 fastboot2 2M */
	{ "misc", 2*1024 }, /* 6 misc 4M */
	{ "modemnvbkup", 2*1024 }, /* 7 modemnvbkup 2M */
	{ "nvme", 4*1024 }, /* 8 NV 4M */
	{ "oeminfo", 32*1024 }, /* 9 oeminfo 32M */
	{ "splash", 8*1024 }, /* 10 android use 8M */
	{ "modemnvm1", 8*1024 }, /* 11 modemnvm1 8M */
	{ "modemnvm2", 8*1024 }, /* 12 modemnvm2 8M */
	{ "modemimage", 64*1024 },/* 13 modemimage 64M */
	{ "dsp", 8*1024 }, /* 14 bbe16 8M */
	{ "hifi", 4*1024 }, /* 15 hifi 2M */
	{ "modemlog", 16*1024 }, /* 16 modemlog 16M */
	{ "boot", 16*1024 }, /* 17 boot 16M */
	{ "recovery", 16*1024 }, /* 18 recovery 16M */
	{ "recovery2", 16*1024 }, /* 19 recovery2 16M */
	{ "splash2", 64*1024 }, /* 20 recovery log 64M */
	{ "cache", 256*1024 }, /* 21 cache 256M */
	{ "3rdmodem", 128*1024 }, /* 22 3rdmodem/dump 128M */
	{ "hisitest0", 2*1024 }, /* 23 reserved0 2M */
	{ "hisitest1", 2*1024 }, /* 24 reserved1 2M */
	{ "hisitest2", 4*1024 }, /* 25 reserved2 4M */
#if !defined(CONFIG_NOT_ADD_3RDMODEMNV)
	{ "3rdmodemnvm", 32*1024 }, /* 26 3rdmodemnvm 32M */
	{ "3rdmodemnvmbkp", 16*1024 }, /* 26 system 16M */
#endif
	{ "system", 1536*1024 }, /* 26 system 1536M */
	{ "cust", 512*1024 }, /* 27 customer 512M */
#if defined(CONFIG_NOT_ADD_3RDMODEMNV)
	{ "userdata", 4288*1024 }, /* 28 userdata 4920M */
#else
	{ "userdata", 4240*1024 }, /* 28 userdata 4G+(reset for userdata) */
#endif
	{ 0, 0 }, /* total 13890M*/
};


#endif

#endif

