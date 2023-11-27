#include "RC4.h"

void print_vec(std::vector<int> &vec, std::string str = "")
{
    std::cout << str << " -----------------" << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void test()
{
    std::vector<int> seed_key = {2, 1, 3, 4};
    std::vector<int> PlainText = {1, 2, 3, 4, 55, 66, 3, 2, 234, 5, 45};

    RC4 r;
    std::vector<int> ciphertext = r.Encrypt(seed_key, PlainText);

    std::vector<int> de_plain = r.Decrypt(seed_key, ciphertext);

    print_vec(PlainText, "plaintext");
    print_vec(ciphertext, "ciphertext");
    print_vec(de_plain, "de_plaintext");
}

int main()
{
    test();
}