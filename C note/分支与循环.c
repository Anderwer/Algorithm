变量赋值与判断
举例: int main()
{
    int num = 4
    if(num = 5)
    printf("5")
return 0;
}
结果:printf: 5

逻辑：if条件判断中的num = 5是赋值，而判断相等应该用num ==5
改进方法：建议写条件时用if(5 ==num),若写错时等号左边为常量，不能赋值，编译器可以识别错误

练习：1.判断一个数是否为奇数
         2.输出1-100之间的奇数

解答：int main()
{
     int i = 1
     while(i<=100)
    {  if(i%2 == 1)
       printf("%d ",i);
       i++
    }

return 0;
}
注：%为求余符号


switch语句

该语句常用于多分支情况，而if语句多用于单分支情况
举例：输出星期几
int main()
{
	int day = 0;
	scanf_s("%d", &day);
	switch (day)
	{
	case 1 :
		printf("星期一");
		break;
	case 2:
		printf("星期二");
		break;
	case 3:
		printf("星期三");
		break;
	case 4:
		printf("星期四");
		break;
	case 5:
		printf("星期五");
		break;
	case 6:
		printf("星期六");
		break;
	case 7:
		printf("星期天");
		break;
        default:
                printf("输入错误，请输入1-7\n")
                break;
	}
	return 0;
}


for 循环

int main()
{
    int i = 0
    for(i=1;i<=10;i++)
    {
      print("%d",i);
     }

return 0;
}


do while 循环打印1-10
int main()
{
   int i = 0;
   do
   {
     printf("%d ",i);
     i++;
    }
   while(i<=10);
return 0;
}

练习：在一个有序的数组中查找某一个数x

解：
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int left = 0; //获取左下标
	int sz = sizeof(arr) / sizeof(arr[0]); //获取数组中元素个数
	int right = sz - 1;
	int k = 7;  // 要寻找的元素
	while (left <= right)
	{
		int mid = (left + right) / 2;//通过while循环对right和left的改变从而改变mid取值
		if (arr[mid] < k)
			left = mid + 1;
		else if (arr[mid] > k)
			right = mid - 1;
		else
		{
			printf("找到元素，元素所在数组下标为:%d", mid);
			break;
		}
	}                //二分法寻找数组元素
	if (left > right)
		printf("未找到元素");

	return 0;
}


练习：计算1!+2!+3!+4!+...+10!

解：

int main()
{
	int i = 1;
	int count = 1;
	int sum = 0;
	for(i = 1;i <= 10;i++)
	{
		count = count * i;
		sum = sum + count;
	}
	printf("%d", sum);
	return 0;
}



练习：编写代码，演示多个字符从两端移动，向中间汇聚

解：

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
int main()
{
	char arr1[] = "welcome to study!!!!!";
	char arr2[] = "#####################";
	int left = 0;
	int size = strlen(arr1);
	int right = size - 1;
	while (left <= right)
	{
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		left++;
		right--;
		printf("%s", arr2);
		Sleep(1000);
		system("cls");
		
	}
	
	return 0;
}


练习：编写代码，模拟用户登录，并且只能登录三次（只允许登录三次，如果密码输入正确则显示登录成功，三次均错误则退出程序）

解：
#include<stdio.h>
#include<string.h>
int main()
{
	int i = 0;
	char password[20] = "0";
	for (i = 0; i < 3; i++)
	{
		printf("请输入密码:");
		scanf_s("%s", password);
		if (strcmp(password, "123456") == 0) //利用string.h中的strcmp函数判断输入字符串是否与原字符串相等，相等则输出0，可理解为相减
		{
			printf("登录成功\n");
			break;
		}
		else
			printf("密码错误，请重新输入\n");

	}
	if (3 == i)
		printf("尝试次数用完，程序退出\n");
	return 0;
}


练习：打印九九乘法表

解：
#include<stdio.h>
int main()
{
	int i, j;
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("%d*%d=%-2d ", i, j, i * j);

		}
		printf("\n");
	}
	
	return 0;
}



练习：猜数字游戏
解:

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void start()
{
    printf("*************************************\n");
    printf("********  输入数字1开始游戏  ********\n");
    printf("********  输入数字0退出游戏  ********\n");
    printf("*************************************\n");
}

void game()
{
    int randon,guess;
    randon = rand()%100+1;
    printf("请输入1-100之间的数字>:");
    while (1)
    {
        scanf_s("%d", &guess);
        if (guess < randon)
            printf("猜小了\n");
        else if (guess > randon)
            printf("猜大了\n");
        else
        {
            printf("恭喜你猜对了，数字是:%d\n", guess);
            break;
        }
    }

}


int main()
{
    srand((unsigned int)time(NULL));
    int input = 0;
    do
    {
        start();
        printf("请选择是否开始游戏>:");
        scanf_s("%d", &input);
        switch(input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }

    } while (input);
    return 0;
} 