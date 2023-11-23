# RSA Encription

## 秘钥生成 

### 第一步

随机选择两个大质数 p 和 q，并计算他们的乘积 n。在日常应用中，出于安全考虑，一般要求 n 换算成二进制要大于 2048 位。

#### 试除法

如果要判定n是否是素数，写一个循环从2到sqrt(n)判断其能否整除n，若都不能则n为素数。

```cpp

bool isPrime(int n)
{
    if(n<2)
        return false;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
            return false;
    }
    return true;
}
```
#### 素性测试

费马小定理：如果p是素数，a是整数，且gcd(p,a)=1，则 $a^{p-1} \equiv 1 \bmod p$

费马小定理是判定一个数是否为素数的必要条件，并非充分条件，因为存在着一些伪素数满足费马小定理却不是素数，如 $$2340 ≡ 1 (\bmod 341)$$，但是$$341=11×31$$

称满足$$a^{n-1} \bmod n = 1 $$的合数n叫做以a为底的伪素数(pseudoprime to base a)。

##### Fermat 素性测试

##### Millar-Rabin 素性测试

要测试 $N$ 是否为素数 ，将 $N-1$ 分解为 $2^8d$ 。在每次测试开始时，先随机选一个介于[1,N−1]的整数 a，

```cpp
typedef long long int ll;
 
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
    for (int i = 1; i <= 20; i++)  // 20为Miller-Rabin测试的迭代次数
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
```

#### 生成大素数

```cpp
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
```

### 第二步

计算 $ n = p * q $ 的欧拉函数 $\varphi(n)$

$\varphi(n) = (p-1)*(q-1)$
```cpp
int phi(int n)
{ 
int res = n;
for (int i = 2; i * i <= n; i++)
{ if (n % i == 0) 
res = res / i * (i - 1); // 先除再乘防止溢出
while (n % i == 0) // 每个质因数只处理一次，可以把已经找到的质因数除干净
n /= i; 
} 
if (n > 1)
res = res / n * (n - 1); // 最后剩下的部分也是原来的n的质因数
return res; 
}
```

### 第三步

选择一个数 $e$ 使其 与 $\varphi(n)$ 互质 ,即 gcd($e$, $\varphi(n)$) = 1  且  1 < $e$ < $\varphi(n)$

e 一般选择 3、17或65537  分别只需要2或17次模乘运算

### 第四步

计算 $e$ mod $\varphi(n)$ 的逆元 $d$，即 $e*d$ mod $\varphi(n)$ = 1

```cpp
ll match_D(ll e, ll phi) // e 欧拉函数 返回 d
{   
    ll x, y;
    if (exgcd(e, phi, x, y)!=1)
    {
        return -1;
    }
    return (x % phi + phi) % phi;
}
```

公钥 (e,n)

私钥 (d,n)


## 加密与解密

加密

$$c = m^e \bmod n$$

解密

$$m = c^d \bmod n$$

```cpp
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
```

参考资料：

[RSA 的原理与实现](https://cjting.me/2020/03/13/rsa/)

[Miller-Rabin素性测试算法详解](https://blog.csdn.net/ECNU_LZJ/article/details/72675595)