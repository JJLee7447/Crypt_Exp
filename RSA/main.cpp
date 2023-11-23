#include "RSA.h"
#include <iostream>
int main(){

    ll M;
    std::cout<<"请输入明文: ";
    std::cin >> M;

    Keys key;
    key = Encrpyt_RSA(M);

    ll C , D, N;
    std::cout<<"请输入密文: ";
    std::cin >> C;
    std::cout<<"请输入私钥 (d,n): ";
    std::cin >> D >> N;

    Private_Key private_key;
    private_key.d = D;
    private_key.n = N;

    ll M_ = Decrypt_RSA(private_key, C);
    std::cout<<"解密后的明文: "<< M_ << std::endl;

}

