/*************************************************************************
    > File Name: func2.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: 2018年01月03日 星期三 22时13分47秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"


#define DISPLAY_MSG "going to display all registered student's info" 

//按平均成绩降序对学生排序，若成绩相同，按照年龄升序排序，并在屏幕上显示排序后的学生信息。

extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun13(void){

	struct list_head *pos,*pos2;

	char id[13] = {0};

	list_stu_t *stu_tmp_node,*stu_tmp_node2;
	list_stu_t * tmp;

	tmp = (list_stu_t *)malloc(sizeof(list_stu_t));
	memset(tmp,0,sizeof(list_stu_t));

	printf("\n"DISPLAY_MSG"\n\n");

	//从链表中查

	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);

		list_for_each(pos2,&stu_tmp_node->list){
			stu_tmp_node2 = list_entry(pos2,list_stu_t,list);

			if(stu_tmp_node2 == &list_stu_head)
				break;

			if(stu_tmp_node->sum < stu_tmp_node2->sum || 
					stu_tmp_node->sum == stu_tmp_node2->sum && stu_tmp_node->age > stu_tmp_node2->age){
				memcpy(tmp,stu_tmp_node,sizeof(list_stu_t)-sizeof(struct list_head));
				memcpy(stu_tmp_node,stu_tmp_node2,sizeof(list_stu_t)-sizeof(struct list_head));
				memcpy(stu_tmp_node2,tmp,sizeof(list_stu_t)-sizeof(struct list_head));
			}
			
		} 
	} 


	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);
		printf("a student's name is %s, sum is %d ,age is %d\n",stu_tmp_node->name,stu_tmp_node->sum,stu_tmp_node->age);
	} 


	printf("\ndisplay over\n\n");
	return 0;
}
