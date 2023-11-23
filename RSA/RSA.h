#ifndef _RSA_H_
#define _RSA_H_

#include <iostream>
using ll = long long;

// 快速乘 a * b % mod
ll ksc(ll a, ll b, ll mod);

// 快速幂 a^b % mod
ll ksm(ll a, ll b, ll mod);

ll mod_mul(ll a, ll b, ll mod);

ll mod_pow(ll a, ll n, ll mod);

// Miller-Rabin随机算法检测n是否为素数
bool Miller_Rabin(ll n);

ll create_prime_num(int keysize); // 素数位数 返回素数

ll exgcd(ll a, ll b, ll &x, ll &y);

ll match_D(ll e, ll phi); // e 欧拉函数 返回 d

struct Private_Key{
    ll d;
    ll n;
};

struct Public_Key{
    ll e;
    ll n;
};

struct Keys{
    Private_Key private_key;
    Public_Key public_key;
};

Keys Encrpyt_RSA(ll m);

ll  Decrypt_RSA(Private_Key private_key, ll C);
#endif  // _RSA_H_