#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

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
    auto start = std::chrono::high_resolution_clock::now();

    Solution solution;

    construcao(solution, instancia);
    Solution best_solution = Solution(solution); // construcao(instancia);

    
    for (int i = 0; i < 21; i++){
        
        construcao(solution, instancia);

        if (solution.custo_total() < best_solution.custo_total()){
        
            best_solution = Solution(solution);

            cout << "------------------" << endl;
            cout << "Iteracao: " << i << endl;
            cout << "Nova Melhor solucao: " << endl;
            cout << "Custo: " << best_solution.custo_total() << endl;
            cout << "------------------" << endl;
        }

        if (i % 10 == 0){
            cout << "------------------" << endl;
            cout << "Iteracao: " << i << endl;
            cout << "------------------" << endl;
        }
        
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    // Cálculo do tempo de execução em segundos
    std::chrono::duration<double> elapsed_seconds = end - start;

    // Impressão do tempo de execução em segundos
    cout << "------------------" << endl;
    cout << "Melhor solucao: " << endl;
    cout << "Custo: " << best_solution.custo_total() << endl;
    best_solution.print_solution();
    std::cout << "Tempo de execução: " << elapsed_seconds.count() << " segundos\n";

    return 0;
}

