#include<iostream>
using namespace std;

struct node
{
    int left, right, num, size, value;
}T[10005];

int cnt = 1;
void insert(int x,int root)
{
    if (cnt == 1)
    {
        T[cnt] = { 0,0,1,1,x };
        cnt++;
    }
    else
    {
        if (x < T[root].value)
        {
            if (T[root].left == 0)
            {
                T[cnt] = { 0,0,1,1,x };
                T[root].left = cnt;
                cnt++;
            }
            else
                insert(x, T[root].left);
        }
        if (x == T[root].value)
            T[root].num++;
        if (x > T[root].value)
        {
            if (T[root].right == 0)
            {
                T[cnt] = { 0,0,1,1,x };
                T[root].right = cnt;
                cnt++;
            }
            else
                insert(x, T[root].right);
        }
    }
    T[root].size = T[T[root].left].size + T[T[root].right].size + T[root].num;
}

int search1(int x,int root)
{
    if (root == 0)
        return 1;
    if (x > T[root].value)
    {
        return T[T[root].left].size + T[root].num + search1(x, T[root].right);
    }
    if (x == T[root].value)
    {
        return T[T[root].left].size + 1;
    }
    if (x < T[root].value)
    {
        return search1(x, T[root].left);
    }
}

int search2(int x,int root)
{
    if (x <= T[T[root].left].size)
        return search2(x, T[root].left);
    if (x <= T[T[root].left].size + T[root].num)
        return T[root].value;
    if (x > T[T[root].left].size)
        return search2(x - T[T[root].left].size - T[root].num, T[root].right);
}

int search3(int x, int root)//求该数最大排名
{
    if (x > T[root].value)
    {
        return T[T[root].left].size + T[root].num + search1(x, T[root].right);
    }
    if (x == T[root].value)
    {
        return T[T[root].left].size + T[root].num;
    }
    if (x < T[root].value)
    {
        return search1(x, T[root].left);
    }
}

int main()
{
    int q, op, x;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> op >> x;
        if (op == 1)
            cout << search1(x, 1) << endl;
        if (op == 2)
            cout << search2(x, 1) << endl;
        if (op == 3)
        {
            int tmp = search1(x, 1);
            if (search2(tmp - 1, 1) == 0)
                cout << "−2147483647" << endl;
            else
                cout << search2(tmp - 1, 1) << endl;
        }
        if (op == 4)
        {
            int tmp = search3(x, 1);
            if (tmp == cnt)//判断输入的x是否为树中最大的数
                cout << "2147483647" << endl;
            else
                cout << search2(tmp+1, 1) << endl;
        }
        if (op == 5)
            insert(x, 1);
    }
    return 0;
}

//洛谷P5076