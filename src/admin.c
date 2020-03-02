
#include "common.h"

/*0 成功  -1 失败*/
int issue_ilottery(ilottery_node_t* ilottery_head)
{
	CONTINUE("开始发布彩票!!!\n");
	if(NULL == ilottery_head){
		return -1;
	}

	if( ilottery_head->prev->ilot.run_status != 0  )
	{
		printf("上一期还未开奖，不能发布彩票!!!\n");
		return -1;
	}

	issue_lot_t ilot;
	memset(&ilot, 0, sizeof(issue_lot_t));
	
	ilot.issue_number = get_issue_number(ilottery_head);  // 获取本期的开奖期号

	ilot.saled_count = get_saled_count();   // 获取本期的售出总数

	ilot.win_total_amount = get_win_total_amount(ilottery_head);  // 获取本期的奖池金额

	//printf("\t\t\t%.1f!!!\n", ilot.win_total_amount);
	ilot.price = get_price();   // 获取本期的票价
	ilot.wined_count = 0;	  // 获取本期的中奖人数
	ilot.run_status = -1;   // 获取本期开奖状态


	//char* 	RUN_STU[2] = {"未开奖","已开奖"};
	//printf("\t\t\t  %d\t\t    %d\t\t\t         %s\t\t\t   %d\t\t\t    %.1f\t\t---%d----\t\t  %d\t\t\n", ilot.issue_number, ilot.price, RUN_STU[ilot.run_status+1],ilot.saled_count,ilot.win_total_amount,ilot.winning_number[0],ilot.wined_count);		
  	// 获取本期的中奖号码
	//get_winning_number(ilot.winning_number);
	printf("本期的期号：%d\n", ilot.issue_number);
	printf("本期的票价：%d元\n", ilot.price);
	printf("本期的奖池金额：%.1lf元\n", ilot.win_total_amount);
	
	
	//申请节点
	ilottery_node_t* new_node = (ilottery_node_t*)calloc(1, sizeof(ilottery_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->ilot = ilot;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	return insert_ilottery_node(ilottery_head, new_node);

}

/*0 成功  -1 失败*/
int login_admin()
{
	char name[SIZE] = {'\0'};
	char pwd[SIZE] = {'\0'};
	printf("请输入管理员账户名: ");
	get_string(name, SIZE);
	printf("请输入密码: ");
	//get_string(pwd, SIZE);
	getPassword(pwd, SIZE);

	/*校验是否是管理员或者公证员*/
	if( strcmp(ADMIN_NAME, name) == 0 && strcmp(ADMIN_PWD, pwd) == 0 )
	{		
		return 0;
	}else{
		return -1;
	}
}








