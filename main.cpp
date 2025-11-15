#include "algoritmos.h"
#include "arquivos.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// --- Protótipos das funções internas do main.cpp ---
int mostrarMenuAlgoritmo();
char mostrarMenuTipo();
int mostrarMenuTamanho();
void processarOrdenacao(const string& nomeAlgoritmo, char tipo, int tamanho);
void executarTesteParaAlgoritmo(const string& nomeAlgoritmo);

// --- Função main() ---
int main() {
    while (true) {
        int escolha = mostrarMenuAlgoritmo();
        string nomeAlgoritmo;
        switch (escolha) {
            case 1: nomeAlgoritmo = "Insertion Sort"; executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 2: nomeAlgoritmo = "Bubble Sort";    executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 3: nomeAlgoritmo = "Selection Sort"; executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 4: nomeAlgoritmo = "Shell Sort";     executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 5: nomeAlgoritmo = "Merge Sort";     executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 6: nomeAlgoritmo = "Quick Sort V1";  executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 7: nomeAlgoritmo = "Quick Sort V2";  executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 8: nomeAlgoritmo = "Quick Sort V3";  executarTesteParaAlgoritmo(nomeAlgoritmo); break;
            case 0: cout << "Saindo do programa...\n"; return 0;
            default: cout << "Opcao invalida! Tente novamente.\n"; break;
        }
    }
    return 0;
}

// --- Implementação das Funções de Lógica e Menus ---

void processarOrdenacao(const string& nomeAlgoritmo, char tipo, int tamanho) {
    string caminho_entrada = gerarCaminhoArquivo(nomeAlgoritmo, "Arquivos de Entrada", tipo, tamanho, "Entrada");
    
    vector<int> vetor_numeros = lerArquivoDeEntrada(caminho_entrada);
    if(vetor_numeros.empty()) {
        cout << "Nao foi possivel ler os dados. O teste sera abortado.\n";
        return;
    }

    cout << "Ordenando o vetor...";
    auto inicio = chrono::high_resolution_clock::now();
    
    if (nomeAlgoritmo == "Insertion Sort")      insertionSort(vetor_numeros);
    else if (nomeAlgoritmo == "Bubble Sort")    bubbleSort(vetor_numeros);
    else if (nomeAlgoritmo == "Selection Sort") selectionSort(vetor_numeros);
    else if (nomeAlgoritmo == "Shell Sort")     shellSort(vetor_numeros);
    else if (nomeAlgoritmo == "Merge Sort")     mergeSort(vetor_numeros);
    else if (nomeAlgoritmo == "Quick Sort V1") quickSort_v1(vetor_numeros);
    else if (nomeAlgoritmo == "Quick Sort V2") quickSort_v2(vetor_numeros);
    else if (nomeAlgoritmo == "Quick Sort V3") quickSort_v3(vetor_numeros);

    
    auto fim = chrono::high_resolution_clock::now();
    cout << " Vetor ordenado!\n";
    
    chrono::duration<double, milli> tempo_gasto = fim - inicio;

    string caminho_saida = gerarCaminhoArquivo(nomeAlgoritmo, "Arquivos de Saida", tipo, tamanho, "Saida");
    string caminho_tempo = gerarCaminhoArquivo(nomeAlgoritmo, "Arquivos de Tempo", tipo, tamanho, "Tempo");
    
    salvarVetorEmArquivo(vetor_numeros, caminho_saida);
    salvarTempoEmArquivo(tempo_gasto.count(), tamanho, caminho_tempo);
}

void executarTesteParaAlgoritmo(const string& nomeAlgoritmo) {
    char tipo = mostrarMenuTipo();
    if (tipo == 'v' || (tipo != 'c' && tipo != 'd' && tipo != 'r')) {
        if(tipo != 'v') cout << "Opcao de tipo invalida, voltando...\n";
        return;
    }

    int tamanho_escolhido = mostrarMenuTamanho();
    if (tamanho_escolhido == 0) return;

    if (tamanho_escolhido == -1) {
        vector<int> todos_os_tamanhos = {10, 100, 1000, 10000, 100000, 1000000};
        cout << "\nIniciando teste para " << nomeAlgoritmo << " para TODOS os tamanhos...\n";
        for (int tamanho_atual : todos_os_tamanhos) {
            cout << "\nProcessando tamanho: " << tamanho_atual << "...\n";
            criarEstruturaDePastas(nomeAlgoritmo);
            cout << "Gerando arquivo de entrada...";
            gerarEntradas(nomeAlgoritmo, tipo, tamanho_atual);
            cout << " Arquivo gerado!\n";
            processarOrdenacao(nomeAlgoritmo, tipo, tamanho_atual);
        }
        cout << "\nTodos os testes foram concluidos com sucesso!\n";
    } else {
        cout << "\nIniciando teste para " << nomeAlgoritmo << " com tamanho " << tamanho_escolhido << "...\n";
        criarEstruturaDePastas(nomeAlgoritmo);
        cout << "Gerando arquivo de entrada...";
        gerarEntradas(nomeAlgoritmo, tipo, tamanho_escolhido);
        cout << " Arquivo gerado!\n";
        processarOrdenacao(nomeAlgoritmo, tipo, tamanho_escolhido);
        cout << "Teste concluido! Arquivos gerados na pasta '" << nomeAlgoritmo << "'.\n";
    }
}

int mostrarMenuAlgoritmo() {
    cout << "\n====== MENU PRINCIPAL ======\n";
    cout << "Escolha o algoritmo de ordenacao:\n";
    cout << "1: Insertion Sort\n";
    cout << "2: Bubble Sort\n";
    cout << "3: Selection Sort\n";
    cout << "4: Shell Sort\n";
    cout << "5: Merge Sort\n";
    cout << "6: Quick Sort (pivo primeiro elemento)\n";
    cout << "7: Quick Sort (pivo mediana de tres)\n";
    cout << "8: Quick Sort (pivo aleatorio)\n";
    cout << "0: Sair\n";
    cout << "Opcao: ";
    int escolha;
    cin >> escolha;
    return escolha;
}

char mostrarMenuTipo() {
    cout << "\nEscolha o tipo de instancia:\n";
    cout << "'c' - Crescente\n";
    cout << "'d' - Decrescente\n";
    cout << "'r' - Aleatoria (Random)\n";
    cout << "'v' - Voltar ao menu principal\n";
    cout << "Opcao: ";
    char escolha;
    cin >> escolha;
    return escolha;
}

int mostrarMenuTamanho() {
    cout << "\nEscolha o tamanho da instancia:\n";
    cout << "1: 10\n";
    cout << "2: 100\n";
    cout << "3: 1.000\n";
    cout << "4: 10.000\n";
    cout << "5: 100.000\n";
    cout << "6: 1.000.000\n";
    cout << "7: Rodar todos os tamanhos\n";
    cout << "0: Voltar ao menu principal\n";
    cout << "Opcao: ";
    int escolha;
    cin >> escolha;
    switch (escolha) {
        case 1: return 10;
        case 2: return 100;
        case 3: return 1000;
        case 4: return 10000;
        case 5: return 100000;
        case 6: return 1000000;
        case 7: return -1;
        default: return 0;
    }
}