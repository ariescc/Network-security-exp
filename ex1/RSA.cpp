#include <iostream>

using namespace std;

long long gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

long long LeastCommonMultiple (int a, int b, int c)

{

    int t = a * b /c;

    return t;

}

long long Mode(long long a, long long b, long long mode)
{
    long long sum = 1;
    a = a % mode;

    while (b > 0) {
        if (b % 2 == 1)     //判断是否是奇数，是奇数的话将多出来的数事先乘如sum
            sum = (sum * a) % mode;

        b /= 2;
        a = (a * a) % mode;// 不断的两两合并再取模，减小a和b的规模
    }
    return sum;
}

int main()
{
    long long p, q, N, L, E, D;
    cin >> p >> q;

    // 输入明文
    long long plaintxt;
    cin >> plaintxt;

    N = p * q;
    cout << "N: " << N << endl;
    // 求最大公因数
    long long c = gcd(p-1, q-1);
    cout << "c: " << c << endl;
    L = LeastCommonMultiple(p-1, q-1, c);
    cout << "L: " << L << endl;

    // E
    for(long long i = L-1; i >= 2; i--) {
        if(gcd(i, L) == 1) E = i;
    }
    cout << "E: " << E << endl;

    // D
    for(long long i = 2; i < L; i++) {
        if((E * i) % L == 1) D = i;
    }
    cout << "D: " << D << endl;

    // 加密
    // 快速幂
    long long mitxt = Mode(plaintxt, E, N);
    cout << mitxt << endl;

    // 解密
    long long jiemi = Mode(mitxt, D, N);
    cout << jiemi << endl;

    return 0;
}

