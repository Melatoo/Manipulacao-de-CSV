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
        void mostraDado();
        void limpaDados();
        void converteDados();
        void adcionaDado();
        void mudaDado();
        void visualizaDados();
        void trocaPosicao();
        void leDado();
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
        mostraDado();
        converteDados();     
        limpaDados();
        contaID++;
    }
    arquivo.close();
}

void csvData::mostraDado() {
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

void csvData::adcionaDado() {
    //esse metodo vai adcionar um novo dado no arquivo data_athlete_event.bin, o posicionando no lugar desejado
    //descobrir o tamanho do arquivo data_athlete_event.bin
    ifstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::binary | ios::app);
    arquivo.seekg(0, arquivo.end);
    long int tamanhoArquivo = arquivo.tellg();
    int tamanhoDado = sizeof(csvData);
    int numeroDados = tamanhoArquivo / tamanhoDado, posicao;   
    arquivo.close();
    //recebe a posicao e os dados
    cout << "Digite a posicao que deseja adcionar o dado: ";
    cin >> posicao;
    if (cin.fail() || posicao > (numeroDados-1) || posicao < 0) {
        cout << "Posicao invalida, ultima posicao possivel: " << (numeroDados-1) << endl;
        return;
    }
    cout << "Digite o ID do dado: ";
    cin >> ID;
    if (cin.fail() || ID < 0 || ID < (numeroDados-1)) {
        cout << "ID invalido ou ja existente" << endl;
        return;
    }
    cout << "Digite o nome do dado: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Digite a cidade do dado: ";
    cin.getline(city, 50);
    cout << "Digite o esporte do dado: ";
    cin.getline(sport, 50);
    cout << "Digite o evento do dado: ";
    cin.getline(event, 180);
    cout << "Digite o NOC do dado: ";
    cin.getline(noc, 4);
    csvData dadoAux;
    fstream arquivo2;
    arquivo2.open("data_athlete_event.bin", ios::binary | ios::in | ios::out | ios::ate);
    for (int i = numeroDados; i > posicao; i--) {
        //le o dado da posicao i e o coloca na posicao i+1
        arquivo2.seekg((i-1) * tamanhoDado);
        arquivo2.read((char*)&dadoAux, tamanhoDado);
        arquivo2.seekp((i) * tamanhoDado);
        arquivo2.write((char*)&dadoAux, tamanhoDado);
        dadoAux.limpaDados();
    }
    //adciona o dado na posicao desejada
    arquivo2.seekp((posicao+1) * tamanhoDado);
    arquivo2.write((char*)this, tamanhoDado);
    arquivo2.close();
}

void csvData::mudaDado() {
    //esse metodo vai mudar os dados de um dado do arquivo data_athlete_event.bin atraves de um id recebido
    fstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::binary | ios::in | ios::out | ios::ate);
    if (arquivo.is_open()) {
        int id;    
        int i = 1;
        cout << "Digite o ID do dado que deseja mudar: ";
        cin >> id;
        if (cin.fail() || id < 0) {
            cout << "ID invalido" << endl;
            return;
        }
        arquivo.seekg((id+1) * sizeof(csvData), ios::beg);
        csvData dado;
        arquivo.read((char*)&dado, sizeof(csvData));
        //se por acaso o id nao for a posicao+1 do dado, ele vai procurar pelo ID
        while(dado.ID != id && !arquivo.eof()) {
            limpaDados();
            arquivo.seekp(i * sizeof(csvData), ios::beg);
            arquivo.read((char*)&dado, sizeof(csvData));
            i++;
        }
        //se o id nao for encontrado, ele vai mostrar uma mensagem de erro      
        if (dado.ID != id) {
            cout << "ID nao encontrado" << endl;
            return;
        }
        dado.mostraDado();
        arquivo.close();
        fstream arquivo;
        arquivo.open("data_athlete_event.bin", ios::binary | ios::in | ios::out | ios::ate);
        if (arquivo.is_open()) {
            cout << "Digite o novo nome: ";
            cin >> dado.name;
            cout << "Digite a nova cidade: ";
            cin >> dado.city;
            cout << "Digite o novo esporte: ";
            cin >> dado.sport;
            cout << "Digite o novo evento: ";
            cin >> dado.event;
            cout << "Digite o novo NOC: ";
            cin >> dado.noc;
            arquivo.seekp((id+1) * sizeof(csvData), ios::beg);
            arquivo.write((char*)&dado, sizeof(csvData));
            arquivo.close();
        }
        else {
            cout << "Erro ao abrir o arquivo" << endl;
        }
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

void csvData::visualizaDados() {
    //esse metodo vai mostrar os dados do arquivo data_athlete_event.bin da posicao x ate a posicao y

    ifstream arquivo;    
    long int tamanhoArquivo = arquivo.tellg();
    int tamanhoDado = sizeof(csvData);
    int numeroDados = tamanhoArquivo / tamanhoDado;
    arquivo.open("data_athlete_event.bin", ios::binary);
    if (arquivo.is_open()) {
        int posicaoInicial, posicaoFinal;
        cout << "Digite a posicao inicial: ";
        cin >> posicaoInicial;
        if (cin.fail() || posicaoInicial < 0) {
            cout << "Posicao invalida" << endl;
            return;
        }
        cout << "Digite a posicao final: ";
        cin >> posicaoFinal;
        if (cin.fail() || posicaoFinal < 0 || posicaoFinal < posicaoInicial || posicaoFinal > (numeroDados-1)) {
            cout << "Posicao invalida" << endl;
            return;
        }      
        //posicionar o ponteiro no inicio do arquivo
        arquivo.seekg((posicaoInicial+1) * sizeof(csvData), ios::beg);
        csvData dado;
        for (int i = posicaoInicial; i <= posicaoFinal; i++) {
            //ler o dado da posicao i e mostrar
            arquivo.read((char*)&dado, sizeof(csvData));
            dado.mostraDado();
        }
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

void csvData::trocaPosicao() {
    //esse metodo vai trocar a posicao de dois dados do arquivo data_athlete_event.bin
    fstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::binary | ios::in | ios::out | ios::ate);
    if (arquivo.is_open()) {
        int posicao1, posicao2;
        cout << "Digite a posicao 1: ";
        if (cin.fail() || posicao1 < 0) {
            cout << "Posicao invalida" << endl;
            return;
        }
        cin >> posicao1;
        cout << "Digite a posicao 2: ";
        if (cin.fail() || posicao2 < 0) {
            cout << "Posicao invalida" << endl;
            return;
        }
        cin >> posicao2;
        csvData dado1, dado2;
        //le os dados das posicoes 1 e 2
        arquivo.seekg((posicao1+1) * sizeof(csvData), ios::beg);
        arquivo.read((char*)&dado1, sizeof(csvData));
        arquivo.seekg((posicao2+1) * sizeof(csvData), ios::beg);
        arquivo.read((char*)&dado2, sizeof(csvData));
        //escreve os dados das posicoes 1 e 2
        arquivo.seekp((posicao1+1) * sizeof(csvData), ios::beg);
        arquivo.write((char*)&dado2, sizeof(csvData));
        arquivo.seekp((posicao2+1) * sizeof(csvData), ios::beg);
        arquivo.write((char*)&dado1, sizeof(csvData));
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

void csvData::leDado() {
    //esse metodo vai ler um dado do arquivo data_athlete_event.bin atraves de um id recebido
    fstream arquivo;
    long int tamanhoArquivo = arquivo.tellg();
    int tamanhoDado = sizeof(csvData);
    int numeroDados = tamanhoArquivo / tamanhoDado;
    arquivo.open("data_athlete_event.bin", ios::binary | ios::ate | ios::in | ios::out);
    if (arquivo.is_open()) {
        int id, i = 0;
        cout << "Digite o ID do dado que deseja ler: ";
        cin >> id;
        if (cin.fail() || id < 0 || id > (numeroDados-1)) {
            cout << "ID invalido" << endl;
            return;
        }
        arquivo.seekg((id+1) * sizeof(csvData), ios::beg);
        csvData dado;
        arquivo.read((char*)&dado, sizeof(csvData));        
        //se por acaso o id nao for a posicao+1 do dado, ele vai procurar pelo ID
        while(dado.ID != id && !arquivo.eof()) {
            limpaDados();
            arquivo.seekp(i * sizeof(csvData), ios::beg);
            arquivo.read((char*)&dado, sizeof(csvData));
            i++;
        }
        dado.mostraDado();
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}