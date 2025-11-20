#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

struct paciente {
    string id;
    int hora;
    int min;
    int senha;
};

int converter(int h, int m) {
    return h*60 + m;
}

void inserir(queue<paciente> &V, queue<paciente> &A, queue<paciente> &D, queue<paciente> &B, int &pico, int &proximaSenha){
    char tipo_atendimento; int hh, mm;
    
    cout << "Selecione o tipo de atendimento: " << endl;
    cout << "'V' para Emergencia" << endl;
    cout << "'A' para Urgencia" << endl;
    cout << "'D' para Pouco Urgente" << endl;
    cout << "'B' para Nao Urgente" << endl;
    cin >> tipo_atendimento;

    tipo_atendimento = toupper(tipo_atendimento);//converte as letras para maiusculo

    cout << "Horario de chegada (HH MM): ";
    cin >> hh >> mm;

    paciente p;
    p.hora = hh;
    p.min = mm;
    p.senha = proximaSenha++;

    if (tipo_atendimento == 'V') { p.id ="V"; V.push(p);
        cout << "Paciente senha: p" << p.senha << " adicionado a fila de Emergencia.\n";
    }
    else if (tipo_atendimento == 'A') { p.id ="A"; A.push(p);
        cout << "Paciente senha: p" << p.senha << " adicionado a fila de Urgencia.\n";
    }
   else if (tipo_atendimento == 'D') { p.id ="D"; D.push(p);
        cout << "Paciente senha: p" << p.senha << " adicionado a fila de Pouco Urgente.\n";
    }
    else if (tipo_atendimento == 'B') { p.id ="B"; B.push(p);
        cout << "Paciente senha: p" << p.senha << " adicionado a fila de Nao Urgente.\n";
    }
    else {
        cout << "Tipo invalido. Use apenas 'V', 'A', 'D' ou 'B'.\n";
    }

    int lotacao = V.size() + A.size() + D.size() + B.size();
    if (lotacao > pico)
    pico = lotacao;
}

void atendimento(queue<paciente> &V, queue<paciente> &A, queue<paciente> &D, queue<paciente> &B,
                 int hh, int mm,
                 int &totalAtendimentos,
                 int &Emergencia, int &Urgencia, int &PoucoUrgente, int &NaoUrgente ,
                 int &maxEspera) {

    int atual = converter(hh,mm);

    if(!V.empty()){//! se for diferente de vazio le o cout se nao vai pro proximo
        paciente p = V.front(); V.pop();//pop remove o primeiro da fila
        Emergencia++; totalAtendimentos++;

        cout << "Atendendo SENHA: p" << p.senha << " (Emergencia)\n";

        int espera = atual - converter(p.hora, p.min);
        if (espera > maxEspera) maxEspera = espera;

    }
    else if(!A.empty()){//empty verifica se a fila esta vazia
        paciente p = A.front(); A.pop();
        Urgencia++; totalAtendimentos++;
        
         cout << "Atendendo SENHA: p" << p.senha << " (Urgencia)\n";

        int espera = atual - converter(p.hora, p.min);
        if (espera > maxEspera) maxEspera = espera;
    }
    else if(!D.empty()){
        paciente p = D.front(); D.pop();//front ver o primeiro da fila
        PoucoUrgente++; totalAtendimentos++;

         cout << "Atendendo SENHA: p" << p.senha << " (Pouco Urgente)\n";

        int espera = atual - converter(p.hora, p.min);
        if (espera > maxEspera) maxEspera = espera;
    }
    else if(!B.empty()){
        paciente p = B.front(); B.pop();
        NaoUrgente++; totalAtendimentos++;

         cout << "Atendendo SENHA: p" << p.senha << " (Nao Urgente)\n";

        int espera = atual - converter(p.hora, p.min);
        if (espera > maxEspera) maxEspera = espera;
    }
    else{
        cout << "Sem pacientes aguardando atendimento." << endl;
    }

    cout << "V:" << V.size() << " A:" << A.size()
         << " D:" << D.size() << " B:" << B.size()
         << " | Atendidos: " << totalAtendimentos << "\n";

}

void relatorio(int totalAtendimentos, int Emergencia, int Urgencia, int PoucoUrgente, int NaoUrgente, int pico, int maxEspera){

    cout << "\n--- RELATÓRIO FINAL ---\n";
    cout << "Total atendidos: " << totalAtendimentos << endl;
    cout << "Por prioridade: V=" << Emergencia << " A=" << Urgencia << " D=" << PoucoUrgente << " B=" << NaoUrgente << endl;
    cout << "Pico de lotacao: " << pico << endl;
    cout << "Espera maxima: " << maxEspera << " min\n";
}

int main(){

    queue<paciente> V, A, D, B;
    int pico = 0;
    int maxEspera = 0;
    int totalAtendimentos = 0;
    int Emergencia = 0, Urgencia = 0, PoucoUrgente = 0, NaoUrgente = 0;
    int proximaSenha = 1;

    char opcao;

    while(true){
        cout << "\n===== MENU DE ATENDIMENTO =====\n"
            << "C. Chegada de paciente\n"
            << "A. Atendimento\n"
            << "D. Relatorio final\n"
            << "Q. Encerrar atendimento.\n"
            << "Selecione umas das opcoes: ";
        cin >> opcao;
        opcao = toupper(opcao);

        if (opcao == 'C') {
            inserir(V, A, D, B, pico, proximaSenha);
        }
        else if (opcao == 'A') {
            int hh, mm;
            cout << "Horario (HH MM): ";
            cin >> hh >> mm;
            atendimento(V, A, D, B, hh, mm, totalAtendimentos, Emergencia, Urgencia, PoucoUrgente, NaoUrgente, maxEspera);
        }
        else if (opcao == 'D') {
            relatorio(totalAtendimentos, Emergencia, Urgencia, PoucoUrgente, NaoUrgente, pico, maxEspera);
        }
        else if (opcao == 'Q') {
            relatorio(totalAtendimentos, Emergencia, Urgencia, PoucoUrgente, NaoUrgente, pico, maxEspera);
            break;
        }
        else {
            cout << "Opcao invalida.\n";
        }
            
    }
}
