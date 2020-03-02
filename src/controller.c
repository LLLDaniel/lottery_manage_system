


#include "common.h"

/*选择身份界面*/
int identity_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head)
{
	int flag = 1;
	while(flag){
		int choice = identity_view();
		switch(choice){
			case 1:
				/*管理员*/
				admin_main_control(user_head, ilottery_head, lottery_head);
				break;
			case 2:
				/*公证员*/
				nottery_main_control(user_head, ilottery_head, lottery_head);
				break;

			case 3:
				/*普通用户*/
				user_main_control(user_head, ilottery_head, lottery_head);
				break;		
			case 0:
				/*退出*/
				flag = 0;
				break;
			default:
				break;
		}
	}
	return 0;
}

/*用户主界面控制函数*/
void user_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head)
{
	int flag = 1;
	while(flag){
		int choice = main_view();
		if(choice == 1){
			/*注册*/
			int ret = register_user(user_head);
			if(ret == 0){
				//display_user_link(user_head);
				CONTINUE("注册成功！！！\n");
			}else{
				CONTINUE("注册失败！！！\n");
			}

		}else if(choice == 2){
			/*登录*/
			user_t* ret = login_user(user_head);
			if( ret == NULL)
			{
				CONTINUE("登陆失败，该用户不存在或者密码错误！！！\n");
			}else{
				printf("登陆成功，欢迎！！！\n");
				user_control(ret, user_head, lottery_head, ilottery_head);
			}

		}else if( choice == 0 ){
			flag = 0;
		}
	}
	

}

/*用户界面控制函数*/
void user_control(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{
	int flag = 1;
	
	while(flag){
		system("clear");
		int choice = user_view();

		switch(choice){
			case 1:
				/*充值*/
				recharge_user(user);
				PAU();
				break;
			case 2:
				/*查看个人信息*/
				display_user_node(user);
				PAU();
				break;

			case 3:
				/*修改个人信息*/
				{
					int ret = change_info_user(user);
					if(ret == 0){
						printf("修改成功，请重新登陆!!!\n");
						PAU();
						return;
					}else{
						printf("修改失败!!!\n");
						PAU();
					}
				}
				break;
			case 4:
				/*查看往期购买彩票中奖信息*/
				display_user_lottery_link(user, lottery_head);
				PAU();
				break;
			case 5:
				/*购买彩票*/
				{
					int ret = user_buy_lottery(user, lottery_head, ilottery_head);
					if(ret == 0){
						printf("༺  ༺  ༺  ༺  ༺  购买成功!!!༻  ༻  ༻  ༻  ༻    \n");
					}else{
						printf("（*^﹏^*）很抱歉，购买失败!!!\n");
					}
				}
				PAU();			
				break;
			case 6:
				/*兑换奖励*/
				{
					int ret = user_redeem_lottery(user, lottery_head, ilottery_head);
					if(ret == 0){
						printf("\n༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻     \n\n");
						printf("༺  ༺  ༺  ༺  ༺  恭喜你，兑换成功!!!༻  ༻  ༻  ༻  ༻     \n\n");
						printf("༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻     \n\n");
					}else{
						printf("（*^﹏^*）很抱歉，兑换失败!!!\n");
					}
				}
				PAU();	
				PAU();		
				break;
			case 7:
				/*益智游戏*/
				game();
				PAU();			
				break;		
				
			case 8:
				/*注销用户*/
				{
					int ret = free_user_node(user, user_head, lottery_head);
					if(ret == 0){
						CONTINUE("注销成功，欢迎再次使用中国福利彩票系统!!!\n");
						return ;
					}else{
						printf("（*^﹏^*）很抱歉，注销失败!!!\n");
					}
				}
				PAU();			
				break;		
			
			
			case 0:
				/*退返上一层*/
				flag = 0;
				break;
			default:
				break;
		}
	}	
}

/*管理员主界面控制函数*/
void admin_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head)
{
	int ret = login_admin();
	if( 0 == ret ){
		printf("进入管理员界面！！！\n");
		admin_control(user_head, ilottery_head);
	}else{
		CONTINUE("登入管理员系统失败！！！\n");
	}
}

/*管理员界面控制函数*/
void admin_control(user_head_t* user_head, ilottery_node_t* ilottery_head)
{


	int flag = 1;
	
	while(flag){
		system("clear");
		int choice = admin_view();
		switch(choice){
			case 1:
				/*发行彩票*/
				{
					int ret = issue_ilottery(ilottery_head);
					if(ret == 0){
						CONTINUE("发行成功!!!\n");
					}else{
						CONTINUE("发行失败!!!\n");
					}
				}
				break;
			case 2:
				/*查看往期彩票*/
				printf("查看往期彩票!!!\n");
				display_ilottery_link(ilottery_head);
				PAU();
				break;
			case 3:
				/*查看彩民信息*/
				printf("查看彩民信息!!!\n");
				display_user_link(user_head);
				PAU();
				break;
		
			case 4:
				/*根据彩民金额排序*/
				printf("根据彩民金额排序!!!\n");
				sort_money_user(user_head);
				CONTINUE("排序成功!!!\n");		
				break;
			case 5:
				/*根据彩民余额区间查询彩民*/
				printf("根据彩民余额区间查询彩民!!!\n");
				display_money_section_user(user_head);	
				PAU();	
				break;

			case 0:
				/*退返上一层*/
				flag = 0;
				break;
			default:
				break;
		}
	}	
}

/*公正员主界面控制函数*/
void nottery_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head)
{
	int ret = login_nottery();
	if( 0 == ret ){
		printf("进入公正员界面！！！\n");
		nottery_control(user_head, lottery_head, ilottery_head);
	}else{
		CONTINUE("登入公正员系统失败！！！\n");
	}
}

/*公正员界面控制函数*/
void nottery_control(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{

	int flag = 1;
	
	while(flag){
		system("clear");
		int choice = nottery_view();
		switch(choice){
			case 1:
				/*彩票开奖*/			
				printf("彩票开奖!!!\n");
				run_lottery(user_head, lottery_head, ilottery_head);
				PAU();
				break;
			case 2:
				/*查看彩票信息*/
				printf("查看彩票信息!!!\n");
				display_ilottery_link(ilottery_head);
				PAU();
				break;
			case 0:
				/*退返上一层*/
				flag = 0;
				break;
			default:
				break;
		}
	}	
}







