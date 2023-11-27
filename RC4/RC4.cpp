#include "RC4.h"

// Path: RC4/RC4.cpp
// S box 0 - 255


std::vector<int> RC4::_S_table;

std::vector<int> RC4::_K_table;

std::vector<int> RC4::_Seed_key;

std::vector<int> RC4::_KeyStream;

void RC4::initial_S_table(std::vector<int> &S_table)
{
    for (int i = 0; i < 256; i++)
    {
        S_table.push_back(i);
    }
}

void RC4::initial_K_table(std::vector<int> &Seed_key, std::vector<int> &K_table)
{
    if (Seed_key.size() > 256){
        std::cout << "Seed_key size is too large" << std::endl;
        exit(0);
    }
    for (int i = 0; i < 256; i++)
    {
        K_table.push_back(Seed_key[i % Seed_key.size()]);
    }
}

void RC4::initial_Permute_S_table(std::vector<int> &S_table,std::vector<int> &K_table){
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S_table[i] + K_table[i]) % 256;
        std::swap(S_table[i], S_table[j]);
    }
}

void RC4::Create_KeyStream(size_t PlainText_size, std::vector<int> &KeyStream, std::vector<int> &S_table){
    int i = 0, j = 0, t = 0;
    for (size_t r = 0; r < PlainText_size; r++)
    {
        i = (i + 1) % 256;
        j = (j + _S_table[i]) % 256;
        std::swap(S_table[i], S_table[j]);
        t = (S_table[i] + S_table[j]) % 256;
        KeyStream.push_back(S_table[t]);
    }
}

void RC4::clear_table(){
    this->_S_table.clear();
    this->_K_table.clear();
    this->_KeyStream.clear();
    this->_Seed_key.clear();
}

std::vector<int> RC4::str_to_vec(const std::string &str){
    std::vector<int> vec;
    for (size_t i = 0; i < str.size(); i++)
    {
        vec.push_back((int)str[i]);
    }
    return vec;
}

std::string RC4::vec_to_str(std::vector<int> &vec){
    std::string str;
    for (size_t i = 0; i < vec.size(); i++)
    {
        str.push_back((char)vec[i]);
    }
    return str;
}

std::vector<int> RC4::Encrypt(std::vector<int> &Seed_key,std::vector<int> &plainText){
    this->_Seed_key = Seed_key;
    initial_S_table(this->_S_table);
    initial_K_table(Seed_key,this->_K_table);
    initial_Permute_S_table(this->_S_table,this->_K_table);
    Create_KeyStream((size_t)plainText.size(),this->_KeyStream, this->_S_table);
    std::vector<int> ciphertext;
    for (size_t i = 0; i < plainText.size(); i++)
    {
        ciphertext.push_back(plainText[i] ^ this->_KeyStream[i]);
    }
    clear_table();
    return ciphertext;
}

std::vector<int> RC4::Decrypt(std::vector<int> &Seed_key,std::vector<int> &ciphertext){
    this->_Seed_key = Seed_key;
    initial_S_table(this->_S_table);
    initial_K_table(Seed_key,this->_K_table);
    initial_Permute_S_table(this->_S_table,this->_K_table);
    Create_KeyStream((size_t)ciphertext.size(),this->_KeyStream, this->_S_table);
    std::vector<int> plaintext;
    for (size_t i = 0; i < ciphertext.size(); i++)
    {
        plaintext.push_back(ciphertext[i] ^ this->_KeyStream[i]);
    
    }
    return plaintext;
}


void RC4::print_vector(std::string table)
{

    if (table == "S" or table == "s")
    {
        std::cout << "S table: ---------------------" << std::endl;
        for (auto &i : _S_table)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << "S table size :" << _S_table.size() << std::endl;
    }
    if (table == "K" or table == "k")
    {
        std::cout << "K table: ---------------------" << std::endl;
        for (auto &i : _K_table)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << "key table size :" << _K_table.size() << std::endl;
    }
    if (table == "ks" or table == "KS")
    {
        std::cout << "key stream: -------------------" << std::endl;
        for (auto &i : _KeyStream)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << "KeyStream size :" << _KeyStream.size() << std::endl;
    }
}

