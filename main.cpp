#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


void leitor_de_instancias(string nome_arquivo, int& n_linhas_ref, int& n_produtos_ref, vector<int>& produtos_ref, vector<vector<int>>& tempo_preparo_ref) {
    
    string linha;
    ifstream arquivo(nome_arquivo);
    
    if (arquivo.is_open())
    {
        arquivo >> n_linhas_ref >> n_produtos_ref;

        // lendo array de produtos
        for (int i = 0; i < n_produtos_ref; i++) {
            int produto;
            arquivo >> produto;
            produtos_ref.push_back(produto);
        }
        
        // lendo matriz de tempo de preparo
        for (int i = 0; i < n_produtos_ref; i++) {
            vector<int> linha;
            for (int j = 0; j < n_produtos_ref; j++) {
                int tempo;
                arquivo >> tempo;
                linha.push_back(tempo);
            }
            tempo_preparo_ref.push_back(linha);
        }
        arquivo.close();
    } else {
        cout << "Unable to open file";
    }
}


int main()
{
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\instancia_1.txt";
    int n_linhas, n_produtos;
    vector<int> produtos;
    vector<vector<int>> tempo_preparo;
    
    leitor_de_instancias(caminho_arquivo, n_linhas, n_produtos, produtos, tempo_preparo);

    cout << "n_linhas: " << n_linhas << endl; 
    cout << "n_produtos: " << n_produtos << endl; 

    cout << "Array de produtos: ";
    for (int i = 0; i < n_produtos; i++) {
        cout << produtos[i] << " ";
    }
    cout << endl;

    cout << "Matriz de tempo de preparo: " << endl;
    for (int i = 0; i < n_produtos; i++) {
        for (int j = 0; j < n_produtos; j++) {
            cout << tempo_preparo[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}