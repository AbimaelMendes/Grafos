#include "Aresta.h"
#include "Grafo.h"
#include <exception>
#include <string>
#include <iostream>

using namespace std;

void print_exception(const exception &e, int level = 0) {
    cerr << "exception: " << string(level, ' ') << e.what() << "\n";
    try {
        rethrow_if_nested(e);
    } catch(const std::exception& nested_exception) {
        print_exception(nested_exception, (level + 2));
    }
}

int main() {
    try {
        //Criação do grafo
        cout << "Informe o numero de nos (N) e de conexoes (C) da rede, separados por espaco: ";
        int num_nos, num_conexoes;
        cin >> num_nos >> num_conexoes;
        Grafo rede(num_nos, num_conexoes);

        //Criando as conexões do grafo
        for (int i = 0; i < num_conexoes; i++)
        {
            try {
                cout << "Crie uma conexão entre dois nos, separados por espaco: ";
                int v1, v2;
                cin >> v1 >> v2;
                rede.insere_aresta(Aresta(v1, v2));
            }
            catch (const exception &e) {
                print_exception(e);
                i--;
            }
        }

        //Determinando o número de rodadas que o usuário deseja realizar a verificação de nos na rede
        cout << "Informe a quantidade de rodadas que deseja realizar: ";
        int rodadas;
        cin >> rodadas;
        
        for (int i = 0; i < rodadas; i++)
        {
            cout << "Informe o no de origem e quantidade de saltos, separados por espaco: ";
            int origem, saltos;
            cin >> origem >> saltos;
            rede.nao_recebem_mensagem(origem, saltos);
        }
    }
    catch (const exception &e) {
        print_exception(e);
    }

    return 0;
}
