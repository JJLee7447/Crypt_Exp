#include"AES.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;

void test1(){
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

    a.Decrypt(cipher,plain_text_str,key1);
    cout << plain_text_str << endl;
}

void test2(){
    AES a;
    string key = "123456789013456";
    std::ifstream in_file;
    in_file.open("./testfile/plain.txt", std::ios::in);
    string str;
    in_file >> str;

    string cipher_text_str = a.En(str, key);

    std::ofstream out_file,out_de_plaintext_file;
    
    out_file.open("./testfile/cipher.txt", std::ios::out);
    out_de_plaintext_file.open("./testfile/de_plaintext.txt", std::ios::out);
    out_file << cipher_text_str;

    string p = a.De(cipher_text_str, key);
    out_de_plaintext_file << p ;

}

void test3(){
    std::ifstream r_file("./testfile/plain.txt"); // 打开文件
    std::string content((std::istreambuf_iterator<char>(r_file)), (std::istreambuf_iterator<char>())); // 使用流迭代器将文件内容读入字符串
    AES a;
    string key = "123456789013456";
    string cipher = a.En(content, key); 

    std::ofstream w_file("./testfile/cipher.txt",std::ios::out); // 打开文件
    w_file << cipher;

    std::ifstream r_file1("./testfile/cipher.txt"); // 打开文件
    std::string content1((std::istreambuf_iterator<char>(r_file1)), (std::istreambuf_iterator<char>())); // 使用流迭代器将文件内容读入字符串

    string plain = a.De(content1, key);

    std::ofstream w_file1("./testfile/de_plain.txt",std::ios::out); // 打开文件
    w_file1 << plain;

    r_file1.close();
    w_file1.close();
    r_file.close();

}
int main()
{
    test3();
}