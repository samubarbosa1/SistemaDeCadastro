#include "Terminal.h"

Terminal::~Terminal()
{
    delete(listaPeriodo);
}

void Terminal::ignoreOtherInputs()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Terminal::clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

void Terminal::showMenu()
{
    bool perguntar{ true };
    while (perguntar) {
        clear();
        char escolha{};
        std::cout << "Qual operacao deseja realizar? (a/b/c/d)\n";
        std::cout << "a) Criar Periodo\n";
        std::cout << "b) Consultar Periodo\n";
        std::cout << "c) Remover Periodo\n";
        std::cout << "d) Sair\n";
        std::cout << "Opcao: ";
        std::cin >> escolha;
        switch (escolha) {
        case('a'): [[fallthrough]];
        case('A'): {
            showMenuAdd();
            break;
        }
        case('b'): [[fallthrough]];
        case('B'): {
            showMenuFind();
            break;
        }
        case('c'): [[fallthrough]];
        case('C'): {
            showMenuDel();
            break;
        }
        case('d'): [[fallthrough]];
        case('D'): {
            return;
        }
        default: {
            std::cout << "Opcao Invalida! (precione enter para continuar)";
            std::cin.get(escolha);
        }
        }
    }
}

void Terminal::showMenuAdd()
{
    clear();

    std::string periodo{}, temp{};
    ignoreOtherInputs();

    Periodo *newElement = new Periodo;
    
    if (this->listaPeriodo->find(newElement->getId()) != nullptr) {
        std::cout << "Periodo ja existente! (precione enter para continuar)\n";
        delete(newElement);
        std::getline(std::cin, temp);
    }
    else
    {
        this->listaPeriodo->add(newElement);
        std::cout << "\nPeriodo " << newElement->getId() << " criado! (precione enter para continuar)\n";
        std::getline(std::cin, temp);
    }
   
    return;
}

void Terminal::showMenuFind()
{
    ignoreOtherInputs();
    std::string periodo{};
    std::string temp{};

Perguntar:
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
            if (!(temp.empty())) if (temp == "n") return;
        }
    }
    Periodo* procurado{ this->listaPeriodo->find(periodo) };
    if (!procurado)
    {
        std::cout << "Periodo nao encontrado.\n "
            << "Caso nao queira procurar um periodo, digite \"n\" (precione enter para continuar)\n";
        std::getline(std::cin, temp);
        if (!(temp.empty())) if (temp == "n") return;
        goto Perguntar;
    }

    this->showMenuPeriodo(procurado);
}

void Terminal::showMenuPeriodo(Periodo* periodo)
{
    char escolha{};
    while (true) {
        clear();
        std::cout << "Periodo " << periodo->getId();
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
            addAluno(periodo);
            break;
        }
        case('b'): [[fallthrough]];
        case('B'): {
            delAluno(periodo);
            break;
        }
        case('c'): [[fallthrough]];
        case('C'): {
            addDisciplina(periodo);
            break;
        }
        case('d'): [[fallthrough]];
        case('D'): {
            delDisciplina(periodo);
            break;
        }
        case('e'): [[fallthrough]];
        case('E'): return;
        }
    }
}

void Terminal::addAluno(Periodo* periodo)
{
    std::string temp{};
    while (true)
    {
        Aluno* novo = new Aluno;
        if (periodo->alunos.find(novo->getId()))
        {
            delete(novo);
            std::cout << "Aluno já existente!\n"
                << "Caso nao queira adicionar um aluno, digite \"n\" \n(precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp == "n") return;
        }
        else
        {
            periodo->alunos.add(novo);
            std::cout << "Novo Aluno Adicionado!\n(precione enter para continuar)\n";
            std::getline(std::cin >> std::ws, temp);
            return;
        }
    }
}

void Terminal::delAluno(Periodo* periodo)
{
/*
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
*/    
}

void Terminal::addDisciplina(Periodo* periodo)
{
    /*
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
    */
    
}

void Terminal::delDisciplina(Periodo* periodo)
{
    /*
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
    */
    
}

void Terminal::showMenuDel()
{
    ignoreOtherInputs();
    std::string periodo;
    while (true)
    {
        Periodo *iterator = listaPeriodo->val;
        clear();
        std::cout << "Qual periodo voce deseja deletar?\n";
        while (iterator)
        {
            std::cout << "- " << iterator->getId() << "\n";
            iterator = iterator->prox;
        }
        std::getline(std::cin >> std::ws, periodo);
        if (this->listaPeriodo->find(periodo) != nullptr)
        {
            this->clear();
            this->listaPeriodo->del(periodo);
            std::cout << "Periodo Deletado!\n";
            system("PAUSE");
            return;
        }
        else
        {
            this->clear();
            std::cout << "Periodo nao encontrado.\n"
                << "Caso nao queira procurar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, periodo);
     
            if (!(periodo.empty())) if (periodo == "n") return;
        }
    }
}

