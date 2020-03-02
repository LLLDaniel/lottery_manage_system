
#include "common.h"

/*0 成功  -1 失败*/
int run_lottery(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{

	if(NULL == user_head && NULL == lottery_head && NULL == ilottery_head ){
		return -1;
	}
	
	if( 0 == ilottery_head->prev->ilot.run_status ){
		printf("当前没有要开的奖！！！\n");
		return -1;
	}
	//CONTINUE("\t\t\t-------!!!\n");
	// 1.停止发售, 获取彩票期号
	ilottery_head->prev->ilot.run_status = 0;
	int issue_number = ilottery_head->prev->ilot.issue_number;

	// 2.获取中奖号码
	int* Win_Number = NULL;
	{
		int ret = 0;
		printf("请选择开奖方式（1.手动开奖  2.机器开奖）！\n");
		scanf("%d",&ret);
		if ( ret == 1)
		{
			Win_Number =  get_winning_number_hand(ilottery_head->prev->ilot.winning_number);
		}
		else if(ret == 2)
		{
			Win_Number =  get_winning_number(ilottery_head->prev->ilot.winning_number);
		}
	}
	


	// 3.遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金
	int count = get_winning_user( user_head, lottery_head, ilottery_head , Win_Number, issue_number);

	// 4.发行彩票的中奖人数更新
	ilottery_head->prev->ilot.wined_count = count;
	printf("中奖号码为%d-%d-%d-%d-%d！！！！！！！！！！！\n",Win_Number[0],Win_Number[1],Win_Number[2],Win_Number[3],Win_Number[4]);
	printf("一共有%d张票中奖！！！！！！！！！！！\n",count);
	return 0;
}


/*0 成功  -1 失败 大于0 表示获奖者的个数*/
/*遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金*/
int get_winning_user(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head, int* Win_Number, int issue_number)
{
	// 1.遍历用户列表
	int count = 0; //统计获奖用户人数
	lottery_node_t* p = lottery_head->prev;
	printf("-----------!!!\n\n");
	while( p != lottery_head &&  issue_number == p->lot.issue_number ){
		
		lot_t lot = p->lot;
		int prize_num[5] = {0};
		int flag = 0;
		
		for( int j = 0; j< lot.note_number; j++)
		{
			for( int i = 0; i < 5; i++)
			{	
				int temp = prize_num[j];
				if( lot.winning_number[j][i] == Win_Number[i] )
				{
					prize_num[j] += 1;
				}
				if( temp == prize_num[j] )
				{
					break;
				}
			
			}
		}
		
		//打印中奖信息
		for( int i = 0;i<lot.note_number;i++)
		{
			if( 0 == prize_num[i])    
			{
				//printf("\t\t\t%s的%d-%d-%d-%d-%d没有得奖！！！\n\n", lot.owner_name, lot.winning_number[i][0],lot.winning_number[i][1], lot.winning_number[i][2], lot.winning_number[i][3], lot.winning_number[i][4]);
				// 给彩票标上奖级
				p->lot.winning_level[i] = prize_num[i];
			
			}else{
				printf("%s赢得了%d等奖！！！\n", lot.owner_name, 6-prize_num[i]);
				// 给彩票标上奖级
				p->lot.winning_level[i] = 6-prize_num[i];
				
				printf("等待%s来拿奖金!!!\n\n",lot.owner_name);
				
				flag= 1;
			
			}
		}
		memset(prize_num ,0, sizeof(int)*5);	
		p = p->prev;	
		if ( flag != 0) count += 1;	
	}
	
	
	return count;
}

/*
	功能: 公正员登陆
	参数：   	
	返回值：-1 失败 0 成功
*/
int login_nottery()
{
	char name[SIZE] = {'\0'};
	char pwd[SIZE] = {'\0'};
	printf("请输入公正员账户名: ");
	get_string(name, SIZE);
	printf("请输入密码: ");
	//get_string(pwd, SIZE);
	getPassword(pwd, SIZE);

	/*校验是否是管理员或者公证员*/
	if( strcmp(NOTTERY_NAME, name) == 0 && strcmp(NOTTERY_PWD, pwd) == 0 )
	{		
		return 0;
	}else{
		return -1;
	}
}







