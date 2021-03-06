

#include "common.h"

/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_ilottery_node(ilottery_node_t* head, ilottery_node_t* new_node)
{
	if(NULL == head || NULL == new_node){
		return -1;
	}
	
	/*找尾节点*/


	new_node->next = head;	
	new_node->prev = head->prev;	
	head->prev->next = new_node;
	head->prev = new_node;
	

	return 0;
}


/*
	功能：创建彩票链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
ilottery_node_t* create_ilottery_link(void)
{
	ilottery_node_t* head = (ilottery_node_t*)calloc(1, sizeof(ilottery_node_t));
	if(NULL == head){
		return NULL;
	}

	head->next = head;
	head->prev = head;
	return head;
}

/*释放彩票链表*/
void free_ilottery_link(ilottery_node_t* head)
{
	assert(head);
	ilottery_node_t* p = head->next;
	ilottery_node_t* q = p;
	while(p != head){
		q = p->next;
		free(p);
		p = q;
	}
	free(head);
	head = NULL;
}

/*打印彩票函数*/
void display_ilottery_link(ilottery_node_t* head)
{
	assert(head);
	char* 	RUN_STU[2] = {"未开奖","已开奖"};
	ilottery_node_t* p = head->prev;
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("发布期号\t彩票单价（元/每注）\t\t开奖状态\t\t售出总数（张）\t\t彩池奖金（元）\t\t中奖号码\t\t中奖人数\t\t\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	while(p != head){
		printf("  %d\t\t    %d\t\t\t         %s\t\t\t   %d\t\t\t %.1f\t\t%d-%d-%d-%d-%d\t\t  %d\t\t\n", p->ilot.issue_number, p->ilot.price, RUN_STU[p->ilot.run_status+1],p->ilot.saled_count,p->ilot.win_total_amount,p->ilot.winning_number[0],p->ilot.winning_number[1],p->ilot.winning_number[2],p->ilot.winning_number[3],p->ilot.winning_number[4],p->ilot.wined_count);
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		p = p->prev;
	}
}

// 获取本期的开奖期号
int get_issue_number(ilottery_node_t* ilottery_head)
{
	int len = 0;
	ilottery_node_t* p = ilottery_head->next;
	while(p != ilottery_head)
	{	
		len++;
		p = p->next;
	}
	return 1000 + len +1 ;
}


// 获取本期的票价
int get_price()
{
	size_t price = 2;

	return price;
}

 // 获取本期的售出总数
int get_saled_count()
{
	return 0;
}

 // 获取本期的奖池金额
double get_win_total_amount(ilottery_node_t* ilottery_head)
{
	
	ilottery_node_t* p = ilottery_head->prev;
	if ( p != ilottery_head )
	{
		if( p->ilot.win_total_amount <= 0 )
		{
			return 20000000.0;	
		}
		return (20000000.0 + p->ilot.win_total_amount);
	}
	else
	{
		return 20000000.0;
	}
}

// 获取本期的中奖号码
int* get_winning_number(int *win_s) 
{
	srand((int)time(NULL));
	
	for(int i = 0;i<5; i++)
	{	
		// 测试用
		win_s[i] = rand()%40 + 1;
		
	}
	//printf("%s\n", winning_number);
	//strcpy(win_s, winning_number); 	
	return win_s;	
}

// 获取本期的中奖号码
int* get_winning_number_hand(int *win_s) 
{
	srand((int)time(NULL));
	
	for(int i = 0;i<5; i++)
	{	
		// 测试用
		//win_s[i] = rand()%40 + 1;
		win_s[i] =  1;
	}
	//printf("%s\n", winning_number);
	//strcpy(win_s, winning_number); 	
	return win_s;	
}






/*0 成功  -1 失败*/
int save_ilottery(ilottery_node_t* ilottery_head)
{
	printf("保存彩票信息进行！！！\n");
	if(NULL == ilottery_head){
		return -1;
	}
	
	FILE* fp = fopen("ilotterys.bin","wb");
	assert(fp);

	ilottery_node_t* p = ilottery_head->next;
	while( p != ilottery_head)
	{
		issue_lot_t ilot = p->ilot;

		if (fwrite(&ilot, sizeof(ilot),1, fp) != 1)
		{
			printf("保存彩票信息失败！！！\n");	
			return -1;
		}
		p = p->next;
	}
	fclose(fp);
	fp =NULL;	
	return 0;
}

/*0 成功  -1 失败*/
int load_ilottery(ilottery_node_t* ilottery_head)
{
	if(NULL == ilottery_head){
		return -1;
	}
	
	FILE* fp = fopen("ilotterys.bin","rb+");
	assert(fp);

	issue_lot_t ilot;
	memset(&ilot, 0 , sizeof(ilot));
	while( fread(&ilot, sizeof(ilot), 1, fp) == 1 )
	{
		//申请节点
		ilottery_node_t* new_node = (ilottery_node_t*)calloc(1, sizeof(ilottery_node_t));
		if(NULL == new_node){
			return -1;
		}
	
		new_node->ilot = ilot;
		new_node->next = NULL;
		new_node->prev = NULL;

		insert_ilottery_node(ilottery_head, new_node);
		memset(&ilot, 0 , sizeof(ilot));
	}
	fclose(fp);
	fp =NULL;
	printf("加载用户信息成功！！！\n");	
	return 0;

}





















