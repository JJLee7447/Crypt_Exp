#include"AES.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    //Vec plain_text_in={0x32, 0x88, 0x31, 0xe0, 0x43, 0x5a, 0x31, 0x37, 0xf6, 0x30, 0x98, 0x07, 0xa8, 0x8d, 0xa2, 0x34};
    //Vec key = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    //Vec key1 = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    Vec_Matrix cipher,plain_text;
    AES a;
    string str = "真的嘛fshdfuhdsfuhoff好烦hi澳反华到付";
    string key = "123456789013456";
    string key1 = "123456789014456";
    string plain_text_str;
    a.Encrypt(str,cipher,key);

    /*
    for (int i = 0; i < cipher_text.size(); i++)
    {
        for (int j = 0; j < cipher_text[i].size(); j++)
        {
            for (int k = 0; k <cipher_text[i][j].size(); k++)
            {
                cout << hex << (int)cipher_text[i][j][k] << " ";
            }
            cout << endl;
        }
        cout<<"-----------------"<<endl;
    }
    */
    a.Decrypt(cipher,plain_text_str,key1);
    cout << plain_text_str << endl;
}