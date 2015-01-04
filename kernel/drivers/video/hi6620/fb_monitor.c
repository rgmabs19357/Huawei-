#include "fb_monitor.h"
#include "k3_fb_def.h"
#include <linux/time.h>
#include <linux/slab.h>

int g_follow_flag;
long g_frame_time_array[MAX_NUM];
long *g_pframeinfo;
int  g_frame_num;
int  g_max_num;

/*
*  Function:    fb_getCurrTime()
*  Description£ºget current time
*/
long k3fb_getCurrTime()
{
	struct timeval curr;
	long currtime;

	do_gettimeofday(&curr);
	currtime = (curr.tv_sec) * 1000
	+ (curr.tv_usec) / 1000;
	
	return currtime;
}

/*
*  Function:    fb_follow_start()
*  Description£ºfollow start 
*/
void k3fb_follow_start()
{
    int i;
	g_follow_flag = G_FOLLOW_FLAG_START;

    k3fb_logi("TAG_Followability,start!\n");
    for(i = 0; i < MAX_NUM; i++)
    {
        g_frame_time_array[i ] = 0;
    }
    //memset(gst_frame_time, 0 ,sizeof(gst_frame_time));
    g_frame_num  = 0;
    g_pframeinfo = g_frame_time_array;
    g_max_num    = MAX_NUM;
}

void k3fb_follow_stop(void __user *p)
{
    int i = 0;
	long time = 0;
    long perframetime = 0;
    
	g_follow_flag = G_FOLLOW_FLAG_STOP;
	
    
    if (copy_from_user(&perframetime, p, sizeof(perframetime))) {
        k3fb_loge("TAG_Followability,copy from user failed!\n");
        return ;
    }
    
    k3fb_logi("TAG_Followability,receive %d frame! \n",g_frame_num);
    k3fb_logi("TAG_Followability,stop and receive refrence time = %ld\n",perframetime);

    if( 2 > g_frame_num )
    {
        return;
    }
    
    for (i = g_frame_num - 1; i >= 1; i--)
    {        
        time = g_pframeinfo[i] - g_pframeinfo[i - 1];

        /* avoid some frame too long ,delete the node */
        if(time > perframetime){
            k3fb_logi("TAG_Followability,%d frame use %ld ms,remove it! \n",i,time);
            
            g_pframeinfo[i] = 0;
            g_frame_num--;
            continue;
         }
         else{
             break;
         }
     }
}

long k3fb_first_disp_time( void __user *p)
{
	long firstdispTime = 0;
	
	if(0 == g_frame_num)
	{
        k3fb_loge("TAG_Followability,frame num is zero!\n");
        return -EFAULT;
	}
	
    if (copy_from_user(&firstdispTime, p, sizeof(firstdispTime))) {
            k3fb_loge("TAG_Followability,copy from user failed!\n");
            return -EFAULT;
        }

    /*get the first disp time*/    
	firstdispTime = g_pframeinfo[0];
    
	if (copy_to_user(p, &firstdispTime, sizeof(firstdispTime))) {
		k3fb_loge("TAG_Followability,copy2user failed!\n");
		return -EFAULT;
    }
    
	return 0;
}

long k3fb_every_disp_time(void __user *p)
{
	int i = 0;
	long time = 0;
	long referencetime;
        
    if( 2 > g_frame_num )
    {
        k3fb_loge("k3fb_every_disp_time,TAG_Followability,%d frame!\n",g_frame_num);
        return  -EFAULT;
    }
	
    if (copy_from_user(&referencetime, p, sizeof(referencetime))) {
            k3fb_loge("k3fb_every_disp_time,TAG_Followability,copy from user failed!\n");
            return -EFAULT;
        }
    k3fb_logi("k3fb_every_disp_time,TAG_Followability, referencetime %lu \n",referencetime);
    
	for (i = 0; i < g_frame_num -1; i++)
	{   
	    /*get every frame dispay used time*/
		time = g_pframeinfo[i+1] - g_pframeinfo[i];

        k3fb_logi("k3fb_every_disp_time,TAG_Followability, %d frame use %ld time!\n",i+1,time);
		if (time > referencetime)
		{
            k3fb_loge("k3fb_every_disp_time,TAG_Followability, %d frame use %ld time failed!\n",i+1,time);
			return -EFAULT;
		}			
	}
	return 0;
}

long k3fb_average_frame_rate(void __user *p)
{
	long averageframerate = 0;
	long startelem;
	long endlem;
	
	if(0 == g_frame_num)
	{
        k3fb_loge("TAG_Followability,frame num is zero!\n");
        return -EFAULT;
	}
	
    if (copy_from_user(&averageframerate, p, sizeof(averageframerate))) {
            k3fb_loge("k3fb_average_frame_rate,TAG_Followability copy from user failed!\n");
            return -EFAULT;
        }

    startelem = g_pframeinfo[0];
    
    endlem = g_pframeinfo[g_frame_num - 1];
    
    if( 0 == endlem - startelem )
    {
        k3fb_loge("k3fb_average_frame_rate,TAG_Followability no update data!\n");
        return -EFAULT;
    }
	averageframerate = (1000 * (g_frame_num - 1) ) /( endlem - startelem) ;

    k3fb_logi("k3fb_average_frame_rate,TAG_Followability averageframerate is %ld \n",averageframerate);

	if (copy_to_user(p, &averageframerate, sizeof(averageframerate))) {
		k3fb_loge("k3fb_average_frame_rate,TAG_Followability copy2user failed!\n");
		return -EFAULT;
    }
	return 0;
}

void k3fb_clear_frame_record()
{   
	g_follow_flag = G_FOLLOW_FLAG_STOP;
	g_frame_num   = 0;
	
	if( g_max_num > MAX_NUM )
	{
	    kfree(g_pframeinfo);
	}
	
    g_pframeinfo  = NULL;
	g_max_num    = 0;
    memset(g_frame_time_array, 0 ,sizeof(g_frame_time_array));
    
    k3fb_logi("TAG_Followability,clear record!\n");
}
void k3fb_listInsert(long currenttime)
{
    long *pframeinfo;
    int i;


    if( g_max_num == MAX_NUM)
    {
        if(g_max_num > g_frame_num )
        {       
            g_frame_time_array[g_frame_num] = currenttime;
            g_frame_num ++;
        }
        else
        {
    	    pframeinfo =(long *)kmalloc(sizeof(long)*MAX_NUM*4 ,GFP_KERNEL);
    	    if(NULL == pframeinfo)
    	    {
                k3fb_loge("TAG_Followability,k3fb_listInsert kmalloc fail!\n");
    	        return;
    	    }
    	    
    	    memset(pframeinfo,0x0,sizeof(long)*MAX_NUM*4);
    	    
    	    for(i = 0; i < MAX_NUM; i++ )
    	    {
    	        pframeinfo[i] = g_frame_time_array[i];
    	    }
    	    pframeinfo[g_frame_num] = currenttime;
    	    g_frame_num ++;  	    
    	    g_pframeinfo = pframeinfo;
    	    g_max_num    = MAX_NUM*4;
        }
    }
    else 
    {
        if(g_max_num > g_frame_num )
        {
            g_pframeinfo[g_frame_num] = currenttime;
            g_frame_num ++;
        }
        else
        {
            k3fb_loge("TAG_Followability,no space to record,current frame %d\n",g_frame_num);
            return;
        } 
    }
}

