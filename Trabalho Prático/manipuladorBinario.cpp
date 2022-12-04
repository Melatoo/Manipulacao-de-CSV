#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

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
        void adcionaDado();
        void mudaDado();
        void mostraDado();
        void visualizaDados();
        void trocaPosicao();
        void limpaDados();
        void leDado();
};

int menu () {
    int opcao;
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
    cout << "Digite o ID do dado: ";
    cin >> ID;
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

void csvData::mostraDado() {
    //metodo que vai mostrar os dados do arquivo data_athlete_events.csv
    cout << "ID: " << ID << " Nome: " << name << " Cidade: " << city << " Esporte: " << sport << " Evento: " << event << " NOC: " << noc << endl;
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
    arquivo.open("data_athlete_event.bin", ios::binary);
    if (arquivo.is_open()) {
        int posicaoInicial, posicaoFinal;
        cout << "Digite a posicao inicial: ";
        cin >> posicaoInicial;
        cout << "Digite a posicao final: ";
        cin >> posicaoFinal;
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
        cin >> posicao1;
        cout << "Digite a posicao 2: ";
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

void csvData::leDado() {
    //esse metodo vai ler um dado do arquivo data_athlete_event.bin atraves de um id recebido
    fstream arquivo;
    arquivo.open("data_athlete_event.bin", ios::binary | ios::ate | ios::in | ios::out);
    if (arquivo.is_open()) {
        int id, i = 0;
        cout << "Digite o ID do dado que deseja ler: ";
        cin >> id;
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
    }
    else {
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

int main () {
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