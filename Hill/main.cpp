#include  "hill.h"
#include <iostream>

using std::cin;
int main(){
    string key , plaintext;
    cout << "input plaintext: ";
    cin >> plaintext;
    cout << "input the key to encode : ";
    cin >> key;
    Hill hill(plaintext,key);
    string hill_cipher = hill.encrypt();
    cout<< "ciphter is " << hill_cipher << endl;

    string de_key;
    cout << "input key to decode : ";
    cin >> de_key;
    
    string de_plain = hill.decrypt(hill_cipher, key);

    cout << "the plaintext is " << de_plain << endl;

    return 0;
}
