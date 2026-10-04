#ifndef GRAFO_H

#define GRAFO_H

#include "Aresta.h"
#include <vector>

class Grafo {
public:
    /** Constroi um grafo simples que possui o numero de vertices recebido por
     *  parametro e que nao possui arestas */
    Grafo(int num_vertices, int num_arestas);

    int num_vertices();
    int num_arestas();

    bool tem_aresta(Aresta e);

    /** Insere uma aresta no grafo caso a aresta ainda nao exista no grafo e
     * nao seja um laco */
    void insere_aresta(Aresta e);

    /** Remove uma aresta do grafo caso a aresta exista no grafo */
    void remove_aresta(Aresta e);

    void imprime();
    std::vector<int> nao_recebem_mensagem(int origem, int saltos);

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::vector<int>> matriz_adj_;

    void valida_vertice(int v);
    void valida_aresta(Aresta e);
    void valida_qtd_arestas(int num_vertices,int num_arestas);
    void busca_larg(int v, std::vector<int> &distancia);
};

#endif /* GRAFO_H */
