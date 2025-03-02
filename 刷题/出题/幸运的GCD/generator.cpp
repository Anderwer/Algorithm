#include <fstream>
#include <iostream>
#include <string>
#include <random>

std::random_device rd;
std::mt19937_64 gen(rd());

void write(std::ofstream& outFile) //n 总量为 1e6
{
    int T = 37;  //一共37组数据, 100 * 10 + 1000 * 9 + 10000 * 9 + 100000 * 9 = 1E6
    outFile << T << " ";

    for(int i = 1; i <= 10; i++)
    {
        int n = 100;
        int m = 100;
        outFile << n << " ";
        outFile << m << " ";

        std::uniform_int_distribution<> part_dist(0, 1);  // 决定选择哪一部分
        std::uniform_int_distribution<> middle_dist(2, n - 1); // 选择 2~n-1
        std::uniform_int_distribution<> query(0, 1);
        for(int j = 1; j <= m; j++)
        {
            int L, R;
            if (part_dist(gen) == 0) L = 1, R = n;
            else
            {
                int a = middle_dist(gen);
                int b = middle_dist(gen);
                L = std::min(a, b);
                R = std::max(a, b);
            }

            int random_bit = query(gen);
            int q = (random_bit == 0) ? 3 : 5;

            outFile << L << " ";
            outFile << R << " ";
            outFile << q;
            if(j == m) outFile << "\n";
            else outFile << " ";
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 1000;
        int m = 1000;
        outFile << n << " ";
        outFile << m << " ";

        std::uniform_int_distribution<> part_dist(0, 1);  // 决定选择哪一部分
        std::uniform_int_distribution<> middle_dist(2, n - 1); // 选择 2~n-1
        std::uniform_int_distribution<> query(0, 1);
        for(int j = 1; j <= m; j++)
        {
            int L, R;
            if (part_dist(gen) == 0) L = 1, R = n;
            else
            {
                int a = middle_dist(gen);
                int b = middle_dist(gen);
                L = std::min(a, b);
                R = std::max(a, b);
            }

            int random_bit = query(gen);
            int q = (random_bit == 0) ? 3 : 5;

            outFile << L << " ";
            outFile << R << " ";
            outFile << q;
            if(j == m) outFile << "\n";
            else outFile << " ";
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 10000;
        int m = 10000;
        outFile << n << " ";
        outFile << m << " ";

        std::uniform_int_distribution<> part_dist(0, 1);  // 决定选择哪一部分
        std::uniform_int_distribution<> middle_dist(2, n - 1); // 选择 2~n-1
        std::uniform_int_distribution<> query(0, 1);
        for(int j = 1; j <= m; j++)
        {
            int L, R;
            if (part_dist(gen) == 0) L = 1, R = n;
            else
            {
                int a = middle_dist(gen);
                int b = middle_dist(gen);
                L = std::min(a, b);
                R = std::max(a, b);
            }

            int random_bit = query(gen);
            int q = (random_bit == 0) ? 3 : 5;

            outFile << L << " ";
            outFile << R << " ";
            outFile << q;
            if(j == m) outFile << "\n";
            else outFile << " ";
        }
    }

    for(int i = 1; i <= 9; i++)
    {
        int n = 100000;
        int m = 100000;
        outFile << n << " ";
        outFile << m << " ";

        std::uniform_int_distribution<> part_dist(0, 1);  // 决定选择哪一部分
        std::uniform_int_distribution<> middle_dist(2, n - 1); // 选择 2~n-1
        std::uniform_int_distribution<> query(0, 1);
        for(int j = 1; j <= m; j++)
        {
            int L, R;
            if (part_dist(gen) == 0) L = 1, R = n;
            else
            {
                int a = middle_dist(gen);
                int b = middle_dist(gen);
                L = std::min(a, b);
                R = std::max(a, b);
            }

            int random_bit = query(gen);
            int q = (random_bit == 0) ? 3 : 5;

            outFile << L << " ";
            outFile << R << " ";
            outFile << q;
            if(j == m) outFile << "\n";
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
    return 0;
}