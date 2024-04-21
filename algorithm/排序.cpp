1.冒泡排序      冒泡排序的平均时间复杂度为 O(n^2)。
 每次排序选出一个最大值放在末尾，然后再次排序
 若有n个元素，则需循环n-1次

 代码实现:
 void bubblesort(int arr[],int len)
 {
     if(len<2) return;// 数组小于2个元素不需要排序。
     bool ifswap = false;  // 记录每轮排序过程中是否交换过元素，false-未交换；true-有交换。

    // 44,3,38,5,47,15,36,26,27,2,46,4,19,50,48  
    for (int ii = len - 1; ii > 0; ii--)    // 一共进行len-1趟比较。
    {
        ifswap = false;
        for (int jj = 0; jj < ii; jj++)       // 每轮只需要比较0......ii之间的元素，ii之后的元素是已经排序好的。
        {
            if (arr[jj] > arr[jj + 1])          // 如果前面的元素大于后面的元素，则交换它位的位置。
            {
                swap(arr[jj], arr[jj + 1]);  // 交换两个元素的位置。
                ifswap = true;
            }
        }
    
        if (ifswap == false) return;     // 如果这一轮没有交换过元素，说明数组已经是有序的了。
    }
 }


 2.选择排序    选择排序的最优时间复杂度、平均时间复杂度和最坏时间复杂度均为 O(n^2)。
 从头扫至尾，找出一个最小的元素，和第一个元素交换，接着从剩下的元素中继续这种选择和交换方式。

 代码实现：
 void selectsort(int arr[], int len)
{
if (len < 2) return; // 数组小于2个元素不需要排序。

int iminpos; // 每趟循环选出的最小值的位置（数组的下标）。

// 44,3,38,5,47,15,36,26,27,2,46,4,19,50,48  
for (int ii = 0; ii < len - 1; ii++)  // 一共进行len-1趟比较。
{
    iminpos = ii;

    for (int jj = ii + 1; jj < len; jj++)  // 每趟只需要比较ii+1......len-1之间的元素，ii之前的元素是已经排序好的。
    {
        // 找出值更小的元素，记下它的位置。
        if (arr[jj] < arr[iminpos])  iminpos = jj;
    }

    // 如果本趟循环的最小的元素不是起始位置的元素，则交换它们的位置。
    if (iminpos != ii) swap(arr[ii], arr[iminpos]);
}

}

3.插入排序   插入排序的最坏时间复杂度和平均时间复杂度都为 O(n^2)。
将待排列元素划分为「已排序」和「未排序」两部分，每次从「未排序的」元素中选择一个插入到「已排序的」元素中的正确位置。

4.桶排序(非常重要)

将要排序的数作为数组下标，例如有一个数为i，则使a[i]++,最终统计a[i]的值为多少，则可以知道一组数据中的i出现了几次

代码实现:洛谷  https://www.luogu.com.cn/problem/P1271 
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 9;
int a[N];//a[i]表示数字i出现的次数

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;cin >> n >> m;
    for(int i = 1;i <= m; ++ i)
    {
        int x;cin >> x;
        a[x] ++;
    }
    for(int i = 0;i <= n; ++ i)
    {
        for(int j = 1;j <= a[i]; ++ j)
        {
            cout << i << ' ';
        }
    }
    return 0;
}

