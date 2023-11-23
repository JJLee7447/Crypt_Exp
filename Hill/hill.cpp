#include "hill.h"

const vector<char> Hill::table = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','h', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's','t', 'u', 'v', 'w', 'x', 'y', 'z' };

const Matrix Hill::key_test = {
    {7, 8},
    {11, 11}};

bool Hill::key_is_inverse(string &key){
    int a = key[0] - 'a';
    int b = key[1] - 'a';
    int c = key[2] - 'a';
    int d = key[3] - 'a';
    int det = a * d - b * c;
    if (det == 0){
        return false;
    }
    return true;
}

Matrix Hill::key_to_matrix(string &key){
    Matrix matrix;
    int i = 0;
    int j = 0;
    for (auto &c : key){
        if (j == 0){
            vector<int> tmp;
            matrix.push_back(tmp);
        }
        matrix[i].push_back(c - 'a');
        j++;
        if (j == 2){
            j = 0;
            i++;
        }
    }
    return matrix;
}

Matrix Hill::Translate_message_to_matrix(string &message){
    Matrix matrix;
    int i = 0;
    int j = 0;
    for (auto &c : message){
        if (j == 0){
            vector<int> tmp;
            matrix.push_back(tmp);
        }
        matrix[i].push_back(c - 'a');
        j++;
        if (j == 2){
            j = 0;
            i++;
        }
    }

    return matrix;
}

string Hill::Translate_matrix_to_message(Matrix &matrix){
    string message;
    for (auto &row : matrix){
        for (auto &col : row){
            message += char(col + 'a');
        }
    }
    return message;
}

Matrix Hill::keyMatrix_mul_mesMatrix(Matrix &key, Matrix &mes_matrix)// 矩阵乘以列向量
{
    Matrix matrix;

    vector<int> temp;
    vector<int> tmp_matrix;

    for(auto &row:mes_matrix){
        for(auto &col:row){
            temp.push_back(col);
        }


        int a = key[0][0] * temp[0] + key[0][1] * temp[1];
        
        int b = key[1][0] * temp[0] + key[1][1] * temp[1];
        
        matrix.push_back({a, b});
        tmp_matrix.clear();
        temp.clear();
    }

    for (auto &row : matrix){
        for (auto &col : row){
            col = col % 26;
        }
    }
    return matrix;
}

Matrix Hill::Get_reverse_matrix(Matrix &matrix){

    int a = matrix[0][0];
    int b = matrix[0][1];
    int c = matrix[1][0];
    int d = matrix[1][1];
    int det = a * d - b * c;

    int mod = det % 26;

    int cal_mod = cal(mod, 26);
    Matrix adj_matrix = {
        {d, -b},
        {-c, a}};

    for(auto &row :adj_matrix){
        for ( auto & col : row){
            if (col < 0){
                col += 26;
            }
        }
    }

    for(auto &row :adj_matrix){
        for ( auto & col : row){
            col = col * 7;
            col = col % 26;
        }
    }

    return adj_matrix;
}

int Hill::exgcd_1(int a, int b, int *x, int *y){
    if (b == 0){
    *x = 1;
    *y = 0;
    return a;
    }
    int r = exgcd_1(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - a / b * (*y);
    return r;
}

int Hill::cal(int a,int n)
{
    int x,y;
    int gcd = exgcd_1(a, n, &x, &y);
    if(1%gcd!=0)
    {
        return -1;
    }
    x*=1/gcd;
    n=abs(n);
    int ans=x%n;
    if(ans<=0)
        ans+=n;
    return ans;
}


string Hill::encrypt(){

    Matrix matrix = keyMatrix_mul_mesMatrix(key_matrix, mes_matrix);
    string message = Translate_matrix_to_message(matrix);
    return message;
}

string Hill::decrypt(string &message, string &key){

    Matrix keyMatrix = key_to_matrix(key);

    Matrix key_reverse = Get_reverse_matrix(keyMatrix);

    Matrix cipherMatrix = Translate_message_to_matrix(message);


    Matrix matrix = keyMatrix_mul_mesMatrix(key_reverse, cipherMatrix);



    string plaintext = Translate_matrix_to_message(matrix);

    return plaintext;
}

