#ifndef S_H
#define S_H
#include<vector>
#include<iostream>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

bool equal_vector(vector<int> &a, vector<int > & e){
    for (int i = 0; i < a.size();i++){
        if (a[i]!=e[i] ){
            return false;
        }
    }
    return true;
}

void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len){
    // 所有数都填完了
    if (first == len) {
        res.emplace_back(output);
        return;
    }
    for (int i = first; i < len; ++i) {
        // 动态维护数组
        swap(output[i], output[first]);
        // 继续递归填下一个数
        backtrack(res, output, first + 1, len);
        // 撤销操作
        swap(output[i], output[first]);
    }
}

// 生成所有排列
vector<vector<int>> permute(int &&num) {
    vector<int> nums;
    for (int i = 0; i < num; ++i) {
        nums.push_back(i);
    }
    vector<vector<int> > res;
    backtrack(res, nums, 0, (int)nums.size());
    return res;
}

// 置换的合成 

vector<int> Mul_func_1(vector<int> &a, vector<int> &b) {
    vector<int> res(a.size(),0);
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size();j++){
            if(i==a[j]){
                for (int k = 0; k < a.size(); k++){
                    if(b[k] == j){    
                        res[i] = k;           
                    }
                }
            }
        }
    }
    return res;
}
vector<int> Mul_func_2(vector<int> &a, vector<int> &b){
    vector<int> res(a.size(), 0);
    for (int i = 0; i < a.size();i++){
        res[a[b[i]]] = i;
    }
    return res;
}

// 求逆

vector<int> Reverse(vector<int> &a, vector<vector<int>> & matrix){
    vector<int> res;
    for (int i = 0; i < matrix.size(); i++)
    {
        res = Mul_func_2(matrix[i], a);
        if (equal_vector(res,matrix[0])){
            return res;
        }
    }
}

void Print_MATRIX(vector<vector<int>>& res) {
    for (auto & i : res) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
void Print_vector(vector<int> &in){
    for(auto &i : in){
        cout << i << " ";
    }
    cout << endl;
}
void Print_vector_3D(vector<vector<vector<int>>> in){
    for (auto &i : in){
        for (auto &j : i){
            for (auto &k : j){
                cout << k << " ";
            }
            cout << endl;
        }
        cout << "------------------";
        cout << endl;
    }
}

vector<vector<vector<int>>> Get_R_coset(vector<vector<int>> &H, vector<vector<int >> & G){
    vector<vector<vector<int>>> res;
    vector<vector<int>> temp1;
    vector<int> temp2;

    for (int i = 0; i < G.size(); i++){
        for (int j = 0; j < H.size(); j++){
            temp2 = Mul_func_1(H[j], G[i]);
            temp1.push_back(temp2);
            temp2.clear();
        }
        res.push_back(temp1);
        temp1.clear();
    }
    return res;
}
vector<vector<vector<int>>> Get_L_coset(vector<vector<int>> &H, vector<vector<int >> & G){
    vector<vector<vector<int>>> res;
    vector<vector<int>> temp1;
    vector<int> temp2;

    for (int i = 0; i < G.size(); i++){
        for (int j = 0; j < H.size(); j++){
            temp2 = Mul_func_1(H[j], G[i]);
            temp1.push_back(temp2);
            temp2.clear();
        }
        res.push_back(temp1);
        temp1.clear();
    }
    return res;
}
#endif 