#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "csvData.h"

using namespace std;

void leArquivo() {
    //essa funcao vai ler todo o arquivo data_athlete_event.bin e mostrar os dados
    ifstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::binary);
    if (arquivo.is_open()) {
        csvData dado;
        while (arquivo.read((char*)&dado, sizeof(csvData))) {
            dado.mostraDado();
        }
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

int menu() {
    int opcao;
    //mostrar erro se opcao nao for int
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1, '  ');
    }
    cout << "1 - Adcionar registro" << endl;
    cout << "2 - Visualizar registros" << endl;
    cout << "3 - Alterar dados de um registro" << endl;
    cout << "4 - Trocar posicao" << endl;
    cout << "5 - Imprimir registro" << endl;
    cout << "6 - Ler um registro" << endl;
    cout << "7 - Sair" << endl;
    cout << "Digite a opcao desejada: ";
    cin >> opcao;
    return opcao;
}

int main() {
    csvData dados;
    int opcao = menu();
    while (opcao != 7) {
        switch (opcao) {
            case 1:
                dados.adcionaDado();
                break;
            case 2:
                dados.visualizaDados();
                break;
            case 3:
                dados.mudaDado();
                break;
            case 4:
                dados.trocaPosicao();
                break;
            case 5:
                leArquivo();
                break;
            case 6:
                dados.leDado();
                break;
            case 7:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida" << endl;
                break;
        }
        opcao = menu();
    }
    return 0;
}