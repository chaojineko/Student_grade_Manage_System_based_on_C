#ifndef _GMS_H_
#define _GMS_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
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

typedef struct tagStudent
{
    char szName[20];  // 姓名
    char szSex[10];   // 性别
    int nAge;         // 年龄
    long long nStuNo; // 学号
    int nScore;       // 成绩
    int hmath;        // 高数
    int clgen;        // 大学英语
    int dsaa;         // 数据结构
    int cs;           // 计算机
    int prothy;       // 概率论
    int clpy;         // 大学物理
} Student;

typedef struct tagNode
{
    Student stu;           // 学生信息
    struct tagNode *pNext; // 指向下一个节点
} Node;

#endif