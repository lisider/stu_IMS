/*************************************************************************
    > File Name: func2.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: 2018年01月03日 星期三 22时13分47秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"


#define PROMPT_QUERY_MSG "please input a student's age" 
#define PROMPT_QUERY_MSG_FORMAT "age(int)"


extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun4(void){

	struct list_head *pos;

	int age = 0;

	list_stu_t *stu_tmp_node;

	printf(PROMPT_QUERY_MSG"\n");
	printf(PROMPT_QUERY_MSG_FORMAT"\n");

	scanf("%d",&age);
	fflush_stdin();
	printf("%d\n",age);

	//从链表中查

	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);
		if(stu_tmp_node->age == age){
			printf("the student's name is %s\n",stu_tmp_node->name);
			return 0;
		}
	} 

	printf("the student is not registered!!!\n");

	return 0;
}
