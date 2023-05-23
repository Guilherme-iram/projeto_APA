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

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n40m5_A.txt";
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
    
    // print solucao inicial
    cout << "------------------" << endl;
    cout << "Solucao inicial: " << endl;
    cout << "Custo: " << solution.custo_total << endl;
    solution.print_solution();
    cout << "------------------" << endl;

    int l1 = 0;
    int l2 = 1;
    int i = 1;
    int j = solution.linhas_producao[l2].produtos.size() - 2;

    reinsertion.movement(solution, l1, l2, i, j);

    cout << "------------------" << endl;
    cout << "Melhor APOS REINSERTION: " << endl;
    cout << "Custo: " << solution.custo_total << endl;
    solution.print_solution();
    std::cout << "FIM DO PROGRAMA" << std::endl;
    cout << "------------------" << endl;

    return 0;
    
}