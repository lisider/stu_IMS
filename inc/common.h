#ifndef __COMMON_H_
#define __COMMON_H_
#include "list.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define fflush_stdin() 		 {int c;while((c = getchar()) != '\n' && c != EOF);}
//#define DB_PATH "/home/linux/pro/student_IMS/college_info.db"
#define DB_PATH "./data/college_info.db"

typedef struct{
	char id[13];
	char name[20];
	char sex;
	short age;
	short score[3];
	short sum;
	short depid;
	struct list_head list;
}list_stu_t;

typedef struct{
	short id;
	char name[20];
	char dean[10];
	char location[50];
	struct list_head list;
}list_dep_t;


#endif
