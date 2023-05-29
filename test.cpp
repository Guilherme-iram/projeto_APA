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
#include "shift.cpp"

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n29m4_A.txt";
    // string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/instancia_custom_2.txt";
    
    Instancia instancia = leitor_de_instancias(caminho_arquivo);

    auto start = std::chrono::high_resolution_clock::now();

    Solution solution1, solution2;
    Algoritmo algoritmo(0.5);
    
    Shiftline shift = Shiftline(instancia);

    solution1 = algoritmo.construcao(instancia);
    solution1.print_solution();
    shift.run(solution1);
    cout << "\n";
    
    solution1.print_solution();
    cout << '\n';
    
    // print todos os custos das linhas de producao 
    
    for (int i = 0; i < solution1.linhas_producao.size(); i++){
        cout << "Linha " << i + 1 << " : "<< solution1.linhas_producao[i].custo << endl;

    }
    
    solution1.calcula_custo_total();
    solution1.print_solution();


    return 0;
    
}