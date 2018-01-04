/*************************************************************************
    > File Name: func2.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: 2018年01月03日 星期三 22时13分47秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"


#define DISPLAY_MSG "going to display all registered student's info" 


extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun2(void){

	struct list_head *pos;

	char id[13] = {0};

	list_stu_t *stu_tmp_node;

	printf("\n"DISPLAY_MSG"\n\n");

	//从链表中查

	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);
		printf("a student's name is %s\n",stu_tmp_node->name);
	} 

	printf("\ndisplay over\n\n");
	return 0;
}
