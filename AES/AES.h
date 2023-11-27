#pragma once
/**
 * @author: JJLee
 * @date: 2023/04/08
 * @email: JJlee7447@gmail.com
 * @github: https://github.com/JJLee7447
 * @brief: AES加密算法 
 * 
 */
#include<bitset>

#include<vector>
#include<string>
#include<algorithm>
#include<iostream>

using std::cout;
using std::endl;
using std::hex;
using std::string;
using std::vector;
using std::bitset;

using Cvec_Matrix =const vector<vector<unsigned char>>;
using Cvec = const vector<unsigned char>;
using Vec_Matrix = vector<vector<unsigned char>>;
using Vec = vector<unsigned char>;
using Byte = bitset<8>;
using Single_Group = vector<Byte>;
using Groups = vector<Single_Group>;
/**
 * 密钥 明文 默认 为 16字节格式 
 *  0x32, 0x88, 0x31, 0xe0, 0x43, 0x5a, 0x31, 0x37, 0xf6, 0x30, 0x98, 0x07, 0xa8, 0x8d, 0xa2, 0x34
*/

class AES
{
private:
    //tips unsigened char is like int but only positive
    //unsigned char is 0-255 , char is -128-127
    //int is -2147483648-2147483647
    static Cvec_Matrix sbox;                    //sbox
    static Cvec_Matrix inv_sbox;                //inverse sbox
    static Cvec rcon;                            //round constant
    static Cvec_Matrix mix_col_mat;             //mix column matrix
    static Cvec_Matrix inv_mix_col_mat;         //inverse mix column matrix
    static Cvec_Matrix shift_row_mat;           //shift row matrix
    static Cvec_Matrix inv_shift_row_mat;       //inverse shift row matrix 
    vector<Vec_Matrix> en_round_key;                         //en_round key
    vector<Vec_Matrix> de_round_key;                         //de_round key


    //private functions
    /**
     * @brief 将8位的明文或密钥转换为一字节
     * @param bit8 8位的明文或密钥
     * @return Byte
    */
    Byte Bit8_to_Byte(const unsigned char &bit8);  

    /**
     * @brief Vector<unsigned char> to vector<bitset<8>>
     * @param Byte_16 16字节的明文或密钥
     * @return Single_Group
    */
    Single_Group Byte16_to_GroupByte(const Vec &Byte_16);  //将16字节的明文或密钥转换为16个8位的字节

    /**
     * @brief 将16字节的明文或密钥转换为4*4的16字节矩阵
     * @param Byte_16 16字节的明文或密钥
     * @return Groups
    */
    Groups Byte16_to_Matrix(Cvec_Matrix &Byte_16);  //将16字节的明文或密钥转换为4*4的16字节矩阵

    /**
     * @brief 将16个8位的字节转换为16字节的明文或密钥
     * @param Byte_16 16个8位的字节
     * @return Vec
    */
    Vec string16_to_Byte16(const string &str);  //将字符串转换为16字节的明文或密钥
    
    /**
     * @brief 将16字节的明文或密钥转换为字符串
     * @param Byte_16 16字节的明文或密钥
     * @return string
    */
    string Byte16_to_string16(Cvec &Byte_16);  //将16字节的明文或密钥转换为字符串

    /**
     * @brief 将16字节的明文或密钥转换为4*4的16字节矩阵
     * @param Byte_16 16字节的明文或密钥
     * @return Vec_Matrix
    */
    Vec_Matrix byte16_to_4_4_mat(Cvec &Byte_16);  //将16字节的明文或密钥转换为4*4的16字节矩阵

    /**
     * @brief 将4*4的16字节矩阵转换为16字节的明文或密钥
     * @param mat_4_4 4*4的16字节矩阵
     * @return Vec
    */
    Vec Mat_4_4_to_16byte(Cvec_Matrix &mat_4_4);  //将4*4的16字节矩阵转换为16字节的明文或密钥

    /**
     * @brief G function
     * @param w 4*4的16字节矩阵
     * @param round 轮数
     * @return Vec
    */
    Vec G_func(Vec &w, int &round);  //G函数


    /**
     * @brief en xor sub key
     * @param w0_ 4*4的16字节矩阵
     * @param w1_ 4*4的16字节矩阵
     * @param w2_ 4*4的16字节矩阵
     * @param w3_ 4*4的16字节矩阵
     * @param round 轮数
     * @return void
    */
    void en_sub_xor_key(Vec &w0_, Vec &w1_, Vec &w2_, Vec &w3_, int &round); //en xor sub key

    /**
     * @brief de xor sub key
     * @param w0_ 4*4的16字节矩阵
     * @param w1_ 4*4的16字节矩阵
     * @param w2_ 4*4的16字节矩阵
     * @param w3_ 4*4的16字节矩阵
     * @param round 轮数
    */
    void de_sub_xor_key(Vec &w0_, Vec &w1_, Vec &w2_, Vec &w3_, int &round); //de xor sub key

    /**
     * @brief en key expansion
     * @param key_16byte 16字节的密钥
     * @return void
     * @note 生成轮密钥
    */
    void EnKeyExpansion(Vec_Matrix &key_16byte);  //En key expansion

    /**
     * @brief de key expansion
     * @param key_16byte 16字节的密钥
     * @return void
     * @note 生成轮密钥
    */
    void DeKeyExpansion(Vec_Matrix &key_16byte);  //De key expansion

    // 核心加密函数

    /**
     * @brief add round key
     * @param state 4*4的16字节矩阵
     * @param round_key 4*4的16字节矩阵
     * @return void
    */
    void AddRoundKey(Vec_Matrix &state, Vec_Matrix &round_key);  //add round key

    /**
     * @brief sub bytes
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void SubBytes(Vec_Matrix &state);  //sub bytes

    /**
     * @brief inverse sub bytes
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void InvSubBytes(Vec_Matrix &state);  //inverse sub bytes

    /**
     * @brief shift rows
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void ShiftRows(Vec_Matrix &state);  //shift rows

    /**
     * @brief inverse shift rows
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void InvShiftRows(Vec_Matrix &state);  //inverse shift rows

    /**
     * @brief mix columns
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void MixColumns(Vec_Matrix &state);  //mix columns

    /**
     * @brief inverse mix columns
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void InvMixColumns(Vec_Matrix &state);  //inverse mix columns

    /**
     * @brief GF(2^8) multiplication
     * @param a unsigned char
     * @param b unsigned char
     * @return unsigned char
    */
    unsigned char GF28_mul(unsigned char a, unsigned char b);  //GF(2^8) multiplication

    /**
     * @brief en cipher
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void EnCipher(Vec_Matrix &state);  //en cipher

    /**
     * @brief de cipher
     * @param state 4*4的16字节矩阵
     * @return void
    */
    void InvCipher(Vec_Matrix &state);  //de cipher

    /**
     * @brief en
     * @param plain_text 明文
     * @param key 密钥
     * @return string
    */
    void byteEncrypt(Cvec &plain_text, Vec &cipher_text, Cvec &key);  //16 byte encrypt

    /**
     * @brief de
     * @param cipher_text 密文
     * @param key 密钥
     * @return string
    */
    void byteDecrypt(Cvec &cipher_text, Vec &plain_text, Cvec &key);  //16 byte decrypt

    /**
     * @brief split string into vector string(64 字节)
     * @param str string
     * @return vector<string>
    */
    vector<string> split_string(string &str);  //split string into vector string

    /**
     * @brief join vector string(64 字节)into string
     * @param str_vec vector<string>
     * @return string
    */
    string join_string(vector<string> &str_vec);  //join vector string into string

public:
    Groups ciphertext;
    void Encrypt(string& plain_text_in, vector<Vec>& cipher_text_out, string& key);  //encrypt
    void Decrypt(vector<Vec>& cipher_text_in, string& plain_text_out, string& key);  //decrypt

    string En(string &plain_text, string &key);  //en
    string De(string &cipher_text, string &key);  //de

    void get_sub_key(Vec &key);  //get sub key
    void get_de_key(Vec &key);   //get de key
};
