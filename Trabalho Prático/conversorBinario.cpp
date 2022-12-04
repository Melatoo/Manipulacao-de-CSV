#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class csvData {
    private:
        //separacao dos dados
        int ID;  
        char name[50];
        char city[50];
        char sport[50]; 
        char event[180];
        char noc[4];
    public:
        //metodos da classe
        void recebeDados();
        void mostraDados();
        void limpaDados();
        void converteDados();
};

void csvData::recebeDados() {
    //recebe os dados do arquivo data_athlete_event.csv
    ifstream arquivo;
    arquivo.open("data_athlete_event.csv");
    string linha;
    int contaID = -1;
    while (arquivo.good()) {
        getline(arquivo, linha);
        int tam = linha.size(), contaDado = 0, contaAspas = 0, contaPosicaoDado = 0;
        for (int i = 0; i < tam; i++) {
            //checa se o caractere e uma virgula ou se esta entre aspas
            if (linha[i] != ',' || contaAspas == 1) {
                //checa se o caractere eh um "abre aspas", se for, aumenta o contador de aspas
                if (linha[i] == '"' && contaAspas == 0) {
                    contaAspas = 1;
                } else if (linha[i] == '"' && contaAspas == 1) {
                    //checa se o caractere eh um "fecha aspas", se for, diminui o contador de aspas
                    contaAspas = 0;
                }
                if (contaDado == 0) {
                    ID = contaID;
                } else if (contaDado == 1) {
                    name[contaPosicaoDado] = linha[i];
                } else if (contaDado == 2) {
                    city[contaPosicaoDado] = linha[i];
                } else if (contaDado == 3) {
                    sport[contaPosicaoDado] = linha[i];
                } else if (contaDado == 4) {
                    event[contaPosicaoDado] = linha[i];
                } else if (contaDado == 5) {
                    noc[contaPosicaoDado] = linha[i];
                }
                contaPosicaoDado++;
            } else {
            contaDado++;
            contaPosicaoDado = 0;
            }
        }
        mostraDados();
        converteDados();     
        limpaDados();
        contaID++;
    }
    arquivo.close();
}

void csvData::mostraDados() {
    //metodo que vai mostrar os dados que estao sendo lidos
    cout << "ID: " << ID << " Nome: " << name << " Cidade: " << city << " Esporte: " << sport << " Evento: " << event << " NOC: " << noc << endl;
}

//limpador
void csvData::limpaDados() {
    ID = '\0';
    for (int i = 0; i < 90; i++) {
        name[i] = '\0';
    }
    for (int i = 0; i < 50; i++) {
        city[i] = '\0';
    }
    for (int i = 0; i < 50; i++) {
        sport[i] = '\0';
    }
    for (int i = 0; i < 180; i++) {
        event[i] = '\0';
    }
    for (int i = 0; i < 4; i++) {
        noc[i] = '\0';
    }
}

void csvData::converteDados() {
    //vai pegar os dados do arquivo data_athlete_events.csv e vai converter para binario
    char *vetorChar = new char[sizeof(csvData)];
    memcpy(vetorChar, this, sizeof(csvData));
    ofstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::app | ios::binary);
    if (arquivo.is_open()) {
        arquivo.write(vetorChar, sizeof(csvData));
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

int main() {
    csvData dado;
    dado.recebeDados();
    return 0;
}