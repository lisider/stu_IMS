#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
char * Reverse(char *s)
{
    char temp;
    char *p = s; 
    char *q = s;
 
    while (*p != '\0')
    {
        p ++;
    }
    q --;
    while (p > q)
    {
        temp = *p;
        *q ++ = *p;
        *q -- = temp;
    }
 
    return s;
}
 
#endif
char* my_itoa(int nval)
{
    static char cBuff[100] = {0};
    int i = 0;
    int nTempVal = nval;
 
    if (nval < 0)
    {
        nval = -1 * nval;
    }
 
    do
    {
        cBuff[i ++] = (nval % 10)  + '0';
        nval = nval / 10;
 
    }while (nval > 0);
 
    if (nTempVal < 0)
    {
        cBuff[i ++] = '-';
    }
    cBuff[i] = '\0';
 
    return cBuff;
}


  
//模糊匹配两个字符串,
//s1 是源字符串 ,s2 是要查找的字符串
int fuzzy_matching(char * s1, char *s2)
{
#if 0
  char s1[] = "hello welcome to china\0"; //源字符串
  printf("input a s1ing:\n");       
  char s2[20];              //要查找的字符串
  fgets(s2, 19, stdin);
#endif
  char *res;
  res = memchr(s1, s2[0], strlen(s1));  //根据要查找的字符串第一个字符，切割源字符串
  if (res == NULL)
  {
    printf("find nothing...\n");
    return 0;
  }
   
  int n;
  while (1)
  {
    n = memcmp(res, s2, strlen(s2) - 1); //比较
    if (n != 0)
    {
      if (strlen(res) <= strlen(s2))  //切割出的字符串小于要查找字符串的长度
      {
        printf("find nothing...\n");
        return 0;
      }
      else
      {  
       //根据要查找的第一个字符继续切割
        res = memchr(res + 1, s2[0], strlen(res));  
        if (res == NULL)
        {
          //printf("find nothing...\n");

          return 0;
        }
          
      }
    }
    else
    { //如果n = 0，找到
      //printf("%s is found..\n", s2);
      return 1;
    }
  }
}
