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


typedef struct {
    int n_linhas;
    int n_produtos;
    vector<int> custo_producao;
    vector<vector<int>> tempo_preparo;
} Instancia;



class Solution{
    public:
        vector<vector<int>> linhas_producao;
        int tempo_total = 9999;
        Instancia instancia;

        Solution(vector<vector<int>> linhas, int tempo_total, Instancia instancia){
            this->linhas_producao = linhas;
            this->tempo_total = tempo_total;
            this->instancia = instancia;
        }

        vector<int> custo_linhas(){
            vector<int> custo_linhas;
            for (int i = 0; i < linhas_producao.size(); i++){
                int custo_linha = 0;
                int len_linha = linhas_producao[i].size();
                for (int j = 0; j < len_linha - 1; j++){
                    custo_linha += instancia.tempo_preparo[linhas_producao[i][j] - 1][linhas_producao[i][j + 1] - 1];
                    custo_linha += instancia.custo_producao[linhas_producao[i][j] - 1];
                }
                custo_linha += instancia.custo_producao[linhas_producao[i][len_linha - 1] - 1];
                custo_linhas.push_back(custo_linha);
            }
            return custo_linhas;
        }

        int custo_total(){
            
            vector<int> custo_linhas = this->custo_linhas();
            int custo_maximo = custo_linhas[0];

            for (int i = 0; i < custo_linhas.size(); i++){
                if (custo_linhas[i] > custo_maximo){
                
                    custo_maximo = custo_linhas[i];
                }
                cout << "Custo da linha " << i + 1 << ": " << custo_linhas[i] << endl;
            }
            return custo_maximo;
        }
};



int main()
{
    string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\instancia_1.txt";
    int n_linhas, n_produtos;
    vector<int> produtos;
    vector<vector<int>> tempo_preparo;
    
    leitor_de_instancias(caminho_arquivo, n_linhas, n_produtos, produtos, tempo_preparo);
    
    Instancia instancia = {n_linhas, n_produtos, produtos, tempo_preparo};
    

    vector<int> linha_1 = {1, 6, 5};
    vector<int> linha_2 = {4, 3, 2};
    vector<vector<int>> linhas = {linha_1, linha_2};
    Solution solution = Solution(linhas, 9999, instancia);
    int custo_total = solution.custo_total();
    cout << "Custo total: " << custo_total << endl;

    /*cout << "n_linhas: " << n_linhas << endl; 
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
    */

    return 0;
}