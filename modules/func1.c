/*************************************************************************
  > File Name: fun1.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: 2017年12月29日 星期五 21时56分58秒
 ************************************************************************/

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3_encap.h"
#include "common.h"
#include "str.h"

#define PROMPT_STU_MSG "please insert a student info"
#define PROMPT_STU_MSG_FORMAT "id(text) name(text) sex(int) age(int) depid(int)"


#define PROMPT_SCORE_MSG "please insert the student's info"
#define PROMPT_SCORE_MSG_FORMAT "score[0](int) score[1](int) score[2](int) sum(int)"

#define PROMPT_DEP_MSG "please insert a dep info"
#define PROMPT_DEP_MSG_FORMAT "id(int) name(text) dean(text) location(text)"

extern list_stu_t list_stu_head;
extern list_dep_t list_dep_head;

//fuction : 录入学生信息
int fun1(void){


	/*------------------------------------------------------
	 *  学生信息部分
	 ------------------------------------------------------*/


	list_stu_t *stu_tmp_node;
	char tmp_str[256] = {0};

	stu_tmp_node = (list_stu_t *)malloc(sizeof(list_stu_t));
	memset(stu_tmp_node,0,sizeof(list_stu_t));


	// 1. 学生信息获取

	printf(PROMPT_STU_MSG"\n");
	printf(PROMPT_STU_MSG_FORMAT"\n");

	scanf("%s %s %d %d %d",
			stu_tmp_node->id,
			stu_tmp_node->name,
			&stu_tmp_node->sex,
			&stu_tmp_node->age,
			&stu_tmp_node->depid);

	fflush_stdin();


	// 2. 验证数据是否已经注册 
	
	if(sqlite_rd_ifexist(DB_PATH,"stu_info","id",stu_tmp_node->id)){ //存在
		printf("this student has been registered\n");
		return 1;
	}


	// 3. 学生分数信息获取

	printf(PROMPT_SCORE_MSG"\n");
	printf(PROMPT_SCORE_MSG_FORMAT"\n");

	scanf("%d %d %d %d",
			&stu_tmp_node->score[0],
			&stu_tmp_node->score[1],
			&stu_tmp_node->score[2],
			&stu_tmp_node->sum);


	// 4. 打印学生综合信息

	puts("\n-----------------------------------\n");
	puts(stu_tmp_node->id);
	puts(stu_tmp_node->name);
	printf("%d\n",stu_tmp_node->sex);
	printf("%d\n",stu_tmp_node->age);
	printf("%d\n",stu_tmp_node->depid);

	printf("%d\n",stu_tmp_node->score[0]);
	printf("%d\n",stu_tmp_node->score[1]);
	printf("%d\n",stu_tmp_node->score[2]);
	printf("%d\n",stu_tmp_node->sum);
	puts("\n-----------------------------------\n");


	// 5. 将学生综合信息 插入链表 list_stu_head

	list_add_tail(&(stu_tmp_node->list),&(list_stu_head.list));


	// 6. 将 学生 信息 写入 数据库 的 stu_info 表

	sprintf(tmp_str,"%s%s%s%s%s,%d,%d,%d%s",
			"insert into stu_info(id,name,sex,age,depid) values(\'",\
			stu_tmp_node->id,\
			"\',\'",\
			stu_tmp_node->name,\
			"\'",\
			stu_tmp_node->sex,\
			stu_tmp_node->age,\
			stu_tmp_node->depid, //TODO ,这个最后插入表中是 0
			");");

	sqlite_wr_insert_record(DB_PATH,tmp_str);


	// 7. 将 学生分数 信息 写入 数据库 的 score_info 表
	
	bzero(tmp_str,sizeof(tmp_str));
	sprintf(tmp_str,"%s%s%s,%d,%d,%d,%d%s",
			"insert into  score_info(id,score1,score2,score3,sum) values(\'",
			stu_tmp_node->id,\
			"\'",\
			stu_tmp_node->score[0],\
			stu_tmp_node->score[1],\
			stu_tmp_node->score[2],\
			stu_tmp_node->sum,
			");");

	sqlite_wr_insert_record(DB_PATH,tmp_str);


	/*------------------------------------------------------
	 *  系信息部分
	 ------------------------------------------------------*/


	// 8. 查询 系信息是否被注册过

	if(!sqlite_rd_ifexist(DB_PATH,"dep_info","id",my_itoa(stu_tmp_node->depid))){ //如果没被注册

		list_dep_t *dep_tmp_node;
		dep_tmp_node = (list_dep_t *)malloc(sizeof(list_dep_t));
		bzero(tmp_str,sizeof(tmp_str));


		// 9. 获取 系 信息

		printf(PROMPT_DEP_MSG"\n");
		printf(PROMPT_DEP_MSG_FORMAT"\n");

		scanf("%d %s %s %s",\
				&dep_tmp_node->id,\
				dep_tmp_node->name,\
				dep_tmp_node->dean,\
				dep_tmp_node->location);


		// 10. 将 系信息插入链表

		list_add_tail(&(dep_tmp_node->list),&(list_stu_head.list));


		// 11. 将系 信息 写入数据库

		sprintf(tmp_str,"%s%d,%s%s%s%s%s%s%s",\
				"insert into dep_info(id,name,dean,location) values(",\
				dep_tmp_node->id,\
				"\'",\
				dep_tmp_node->name,\
				"\',\'",\
				dep_tmp_node->dean,\
				"\',\'",\
				dep_tmp_node->location,\
				"\');");

		sqlite_wr_insert_record(DB_PATH,tmp_str);

	}

	return 0;
}
