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
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n29m4_A.txt";
    // string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/instancia_custom_2.txt";
    
    Instancia instancia = leitor_de_instancias(caminho_arquivo);

    auto start = std::chrono::high_resolution_clock::now();

    Solution solution1, solution2;
    Algoritmo algoritmo;
    vector<int> custos_1;
    vector<int> custos_2;

    for (int i = 0; i < 1000; i++) 
    {
        solution1 = algoritmo.construcao(instancia);
        solution2 = algoritmo.construcao(instancia);
        custos_1.push_back(solution1.custo_total);
        custos_2.push_back(solution2.custo_total);
    }
    
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    double media_custos_1 = 0;
    double media_custos_2 = 0;

    for (int i = 0; i < custos_1.size(); i++)
    {
        media_custos_1 += custos_1[i];
        media_custos_2 += custos_2[i];
    }

    media_custos_1 /= custos_1.size();
    media_custos_2 /= custos_2.size();

    solution1.print_solution();
    cout << "media custos 1: " << media_custos_1 << endl;
    cout << "---" << endl;
    solution2.print_solution();
    cout << "media custos 2: " << media_custos_2 << endl;

    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;

    return 0;
    
}