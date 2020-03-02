#ifndef USER_LINK_H_
#define USER_LINK_H_



/*用户结构体*/
typedef struct user{
	char 	name[SIZE];
	char 	pwd[SIZE];
	double  	money;
}user_t;


/*普通节点结构*/
typedef struct user_link_node{
	user_t 			user;
	struct user_link_node* 	next;
}user_node_t;

/*头结点类型*/
typedef struct user_link_head{
	int 			count;
	struct user_link_node* 	next;
}user_head_t;

/*
	功能：创建用户链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
user_head_t* create_user_link(void);


/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_user_node(user_head_t* head, user_node_t* new_node);

/*
	功能：校登陆核节点
	参数：head 头结点  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
user_node_t* check_user(user_head_t* head, user_t* user_node);

/*
	功能：注册去重
	参数：head 头结点  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
user_node_t* check_duplicate_user(user_head_t* head, user_t* user_node);


/*
	功能: 用户充值
	参数：  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int recharge_user(user_t* user);

/*
	功能: 用户修改自己的信息
	参数：  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int change_info_user(user_t* user);

/*释放用户链表*/
void free_user_link(user_head_t* head);

/*打印测试函数*/
void display_user_link(user_head_t* head);

/*打印用户个人信息函数*/
void display_user_node(user_t* user);

/*打印用户中奖情况函数*/
void display_user_node_prize(user_t* user);

/*对用户链表根据金额大小排序*/
void sort_money_user(user_head_t* head);

/*根据彩民余额区间查询彩民*/
void display_money_section_user(user_head_t* head);  

/*释放用户个人账户*/
int free_user_node(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head);

/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node_(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head);


#endif
