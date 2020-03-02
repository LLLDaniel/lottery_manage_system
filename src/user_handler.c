
#include "common.h"




/*0 成功  -1 失败*/
int register_user(user_head_t* user_head)  //普通用户注册
{
	if(NULL == user_head){
		return -1;
	}
	
	user_t user;
	memset(&user, 0, sizeof(user));
	
	printf("请输入用户名: ");
	get_string(user.name, SIZE);

	/*查找是否重名*/
	{
		user_node_t* get_user = NULL;
		get_user = check_duplicate_user(user_head, &user);
		if(get_user != NULL)
		{	
			printf("已经存在相同用户名！！！\n");
			return -1;
		}
	}
	printf("请输入密码: ");
	//get_string(user.pwd, SIZE);
	getPassword(user.pwd, SIZE);
	char pwd_double[SIZE] = {'\0'};
	printf("请再次输入密码: ");
	//get_string(pwd_double, SIZE);
	getPassword(pwd_double, SIZE);

	if( strcmp(pwd_double, user.pwd) != 0)
	{
		printf("两次输入密码不一致，请重新注册！！！\n");
		return -1;
	}



	user.money = 100.0;
	
	//申请节点
	user_node_t* new_node = (user_node_t*)calloc(1, sizeof(user_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->user = user;
	new_node->next = NULL;
	
	return insert_user_node(user_head, new_node);
}

/* !NULL 成功  NULL 失败*/
user_t* login_user(user_head_t* user_head)
{
	if(NULL == user_head){
		return NULL;
	}
	
	user_t user;
	memset(&user, 0, sizeof(user));
	
	printf("请输入用户名: ");
	get_string(user.name, SIZE);
	printf("请输入密码: ");

	getPassword(user.pwd, SIZE);
	
	{
		//输入验证码
		int ret = identifyCode();
		if( 0==ret )
		{	
			return NULL;
		}	
	}
	user_node_t* get_user = check_user(user_head, &user);
	if(get_user != NULL)
	{
		return &get_user->user;
	}
	return NULL;
}

/*0 成功  -1 失败*/
int load_user(user_head_t* user_head)
{
	if(NULL == user_head){
		return -1;
	}
	
	FILE* fp = fopen("users.bin","rb+");
	assert(fp);

	user_t user;
	memset(&user, 0 , sizeof(user));
	while( fread(&user, sizeof(user), 1, fp) == 1 )
	{
		//申请节点
		user_node_t* new_node = (user_node_t*)calloc(1, sizeof(user_node_t));
		if(NULL == new_node){
			return -1;
		}
	
		new_node->user = user;
		new_node->next = NULL;
		insert_user_node(user_head, new_node);
		memset(&user, 0 , sizeof(user));
	}
	fclose(fp);
	fp =NULL;	
	return 0;
	printf("加载用户信息成功！！！\n");
}


/*0 成功  -1 失败*/
int save_user(user_head_t* user_head)
{
	printf("保存用户信息进行！！！\n");
	if(NULL == user_head){
		return -1;
	}
	
	FILE* fp = fopen("users.bin","wb");
	assert(fp);

	user_node_t* user_node = user_head->next;
	while( user_node != NULL)
	{
		user_t user = user_node->user;

		if (fwrite(&user, sizeof(user),1, fp) != 1)
		{
			printf("保存用户信息失败！！！\n");	
			return -1;
		}
		user_node = user_node->next;
	}
	fclose(fp);
	fp =NULL;	
	return 0;
}








