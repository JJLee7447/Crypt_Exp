#include"SHA256.h"
#include<iostream>

using std::cout;
using std::endl;
int main()
{
    Ljj::SHA256 sha256;
    std::string s{"李佳骏"};

    std::string digest(sha256(s));
    cout<<s<<"\n"<<digest<<endl;
    return 0;
}
