#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

#include "Instancia.cpp"
#include "Solution.cpp"
#include "Construcao.cpp"
#include "SwapIntra.cpp"
#include "SwapInter.cpp"
#include "Reinsertion.cpp"
#include "Perturbacao.cpp"
#include "VND.cpp"
#include "csv.cpp"

using namespace std;

int main()
{

    // criarArquivoCSV("./resultados/resultados_custo.csv");
    // criarArquivoCSV("./resultados/resultados_construcao.csv");
    // criarArquivoCSV("./resultados/resultados_VND.csv");
    
    // criarArquivoCSV("./resultados/resultados_custo_tempo.csv");
    // criarArquivoCSV("./resultados/resultados_construcao_tempo.csv");
    // criarArquivoCSV("./resultados/resultados_VND_tempo.csv");
    
    vector<string> instances_name = 
    {
        "n10m2_A.txt",
        "n10m2_B.txt",
        "n15m3_A.txt",
        "n15m3_B.txt",
        "n15m4_A.txt",
        "n15m4_B.txt",
        "n29m4_A.txt",
        "n29m4_B.txt",
        "n29m6_A.txt",
        "n29m6_B.txt",
        "n40m5_A.txt",
        "n40m5_B.txt",
        "n52m5_A.txt",
        "n52m5_B.txt",
        "n450m16_A.txt",
        "n500m10_A.txt"
    };

    vector<double> medias_construcoes;
    vector<double> medias_VND;
    vector<double> medias_custos;

    vector<double> medias_construcoes_tempos;
    vector<double> medias_VND_tempos;
    vector<double> medias_custos_tempos;

    int Multi_Start_max_iter = 256;
    int ILS_max_iter = 4;
    int exec_max = 10;

    // Nao ta pegando as 2 ultimas instancias grandes aqui pra agilizar os testes
    for (int inst = 0; inst < instances_name.size(); inst++)
    {
        vector<int> custos = {};
        vector<int> custos_construcao = {};
        vector<double> custos_vnd = {};

        vector<double> tempos_custos = {};
        vector<double> tempos_construcoes = {};
        vector<double> tempos_vnd = {};
        

        for (int exec = 0; exec < exec_max; exec++)
        {

            //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
            // string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\" + instances_name[inst];
            // string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n52m5_A.txt";
            string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/" + instances_name[inst];
            
            Instancia instancia = leitor_de_instancias(caminho_arquivo);

            auto start_ils = std::chrono::high_resolution_clock::now();

            Solution solution;
            Solution best_solution;
            Algoritmo algoritmo;

 
            
            SwapIntra swintra = SwapIntra(instancia);
            SwapInter swinter = SwapInter(instancia);
            Reinsertion reinsertion = Reinsertion(instancia);
            Pertubacao_double_swap pertubacao = Pertubacao_double_swap(instancia);

            auto start_construcao = std::chrono::high_resolution_clock::now();
            solution = algoritmo.construcao(instancia);
            custos_construcao.push_back(solution.custo_total);
            auto end_construcao = std::chrono::high_resolution_clock::now();
            tempos_construcoes.push_back((end_construcao - start_construcao).count());
            
            best_solution = Solution(solution);

            auto start_vnd = std::chrono::high_resolution_clock::now();
            buscaLocal(best_solution, swintra, swinter, reinsertion);
            auto end_vnd = std::chrono::high_resolution_clock::now();

            custos_vnd.push_back(best_solution.custo_total);
            tempos_vnd.push_back((end_vnd - start_vnd).count());

            for (int i = 0; i < Multi_Start_max_iter; i++){

                // if (i % 2 == 0)
                // {
                //     solution = algoritmo.construcao(instancia);
                // }
                // else
                // {
                //     solution = algoritmo.construcao_melhor_insersao(instancia);
                // }

                solution = algoritmo.construcao(instancia);
                buscaLocal(solution, swintra, swinter, reinsertion);

                for (int j = 0; j < ILS_max_iter; j++)
                {
                    pertubacao.run(solution);
                    buscaLocal(solution, swintra, swinter, reinsertion);

                    if (solution.custo_total < best_solution.custo_total)
                    {
                        best_solution = Solution(solution);

                        cout << "------------------" << endl;
                        cout << "Iteracao GRASP: " << i << endl;
                        cout << "Iteracao ILS: " << j << endl;
                        cout << "NOVO MELHOR Custo: " << best_solution.custo_total << endl;
                        cout << "------------------" << endl;

                        j = 0;
                    }
                }
            }

            auto end_ils = std::chrono::high_resolution_clock::now();

            // Cálculo do tempo de execução em segundos
            std::chrono::duration<double> elapsed_seconds = end_ils - start_ils;

            cout << "------------------" << endl;
            cout << "Melhor solucao APOS SWAP: " << endl;
            cout << "Custo: " << best_solution.custo_total << endl;
            best_solution.print_solution();
            std::cout << "Tempo de execução: " << elapsed_seconds.count() << " segundos\n";
            cout << "------------------" << endl;

            custos.push_back(best_solution.custo_total);
            tempos_custos.push_back(elapsed_seconds.count());

        }
        
        double media_custo = 0;
        double media_vnd = 0;
        double media_construcao = 0;

        double media_custo_tempo = 0;
        double media_vnd_tempo = 0;
        double media_construcao_tempo = 0;


        for (int i = 0; i < custos.size(); i++)
        {
            media_custo += custos[i];
            media_vnd += custos_vnd[i];
            media_construcao += custos_construcao[i];

            media_custo_tempo += tempos_custos[i];
            media_vnd_tempo += tempos_vnd[i];
            media_construcao_tempo += tempos_construcoes[i];
        }

        media_custo = media_custo / custos.size();
        media_vnd = media_vnd / custos_vnd.size();
        media_construcao = media_construcao / custos_construcao.size();

        media_custo_tempo = media_custo_tempo / tempos_custos.size();
        media_vnd_tempo = media_vnd_tempo / tempos_vnd.size();
        media_construcao_tempo = media_construcao_tempo / tempos_construcoes.size();

        medias_custos.push_back(media_custo);
        medias_VND.push_back(media_vnd);
        medias_construcoes.push_back(media_construcao);

        medias_custos_tempos.push_back(media_custo_tempo);
        medias_VND_tempos.push_back(media_vnd_tempo);
        medias_construcoes_tempos.push_back(media_construcao_tempo);
    }

    // imprima todos os custos
    double tempo_total = 0;
    cout << "------------------" << endl;
    cout << "Custos Médios : " << endl;
    for (int i = 0; i < medias_custos.size(); i++)
    {
        cout << "------------------" << endl;
        cout << instances_name[i] << endl;
        cout << " => " << medias_custos[i] << " | " << medias_construcoes[i] << " | " << medias_VND[i] << " | " << 
        medias_custos_tempos[i]  << "s" << endl ;
        tempo_total += medias_custos_tempos[i];
    }

    cout << "------------------" << endl;
    cout << "\nMédia tempo total: " << tempo_total * exec_max << endl;

    vector<string> registro_custo = {};
    vector<string> registro_VND = {};
    vector<string> registro_construcao = {};

    vector<string> registro_custo_tempo = {};
    vector<string> registro_VND_tempo = {};
    vector<string> registro_construcao_tempo = {};

    registro_custo.push_back(std::to_string(exec_max));
    registro_custo.push_back(std::to_string(Multi_Start_max_iter));
    registro_custo.push_back(std::to_string(ILS_max_iter));

    registro_construcao.push_back(std::to_string(exec_max));
    registro_construcao.push_back(std::to_string(Multi_Start_max_iter));
    registro_construcao.push_back(std::to_string(ILS_max_iter));

    registro_VND.push_back(std::to_string(exec_max));
    registro_VND.push_back(std::to_string(Multi_Start_max_iter));
    registro_VND.push_back(std::to_string(ILS_max_iter));

    registro_custo_tempo.push_back(std::to_string(exec_max));
    registro_custo_tempo.push_back(std::to_string(Multi_Start_max_iter));
    registro_custo_tempo.push_back(std::to_string(ILS_max_iter));

    registro_construcao_tempo.push_back(std::to_string(exec_max));
    registro_construcao_tempo.push_back(std::to_string(Multi_Start_max_iter));
    registro_construcao_tempo.push_back(std::to_string(ILS_max_iter));

    registro_VND_tempo.push_back(std::to_string(exec_max));
    registro_VND_tempo.push_back(std::to_string(Multi_Start_max_iter));
    registro_VND_tempo.push_back(std::to_string(ILS_max_iter));

    for (int i = 0; i < medias_custos.size(); i++)
    {
        registro_custo.push_back(std::to_string(medias_custos[i]));
        registro_VND.push_back(std::to_string(medias_VND[i]));
        registro_construcao.push_back(std::to_string(medias_construcoes[i]));

        registro_custo_tempo.push_back(std::to_string(medias_custos_tempos[i]));
        registro_VND_tempo.push_back(std::to_string(medias_VND_tempos[i]));
        registro_construcao_tempo.push_back(std::to_string(medias_construcoes_tempos[i]));
    }

    if (registro_custo.size() - 3 != instances_name.size())
    {
        for (int i = 0; i < registro_custo.size() - 3 - instances_name.size(); i++)
        {
            registro_custo.push_back("9999");
            registro_VND.push_back("9999");
            registro_construcao.push_back("9999");

            registro_custo_tempo.push_back("9999");
            registro_VND_tempo.push_back("9999");
            registro_construcao_tempo.push_back("9999");
        }
    }
    
    // adicionarRegistroCSV("resultados/resultados_custo.csv", registro_custo);
    // adicionarRegistroCSV("resultados/resultados_construcao.csv", registro_construcao);
    // adicionarRegistroCSV("resultados/resultados_VND.csv", registro_VND);
    
    // adicionarRegistroCSV("resultados/resultados_custo_tempo.csv", registro_custo_tempo);
    // adicionarRegistroCSV("resultados/resultados_construcao_tempo.csv", registro_construcao_tempo);
    // adicionarRegistroCSV("resultados/resultados_VND_tempo.csv", registro_VND_tempo);


    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_custo.csv", registro_custo);
    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_construcao.csv", registro_construcao);
    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_VND.csv", registro_VND);

    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_custo_tempo.csv", registro_custo_tempo);
    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_construcao_tempo.csv", registro_construcao_tempo);
    adicionarRegistroCSV("/home/mikenew/projeto_APA/resultados/resultados_VND_tempo.csv", registro_VND_tempo);
    
    std::cout << "FIM DO PROGRAMA" << std::endl;
    
    return 0;
    
}