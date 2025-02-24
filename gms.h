#ifndef _GMS_H_
#define _GMS_H_

#define MAX_NAME_LENGTH 20
#define MAX_SEX_LENGTH 10
#define MAX_SCORE 100
#define MIN_SCORE 0

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <locale.h>

// 函数声明
void Menu();
void InputStudent();
void PrintStudent();
void CountStudent();
void FindStudent();
void ChangeStudent();
void DeleteStudent();
void ExportToFile();
void ImportFromFile();
void Functionselect(int choice);
void ClearAllStudents();
int VerifyPassword();
int getch();

// static pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t list_mutex;

typedef struct tagStudent
{
    char szName[MAX_NAME_LENGTH]; // 姓名
    char szSex[MAX_SEX_LENGTH];   // 性别
    int nAge;                     // 年龄
    long long nStuNo;             // 学号
    int nScore;                   // 成绩
    int hmath;                    // 高数
    int clgen;                    // 大学英语
    int dsaa;                     // 数据结构
    int cs;                       // 计算机
    int prothy;                   // 概率论
    int clpy;                     // 大学物理
} Student;

typedef struct tagNode
{
    Student stu;           // 学生信息
    struct tagNode *pNext; // 指向下一个节点
    struct tagNode *pPrev; // 指向上一个节点
} Node;

extern Node *g_pHead;

#endif