#include "Grafo.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

Grafo::Grafo(int num_vertices, int num_arestas) {
    if (num_vertices <= 0) {
        throw(invalid_argument("Erro no construtor Grafo(int): o numero de "
            "vertices " + to_string(num_vertices) + " eh invalido!"));
    }

    this->valida_qtd_arestas(num_vertices, num_arestas);

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    matriz_adj_.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        matriz_adj_[i].resize(num_vertices, 0);
    }
    for (int i = 0; i < num_vertices_; i++) {
        cout << "No " << i << " criado com sucesso." << endl;
    }
    cout << "------------------------------------------------------" << endl;
}

int Grafo::num_vertices() {
    return num_vertices_;
}

int Grafo::num_arestas() {
    return num_arestas_;
}

bool Grafo::tem_aresta(Aresta e) {
    if (matriz_adj_[e.v1][e.v2] != 0) {
        return true;
    }
    return false;
}

void Grafo::insere_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "insere_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if (!tem_aresta(e) && (e.v1 != e.v2)) {
        matriz_adj_[e.v1][e.v2] = 1;
        matriz_adj_[e.v2][e.v1] = 1;

        num_arestas_++;
    }
}

void Grafo::remove_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "remove_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if (tem_aresta(e)) {
        matriz_adj_[e.v1][e.v2] = 0;
        matriz_adj_[e.v2][e.v1] = 0;

        num_arestas_--;
    }
}

void Grafo::imprime() {
    for (int v = 0; v < num_vertices_; v++) {
        cout << v << ":";
        for (int u = 0; u < num_vertices_; u++) {
            if (matriz_adj_[v][u] != 0) {
                cout << " " << u;
            }
        }
        cout << "\n";
    }
}

void Grafo::valida_vertice(int v) {
    if ((v < 0) || (v >= num_vertices_)) {
        throw out_of_range("Indice de vertice invalido: " + to_string(v));
    }
}

void Grafo::valida_aresta(Aresta e) {
    valida_vertice(e.v1);
    valida_vertice(e.v2);
}

void Grafo::valida_qtd_arestas(int num_vertices,int num_arestas) {
    int max_arestas = (num_vertices * (num_vertices - 1)) / 2;
    if (num_arestas > max_arestas) {
        throw invalid_argument("Erro na operacao valida_qtd_arestas(int): "
            "a quantidade de arestas " + to_string(num_arestas) + " eh "
            "invalida! O numero maximo de arestas para um grafo com "
            + to_string(num_vertices) + " vertices eh " + to_string(max_arestas));
    }
}

void Grafo::busca_larg(int v, int distancia[]) {
    // Criacao e inicializacao do vetor marcado
    // Inicializacao dos vetores pai e dist

    queue<int> fila;

    vector<int> marcado(num_vertices_, 0);
    marcado[v] = 1;
    distancia[v] = 0;

    fila.push(v);

    while (!fila.empty()) {
        int w = fila.front();
        fila.pop();

        printf("%d\n", w);

        for (int u = 0; u < num_vertices_; u++) {
            if (matriz_adj_[w][u] != 0) {
                if (marcado[u] == 0) {
                    marcado[u] = 1;
                    distancia[u] = distancia[w] + 1;
                    fila.push(u);
                }
            }
        }
    }
}
