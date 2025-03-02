#include <fstream>
#include <iostream>
#include <string>
#include <random>

const int N = 10000; //生成的 a[i] 的值域
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<int64_t> dist(-N, N); //规定 a[i] 的范围

void write(std::ofstream& outFile) //n 总量为 1e6
{
    int T = 37;  //一共37组数据, 100 * 10 + 1000 * 9 + 10000 * 9 + 100000 * 9 = 1E6
    outFile << T << "\n";

    for(int i = 1; i <= 10; i++) 
    {
        int n = 100; 
        outFile << n << "\n";

        for(int j = 1; j <= n; j++) 
        {
            int64_t a_i = dist(gen); //给每个 a[i] 随机生成
            outFile << a_i;
            if(j == n) outFile << "\n";
            else outFile << " ";  
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 1000;
        outFile << n << "\n";

        for(int j = 1; j <= n; j++)
        {
            int64_t a_i = dist(gen);
            outFile << a_i;
            if(j == n) outFile << "\n";
            else outFile << " ";
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 10000;
        outFile << n << "\n";

        for(int j = 1; j <= n; j++)
        {
            int64_t a_i = dist(gen);
            outFile << a_i;
            if(j == n) outFile << "\n";
            else outFile << " ";
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 100000;
        outFile << n << "\n";

        for(int j = 1; j <= n; j++)
        {
            int64_t a_i = dist(gen);
            outFile << a_i;
            if(j == n) outFile << "\n";
            else outFile << " ";
        }
    }
}

int main()
{
    int Num = 10; //创建多少个数据点

    for(int i = 0; i < Num; i++) //注意, 先在generator.cpp的目录下新建文件夹 "source"
    {
        std::string textName = "./source/" + std::to_string(i) + ".in";
        std::ofstream outFile(textName); //创建并打开文件

        if(!outFile.is_open())
        {
            std::cerr << "无法创建或打开文件！" << std::endl;
        }
        
        write(outFile);

        outFile.close(); //关闭文件
        std::cout << "The " << i << " group succeed\n";
    }
    getchar();
}