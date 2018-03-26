/*************************************************************************
    > File Name: func2.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: 2018年01月03日 星期三 22时13分47秒
 ************************************************************************/

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3_encap.h"
#include "common.h"


#define PROMPT_QUERY_MSG "please input a student's id" 
#define PROMPT_QUERY_MSG_FORMAT "id(text)"


extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun3(void){

	struct list_head *pos;

	char id[13] = {0};

	list_stu_t *stu_tmp_node;

	printf(PROMPT_QUERY_MSG"\n");
	printf(PROMPT_QUERY_MSG_FORMAT"\n");

	scanf("%s",id);
	fflush_stdin();
	printf("%s\n",id);

	//从链表中查

	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);
		if(!strcmp(stu_tmp_node->id,id)){
			printf("the student's name is %s\n",stu_tmp_node->name);
			return 0;
		}
	} 

	printf("the student is not registered!!!\n");

	return 0;
}
