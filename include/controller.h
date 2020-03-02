#ifndef CONTROLLER_H_
#define CONTROLLER_H_



/*选择身份界面*/
int identity_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head);

/*用户主界面控制函数*/
void user_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head);

/*用户界面控制函数*/
void user_control(user_t* user, user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head);


/*管理员界面控制函数*/
void admin_control(user_head_t* user_head, ilottery_node_t* ilottery_head);

/*公正员界面控制函数*/
void nottery_control(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head);

/*管理员主界面控制函数*/
void admin_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head);

/*公正员主界面控制函数*/
void nottery_main_control(user_head_t* user_head, ilottery_node_t* ilottery_head, lottery_node_t* lottery_head);

#endif
