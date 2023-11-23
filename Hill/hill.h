#ifndef HILL_H
#define HILL_H
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using Matrix = vector<vector<int>>;

class Hill 
{
private:
    static const vector<char> table;        // 字母表
    
    bool key_is_inverse(string &key);       // 判断密钥是否可逆

    Matrix key_to_matrix(string &key);      // 将密钥转换为矩阵
    Matrix Translate_message_to_matrix(string &message); // 将 string转换为矩阵
    string Translate_matrix_to_message(Matrix &matrix);  // 将矩阵转换为 string
    Matrix Get_reverse_matrix(Matrix &matrix); // 求矩阵的逆矩阵

    int exgcd_1(int a, int b, int *x, int *y);
    int cal(int a, int n);

    string key;
    string in_plaintext;
    string out_ciphertext;
    string out_plaintext;

    Matrix key_matrix;
    Matrix mes_matrix; 

    Matrix keyMatrix_mul_mesMatrix(Matrix &key_matrix, Matrix &mes_matrix); // 矩阵乘以列向量
    static const vector<vector<int>> key_test;  // 测试用密钥

public:
    Hill(string &message, string &key) {

        if(message.size() % 2 != 0){ // 奇数填充 x 
            message += 'x';
        }
        this->in_plaintext = message;
        this->key = key;
        this->mes_matrix = Translate_message_to_matrix(message);
        this->key_matrix = key_to_matrix(key);
        bool flag = key_is_inverse(key);
        if(!flag){
            cout << "key is not inverse" << endl;
            exit(1);
        }
        
    }
    string encrypt();
    string decrypt(string &ciphertext, string &key);

    void print_Matrix(){
         
        for (auto &row : this->mes_matrix){
            for (auto &col : row){
                std::cout << col << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (auto &row : this->key_matrix){
            for (auto &col:row){
                std::cout << col << " ";
            }
            std::cout << std::endl;
        }
    }

};
#endif
