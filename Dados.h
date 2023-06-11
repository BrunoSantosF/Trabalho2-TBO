#ifndef DADOS_H
#define DADOS_H

/// @brief imprime o tempo de deslocamento no arquivo
/// @param arquivo arquivo de saída
/// @param tempoEmSegundos tempo, em segundos
void imprimeTempo(FILE * arquivo, double tempoEmSegundos);

/// @brief imprime o vertice no arquivo
/// @param arquivo arquivo de saída
/// @param vertice vertice a ser impresso
/// @param limite controle para quebra de linha
void imprimeVertice(FILE * arquivo, int vertice, int limite);

/// @brief obtem a quantidade de linhas de um arquivo
/// @param arquivo arquivo a ser inspecionado
/// @return quantidade de linhas
int nmrLinhasArquivo(FILE * arquivo);

/// @brief lê os parâmetros de interesse das linhas iniciais
/// @param entrada arquivo de entrada
/// @param N numero de vertices
/// @param M numero de arestas
/// @param S nó de origem
/// @param T nó de destino
void leituraParametros(FILE * entrada, int * N, int * M, int * S, int * T);

/// @brief obtém a informação das arestas
/// @param entrada arquivo de entrada
/// @param arestas matriz para armazenar as arestas
/// @param qtd quantidade de arestas
void leituraArestas(FILE * entrada, double *** arestas, int qtd);

/// @brief obtém as informações de mudanças nos tráfegos
/// @param entrada arquivo de entrada
/// @param trafego matriz com as mudanças nas arestas
/// @param qtd quantidade de arestas
/// @param numLinhas usado para o tamanho da matriz de trafego
/// @param numArestas usado para o tamanho da matriz de trafego
void leituraTrafegos(FILE * entrada, int *** trafego, int * qtd, int numLinhas, int numArestas);

/// @brief realiza o processamento dos dados
/// @param saida arquivo de saida
/// @param arestas vetor com as arestas
/// @param N numero de vertices
/// @param M numero de arestas
/// @param S nó de origem
/// @param T nó de destino
/// @param trafego vetor de tráfego
/// @param tamanhoTrafego tamanho do vetor de tráfego
void processaDados(FILE * saida, double ** arestas, int M, int N, int S, int T, int ** trafego, int tamanhoTrafego);

/// @brief libera a memória alocada dinamicamente
/// @param arestas vetor de arestas
/// @param M numero de arestas
/// @param trafego vetor de trafego
/// @param tamanhoTrafego tamanho do vetor de trafego
void liberaDados(double ** arestas, int M, int ** trafego, int tamanhoTrafego);


#endif