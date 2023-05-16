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
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\instancia_custom_4_20.txt";
    //string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/instancia_1.txt";
    
    Instancia instancia = leitor_de_instancias(caminho_arquivo);

    // print all products ids
    auto start = std::chrono::high_resolution_clock::now();

    Solution solution;
    Algoritmo algoritmo;

    solution = algoritmo.construcao(instancia);
    Solution best_solution = Solution(solution); 

    // print solucao inicial
    cout << "------------------" << endl;
    cout << "Solucao inicial: " << endl;
    cout << "Custo: " << solution.custo_total() << endl;
    solution.print_solution();
    cout << "------------------" << endl;

    for (int i = 0; i < 51; i++){
        
        solution = algoritmo.construcao(instancia);

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
    std::cout << "FIM DO PROGRAMA" << std::endl;
    cout << "------------------" << endl;
    return 0;
}

