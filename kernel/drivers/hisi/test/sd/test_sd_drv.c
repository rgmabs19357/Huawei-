/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_sd_drv.c
  版 本 号   : 初稿
  生成日期   : 2012年11月02日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月02日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/slab.h>
#include <linux/kernel.h>


#include "test_sd_drv.h"
#include <drv_sd_if.h>


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
int g_bufferSize = 0x10000;

 unsigned char *s_buffer = NULL;
 unsigned char *d_buffer = NULL;
 unsigned char *c_buffer = NULL;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
int bsp_sd_data_cmp(char *buffer1,char *buffer2)
{
    int j = 0;

    /*compare with write data*/
    for(j=0; j<512; j++){

    	if((buffer1[j]) != (buffer2[j])){

            (void)printk("read don't = write!,read [%d] data is %d,write data is %d\n",j,*buffer1,*buffer2);
            return -1;
        }

    }

    return 0;
}


int test_sd_write_single(void)
{
    int ret       = 0;
    char buff_w[512] = {0x55};
    char buff_r[512] = {0};

    ret = sd_get_status();
    if(-1 == ret)
    {
        (void)printk("test_sd_write_single is error! card is out \n\r");
        return -1;

    }

    ret = sd_sg_init_table(buff_w,1*0x200);
    if (0 != ret){

         (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
         return -1;

    }

    ret = sd_multi_transfer(0,1,512,1);
    if (0 != ret){

         (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
         return -1;

    }

    ret = sd_sg_init_table(buff_r,1*0x200);
    if (0 != ret){

         (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
         return -1;

    }

    ret = sd_multi_transfer(0,1,512,0);
    if (0 != ret){

         (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
         return -1;

    }

    ret = bsp_sd_data_cmp(buff_w,buff_r);
    if (0 != ret){

         (void)printk("bsp_sd_data_cmp is error! ret is %x \n\r",ret);
         return -1;

    }

    return 0;

}


int test_sd_write_multi(int blkcount)
{
     int sd_cap  = sd_get_capacity();
     int i = 0;
     int loop_cnt = sd_cap;
     int ret       = 0;
     char buff_w[512] = {0x55};
     char buff_r[512] = {0};

     if (blkcount > loop_cnt){

         (void)printk("bsp_sd_multi_write_test: g_test_loop is over \n\r");

         return -1;
     }

     for(i = 0; i< blkcount; i++)
     {

        ret = sd_get_status();
        if(-1 == ret)
        {
            return -1;

        }

        ret = sd_sg_init_table(buff_w,1*0x200);
        if (0 != ret){

             (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_multi_transfer(i,1,512,1);
        if (0 != ret){

             (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_sg_init_table(buff_r,1*0x200);
        if (0 != ret){

             (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_multi_transfer(i,1,512,0);
        if (0 != ret){

             (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = bsp_sd_data_cmp(buff_w,buff_r);
        if (0 != ret){

             (void)printk("bsp_sd_data_cmp is error! ret is %x \n\r",ret);
             return -1;
        }

     }

     return 0;
}


int test_sd_write_all(void)
{
     int sd_cap  = sd_get_capacity();
     int i = 0;
     int loop_cnt = sd_cap;
     int ret       = 0;
     char buff_w[512] = {0x55};
     char buff_r[512] = {0};

     for(i = 0; i<loop_cnt; i++)
     {

        ret = sd_get_status();
        if(-1 == ret)
        {
            return -1;

        }

        ret = sd_sg_init_table(buff_w,1*0x200);
        if (0 != ret){

             (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_multi_transfer(i,1,512,1);
        if (0 != ret){

             (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_sg_init_table(buff_r,1*0x200);
        if (0 != ret){

             (void)printk("sd_sg_init_table is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = sd_multi_transfer(i,1,512,0);
        if (0 != ret){

             (void)printk("sd_multi_transfer is error! ret is %x \n\r",ret);
             return -1;

        }

        ret = bsp_sd_data_cmp(buff_w,buff_r);
        if (0 != ret){

             (void)printk("bsp_sd_data_cmp is error! ret is %x \n\r",ret);
             return -1;
        }

     }

     return 0;
}


int test_sd_read_single(void)
{
    int ret = 0;

    ret = test_sd_write_single();
    if (0 != ret){

        (void)printk("bsp_sd_single_read_test is error! ret is %x \n\r",ret);

        return -1;

    }

    return 0;
}


int test_sd_read_multi(int blockcount)
{
    int ret = 0;

    ret = test_sd_write_multi(blockcount);
    if (0 != ret){

        (void)printk("bsp_sd_multi_read_test is error! ret is %x \n\r",ret);

        return -1;

    }

    return 0;
}


int test_sd_read_all(void)
{
    int ret = 0;

    ret = test_sd_write_all();
    if (0 != ret){

        (void)printk("bsp_sd_all_read_test is error! ret is %x \n\r",ret);

        return -1;

    }

    return 0;
}


void set_buffer_size(int size)
{
    g_bufferSize = size;

}

int get_buffer_size(void)
{
    return g_bufferSize;

}

int sd_multi_w_prepare(unsigned char value1, unsigned char value2)
{
    int i = 0;
    unsigned char *buffer = NULL;
    int ret  = 0;

    s_buffer = kzalloc(SD_MULTI_BUFFER_SIZE, GFP_KERNEL);
    if (NULL == s_buffer)
    {
        printk("s_buffer kmalloc fail!\n");
        return -1;
    }
    buffer = s_buffer;
    for(i = 0; i < (SD_MULTI_BUFFER_SIZE >> 1); i++)
    {
        *(buffer+2*i) = value1;
        *(buffer+2*i+1) = value2;
    }
    ret = sd_sg_init_table(s_buffer,SD_MULTI_BUFFER_SIZE);
    return ret;
}


int sd_multi_r_prepare(void)
{
    int ret = 0;
    d_buffer = kzalloc(SD_MULTI_BUFFER_SIZE, GFP_KERNEL);
    if (NULL == d_buffer)
    {
        printk("d_buffer kmalloc fail!\n");
        return -1;
    }
    ret = sd_sg_init_table(d_buffer,SD_MULTI_BUFFER_SIZE);
    return ret;
}

int sd_multi_r_compare_prepare(unsigned char value1, unsigned char value2)
{
    int i = 0;
    unsigned char *buffer = NULL;
    int ret = 0;

    d_buffer = kzalloc(SD_MULTI_BUFFER_SIZE, GFP_KERNEL);
    c_buffer = kzalloc(SD_MULTI_BUFFER_SIZE, GFP_KERNEL);

    buffer = c_buffer;
    for(i = 0; i < (SD_MULTI_BUFFER_SIZE >> 1); i++)
    {
        *(buffer+2*i) = value1;
        *(buffer+2*i+1) = value2;
    }

    ret = sd_sg_init_table(d_buffer,SD_MULTI_BUFFER_SIZE);
    return ret;
}


int sd_test_multi_w_test(unsigned int blkAddr)
{
    int ret,capacity,blknum;

    blknum = SD_MULTI_BUFFER_SIZE/SDMMC_BLOCK_BYTE;
    capacity = sd_get_capacity();

    if((blkAddr + blknum) > capacity)
    {
        printk("block number is over capacity!\n");
        return -1;
    }
    ret = sd_multi_transfer(blkAddr, blknum, SDMMC_BLOCK_BYTE, 1);
    if (ret)
    {
        printk("sd_test_write err!\n");
        kzfree(s_buffer);
        s_buffer = NULL;
        return ret;
    }

    return 0;
}

int sd_test_multi_r_test(unsigned int blkAddr)
{
    int ret,i,capacity,blknum;
    unsigned char *buffer = NULL;
    capacity = sd_get_capacity();
    blknum = SD_MULTI_BUFFER_SIZE/SDMMC_BLOCK_BYTE;

    if((blkAddr + blknum) > capacity)
    {
        printk("block number is over capacity!\n");
        return -1;
    }

    buffer = d_buffer;
    ret = sd_multi_transfer(blkAddr, blknum, SDMMC_BLOCK_BYTE, 0);
    if (ret)
    {
        printk("sd_test_read err!\n");
        kzfree(d_buffer);
        d_buffer = NULL;
        return ret;
    }

    else
    {
        /*printk 512B*/
        for(i=0;i<512;i++)
        {
            printk("d_buffer[%d]=%d\n\r",i,*buffer++);

        }
    }

    kzfree(d_buffer);
    d_buffer = NULL;

    return 0;
}


int sd_test_multi_r_compare_test(unsigned int blkAddr)
{
    int ret,j,capacity,blknum;
    unsigned char *buffer1 = NULL;
    unsigned char *buffer2 = NULL;
    capacity = sd_get_capacity();
    blknum = SD_MULTI_BUFFER_SIZE/SDMMC_BLOCK_BYTE;

    if((blkAddr + blknum) > capacity)
    {
        printk("block number is over capacity!\n");
        return (u32)ERROR;
    }

    buffer1 = d_buffer;
    buffer2 = c_buffer;

    ret = sd_multi_transfer(blkAddr, blknum, SDMMC_BLOCK_BYTE, 0);
    if (ret)
    {
        printk("sd_test_read err!\n");
        kzfree(d_buffer);
        kzfree(c_buffer);
        d_buffer = NULL;
        c_buffer = NULL;
        return ret;
    }

    else
    {
        /*compare with write data*/
        for(j=0;j<SD_MULTI_BUFFER_SIZE;j++)
        {
            if(*(buffer1++) != *(buffer2++))
            {

                printk("read don't = write!,read [%d] data is %d,write data is %d\n",j,*buffer1,*buffer2);
                kzfree(d_buffer);
                kzfree(c_buffer);
                d_buffer = NULL;
                c_buffer = NULL;
                return -1;
            }
            if (j<512)
            {
                printk("d_buffer[%d]=%d\n\r",j,*buffer1);
            }

        }
    }

    kzfree(d_buffer);
    kzfree(c_buffer);
    d_buffer = NULL;
    c_buffer = NULL;
    return 0;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

