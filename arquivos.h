#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <string>
#include <vector>

void criarEstruturaDePastas(const std::string& nomeAlgoritmo);
void gerarEntradas(const std::string& nomeAlgoritmo, char tipo, int tamanho);
std::vector<int> lerArquivoDeEntrada(const std::string& caminho);
void salvarVetorEmArquivo(const std::vector<int>& vetor, const std::string& caminho);
void salvarTempoEmArquivo(double tempo_ms, int tamanho, const std::string& caminho);
std::string gerarCaminhoArquivo(const std::string& nomeAlgoritmo, const std::string& categoria, char tipo, int tamanho, const std::string& prefixo);

#endif