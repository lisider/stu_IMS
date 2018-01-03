/*************************************************************************
  > File Name: main.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: 2017年12月28日 星期四 23时24分58秒
 ************************************************************************/

#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "fuction.h"
#include "sqlite3_encap.h"

//类型定义区

typedef int (*cmd_func_t)(void);

typedef struct {
	int cmd;
	cmd_func_t func;
}cmd_group_t;

//变量定义区

list_stu_t list_stu_head;
list_dep_t list_dep_head;


//函数区
int main(int argc , char ** argv){

	int ret = 0;
	int cmd = -1;;
	int row_total = 0;
	int i = 0;
	char tmp_str[32] = {0};
	int tmp_row = 0;
	list_stu_t *stu_tmp_node;
	list_dep_t *dep_tmp_node;


	//0.初始化链表

	INIT_LIST_HEAD(&(list_stu_head.list));  
	INIT_LIST_HEAD(&(list_dep_head.list));  


	//2.读 数据库 ,写入 链表 list_stu_head


	//得到数据库的大小
	row_total = atoi(sqlite_rd_total_row(DB_PATH,"stu_info",tmp_str,sizeof(tmp_str)));
	if(row_total == 0){
		printf("there is no record in the table stu_info");
		return -1;
	}
	
	for(i = 1;i <= row_total;i++ ){

		stu_tmp_node = (list_stu_t *)malloc(sizeof(list_stu_t));

		//return 的值 是 char *
		sqlite_rd_by_row_column(DB_PATH,"stu_info",i,0,stu_tmp_node->id,sizeof(stu_tmp_node->id));
		sqlite_rd_by_row_column(DB_PATH,"stu_info",i,1,stu_tmp_node->name,sizeof(stu_tmp_node->name));
		stu_tmp_node->sex = atoi(sqlite_rd_by_row_column(DB_PATH,"stu_info",i,2,tmp_str,sizeof(tmp_str)));
		stu_tmp_node->age = atoi(sqlite_rd_by_row_column(DB_PATH,"stu_info",i,3,tmp_str,sizeof(tmp_str)));
		stu_tmp_node->depid = atoi(sqlite_rd_by_row_column(DB_PATH,"stu_info",i,4,tmp_str,sizeof(tmp_str)));
		//填充

		stu_tmp_node->score[0] = atoi(sqlite_rd_by_id(DB_PATH,"score_info",stu_tmp_node->id,1,tmp_str,sizeof(tmp_str)));
		stu_tmp_node->score[1] = atoi(sqlite_rd_by_id(DB_PATH,"score_info",stu_tmp_node->id,2,tmp_str,sizeof(tmp_str)));
		stu_tmp_node->score[2] = atoi(sqlite_rd_by_id(DB_PATH,"score_info",stu_tmp_node->id,3,tmp_str,sizeof(tmp_str)));
		stu_tmp_node->sum = atoi(sqlite_rd_by_id(DB_PATH,"score_info",stu_tmp_node->id,4,tmp_str,sizeof(tmp_str)));

		printf("stu_node%d : %s %s %d %d %d %d %d %d %d\n",
				i,
				stu_tmp_node->id,
				stu_tmp_node->name,
				stu_tmp_node->sex,
				stu_tmp_node->age,
				stu_tmp_node->depid,
				stu_tmp_node->score[0],
				stu_tmp_node->score[1],
				stu_tmp_node->score[2],
				stu_tmp_node->sum);

		list_add_tail(&(stu_tmp_node->list),&(list_stu_head.list));
		//list_add(&(stu_tmp_node->list),&(list_stu_head.list));
	}

	//3.读 数据库 ,写入 链表 list_dep_head
	row_total = atoi(sqlite_rd_total_row(DB_PATH,"dep_info",tmp_str,sizeof(tmp_str)));
	if(row_total == 0){
		printf("there is no record in the table stu_info");
		return -1;
	}


	for(i = 1;i <= row_total;i++ ){
		dep_tmp_node = (list_dep_t *)malloc(sizeof(list_dep_t));
		//填充
		dep_tmp_node->id = atoi(sqlite_rd_by_row_column(DB_PATH,"dep_info",i,0,tmp_str,sizeof(tmp_str)));
		sqlite_rd_by_row_column(DB_PATH,"dep_info",i,1,dep_tmp_node->name,sizeof(dep_tmp_node->name));
		sqlite_rd_by_row_column(DB_PATH,"dep_info",i,2,dep_tmp_node->dean,sizeof(dep_tmp_node->dean));
		sqlite_rd_by_row_column(DB_PATH,"dep_info",i,3,dep_tmp_node->location,sizeof(dep_tmp_node->location));

		printf("dep_node%d : %d %s %s %s\n",
				i,
				dep_tmp_node->id,
				dep_tmp_node->name,
				dep_tmp_node->dean,
				dep_tmp_node->location);

		list_add_tail(&(dep_tmp_node->list),&(list_stu_head.list));
		//list_add(&(dep_tmp_node->list),&(list_stu_head.list));
	}


	//4.注册各种函数到数组中
	cmd_group_t cmd_group[]={
		{0,fun0},
		{1,fun1},
		{2,NULL},
		{3,fun3},
		{4,NULL},
		{5,NULL},
		{6,NULL},
		{7,NULL},
		{8,NULL},
		{9,NULL},
		{10,NULL},
		{11,NULL},
		{12,NULL},
		{13,NULL},
		{-1,NULL}
	};


	printf("please input some value less then %d,but more than -1\n",(int)(ARRAY_SIZE(cmd_group)-1));

	for(;;){

		printf(">");
		fflush(stdout);

		if(scanf("%d",&cmd) !=1 ) //滤掉 r q 等非数字字符
		{
			fflush_stdin();
			//setbuf(stdin, NULL);
			goto errmsg;
		}

		//	printf("cmd : %d\n",cmd);

		if( cmd < ARRAY_SIZE(cmd_group)-1 && cmd >=0 ){
			if( (ret = cmd_group[cmd].func()) < 0)
				return ret;
			else{
				//setbuf(stdin, NULL);
				//fflush_stdin(); //必须在功能中处理好自己的缓冲区
				continue;
			}
		}else{
			//setbuf(stdin, NULL);
			fflush_stdin();
			goto errmsg;
		}

errmsg:
		printf("your input is illegal, you can  try value less then %d,but more than -1\n",(int)(ARRAY_SIZE(cmd_group)-1));
	}

	return 0;
}
