#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Instancia.cpp"
#include "Solution.cpp"
#include "Construcao.cpp"

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\instancia_1.txt";
    //string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/instancia_1.txt";
    
    int n_linhas, n_produtos;
    vector<int> produtos;
    vector<int> custo_produtos;
    vector<vector<int>> tempo_preparo;
    
    leitor_de_instancias(caminho_arquivo, n_linhas, n_produtos, produtos, custo_produtos, tempo_preparo);
    
    Instancia instancia = {n_linhas, n_produtos, produtos, custo_produtos, tempo_preparo};
    
    // print all products ids

    Solution solution = construcao(instancia);

    // Linha_producao linha_1 = {0, {1, 6, 5}};
    // Linha_producao linha_2 = {0, {4, 3, 2}};

    // vector<Linha_producao> linhas = {linha_1, linha_2};
    // Solution solution = Solution(linhas, 999, instancia);
    // Solution solution = Construction(instancia);

    int custo_total = solution.custo_total();

    cout << "Custo total: " << custo_total << endl;
    
    return 0;
}

