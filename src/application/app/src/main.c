/*********************************************************************
*
*	Copyright (c) dreamczf@aliyun.com
*	All rights reserved.
*
*      Filename:	main.c
*      Abstract:	��Ҫ�����ļ�������
*
*      Filename:	main.c
*        Author:	caozhaofei
*       Version:	0.0.1
*          Date:	2017-11-20 15:38:17
*   Description:	�޸�˵��
*
*
*********************************************************************/
#include "app_init.h"
#include "bsp.h"
#include "task_test.h"

int main(void)
{
	bsp_init();
	app_init();
	
	while(1){
		task_test();
	}
}
