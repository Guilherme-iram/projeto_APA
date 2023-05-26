#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void criarArquivoCSV(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        // Escrever o cabeçalho das colunas
        arquivo << "exec_max,Iter_GRASP,Iter_ILS,n10m2_A,n10m2_B,n15m3_A,n15m3_B,n15m4_A,n15m4_B,n29m4_A,n29m4_B,n29m6_A,n29m6_B,n40m5_A,n40m5_B,n52m5_A,n52m5_B,n450m16_A,n500m10_A\n";
        arquivo.close();
        std::cout << "Arquivo CSV criado com sucesso.\n";
    } else {
        std::cout << "Erro ao criar o arquivo CSV.\n";
    }
}

void carregarCSV(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            std::string valor;
            std::vector<std::string> valores;
            while (std::getline(iss, valor, ',')) {
                valores.push_back(valor);
            }
            
            // Processar os valores (exemplo: imprimir)
            for (const auto& v : valores) {
                std::cout << v << " ";
            }
            std::cout << "\n";
        }
        
        arquivo.close();
    } else {
        std::cout << "Erro ao carregar o arquivo CSV.\n";
    }
}


void adicionarRegistroCSV(const std::string& nomeArquivo, const std::vector<std::string>& registro) {
    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (arquivo.is_open()) {
        for (size_t i = 0; i < registro.size(); ++i) {
            arquivo << registro[i];
            if (i < registro.size() - 1) {
                arquivo << ",";
            }
        }
        arquivo << "\n";
        arquivo.close();
        std::cout << "Registro adicionado com sucesso.\n";
    } else {
        std::cout << "Erro ao adicionar o registro ao arquivo CSV.\n";
    }
}

