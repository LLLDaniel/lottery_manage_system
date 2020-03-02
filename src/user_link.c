
#include "common.h"

/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_user_node(user_head_t* head, user_node_t* new_node)
{
	if(NULL == head || NULL == new_node){
		return -1;
	}
	
	/*找尾节点*/
	if(head->next == NULL){
		head->next = new_node;
		new_node->next = NULL;
	}else{
		user_node_t* p = head->next;
		while(p->next != NULL){
			p = p->next;
		}
		
		p->next = new_node;
		new_node->next = NULL;
	}	
		
	return 0;
}


/*
	功能：创建用户链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
user_head_t* create_user_link(void)
{
	user_head_t* head = (user_head_t*)calloc(1, sizeof(user_head_t));
	if(NULL == head){
		return NULL;
	}
	
	head->next = NULL;
	return head;
}

/*释放用户链表*/
void free_user_link(user_head_t* head)
{
	assert(head);
	user_node_t* p = head->next;
	user_node_t* q = p;
	while(p){
		q = p->next;
		free(p);
		p = q;
	}
	free(head);
	head = NULL;
}

/*打印测试函数*/
void display_user_link(user_head_t* head)
{
	assert(head);
	user_node_t* p = head->next;
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\t\t\t\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	while(p){
		printf("%s\t\t\t%s\t\t\t%.1lf\t\t\t\n", p->user.name, p->user.pwd, p->user.money);
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
		p = p->next;
	}
}

/*登陆校核函数*/
user_node_t* check_user(user_head_t* head, user_t* user_node)
{
	if(NULL == head || NULL == user_node){
		return NULL;
	}
	
	/*找节点*/
	user_node_t* p = head->next;
	while(p != NULL){
		if( (strcmp(p->user.name,user_node->name) == 0) && (strcmp(p->user.pwd,user_node->pwd) == 0))
		{
			//printf("查到了一个\n");
			return p;
		}
		p = p->next;
	}		
	return NULL;
}

/*注册去重函数*/
user_node_t* check_duplicate_user(user_head_t* head, user_t* user_node)
{
	if(NULL == head || NULL == user_node){
		return NULL;
	}

	/*找节点*/
	user_node_t* p = head->next;
	while(p != NULL){
		if( (strcmp(p->user.name,user_node->name) == 0))
		{
			//printf("查到了一个\n");
			return p;
		}
		p = p->next;
	}
	//printf("没有查到\n");		
	return NULL;
}


/*用户充值函数*/
int recharge_user(user_t* user)
{
	printf("进入充值界面\n");
	printf("账户余额为：%.1lf元\n", user->money);
	int charge_m = 0;
	while(charge_m <= 0)
	{
		printf("请输入充值金额(正数)：");
		scanf("%d",&charge_m);	
	}
	
	user->money += charge_m;
	printf("充值成功！！！\n");
	printf("账户余额为：%.1lf元\n", user->money);
	//sleep(3);
	
	return 0;
}

/*打印用户个人信息函数*/
void display_user_node(user_t* user)
{
	assert(user);
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("%s\t\t\t%s\t\t\t%.1lf\n", user->name, user->pwd, user->money);

}


/*打印用户中奖情况函数*/
void display_user_node_prize(user_t* user)
{
	assert(user);
	printf("进入中奖情况页面\n");
}



/*用户修改自己的信息*/
int change_info_user(user_t* user)
{
	assert(user);
	printf("进入修改用户密码界面（Esc强制退回）\n");
	int flag = 1;
	while(flag)
	{
		char new_pwd[SIZE] = {'\0'};
		char new_pwd_t[SIZE] = {'\0'};
		printf("请输入新的密码：");
		//get_string(new_pwd, SIZE);
		getPassword(new_pwd, SIZE);
		if( (strcmp(user->pwd,new_pwd) == 0))
		{
			printf("新密码和旧密码不能一致！！！\n");
			FLUSH();
			continue;
		
		}else if( new_pwd[0] == 27 ){
			return -1;
		}
		
		printf("请再次确认新的密码：");
		//get_string(new_pwd_t, SIZE);
		getPassword(new_pwd_t, SIZE);
		
		if( new_pwd_t[0] == 27 )
		{
			return -1;
		}
		else if( (strcmp(new_pwd_t,new_pwd) != 0))
		{
			printf("两次密码不一致！！！\n");
			FLUSH();
			continue;
		
		}
		else
		{
			flag  = 0;
			strcpy(user->pwd,new_pwd);
			return 0;
		}
	}
	return 0;
	
}

/*对用户链表根据金额大小排序*/
void sort_money_user(user_head_t* head)
{
	if( head == NULL || head->next == NULL || head->next->next == NULL )
	{
		return;
	}
	user_node_t* p = head->next;
	user_node_t* q = p;
	for( p = head->next; p->next!= NULL; p = p->next)
	{
		//user_t user = p->user;
		for( q = p->next; q != NULL; q = q->next)
		{
			if(q->user.money > p->user.money)
			{
				user_t user = p->user;
				p->user = q->user;
				q->user = user;
			}
		}
		
	}
}


/*根据彩民余额区间查询彩民*/
void display_money_section_user(user_head_t* head)
{
	assert(head);
	int max = 0, min = 0;
	printf("请输入最大金额:");
	scanf("%d",&max);
	printf("请输入最小金额:");
	scanf("%d",&min);
	FLUSH();

	user_node_t* p = head->next;
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	while(p){
		if( p->user.money <= max && p->user.money > min )
		{
			printf("%s\t\t\t%s\t\t\t%.1lf\t\t\t\n\n", p->user.name, p->user.pwd, p->user.money);
			printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");		
		}
		p = p->next;
	}
}


/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node_(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head)
{
	assert(user && user_head && lottery_head );
	// 1.如果该用户购买了彩票，清空这张彩票上的人名
	lottery_node_t* p_lott = lottery_head->next;

	while( p_lott != lottery_head ){
		if( strcmp( p_lott->lot.owner_name, user->name) == 0 )
		{
			memset( p_lott->lot.owner_name, 0 , SIZE);
		}	
		p_lott = p_lott->next;
	}
	// 2.修改用户链表，抹掉用户链表上的相关名字
	user_node_t* p = user_head->next;
	
	FILE* fp = fopen("deregister_users.bin","a+");
	
	while(p){		
		if( strcmp( user->name,p->user.name ) == 0 )
		{
			fwrite(&p->user,sizeof(user_node_t), 1, fp);
			memset( p->user.name, 0 , SIZE);	
		} 
		p = p->next;
	}	
	fclose(fp);
	return 0;
}


/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head)
{
	assert(user && user_head && lottery_head );
	// 1.如果该用户购买了彩票，清空这张彩票上的人名
	lottery_node_t* p_lott = lottery_head->next;

	while( p_lott != lottery_head ){
		if( strcmp( p_lott->lot.owner_name, user->name) == 0 )
		{
			memset( p_lott->lot.owner_name, 0 , SIZE);
		}	
		p_lott = p_lott->next;
	}
	// 2.修改用户链表，抹掉用户链表上的相关名字
	user_node_t* p = user_head->next;
	if(p == NULL || p->next == NULL)
	{
	
		free(p);
		user_head->next = NULL;
		return 0;
	}
	
	user_node_t* q = p;
	
	FILE* fp = fopen("deregister_users.bin","a+");
	
	while(p != NULL){		
		if( strcmp( user->name,p->user.name ) == 0 )
		{
			fwrite(&p->user,sizeof(user_node_t), 1, fp);
			q->next = p->next;
			free(p);
			p=NULL;	
			fclose(fp);		
			return 0;	
		} 
		q = p;
		p = p->next;
	}	
	
	return -1;
}



































