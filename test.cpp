#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Instancia.cpp"
#include "Solution.cpp"
#include "Construcao.cpp"
#include "SwapIntra.cpp"
#include "SwapInter.cpp"
#include "Reinsertion.cpp"
#include "Perturbacao.cpp"

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n10m2_A.txt";
    // string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/instancia_custom_2.txt";
    
    Instancia instancia = leitor_de_instancias(caminho_arquivo);

    auto start = std::chrono::high_resolution_clock::now();

    Solution solution;
    Algoritmo algoritmo;

    solution = algoritmo.construcao(instancia);
    Solution best_solution = Solution(solution); 

    // SwapIntra swintra = SwapIntra(instancia);
    // SwapInter swinter = SwapInter(instancia);
    Reinsertion reinsertion = Reinsertion(instancia);
    Pertubacao_ultra_swap pertubacao = Pertubacao_ultra_swap(instancia); 
    // print solucao inicial
    cout << "------------------" << endl;
    cout << "Solucao inicial: " << endl;
    cout << "Custo: " << solution.custo_total << endl;
    solution.print_solution();
    cout << "------------------" << endl;

    pertubacao.run(solution);
    solution.calcula_custo_total();
    cout << "------------------" << endl;
    // pertubacao.run(solution);
    solution.print_solution();
    return 0;
    
}