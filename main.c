#include "gms.h"

int main()
{
    // 使用整型接收用户选择，避免 getchar() 遗留换行符的问题
    while (1)
    {
        Menu();
        int choice = 0;
        if (scanf("%d", &choice) != 1)
        {
            // 读入错误时清理缓冲区
            while (getchar() != '\n')
                ;
            printf("输入有误，请重新选择\n\n");
            continue;
        }
        // 清理换行符
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1: // 1.录入学生信息
            InputStudent();
            break;
        case 2: // 2.打印学生信息
            PrintStudent();
            break;
        case 3: // 3.统计所有学生人数
            CountStudent();
            break;
        case 4: // 4.查找学生信息
            FindStudent();
            break;
        case 5: // 5.修改学生信息
            ChangeStudent();
            break;
        case 6: // 6.删除学生信息
            DeleteStudent();
            break;
        case 7: // 7.导出文件
            ExportToFile();
            break;
        case 8: // 8.导入文件
            ImportFromFile();
            break;
        case 0:
            return 0;
        default:
            printf("输入有误，没有该功能\n\n");
            break;
        }
    }
    return 0;
}