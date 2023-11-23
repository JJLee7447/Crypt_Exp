#include "RSA.h"

using ll = long long;

// 快速乘 a * b % mod
ll ksc(ll a, ll b, ll mod) {
    ll ans = 0;
    while(b) {
		if(b & 1) {
	    	ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
    }
    return ans;
}
// 快速幂 a^b % mod
ll ksm(ll a, ll b, ll mod) {
    ll ans = 1, base = a;
    while(b) {
		if(b & 1) {
	    	//优化1
	    	ans = ksc(ans, base, mod) % mod;
		}
		//优化2
		base = ksc(base, base, mod) % mod;
		b >>= 1;
    }
    return ans;
}
 
ll mod_mul(ll a, ll b, ll mod)
{
    ll res = 0;
    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}
 
ll mod_pow(ll a, ll n, ll mod)
{
    ll res = 1;
    while (n)
    {
        if (n & 1)
            res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}
 
// Miller-Rabin随机算法检测n是否为素数
bool Miller_Rabin(ll n)
{
    if (n == 2)
        return true;
    if (n < 2 || !(n & 1))
        return false;
    ll m = n - 1, k = 0;
    while (!(m & 1))
    {
        k++;
        m >>= 1;
    }
    for (int i = 1; i <= 30; i++)  // 20为Miller-Rabin测试的迭代次数
    {
        ll a = rand() % (n - 1) + 1;
        ll x = mod_pow(a, m, n);
        ll y;
        for (int j = 1; j <= k; j++)
        {
            y = mod_mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1)
                return false;
            x = y;
        }
        if (y != 1)
            return false;
    }
    return true;
}

ll create_prime_num(int keysize)      // 素数位数 返回素数
{
    srand((unsigned)time(NULL));
    while(1){
        ll n = rand()%(1<<keysize) + (1<<keysize) ; // 将二进制1左移keysize位
        if (n%2 !=0)
        {
            bool flag = true;

            for (int i = 0; i < 5; i++)
            {
                if (Miller_Rabin(n) == false)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                return n;
            }
        }
    }
}

ll exgcd(ll a,ll b, ll &x,ll &y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    ll d =  exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll match_D(ll e, ll phi) // e 欧拉函数 返回 d
{   
    ll x, y;
    if (exgcd(e, phi, x, y)!=1)
    {
        return -1;
    }
    return (x % phi + phi) % phi;
}

Keys  Encrpyt_RSA(ll m){
    ll p = create_prime_num(7);
    ll q = create_prime_num(7);

    while (p == q)
    {
        q = create_prime_num(10);
    }

    ll e = 65537;
    ll d = match_D(e, (p - 1) * (q - 1));

    ll n = p * q;

    long long C = ksm(m, e, n);

    std::cout<<"密文: "<< C << std::endl;
    std::cout<<"私钥 (d,n) :"<< d << " " << n << std::endl;
    Private_Key private_key;
    private_key.d = d;
    private_key.n = n;
    Public_Key public_key;
    public_key.e = e;
    public_key.n = n;
    Keys keys;
    keys.private_key = private_key;
    keys.public_key = public_key;
    return keys;
}

ll Decrypt_RSA(Private_Key private_key, ll C){
    ll M = ksm(C, private_key.d , private_key.n);
    return M;
}