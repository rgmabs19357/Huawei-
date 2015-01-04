#include <mach/clock.h>
#include <linux/clk.h>
#include <linux/device.h>

struct clk *g_clk = NULL;
extern struct clk_lookup k3v2_clk_lookups[];


int board_clk_get(unsigned int id)
{
	/*check id valid*/
	
	if(k3v2_clk_lookups[id].dev_id != NULL) {
		printk("dev name:%s clk index:%d\n", k3v2_clk_lookups[id].dev_id, id);
		g_clk = clk_get((struct device *)(k3v2_clk_lookups[id].dev_id), NULL);
	}
	else if(k3v2_clk_lookups[id].con_id != NULL) {
		printk("clk name:%s clk index:%d\n", k3v2_clk_lookups[id].con_id, id);
		g_clk = clk_get(NULL, k3v2_clk_lookups[id].con_id);
	}
	else	{
		printk("invalid id:%d\n", id);
		return -1;
	}
	
	if (g_clk == NULL)
	{
		printk("board_clk_get: g_clk == NULL\n");
		return -1;
	}
	printk("board_clk_get, g_clk: %p\n", g_clk);

	return 0;
}

int board_clk_set_rate(long int rate)
{
	int ret = 0;
	ret = clk_set_rate(g_clk, rate);
	if (ret < 0)
		return 1;
	
	return 0;
}

/* board side system test begin */
/* source clock without parent clock */
#define BOARDST_CLK_SOURCE "clkin_sys"
#define BOARDST_CLK_SYS_RATE 19200000
int board_st01_clk_set_rate(void)
{
	/* only one scene */
	int ret = 0;
	struct clk *clk = NULL;

	clk = clk_get(NULL, BOARDST_CLK_SOURCE);
	ret = clk_set_rate(clk, BOARDST_CLK_SYS_RATE);
	printk("clock %s rate: %lu, ret: %d\n", clk->name, clk->rate, ret);

	if (ret != -1)
		return 1;

	return 0;
}

/* clock with one parent clock */
#define BOARDST_CLK_EDC0_SRC "clk_dsppll_edc0_core_gated"		/* no divisor */
#define BOARDST_CLK_EDC1 "clk_edc1_core"		/* has divisor */
#define BOAEDST_CLK_EDC0_SRC_RATE 1200000000		/* dsppll output rate */
#define BOAEDST_CLK_EDC1_RATE 1188000000/4			/* hdmipll output 1188000 rate */

int board_st02_clk_set_rate(void)
{
	int ret1 = 0;
	int ret2 = 0;
	struct clk *clk = NULL;

	/* clock no divisor */
	clk = clk_get(NULL, BOARDST_CLK_EDC0_SRC);
	ret1 = clk_set_rate(clk, BOAEDST_CLK_EDC0_SRC_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	/* clock has divisor */
	clk = clk_get(NULL, BOARDST_CLK_EDC1);
	ret2 = clk_set_rate(clk, BOAEDST_CLK_EDC1_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	if (ret1 != -1 || ret2 == -1)
	{
		printk("ret1: %d\nret2: %d\n", ret1, ret2);
		return 1;
	}
	return 0;
}

/* clock has one parent with more then one grand parents,
 * set too small or small rate
 */
#define BOARDST_CLK_EDC0 "clk_edc0_core"	/* one grand parent */
#define BOARDST_CLK_EDC0_RATE 1200000000/5
#define BOARDST_CLK_EDC0_TOO_SMALL_RATE 1200000000/128

int board_st03_clk_set_rate(void)
{
	int ret1 = 0;
	int ret2 = 0;
	struct clk *clk = NULL;

	/* clock with one grand parent */
	clk = clk_get(NULL, BOARDST_CLK_EDC0);
	ret1 = clk_set_rate(clk, BOARDST_CLK_EDC0_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	/* clock set too small rate */
	clk = clk_get(NULL, BOARDST_CLK_EDC0);
	ret2 = clk_set_rate(clk, BOARDST_CLK_EDC0_TOO_SMALL_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	if (ret1 == -1 || ret2 != -1)
	{
		printk("ret1: %d\nret2: %d\n", ret1, ret2);
		return 1;
	}

	return 0;
}

/* clock set too large rate */
#define BOARDST_CLK_EDC0_PIX_LDI "clk_edc0_pix_ldi"
#define BOARDST_CLK_EDC0_PIX_LDI_RATE 1440000000	/* PERIPHPLL output rate (largest rate) */
#define BOARDST_CLK_EDC0_PIX_LDI_TOO_LARGE_RATE 1500000000

int board_st04_clk_set_rate(void)
{
	int ret1 = 0;
	int ret2 = 0;
	struct clk *clk = NULL;

	/* clock with more then one grand parent */
	clk = clk_get(NULL, BOARDST_CLK_EDC0_PIX_LDI);
	ret1 = clk_set_rate(clk, BOARDST_CLK_EDC0_PIX_LDI_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	/* clock set to large rate */
	clk = clk_get(NULL, BOARDST_CLK_EDC0_PIX_LDI);
	ret2 = clk_set_rate(clk, BOARDST_CLK_EDC0_PIX_LDI_TOO_LARGE_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	if (ret1 != 0 || ret2 != 0)
	{
		printk("ret1: %d\nret2: %d\n", ret1, ret2);
		return 1;
	}

	return 0;
}

/* clock has more then one parents, set proper or non-proper rate */
#define BOARDST_CLK_MALI "clk_mali"
#define BOARDST_CLK_MALI_HIGHT_RATE 1066000000/2
#define BOARDST_CLK_MALI_RATE 500000000/2
#define BOARDST_CLK_MALI_NON_PROPER_RATE 110000000

/* clock set proper rate of higher rate parent available */
int board_st05_clk_set_rate(void)
{
	int ret = 0;
	struct clk *clk = NULL;

	/* set proper rate of higher rate parent available */
	clk = clk_get(NULL, BOARDST_CLK_MALI);
	ret = clk_set_rate(clk, BOARDST_CLK_MALI_HIGHT_RATE);
	printk("clock %s rate: %lu ret: %d\n", clk->name, clk->rate, ret);
	
	if (ret != 0)
		return 1;

	return 0;
}

/* clock set non-proper rate of another parent */
int board_st06_clk_set_rate(void)
{
	int ret1 = 0;
	int ret2 = 0;
	struct clk *clk = NULL;

	/* set non-proper rate of current parent */
	clk = clk_get(NULL, BOARDST_CLK_MALI);
	ret1 = clk_set_rate(clk, BOARDST_CLK_MALI_NON_PROPER_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);
	
	/* set proper rate of current parent */
	clk = clk_get(NULL, BOARDST_CLK_MALI);
	ret2 = clk_set_rate(clk, BOARDST_CLK_MALI_RATE);
	printk("clock %s rate: %lu\n", clk->name, clk->rate);

	if (ret1 != 0 || ret2 != 0)
	{
		printk("ret1: %d\nret2: %d\n", ret1, ret2);
		return 1;
	}

	return 0;
}

/* board side system test begin */
	
int board_st_clk_set_rate(void)
{
	//board_st01_clk_set_rate();
	board_st02_clk_set_rate();
	board_st03_clk_set_rate();
	board_st04_clk_set_rate();
	board_st05_clk_set_rate();
	board_st06_clk_set_rate();
	
	return 0;
}
