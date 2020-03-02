#include "common.h"


/*
*Target：彩票管理系统-iotek-pw-1907
*Author：luxi
*Date：日期-2019-11-26-17:03:00
*/


int main(void)
{
	user_head_t* user_head = create_user_link();  // 创建用户链表
	ilottery_node_t* ilottery_head = create_ilottery_link(); // 创建发行彩票链表
	lottery_node_t* lottery_head = create_lottery_link(); // 创建用户彩票链表

	if(NULL == user_head || NULL == ilottery_head ){
		return 0;
	}
	
	/*加载*/
	load_user(user_head);
	load_ilottery(ilottery_head);
	load_lottery(lottery_head);

	identity_control(user_head,ilottery_head,lottery_head);

	/*保存*/
	save_user(user_head); // 保存用户链表
	save_ilottery(ilottery_head); // 保存发行彩票链表
	save_lottery(lottery_head); // 保存用户彩票链表

	free_user_link(user_head);
	free_ilottery_link(ilottery_head);
	free_lottery_link(lottery_head);
	return 0;
}




