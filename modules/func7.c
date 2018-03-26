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


#define PROMPT_QUERY_MSG "please input a dep's name" 
#define PROMPT_QUERY_MSG_FORMAT "name(text)"


extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

int fun7(void){

	struct list_head *pos,*n;

	char name[20] = {0};// dep 的 name
	int depid = 0;

	list_stu_t *stu_tmp_node;
	list_dep_t *dep_tmp_node;

	printf(PROMPT_QUERY_MSG"\n");
	printf(PROMPT_QUERY_MSG_FORMAT"\n");

	scanf("%s",name);
	fflush_stdin();
	printf("%s\n",name);

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
	list_for_each_safe(pos,n,&list_stu_head.list) {  
		list_del(pos);
		stu_tmp_node = list_entry(pos,list_stu_t,list);

		if(!strcmp(stu_tmp_node->id,id)){
			depid = stu_tmp_node->depid;
			printf("the student's name is %s ,depid is %d\n",stu_tmp_node->name,stu_tmp_node->depid);
			goto search_dep;
		}

		free(stu_tmp_node);
	}


	printf("the student is not registered!!!\n");
	return 1;

search_dep:
#endif


	list_for_each_safe(pos,n,&list_dep_head.list) {  
		//list_del(pos);
		dep_tmp_node = list_entry(pos,list_dep_t,list);
		if(!strcmp(dep_tmp_node->name,name)){
			depid = dep_tmp_node->id;
			printf("the dep name is %s, the dep id is %d\n",dep_tmp_node->name,dep_tmp_node->id);
			free(dep_tmp_node);
			goto search_stu;
		}
		//free(dep_tmp_node);
	}


search_stu:

	list_for_each_safe(pos,n,&list_stu_head.list) {  
		//list_del(pos);
		stu_tmp_node = list_entry(pos,list_stu_t,list);

		if(stu_tmp_node->depid == depid && stu_tmp_node->sex == 1){
			printf("the student's name is %s ,depid is %d\n",stu_tmp_node->name,stu_tmp_node->depid);
		}

		//free(stu_tmp_node);
	}



	//printf("there is a student whose id is %s,depid is %d,but the dep info not registered\n",stu_tmp_node->name,stu_tmp_node->depid);

	return 0;
}
