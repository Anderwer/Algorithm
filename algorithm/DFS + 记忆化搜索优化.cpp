//先给出朴素DFS求解斐波那契数列
int f(int n) {
    if(n <= 1) {
        return 1;
    }
    return f(n-1) + f(n-2);
}

//其中有很多不必要的重复计算步骤
//对其进行记忆化搜索优化

const int INF = -1;
int h[46];

void init() {
    memset(h, INF, sizeof(h));  // 1）初始化记忆数组
}

int f(unsigned int n) {
    if(n <= 1) {
        return 1;
    }
    int &fib = h[n];            // 2）将fib引用成记忆数组中第n步的值
    if(fib != INF) {            //    引用后改变两者其中一个，值都会改变
        return fib;             // 3）fib != INF指当前fib已经计算过了
    }
    fib = f(n-1) + f(n-2);      // 4）
    return fib;
}
