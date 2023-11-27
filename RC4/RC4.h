#pragma once

/**
 * @file RC4.h
 * @brief RC4 algorithm
 * @version 1.0
 * @date 2023-11-27
 * @author JJLee7447
*/


#include <vector>
#include <string>
#include <iostream>

class RC4
{
private:
    static std::vector<int> _S_table;
    static std::vector<int> _Seed_key;
    static std::vector<int> _K_table;
    static std::vector<int> _KeyStream;

    /**
     * @brief initial S table
     * @param S_table: the S table
     * @return void
    */
   static void initial_S_table(std::vector<int> & S_table); // initial the S table

    /**
     * @brief initial the K table
     * @param Seed_key: the seed key
     * @param K_table: the K table
     * @return void 
     */
    static void initial_K_table(std::vector<int> &Seed_key,std::vector<int> &K_table); // initial the K table

    /**
     * @brief initial permute the S table
     * @param K_table: the K table
     * @param S_table: the S table
     * @return void  
     */
    static void initial_Permute_S_table(std::vector<int> &S_table,std::vector<int> &K_table); // initial the S table

    /**
     * @brief create the key stream
     * @param PlianText_size: the size of the plaintext
     * @param KeyStream: the key stream
     * @param S_table: the S table
     * @return 
    */
    static void Create_KeyStream(size_t PlainText_size, std::vector<int> &KeyStream, std::vector<int> &S_table);

    /**
     * @brief clear all tables
     * @param void
    */

    void clear_table();

    /**
     * @brief string to vector<int>
     * @param str: the string
     * @return vector<int>
    */
    std::vector<int> str_to_vec(const std::string &str);

    /**
     * @brief vector<int> to string
     * @param vec: the vector<int>
     * @return string
    */
    std::string vec_to_str(std::vector<int> &vec);
public:
    RC4(){} 

    /**
     * @brief Encrypt the plaintext
     * @param plaintext: the plaintext
     * @param seed_key: the seed key
     * @return ciphertext
     */
    std::vector<int> Encrypt(std::vector<int> &seed_key,std::vector<int> &plainText);


    /**
     * @brief Decrypt the ciphertext
     * @param ciphertext: the ciphertext
     * @param seed_key: the seed key
     * @return plaintext
     */
    std::vector<int> Decrypt(std::vector<int> &Seed_key,std::vector<int> &ciphertext);

    /**
     * @brief print the s and k table
     * @param 'k' or 's' or "ks"
     *
     */
    void print_vector(std::string table);

};