

#include "common.h"




void display_user_lottery_link(user_t* user, lottery_node_t* lottery_head)	//打印用户的个人彩票的链表
{
	char* PRIZE[7] = {"未开奖","未中奖","一等奖","二等奖","三等奖","四等奖","五等奖"};
	char* WIN_STU[2] = {"未领奖","已领奖"};
	lottery_node_t* p = lottery_head->prev;
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	 printf("彩票ID\t\t彩票期号\t购买者\t\t购买彩号\t注数\t\t领奖状态\t中奖信息\t\t中奖金额（元）\t\t\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	
	while( p != lottery_head )
	{
		if( strcmp( p->lot.owner_name, user->name) == 0 )
		{	
			//循环打印
			for ( int i = 1; i<= p->lot.note_number; i++)
			{
				printf(" %04d\t\t %d\t\t %s\t\t%02d-%02d-%02d-%02d-%02d\t %d\t\t %s\t\t %s\t\t\t  %.1lf\t\n", p->lot.id, p->lot.issue_number, p->lot.owner_name,p->lot.winning_number[i-1][0],p->lot.winning_number[i-1][1],p->lot.winning_number[i-1][2],p->lot.winning_number[i-1][3],p->lot.winning_number[i-1][4],i,WIN_STU[p->lot.winning_status+1],PRIZE[p->lot.winning_level[i-1]+1],p->lot.winning_amount[i-1]);
			}
			
			printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");	
		}
		p = p->prev;
	}
}



int get_issue_number_user_lott( ilottery_node_t* ilottery_head)  //获取彩票发布期号，要发行彩票的链表
{
	if(ilottery_head->prev != ilottery_head)
	{
		return ilottery_head->prev->ilot.issue_number;
	}
	else
	{
		return 1000;
	}
}

int get_id(lottery_node_t* lottery_head) //获取彩票id，
{	
	if(lottery_head->prev != lottery_head)
	{
		return lottery_head->prev->lot.id + 1;
	}
	else
	{
		return 1;
	}
}

int deduct_user_money(user_t* user, int note_number)   //根据用户购买注数扣钱
{	
	if( NULL == user)
	{
		return -1;
	}
	// 用户余额不足返回 购买失败
	if( user->money < note_number*2 )
	{
		return -1;
	}
	user->money -= note_number*2;
	return 0;
}


int check_winning_number_user( int *winning_number )  //检查用户输入的彩号
{
	for( int i=0;i<5;i++)
	{
		//printf("\t\t\t%d--------------------------------------\n\n",*(winning_number+i));
		if( *(winning_number+i) > WIN_NUMBER_RANGE || *(winning_number+i) < 1 )
		{
			return -1;
		}
	}
	return 0;
}

int get_winning_number_user(int (*winning_number)[5],int* note_number)  //获取购买者填写的彩票选号
{	
	int flag = 1;
	do{
		printf("请输入你想要选择的彩号--------------------------------------\n\n");
		
		//获取用户输入的5注彩票
		int noteNum = 0;
		int cho = 0;
		for( noteNum= 0; noteNum<5; noteNum++)
		{
			
			if( 2 == cho ) break;
			cho = 0;
			
			while(1)
			{	
				printf("请输入第%d注你想要选择的五位彩号:",noteNum+1);
				for( int i = 0;i<5;i++)
				{
					scanf("%d", &winning_number[noteNum][i]);
				}
				FLUSH();
				int ret = check_winning_number_user( (int*)winning_number+noteNum );
				if( 0==ret )
				{
					break;	
				}
				else{
					printf("您所选的彩号不在开彩范围，请重新输入！！！\n\n");
				}
			}
			if( 4 > noteNum )
			{
				printf("\n请选择您的操作(1.继续下注 2.停止下注):");
				scanf("%d",&cho);
				FLUSH();
		 	}			
		}
		
		
		*note_number = noteNum;  // 把购买注数复制到彩票节点上
		//printf("%d----",*note_number);
		if( 0 != (*note_number) )
		{
			//购买成功，显示信息
			printf("您购买的彩号是：\n\n");
			printf("\n༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻   \n\n");
			for(int i = 0;i<5;i++)
			{
				printf("༺  ༺  ༺  ༺  ༺    %02d --- %02d --- %02d --- %02d --- %02d  ༻  ༻  ༻  ༻  ༻    \n\n", winning_number[i][0],winning_number[i][1],winning_number[i][2],winning_number[i][3],winning_number[i][4]);
			}
			printf("༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻   \n\n");
			while(1){
				int choice = 0;
				printf("你将支付 %d 元钱，请确认你的选择（1:确认，2:重新填写彩号,3:停止购买彩票）:", (*note_number)*2);
				scanf("%d", &choice);
				FLUSH();
				if( 1 == choice ){
					flag = 0;
					break;
				}
				else if( 2 == choice ){	
					memset(winning_number, 0, sizeof(int)*25);				
					break;
				}
				else if( 3 == choice ){	
					memset(winning_number, 0, sizeof(int)*25);				
					return -1;
				}
			}
			
		}
	}while( 1 == flag );
	
	return 0;
}


/*
	功能: 用户购买彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_buy_lottery(user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)  //用户购买彩票
{

	
	 if(NULL == user || NULL == lottery_head || NULL == ilottery_head ){
		return -1;
	}
	//CONTINUE("\t\t\t-------!!!\n");
	//如果发行彩票的开奖了，不能买
	if( ilottery_head->prev->ilot.run_status == 0 )
	{
		printf("很抱歉，本期彩票正在开奖，不能购买，请等待新一期的彩票发布......\n");
		return -1;
	}
	printf("开始彩票购买（说明：彩号在1~%d之间选择，最多购买五注，每注2元钱）\n", WIN_NUMBER_RANGE);
	
	lot_t lot;
	memset(&lot, 0, sizeof(lot));
	
	/*输入买彩票的相关信息*/
	memset(lot.winning_amount , 0, sizeof(int)*5);
	lot.id = get_id(lottery_head); //获取彩票id，

	lot.issue_number = get_issue_number_user_lott(ilottery_head);  //获取彩票发布期号，要发行彩票的链表
	//printf("请输入购买的注数: ");   //获取用户购买的注数，要扣钱
	//scanf("%d", &lot.note_number);
	//FLUSH();
	
	strcpy(lot.owner_name, user->name);  // 获取购买者的姓名
	int ret_c = get_winning_number_user(lot.winning_number, &lot.note_number);  //获取购买者填写的彩票选号
	if( -1 == ret_c ){
		return -1;     //用户停止购买彩票
	}
	
	int ret = 0;
	if( (ret = deduct_user_money(user, lot.note_number)) == -1)   //扣钱
	{
		CONTINUE("很抱歉，余额不足，彩票购买失败！！！\n");
		return -1;
	}
	lot.winning_status = -1;
	//lot.winning_level[5] = {-1};
	memset(lot.winning_level, -1, sizeof(int)*5);
	
	//申请节点
	lottery_node_t* new_node = (lottery_node_t*)calloc(1, sizeof(lottery_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->lot = lot;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	insert_lottery_node(lottery_head, new_node);

	// 彩票的售出总数加1
	ilottery_head->prev->ilot.saled_count += 1;
	// 发行彩票根据用户购买注数增加奖池金额
	ilottery_head->prev->ilot.win_total_amount += lot.note_number*2;
	
	
	
	//display_lottery_link(lottery_head);

	return 0;
}


/*
	功能: 用户兑换彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_redeem_lottery(user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{

	//CONTINUE("进入彩票兑换\n");
	if(NULL == user || NULL == lottery_head || NULL == ilottery_head ){
		return -1;
	}
	
	//用户输入需要兑换的彩票的ID,获取几等奖
	int lottery_id = 0;
	int issue_number = 0;
	int* prize_level = NULL;
	printf("请输入需要兑换的彩票的ID:");
	scanf("%d", &lottery_id);
	FLUSH();
	printf("请输入需要兑换的彩票的发布期号:");
	scanf("%d", &issue_number);
	FLUSH();
	lottery_node_t* p_lott = lottery_head->prev;
	//进入循环，寻找对应的彩票获取获奖等级，
	while( p_lott != lottery_head ){
		// 如果id相等，领奖状态为-1未领奖，已经中奖信息不是0和-1，发布期号相等, 用户名相等
		if( p_lott->lot.id == lottery_id && p_lott->lot.winning_status == -1 && p_lott->lot.issue_number == issue_number && (strcmp(p_lott->lot.owner_name, user->name) == 0 ) ){
			//获取中奖等级
			prize_level = (int*)p_lott->lot.winning_level;
			break;
			
		}
		p_lott = p_lott->prev;
		//printf("-----------1！！！\n");
	}
	//printf("-----------2！！！\n");
	if( (prize_level == NULL) || (prize_level[0] == 0 && prize_level[1] == 0 && prize_level[2] == 0 && prize_level[3] == 0 && prize_level[4] == 0 )) 
	{
		printf("很抱歉，该彩票不存在或者未中奖！！！\n");
		return -1;
	}
	
	
	//找到对应的发行彩票，取钱，给用户的账户加钱
	ilottery_node_t* p_ilott = ilottery_head->prev;
	if( p_ilott->ilot.issue_number != issue_number ) 
	{
		printf("很抱歉，该彩票不存在或者未中奖，或者该期的兑奖期限已过！！！\n");
		return -1;
	}
	
	//三方改变金额
	redeem_money(user, p_lott, p_ilott, prize_level);
		
	//用户彩票上的兑换奖励信息改为已经兑换奖励0,防止重复领奖
	p_lott->lot.winning_status = 0;
	
	return 0;
}

/*
	功能: 三方改变金额
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针  prize_level 用户获奖等级 
	返回值：-1 失败 0 成功
*/
int redeem_money(user_t* user, lottery_node_t* lott_p, ilottery_node_t* ilott_p, int* prize_level)
{
	for(int i=0; i<5; i++)
	{
		switch(prize_level[i])
		{
			case 1:		//一等奖
				{
					double money = 0.3*ilott_p->ilot.win_total_amount + 5000000.0;   //一等奖中奖金额，总的金额的百分之30,外加500万
					printf("您成功兑换%d等奖，奖金为 30%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 5000000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
				}
				break;
			case 2:		//二等奖
				{
					double money = 0.1*ilott_p->ilot.win_total_amount + 1000000.0;  //二等奖中奖金额，总的金额的百分之10,外加一百万
					printf("您成功兑换%d等奖，奖金为 10%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 1000000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
				}
				break;
			case 3:		//三等奖
				{
					double money = 0.05*ilott_p->ilot.win_total_amount + 200000.0;    //三等奖中奖金额，总的金额的百分之5，外加20万
					printf("您成功兑换%d等奖，奖金为 5%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 200000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖	
				}
				break;
			case 4:		//四等奖
				{
					double money = 200.0;
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
					printf("您成功兑换%d等奖，奖金为 %.1lf 元，已经发放到您的账户\n",prize_level[i], money);
				}
				break;
			case 5:		//五等奖
				{
					double money = 5.0;
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
					printf("您成功兑换%d等奖，奖金为 %.1lf 元，已经发放到您的账户\n",prize_level[i], money);
				}
				break;	
		}
		
	}
	return 0;
}





















