#include "arquivos.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

string getNomeTipo(char tipo) {
    if (tipo == 'c') return "Crescente";
    if (tipo == 'd') return "Decrescente";
    if (tipo == 'r') return "Random";
    return "Desconhecido";
}

string gerarCaminhoArquivo(const string& nomeAlgoritmo, const string& categoria, char tipo, int tamanho, const string& prefixo) {
    string nome_tipo = getNomeTipo(tipo);
    return nomeAlgoritmo + "/" + categoria + "/" + nome_tipo + "/" + prefixo + nome_tipo + to_string(tamanho) + ".txt";
}

void criarEstruturaDePastas(const string& nomeAlgoritmo) {
    vector<string> tipos = {"Crescente", "Decrescente", "Random"};
    vector<string> categorias = {"Arquivos de Entrada", "Arquivos de Saida", "Arquivos de Tempo"};
    for (const auto& categoria : categorias) {
        for (const auto& tipo : tipos) {
            fs::create_directories(nomeAlgoritmo + "/" + categoria + "/" + tipo);
        }
    }
}

void gerarEntradas(const string& nomeAlgoritmo, char tipo, int tamanho) {
    string caminho = gerarCaminhoArquivo(nomeAlgoritmo, "Arquivos de Entrada", tipo, tamanho, "Entrada");
    ofstream arquivo(caminho);
    arquivo << tamanho << "\n";
    random_device rd;
    mt19937 gerador(rd());
    uniform_int_distribution<> distribuicao(1, 1000000);
    for (int i = 0; i < tamanho; ++i) {
        if (tipo == 'c') arquivo << i + 1 << "\n";
        else if (tipo == 'd') arquivo << tamanho - i << "\n";
        else arquivo << distribuicao(gerador) << "\n";
    }
    arquivo.close();
}

vector<int> lerArquivoDeEntrada(const string& caminho) {
    ifstream arquivo_entrada(caminho);
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao ler o arquivo: " << caminho << endl;
        return {}; // Retorna um vetor vazio em caso de erro
    }
    int tamanho_lido;
    arquivo_entrada >> tamanho_lido;
    vector<int> vetor_numeros(tamanho_lido);
    for (int i = 0; i < tamanho_lido; ++i) {
        arquivo_entrada >> vetor_numeros[i];
    }
    arquivo_entrada.close();
    return vetor_numeros;
}

void salvarVetorEmArquivo(const vector<int>& vetor, const string& caminho) {
    ofstream arquivo(caminho);
    arquivo << vetor.size() << "\n";
    for (int valor : vetor) {
        arquivo << valor << "\n";
    }
    arquivo.close();
}

void salvarTempoEmArquivo(double tempo_ms, int tamanho, const string& caminho) {
    ofstream arquivo(caminho);
    double tempo_s = tempo_ms / 1000.0;
    double tempo_min = tempo_s / 60.0;
    double tempo_hr = tempo_min / 60.0;
    long long total_seconds_int = static_cast<long long>(tempo_s);
    long long hours = total_seconds_int / 3600;
    long long minutes = (total_seconds_int % 3600) / 60;
    long long seconds = total_seconds_int % 60;
    arquivo << "Tamanho da instancia: " << tamanho << "\n";
    arquivo << "----------------------------------------\n";
    arquivo << fixed << setprecision(8);
    arquivo << "Tempo em milissegundos: " << tempo_ms << " ms\n";
    arquivo << "Tempo em segundos: " << tempo_s << " s\n";
    arquivo << "Tempo em minutos: " << tempo_min << " min\n";
    arquivo << "Tempo em horas: " << tempo_hr << " h\n";
    arquivo << "----------------------------------------\n";
    arquivo << "Formato (H:M:S aproximado): " << hours << "h " << minutes << "m " << seconds << "s\n";
    arquivo.close();
}