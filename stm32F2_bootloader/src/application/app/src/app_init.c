/*********************************************************************
*
*	Copyright (c) dreamczf@aliyun.com
*	All rights reserved.
*
*      Filename:	app_init.c
*      Abstract:	��Ҫ�����ļ�������
*
*      Filename:	app_init.c
*        Author:	caozhaofei
*       Version:	0.0.1
*          Date:	2017-11-20 15:12:28
*   Description:	�޸�˵��
*
*
*********************************************************************/

#include "app_init.h"

#include <stdio.h>


const S_VERSION gs_ver = {
	{0,0,1},   //X.Y.ZZ Ӳ���汾��
	{0,0,1}     //X.Y.ZZ ����汾��
};

void system_init_info(void)
{
	printf("\r\n\r\n");
	printf("System Start\r\n");
	printf("Build:%s %s\r\n",__DATE__,__TIME__); //��ȡ�������ڡ�ʱ��
	printf("Software Ver :%d.%d.%d\r\n",gs_ver.s_ver[0],gs_ver.s_ver[1],gs_ver.s_ver[2]);
	printf("Hardware Ver :%d.%d.%d\r\n",gs_ver.h_ver[0],gs_ver.h_ver[1],gs_ver.h_ver[2]);
	printf("Device UUID:\r\n");
}

void app_init(void)
{
	system_init_info();
}

