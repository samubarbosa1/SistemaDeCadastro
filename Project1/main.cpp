#include "Terminal.h"

int main()
{
    Terminal *myTerminal = new Terminal;
    myTerminal->showMenu();
    return 0;
}

/*typedef struct {
    char codigo[6];
    char nome[100];
    char cpf[20];
} Aluno;

typedef struct {
    char codigo[5];
    char nome[100];
    char professor[100];
    int creditos;
} Disciplina;


typedef struct {
    char periodo[7];
    std::vector<Aluno>* alunos;
    std::vector<Disciplina>* disciplinas;
} Periodo;


// Works
Periodo* criarPeriodo(const char* char_periodo) {
    Periodo* periodo = new Periodo;
    periodo->alunos = new std::vector<Aluno>;
    periodo->disciplinas = new std::vector<Disciplina>;
    strcpy_s(periodo->periodo, char_periodo);
    return periodo;
}

// Works
Aluno* criarAluno(const char* codigo, const char* nome, const char* cpf) {
    Aluno* aluno = new Aluno;
    strcpy_s(aluno->codigo, codigo);
    strcpy_s(aluno->nome, nome);
    strcpy_s(aluno->cpf, cpf);
    return aluno;
}

// Works
Disciplina* criarDisciplina(const char* codigo, const char* nome, const char* professor, int creditos) {
    Disciplina* disciplina = new Disciplina;
    strcpy_s(disciplina->codigo, codigo);
    strcpy_s(disciplina->nome, nome);
    strcpy_s(disciplina->professor, professor);
    disciplina->creditos = creditos;
    return disciplina;
}

// Works
void inserirAluno(Periodo* per, Aluno* alu) {
    per->alunos->push_back(*alu);
}

// Works
void inserirDisciplina(Periodo* per, Disciplina* dis) {
    per->disciplinas->push_back(*dis);
}

void removerAluno(Periodo* per, Aluno* alu) {
    std::vector<Aluno>* lista = per->alunos;
    int size = lista->size();
    for (int i{}; i < size; i++) {
        if (strcmp((*lista)[i].codigo, alu->codigo)) {
            (*lista).erase((*lista).begin() + i);
            return;
        }
    }
}


void removerDisciplina(Periodo* per, Disciplina* dis) {
    std::vector<Disciplina>* lista = per->disciplinas;
    int size = lista->size();
    for (int i{}; i < size; i++) {
        if (strcmp((*lista)[i].codigo, dis->codigo)) {
            (*lista).erase((*lista).begin() + i);
            return;
        }
    }
}

// Works
void printPeriodo(Periodo* per) {
    std::cout << "Periodo\n";
    std::cout << "Data " << per->periodo << "\n";
    std::cout << "Total de alunos " << per->alunos->size() << "\n";
    std::cout << "Total de Disciplinas " << per->disciplinas->size() << "\n\n";
}

// Works
void printDisciplina(Disciplina* dis) {
    std::cout << "Disciplina\n";
    std::cout << "Codigo " << dis->codigo << "\n";
    std::cout << "Materia " << dis->nome << "\n";
    std::cout << "Professor " << dis->professor << "\n";
    std::cout << "Creditos " << dis->creditos << "\n\n";
}

// Works
void printAluno(Aluno* alu) {
    std::cout << "Aluno\n";
    std::cout << "Codigo " << alu->codigo << "\n";
    std::cout << "Nome " << alu->nome << "\n";
    std::cout << "CPF " << alu->cpf << "\n\n";
}

// Works
void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

// Works
void ignoreOtherInputs() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Works
void printAlunos(Periodo* per) {
    clear();
    std::cout << "Alunos de " << per->periodo << '\n';
    std::vector<Aluno> alunos{ *(per->alunos) };
    unsigned long long size{ per->alunos->size() };
    for (int i{}; i < size; i++) {
        printAluno(&(alunos[i]));
    }
}

// Works
void printDisciplinas(Periodo* per) {
    clear();
    std::cout << "Disciplinas de " << per->periodo << "\n\n";
    std::vector<Disciplina> disciplinas{ *(per->disciplinas) };
    unsigned long long size{ per->disciplinas->size() };
    for (int i{}; i < size; i++) {
        printDisciplina(&(disciplinas[i]));
    }
}

// Works
int existePeriodo(std::vector<Periodo>& periodos, std::string& nome_periodo) {
    int size = periodos.size();
    for (int i{}; i < size; i++) {
        if (periodos[i].periodo == nome_periodo) {
            return i;
        }
    }
    return -1;
}

// Works
int existeAluno(Periodo& periodo, std::string codigo_aluno) {
    int size = periodo.alunos->size();
    for (int i{}; i < size; i++) {
        if ((*(periodo.alunos))[i].codigo == codigo_aluno) {
            return i;
        }
    }
    return -1;
}

// Works
int existeDisciplina(Periodo& periodo, const char* codigo_disciplina) {
    int size = periodo.disciplinas->size();
    for (int i{}; i < size; i++) {
        if (!strcmp((*(periodo.disciplinas))[i].codigo, codigo_disciplina)) {
            return i;
        }
    }
    return -1;
}

// Works
int questionarCriarPeriodo(std::vector<Periodo>& periodos) {
    std::string periodo{};
    std::string temp{};
    ignoreOtherInputs();
    while (true) {
        clear();
        std::cout << "Qual sera o novo periodo? (xxxx.x)\n\n";
        std::getline(std::cin >> std::ws, periodo);
        if (periodo.size() != 6) {
            std::cout << "\nFormatacao de periodo invalida! (1)\n";
            std::cout << "Caso nao queira adicionar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp[0] == 'n') return 0;
        }
        else if (periodo[4] == '.') {
            if (existePeriodo(periodos, periodo)) {
                periodos.push_back(*(criarPeriodo(periodo.data())));
                std::cout << "\nPeriodo " << periodo << " criado! (precione enter para continuar)\n";
                std::getline(std::cin, temp);
                return 0;
            }
            std::cout << "\nPeriodo " << periodo << " repetido! (3) (precione enter para continuar)\n";
            std::cout << "Caso nao queira adicionar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp[0] == 'n') return 0;
        }
        else {
            std::cout << "\nFormatacao de periodo invalida! (2)\n";
            std::cout << "Caso nao queira adicionar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp[0] == 'n') return 0;
        }
    }
}

int editarPeriodo(Periodo& periodo) {
    char escolha{};
    std::string temp{};
    while (true) {
        clear();
        printPeriodo(&periodo);
        std::cout << "\n Gostaria de verificar:\n";
        std::cout << "a) Adicionar Aluno\n";
        std::cout << "b) Remover Aluno\n";
        std::cout << "c) Adicionar Disciplina\n";
        std::cout << "d) Remover Disciplina\n";
        std::cout << "e) Sair\n";
        std::cout << "Opcao: ";
        std::cin >> escolha;
        ignoreOtherInputs();
        switch (escolha) {
        case('a'): [[fallthrough]];
        case('A'): {
            std::string codigo{};
            std::cout << "Qual codigo desse aluno?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 5) {
                std::cout << "Formato de codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeAluno(periodo, codigo);
                if (index == -1) {
                    std::string nome{};
                    std::string cpf{};
                    std::cout << "Insira o nome do aluno: ";
                    std::getline(std::cin >> std::ws, nome);
                    std::cout << "Insira o cpf do aluno: ";
                    std::getline(std::cin >> std::ws, cpf);
                    if (nome.size() > 99) {
                        std::cout << "Nome grande demais!\n";
                        std::getline(std::cin, temp);
                    }
                    else if (cpf.size() > 19) {
                        std::cout << "Cpf grande demais!\n";
                        std::getline(std::cin, temp);
                    }
                    else {
                        (*(periodo.alunos)).push_back(*criarAluno(codigo.c_str(), nome.c_str(), cpf.c_str()));
                        std::cout << "Aluno adicionado!\n";
                        std::getline(std::cin, temp);
                    }
                }
                else {
                    std::cout << "Aluno ja existe! \n";
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case('b'): [[fallthrough]];
        case('B'): {
            std::string codigo{};
            std::cout << "Qual o codigo desse aluno?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 5) {
                std::cout << "Formato de codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeAluno(periodo, codigo);
                if (index == -1) {
                    std::cout << "Aluno nao existe!\n";
                    std::getline(std::cin, temp);
                }
                else {
                    printAluno(&((*(periodo.alunos))[index]));
                    std::vector<Aluno> alunos = (*(periodo.alunos));
                    alunos.erase(alunos.begin() + index);
                    std::cout << "Aluno removido com sucesso!\n";
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case('c'): [[fallthrough]];
        case('C'): {
            std::string codigo{};
            std::cout << "Qual codigo dessa disciplina?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 4) {
                std::cout << "Formato de codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeDisciplina(periodo, codigo.c_str());
                if (index == -1) {
                    std::string nome{};
                    std::string professor{};
                    int creditos{};
                    std::cout << "Insira o nome da disciplina: ";
                    std::getline(std::cin >> std::ws, nome);
                    std::cout << "Insira o nome do professor: ";
                    std::getline(std::cin >> std::ws, professor);
                    std::cout << "Creditos da disciplina: ";
                    std::cin >> creditos;
                    if (nome.size() > 99) {
                        std::cout << "Nome grande demais!\n";
                        std::getline(std::cin, temp);
                    }
                    else if (professor.size() > 99) {
                        std::cout << "Nome do professor grande demais!\n";
                        std::getline(std::cin, temp);
                    }
                    else if (creditos < 0) {
                        std::cout << "Credito negativo nao pode!\n";
                        std::getline(std::cin, temp);
                    }
                    else {
                        (*(periodo.disciplinas)).push_back(*criarDisciplina(codigo.c_str(), nome.c_str(), professor.c_str(), creditos));
                        std::cout << "Disciplina adicionada!\n";
                        std::getline(std::cin, temp);
                    }
                }
                else {
                    std::cout << "Disciplina ja existe! \n";
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case('d'): [[fallthrough]];
        case('D'): {
            std::string codigo{};
            std::cout << "Qual o codigo dessa disciplina?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 4) {
                std::cout << "Formato de codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeDisciplina(periodo, codigo.c_str());
                if (index == -1) {
                    std::cout << "Disciplina nao existe!\n";
                    std::getline(std::cin, temp);
                }
                else {
                    removerDisciplina(&periodo, &(*(periodo.disciplinas))[index]);
                    std::cout << "Disciplina removida com sucesso!\n";
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case('e'): [[fallthrough]];
        case('E'): return 0;
        }
    }
}

int askPeriodo(Periodo& periodo) {
    char escolha{};
    std::string temp{};
    while (true) {
        clear();
        printPeriodo(&periodo);
        std::cout << "\n Gostaria de verificar:\n";
        std::cout << "a) Alunos\n";
        std::cout << "b) Aluno especifico\n";
        std::cout << "c) Disciplinas\n";
        std::cout << "d) Disciplina especifica\n";
        std::cout << "e) Editar\n";
        std::cout << "f) Sair\n";
        std::cout << "Opcao: ";
        std::cin >> escolha;
        ignoreOtherInputs();
        switch (escolha) {
        case ('a'): [[fallthrough]];
        case ('A'): {
            printAlunos(&periodo);
            std::getline(std::cin, temp);
            break;
        }
        case ('b'): [[fallthrough]];
        case ('B'): {
            std::string codigo{};
            std::cout << "Qual codigo do aluno?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 5) {
                std::cout << "Codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeAluno(periodo, codigo);
                if (index == -1) {
                    std::cout << "Codigo nao encontrado! (2)\n";
                    std::getline(std::cin, temp);
                }
                else {
                    printAluno(&(*(periodo.alunos))[index]);
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case ('c'): [[fallthrough]];
        case ('C'): {
            printDisciplinas(&periodo);
            std::getline(std::cin, temp);
            break;
        }
        case ('d'): [[fallthrough]];
        case ('D'): {
            std::string codigo{};
            std::cout << "Qual codigo da disciplina?\n";
            std::getline(std::cin >> std::ws, codigo);
            if (codigo.size() != 4) {
                std::cout << "Codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                int index = existeDisciplina(periodo, codigo.c_str());
                if (index == -1) {
                    std::cout << "Codigo nao encontrado! (2)\n";
                    std::getline(std::cin, temp);
                }
                else {
                    printDisciplina(&(*(periodo.disciplinas))[index]);
                    std::getline(std::cin, temp);
                }
            }
            break;
        }
        case ('e'): [[fallthrough]];
        case ('E'): {
            editarPeriodo(periodo);
            break;
        }
        case ('f'): [[fallthrough]];
        case('F'): return 0;
        default: {
            std::cout << "Input invalido!\n";
            std::getline(std::cin >> std::ws, temp);
            if (!(temp.empty())) if (temp[0] == 'n') return 0;
        }
        }
    }
}

int consultarPeriodo(std::vector<Periodo>& periodos) {
    std::string periodo{};
    std::string temp{};
perguntar:
    ignoreOtherInputs();
    while (true) {
        clear();
        std::cout << "Qual periodo deseja buscar? (xxxx.x)\n\n";
        std::getline(std::cin, periodo);

        if (periodo.size() == 6 && periodo[4] == '.') {
            break;
        }
        else {
            std::cout << "\nFormatacao de periodo invalida!\n";
            std::cout << "Caso nao queira procurar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp[0] == 'n') return 0;
        }
    }
    int index_per = existePeriodo(periodos, periodo);

    if (index_per != -1) {
        return askPeriodo(periodos[index_per]);
    }
    else {
        std::cout << "\nPeriodo nao encontrado!\n";
        std::cout << "Caso nao queira procurar um periodo, digite \"n\" (precione enter para continuar)\n";
        std::getline(std::cin, temp);
        if (!(temp.empty())) if (temp[0] == 'n') return 0;
        goto perguntar;
    }
}

void showTerminal(std::vector<Periodo>& periodos) {
    bool perguntar{ true };
    while (perguntar) {
        clear();
        char escolha{};
        std::cout << "Qual operacao deseja realizar? (a/b/c)\n";
        std::cout << "a) Criar Periodo\n";
        std::cout << "b) Consultar Periodo\n";
        std::cout << "c) Remover Periodo\n";
        std::cout << "Opcao: ";
        std::cin >> escolha;
        switch (escolha) {
        case('a'): [[fallthrough]];
        case('A'): {
            questionarCriarPeriodo(periodos);
            break;
        }
        case('b'): [[fallthrough]];
        case('B'): {
            consultarPeriodo(periodos);
            break;
        }
        default: {
            std::cout << "Opcao Invalida! (precione enter para continuar)";
            std::cin.get(escolha);
        }
        }

    }
}


int main() {
    std::vector<Periodo> periodos{};
    showTerminal(periodos);
}*/

