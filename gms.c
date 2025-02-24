#include "gms.h"

pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

Node *g_pHead = NULL; // 定义头指针

// 菜单
void Menu()
{
    printf("*************************************************\n");
    printf("*\t\t大学生成绩管理系统\t\t*\n");
    printf("*\t\t请选择功能\t\t\t*\n");
    printf("*************************************************\n");
    printf("*\t\t1.录入学生信息\t\t\t*\n");
    printf("*\t\t2.打印学生信息\t\t\t*\n");
    printf("*\t\t3.统计所有学生人数\t\t*\n");
    printf("*\t\t4.查找学生信息\t\t\t*\n");
    printf("*\t\t5.修改学生信息\t\t\t*\n");
    printf("*\t\t6.删除学生信息\t\t\t*\n");
    printf("*\t\t7.导出学生信息到文件\t\t*\n");
    printf("*\t\t8.从文件导入学生信息\t\t*\n");
    printf("*\t\t0.退出系统\t\t\t*\n");
    printf("*************************************************\n");
}

// 1.录入学生信息
void InputStudent()
{
    pthread_mutex_lock(&list_mutex);
    // 在堆上分配一个节点内存
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    pNewNode->pNext = NULL;
    pNewNode->pPrev = NULL;

    // 录入学生信息
    printf("请输入学生姓名：\n");
    scanf("%s", pNewNode->stu.szName);
    printf("请输入性别：\n");
    scanf("%s", pNewNode->stu.szSex);
    printf("请输入学生年龄：\n");
    scanf("%d", &pNewNode->stu.nAge);
    printf("请输入学号：\n");
    scanf("%lld", &pNewNode->stu.nStuNo);
    printf("请输入成绩：\n");
    scanf("%d", &pNewNode->stu.nScore);
    printf("请输入高数成绩：\n");
    scanf("%d", &pNewNode->stu.hmath);
    printf("请输入大学英语成绩：\n");
    scanf("%d", &pNewNode->stu.clgen);
    printf("请输入数据结构成绩：\n");
    scanf("%d", &pNewNode->stu.dsaa);
    printf("请输入计算机成绩：\n");
    scanf("%d", &pNewNode->stu.cs);
    printf("请输入概率论成绩：\n");
    scanf("%d", &pNewNode->stu.prothy);
    printf("请输入大学物理成绩：\n");
    scanf("%d", &pNewNode->stu.clpy);
    printf("学生信息录入成功。\n\n");

    // 插入到循环双向链表中
    if (g_pHead == NULL)
    {
        g_pHead = pNewNode;
        pNewNode->pNext = pNewNode;
        pNewNode->pPrev = pNewNode;
    }
    else
    {
        Node *pLast = g_pHead->pPrev;
        pNewNode->pNext = g_pHead;
        pNewNode->pPrev = pLast;
        pLast->pNext = pNewNode;
        g_pHead->pPrev = pNewNode;
    }

    pthread_mutex_unlock(&list_mutex);
}

// 2.打印学生信息
void PrintStudent()
{
    if (g_pHead == NULL)
    {
        printf("暂无学生信息\n");
        return;
    }

    // 打印表头
    printf("*********************************************************************************\n");
    printf("* %-20s *\n", "大学生成绩管理系统");
    printf("*********************************************************************************\n");
    printf("* %-12s * %-12s * %-8s * %-6s * %-8s * %-12s * %-14s * %-12s * %-12s * %-12s * %-12s *\n",
           "学号", "姓名", "性别", "年龄", "成绩", "高数成绩", "大学英语成绩", "数据结构成绩", "计算机成绩", "概率论成绩", "大学物理成绩");
    printf("*********************************************************************************\n");

    Node *p = g_pHead;
    do
    {
        printf("*\t%lld\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\n",
               p->stu.nStuNo,
               p->stu.szName,
               p->stu.szSex,
               p->stu.nAge,
               p->stu.nScore,
               p->stu.hmath,
               p->stu.clgen,
               p->stu.dsaa,
               p->stu.cs,
               p->stu.prothy,
               p->stu.clpy);
        printf("*********************************************************************************\n");
        p = p->pNext;
    } while (p != g_pHead);
}

// 3.统计所有学生人数
void CountStudent()
{
    int countStu = 0;
    if (g_pHead == NULL)
    {
        printf("学生总人数：%d\n\n", countStu);
        return;
    }

    Node *p = g_pHead;
    do
    {
        countStu++;
        p = p->pNext;
    } while (p != g_pHead);

    printf("学生总人数：%d\n\n", countStu);
}

// 4.查找学生信息
void FindStudent()
{
    long long stuNum;
    printf("请输入查找学生学号：");
    scanf("%lld", &stuNum);

    if (g_pHead == NULL)
    {
        printf("系统中暂无学生信息，请录入后再来打印查看。\n\n");
        return;
    }

    bool isShowHead = false;
    bool isFindStu = false;
    Node *p = g_pHead;
    do
    {
        if (stuNum == p->stu.nStuNo)
        {
            if (!isShowHead)
            {
                printf("*********************************************************************************\n");
                printf("* %-12s * %-12s * %-8s * %-6s * %-8s * %-12s * %-14s * %-12s * %-12s * %-12s * %-12s *\n",
                       "学号", "姓名", "性别", "年龄", "成绩", "高数成绩", "大学英语成绩", "数据结构成绩", "计算机成绩", "概率论成绩", "大学物理成绩");
                printf("*********************************************************************************\n");
                isShowHead = true;
            }
            printf("*\t%lld\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\n",
                   p->stu.nStuNo,
                   p->stu.szName,
                   p->stu.szSex,
                   p->stu.nAge,
                   p->stu.nScore,
                   p->stu.hmath,
                   p->stu.clgen,
                   p->stu.dsaa,
                   p->stu.cs,
                   p->stu.prothy,
                   p->stu.clpy);
            printf("*********************************************************************************\n");
            isFindStu = true;
        }
        p = p->pNext;
    } while (p != g_pHead);

    if (!isFindStu)
    {
        printf("学号输入有误，系统中暂无该学生信息。\n\n");
    }
}

// 5.修改学生信息
void ChangeStudent()
{
    long long stuNum;
    printf("请输入欲修改学生的学号：");
    scanf("%lld", &stuNum);

    if (g_pHead == NULL)
    {
        printf("系统中暂无学生信息，无法进行修改。\n\n");
        return;
    }

    bool isShowHead = false;
    bool isFindStu = false;
    Node *p = g_pHead;
    do
    {
        if (stuNum == p->stu.nStuNo)
        {
            if (!isShowHead)
            {
                printf("*********************************************************************************\n");
                printf("* %-12s * %-12s * %-8s * %-6s * %-8s * %-12s * %-14s * %-12s * %-12s * %-12s * %-12s *\n",
                       "学号", "姓名", "性别", "年龄", "成绩", "高数成绩", "大学英语成绩", "数据结构成绩", "计算机成绩", "概率论成绩", "大学物理成绩");
                printf("*********************************************************************************\n");
                isShowHead = true;
            }
            printf("*\t%lld\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\t%d\t*\n",
                   p->stu.nStuNo,
                   p->stu.szName,
                   p->stu.szSex,
                   p->stu.nAge,
                   p->stu.nScore,
                   p->stu.hmath,
                   p->stu.clgen,
                   p->stu.dsaa,
                   p->stu.cs,
                   p->stu.prothy,
                   p->stu.clpy);
            // 修改学生信息
            printf("请输入学生姓名：\n");
            scanf("%s", p->stu.szName);
            printf("请输入性别：\n");
            scanf("%s", p->stu.szSex);
            printf("请输入学生年龄：\n");
            scanf("%d", &p->stu.nAge);
            printf("请输入学号：\n");
            scanf("%lld", &p->stu.nStuNo);
            printf("请输入成绩：\n");
            scanf("%d", &p->stu.nScore);
            printf("请输入高数成绩：\n");
            scanf("%d", &p->stu.hmath);
            printf("请输入大学英语成绩：\n");
            scanf("%d", &p->stu.clgen);
            printf("请输入数据结构成绩：\n");
            scanf("%d", &p->stu.dsaa);
            printf("请输入计算机成绩：\n");
            scanf("%d", &p->stu.cs);
            printf("请输入概率论成绩：\n");
            scanf("%d", &p->stu.prothy);
            printf("请输入大学物理成绩：\n");
            scanf("%d", &p->stu.clpy);
            isFindStu = true;
            printf("*********************************************************************************\n");
            printf("学生信息修改成功，请注意及时保存。\n\n");
        }
        p = p->pNext;
    } while (p != g_pHead);

    if (!isFindStu)
    {
        printf("学号输入有误，系统中暂无该学生信息，无法进行修改。\n\n");
    }
}

// 6.删除学生信息
void DeleteStudent()
{
    long long stuNum;
    printf("请输入删除学生的学号：");
    scanf("%lld", &stuNum);

    if (g_pHead == NULL)
    {
        printf("系统中暂无学生信息，无法进行删除操作。\n\n");
        return;
    }

    bool isFindStu = false;
    Node *p = g_pHead;
    Node *toDelete = NULL;

    do
    {
        if (stuNum == p->stu.nStuNo)
        {
            toDelete = p;
            isFindStu = true;
            break;
        }
        p = p->pNext;
    } while (p != g_pHead);

    if (!isFindStu)
    {
        printf("学号输入有误，系统中暂无该学生信息，无法进行删除操作。\n\n");
        return;
    }

    // 删除找到的节点保存下一个指针
    Node *nextNode = toDelete->pNext;
    if (toDelete->pNext == toDelete)
    {
        // 只有一个节点
        g_pHead = NULL;
    }
    else
    {
        toDelete->pPrev->pNext = toDelete->pNext;
        toDelete->pNext->pPrev = toDelete->pPrev;
        if (toDelete == g_pHead)
        {
            g_pHead = toDelete->pNext;
        }
    }
    free(toDelete);
    printf("删除成功\n");
}

// 7.导出函数
void ExportToFile()
{
    FILE *fp = fopen("student_data.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "错误: 无法创建文件 'student_data.txt' (错误码: %d)\n", errno);
        return;
    }
    if (g_pHead != NULL)
    {
        Node *p = g_pHead;
        do
        {
            fprintf(fp, "%s %s %d %lld %d %d %d %d %d %d %d\n",
                    p->stu.szName,
                    p->stu.szSex,
                    p->stu.nAge,
                    p->stu.nStuNo,
                    p->stu.nScore,
                    p->stu.hmath,
                    p->stu.clgen,
                    p->stu.dsaa,
                    p->stu.cs,
                    p->stu.prothy,
                    p->stu.clpy);
            p = p->pNext;
        } while (p != g_pHead);
    }
    fclose(fp);
    printf("学生信息已导出至 student_data.txt\n\n");
}

// 8.导入函数
void ImportFromFile()
{
    FILE *fp = fopen("student_data.txt", "r");
    if (!fp)
    {
        printf("文件打开失败，无法导入\n\n");
        return;
    }
    // 清空原有链表数据
    ClearAllStudents();

    while (1)
    {
        Node *pNewNode = (Node *)malloc(sizeof(Node));
        pNewNode->pNext = NULL;
        pNewNode->pPrev = NULL;
        if (fscanf(fp, "%s %s %d %lld %d %d %d %d %d %d %d",
                   pNewNode->stu.szName,
                   pNewNode->stu.szSex,
                   &pNewNode->stu.nAge,
                   &pNewNode->stu.nStuNo,
                   &pNewNode->stu.nScore,
                   &pNewNode->stu.hmath,
                   &pNewNode->stu.clgen,
                   &pNewNode->stu.dsaa,
                   &pNewNode->stu.cs,
                   &pNewNode->stu.prothy,
                   &pNewNode->stu.clpy) != 11)
        {
            free(pNewNode);
            break;
        }
        // 插入到循环双向链表中
        if (g_pHead == NULL)
        {
            g_pHead = pNewNode;
            pNewNode->pNext = pNewNode;
            pNewNode->pPrev = pNewNode;
        }
        else
        {
            Node *pLast = g_pHead->pPrev;
            pNewNode->pNext = g_pHead;
            pNewNode->pPrev = pLast;
            pLast->pNext = pNewNode;
            g_pHead->pPrev = pNewNode;
        }
    }
    fclose(fp);
    printf("成功从 student_data.txt 导入学生信息\n\n");
}

// 清理所有学生节点的内存
void ClearAllStudents()
{
    if (g_pHead == NULL)
        return;
    Node *p = g_pHead->pNext;
    while (p != g_pHead)
    {
        Node *temp = p;
        p = p->pNext;
        free(temp);
    }
    free(g_pHead);
    g_pHead = NULL;
}

// 功能选择函数
void Functionselect(int choice)
{
    switch (choice)
    {
    case 1: // 录入学生信息
        InputStudent();
        break;
    case 2: // 打印学生信息
        PrintStudent();
        break;
    case 3: // 统计所有学生人数
        CountStudent();
        break;
    case 4: // 查找学生信息
        FindStudent();
        break;
    case 5: // 修改学生信息
        ChangeStudent();
        break;
    case 6: // 删除学生信息
        DeleteStudent();
        break;
    case 7: // 导出文件
        ExportToFile();
        break;
    case 8: // 导入文件
        ImportFromFile();
        break;
    default:
        printf("输入有误，没有该功能\n\n");
        break;
    }
}

int getch()
{
    int ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // 保存当前属性
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 关闭缓冲和回显
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复属性
    return ch;
}

int VerifyPassword()
{
    char input[50];
    char password[] = "123456789"; // 修改密码
    int index = 0;
    char ch;
    printf("请输入密码: ");
    while (1)
    {
        ch = getch();
        if (ch == '\n' || ch == '\r')
        {
            input[index] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 127 || ch == '\b')
        {
            if (index > 0)
            {
                index--;
                printf("\b \b");
            }
        }
        else
        {
            input[index++] = ch;
            printf("*");
        }
    }
    if (strcmp(input, password) == 0)
    {
        printf("密码验证成功!\n\n");
        return 1;
    }
    else
    {
        printf("密码错误，程序即将退出。\n");
        return 0;
    }
}

/*1、学生成绩管理系统
（1）问题描述：要求以学生成绩管理业务为背景，设计一个“学生成绩管理系统”程序。
    对于学校来讲，学生成绩管理系统是不可缺少的组成部分，主要是对学生资料的录入、浏览、插入和删除等基本功能的实现。

（2）设计要求：编制一个学生成绩管理程序。设学生成绩以一个学生一条记录的形式存储，每个学生记录包含的信息有学号和各门功课的成绩。
    设每位学生学习高等数学、大学英语、数据结构与算法、计算机组成原理、概率论与数理统计和大学物理6门课程。

（3）数据结构：使用单链表作为实现该问题的数据结构。

（4）实现操作：程序设计一般由算法和数据结构两部分构成。管理学生的成绩适合用单链表，方便随时插入和删除学生记录，实现动态管理。
    一个学生作为一个结点，该结点类型为结构体，结构体中的域表示学生的属性。每个结点除了存放属性外，还存放指向后继结点的指针。
①定义单链表结点的结构体；
②单链表的建立模块；
③插入模块；
④删除模块；
⑤输出模块；
⑥主模块
*/