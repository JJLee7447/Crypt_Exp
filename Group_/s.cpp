#include "s.h"
typedef vector<vector<vector<int>>> vector_3D;
typedef vector<vector<int>> Germutation;
typedef vector<int> Permutation;

void test_R_L_coset(Germutation &G){
    Permutation a = G[1];
    Permutation b = G[5];
    Germutation H = {a, b};
    vector_3D R = Get_R_coset(H, G);
    vector_3D L = Get_L_coset(H, G);

    printf("R coset is \n");
    printf("------------------\n");
    Print_vector_3D(R);

    printf("L coset is \n");
    printf("------------------\n");
    Print_vector_3D(L);
}
void test_Mul_func(Germutation &G){

    vector<int> a = Mul_func_2(G[2], G[5]);

    printf("Mul_func test \n------------------\n");
    printf("G[2] is \n");
    Print_vector(G[2]);
    printf("res[5] is \n");
    Print_vector(G[5]);
    printf("the result of G[2] * res [5] is \n");
    Print_vector(a);
    printf("------------------\n");
}

void test_Get_Reverse(Permutation &a,Germutation &G){
    vector<int> res = Reverse(a, G);
    printf("Reverse test \n------------------\n");
    printf("a is \n");
    Print_vector(a);
    printf("the result of Reverse(a) is \n");
    Print_vector(res);
    printf("------------------\n");
}

int main() {
    Germutation G = permute(3);
    Permutation a = G[3];
    test_Mul_func(G);
    test_Get_Reverse(a, G);
    test_R_L_coset(G);
   
}
