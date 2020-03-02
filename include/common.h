#ifndef COMMON_H_
#define COMMON_H_

/*
*Target：彩票管理系统-iotek-pw-1907
*Author：luxi
*Date：日期-2019-11-26-17:03:00
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>  
# include<termios.h>  


#define SIZE 20
#define ADMIN_NAME "admin"
#define ADMIN_PWD "1"
#define NOTTERY_NAME "nottery"
#define NOTTERY_PWD "1"
#define WIN_NUMBER_SIZE 5
#define WIN_NUMBER_RANGE 40


#include "menuView.h"
#include "getPasswd.h"
#include "user_lottery_link.h"
#include "user_link.h"
#include "issue_lottery.h"
#include "user_handler.h"
#include "lottery_handler.h"
#include "controller.h"
#include "admin.h"
#include "nottery.h"

#define FLUSH() { char ch = '\0'; while( (ch = getchar()) != '\n' && ch != EOF); }
#define PAU()  getchar(); getchar(); 



/*界面暂停*/
#define CONTINUE(X) { printf(X);  getchar(); }


//定义日期结构体
//typedef struct date{
//	int 	year;
//	int 	month;
//	int 	day;
//	int 	hour;
//	int 	min;
//	int 	sec;
//}date_t;


char *get_string(char *s, int len);

/*
	function:验证码
	return:正确返回1，否则返回0
*/
int identifyCode(void);

//小游戏
void game();

#endif
