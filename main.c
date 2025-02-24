#include "gms.h"

int main()
{
    setlocale(LC_ALL, "");
    // 密码验证功能
    if (!VerifyPassword())
    {
        return 1;
    }
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
        if (choice == 0)
        {
            return 0;
        }
        Functionselect(choice);
    }
    return 0;
}