/*************************************************************************
    > File Name: func2.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: 2018年01月03日 星期三 22时13分47秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"


#define PROMPT_QUERY_MSG "please input a student's id" 
#define PROMPT_QUERY_MSG_FORMAT "id(text)"


extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun6(void){

	struct list_head *pos,*n;

	char id[13] = {0};
	int depid = 0;

	list_stu_t *stu_tmp_node;
	list_dep_t *dep_tmp_node;

	printf(PROMPT_QUERY_MSG"\n");
	printf(PROMPT_QUERY_MSG_FORMAT"\n");

	scanf("%s",id);
	fflush_stdin();
	printf("%s\n",id);

	//从链表中查

#if 0
	list_for_each(pos,&list_stu_head.list){
		stu_tmp_node = list_entry(pos,list_stu_t,list);
		if(!strcmp(stu_tmp_node->id,id)){
			depid = stu_tmp_node->depid;
			printf("the student's name is %s ,depid is %d\n",stu_tmp_node->name,stu_tmp_node->depid);
			goto search_dep;
		}
	} 
#endif
	list_for_each_safe(pos,n,&list_stu_head.list) {  
		//list_del(pos);
		stu_tmp_node = list_entry(pos,list_stu_t,list);

		if(!strcmp(stu_tmp_node->id,id)){
			depid = stu_tmp_node->depid;
			printf("the student's name is %s ,depid is %d\n",stu_tmp_node->name,stu_tmp_node->depid);
			goto search_dep;
		}

		//free(stu_tmp_node);
	}


	printf("the student is not registered!!!\n");
	return 1;

search_dep:

	printf("----1\n");

	list_for_each_safe(pos,n,&list_dep_head.list) {  
		//list_del(pos);
		dep_tmp_node = list_entry(pos,list_dep_t,list);
		if(dep_tmp_node->id == depid){
			printf("the student's name is %s ,depid is %d, dean's name is %s\n",stu_tmp_node->name,stu_tmp_node->depid,dep_tmp_node->dean);
			return 0;
		}
		//free(dep_tmp_node);
	}

	printf("there is a student whose id is %s,depid is %d,but the dep info not registered\n",stu_tmp_node->name,stu_tmp_node->depid);

	return 0;
}
