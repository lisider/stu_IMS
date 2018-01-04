/*************************************************************************
  > File Name: fun1.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: 2017年12月29日 星期五 21时56分58秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"

#define PROMPT_DEL_MSG "please insert a student's id"
#define PROMPT_DEL_MSG_FORMAT "id(text)"


#define PROMPT_SCORE_MSG "please insert the student's info"
#define PROMPT_SCORE_MSG_FORMAT "score[0](int) score[1](int) score[2](int) sum(int)"

#define PROMPT_DEP_MSG "please insert a dep info"
#define PROMPT_DEP_MSG_FORMAT "id(int) name(text) dean(text) location(text)"

extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

//fuction : 录入学生信息
int fun9(void){


	/*------------------------------------------------------
	 *  学生信息部分
	 ------------------------------------------------------*/


	list_stu_t *stu_tmp_node;
	struct list_head *pos,*n;
	char tmp_str[256] = {0};

	char id[13] = {0};


	// 1. 学生信息获取

	printf(PROMPT_DEL_MSG"\n");
	printf(PROMPT_DEL_MSG_FORMAT"\n");

	scanf("%s",id);

	fflush_stdin();


	// 2. 验证数据是否已经注册 
	
	if(!sqlite_rd_ifexist(DB_PATH,"stu_info","id",id)){ //不存在
		printf("this student has not been registered\n");
		return 1;
	}


	// 3. 查询 stu 链表 ,并删除

	//怎么删除一个链表
	list_for_each_safe(pos,n,&list_stu_head.list) {  
		stu_tmp_node = list_entry(pos,list_stu_t,list);

		if(!strcmp(stu_tmp_node->id,id)){
			list_del(pos);
		}

		free(stu_tmp_node);
	}


	// 6. 将 学生 信息 从 数据库 的 stu_info 表 删除
	
	bzero(tmp_str,sizeof(tmp_str));
	sprintf(tmp_str,"%s%s%s%s%s",
			"delete from stu_info where id = ",
			"\'",
			id,
			"\'",
			";");

	sqlite_wr_del_record(DB_PATH,tmp_str);


	// 7. 将 学生 信息 从 数据库 的 score_info 表 删除
	
	bzero(tmp_str,sizeof(tmp_str));
	sprintf(tmp_str,"%s%s%s%s%s",
			"delete from stu_info where id = ",
			"\'",
			id,
			"\'",
			";");

	sqlite_wr_del_record(DB_PATH,tmp_str);

	return 0;
}
