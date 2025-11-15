#include "algoritmos.h"
#include <utility> // Para std::swap
#include <random>

void insertionSort(std::vector<int>& vetor) {
    for (size_t i = 1; i < vetor.size(); i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

void bubbleSort(std::vector<int>& vetor) {
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                std::swap(vetor[j], vetor[j + 1]);
            }
        }
    }
}

void selectionSort(std::vector<int>& vetor) {
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(vetor[i], vetor[min_idx]);
        }
    }
}

void shellSort(std::vector<int>& vetor) {
    int n = vetor.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = vetor[i];
            int j;
            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap) {
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = temp;
        }
    }
}

// Função auxiliar para juntar (merge) duas metades ordenadas
void merge(std::vector<int>& vetor, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Cria vetores temporários
    std::vector<int> L(n1), R(n2);

    // Copia os dados para os vetores temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    // Junta os vetores temporários de volta no vetor original
    int i = 0;
    int j = 0;
    int k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }
}

// Função recursiva que divide o vetor e chama a função de merge
void mergeSortRecursive(std::vector<int>& vetor, int inicio, int fim) {
    if (inicio >= fim) {
        return; // Retorna se o vetor tem 1 ou 0 elementos
    }
    int meio = inicio + (fim - inicio) / 2;
    mergeSortRecursive(vetor, inicio, meio);
    mergeSortRecursive(vetor, meio + 1, fim);
    merge(vetor, inicio, meio, fim);
}

// Função principal do Merge Sort que o `main.cpp` irá chamar
void mergeSort(std::vector<int>& vetor) {
    mergeSortRecursive(vetor, 0, vetor.size() - 1);
}

// --- Função auxiliar para particionar ---
int particionar(std::vector<int>& vetor, int inicio, int fim, int pivoIndex) {
    int pivo = vetor[pivoIndex];
    std::swap(vetor[pivoIndex], vetor[fim]); // coloca o pivô no final
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            std::swap(vetor[i], vetor[j]);
        }
    }
    std::swap(vetor[i + 1], vetor[fim]);
    return i + 1;
}

// --- Função recursiva genérica do QuickSort ---
void quickSortRec(std::vector<int>& vetor, int inicio, int fim, int versao, std::mt19937& gerador) {
    if (inicio < fim) {
        int pivoIndex;
        if (versao == 1) {
            // Versão 1 - pivô é o primeiro elemento
            pivoIndex = inicio;
        } 
        else if (versao == 2) {
            // Versão 2 - mediana de três
            int meio = inicio + (fim - inicio) / 2;
            int a = vetor[inicio], b = vetor[meio], c = vetor[fim];
            if ((a > b) != (a > c)) pivoIndex = inicio;
            else if ((b > a) != (b > c)) pivoIndex = meio;
            else pivoIndex = fim;
        } 
        else {
            // Versão 3 - pivô aleatório com gerador moderno
            std::uniform_int_distribution<> dist(inicio, fim);
            pivoIndex = dist(gerador);
        }

        int p = particionar(vetor, inicio, fim, pivoIndex);
        quickSortRec(vetor, inicio, p - 1, versao, gerador);
        quickSortRec(vetor, p + 1, fim, versao, gerador);
    }
}

// --- Versão 1 ---
void quickSort_v1(std::vector<int>& vetor) {
    std::random_device rd;
    std::mt19937 gerador(rd());
    quickSortRec(vetor, 0, vetor.size() - 1, 1, gerador);
}

// --- Versão 2 ---
void quickSort_v2(std::vector<int>& vetor) {
    std::random_device rd;
    std::mt19937 gerador(rd());
    quickSortRec(vetor, 0, vetor.size() - 1, 2, gerador);
}

// --- Versão 3 ---
void quickSort_v3(std::vector<int>& vetor) {
    std::random_device rd;
    std::mt19937 gerador(rd());
    quickSortRec(vetor, 0, vetor.size() - 1, 3, gerador);
}
