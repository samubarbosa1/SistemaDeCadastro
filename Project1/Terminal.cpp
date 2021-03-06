#include "Terminal.h"
#include <string>


Terminal::Terminal()
{
}

Terminal::Terminal(std::string arquivo)
{
    std::ifstream file;
    default_arq = arquivo;
    file.open(arquivo);
    if (!file) {
        std::cout << "Nao foi possivel abrir o arquivo default!\nA tabela sera iniciada vazia. (precione enter para continuar)\n";
        std::getline(std::cin, arquivo);
    }
    else {
        uploadState(file, false);
        std::cout << "Arquivo default iniciado com sucesso! \n";
        std::getline(std::cin, arquivo);
    }
    file.close();
}

Terminal::~Terminal()
{
    std::string temp{};
    std::ofstream file;
    if (default_arq.size()) {
        file.open(default_arq);
        if (!file) {
            std::cout << "Nao foi possivel abrir o arquivo! \n";
            std::cout << "Gostaria de salvar em outro arquivo? (s/n)\n";
            std::getline(std::cin >> std::ws, temp);
            if (temp[0] == 's' || temp[0] == 'S') {
                file = getFile();
                saveState(file);
                std::cout << "Arquivo salvo com sucesso! \n";
                std::getline(std::cin, temp);
            }
        }
        else {
            saveState(file);
            std::cout << "Arquivo salvo com sucesso! \n";
            std::getline(std::cin, temp);
        }
    }
    else {
        file = getFile();
        saveState(file);
        std::cout << "Arquivo salvo com sucesso! \n";
        std::getline(std::cin, temp);
    }
    file.close();
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
        std::cout << "Qual operacao deseja realizar? (a/b/c/d/l/s)\n";
        std::cout << "a) Criar Periodo\n";
        std::cout << "b) Consultar Periodo\n";
        std::cout << "c) Remover Periodo\n";
        std::cout << "d) Sair\n";
        std::cout << "l) Ler\n";
        std::cout << "s) Salvar\n";
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
            case('l'): [[fallthrough]];
            case('L'): {
                readState();
                break;
            }
            case('s'): [[fallthrough]];
            case('S'): {
                std::ofstream file{ getFile() };
                saveState(file);
                break;
            }
            default: {
                std::cout << "Opcao Invalida! (precione enter para continuar)";
                std::cin.get(escolha);
                ignoreOtherInputs();
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
        Periodo* iterator = listaPeriodo->val;
        std::cout << "Qual periodo voce deseja buscar?(xxxx.x)\n\n";
        while (iterator)
        {
            iterator->printPeriodo();
            iterator = iterator->prox;
        }
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
    std::string temp{};
    while (true) {
        clear();
        showDadosPeriodo(periodo);
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
            clear();
            if (periodo->alunos.size() == 0)
                std::cout << "Nenhum aluno encontrado. (Pressione <enter> para continuar)\n";
            periodo->alunos.print();
            std::getline(std::cin, temp);
            break;
        }
        case ('b'): [[fallthrough]];
        case ('B'): {
            std::string codigo{};
            std::cout << "Qual codigo do aluno?\n";
            std::getline(std::cin >> std::ws, codigo);
            Aluno* aluno = periodo->alunos.find(codigo);
            if (!aluno) {
                std::cout << "Codigo invalido! (1)\n";
                std::getline(std::cin, temp);
            }
            else {
                clear();
                aluno->print();
                std::getline(std::cin, temp);
            }
            break;
        }
        case ('c'): [[fallthrough]];
        case ('C'): {
            clear();
            if (periodo->disciplinas.size() == 0)
                std::cout << "Nenhuma disciplina encontrada. (Pressione <enter> para continuar)\n";
            periodo->disciplinas.print();
            std::getline(std::cin, temp);
            break;
        }
        case ('d'): [[fallthrough]];
        case ('D'): {
            std::string codigo{};
            std::cout << "Qual codigo da disciplina?\n";
            std::getline(std::cin >> std::ws, codigo);
            Disciplina* disciplina = periodo->disciplinas.find(codigo);
            if (!disciplina) {
                std::cout << "Codigo invalido!\n";
                std::getline(std::cin, temp);
            }
            else {
                clear();
                disciplina->print();
                std::getline(std::cin, temp);
            }
            break;
        }
        case ('e'): [[fallthrough]];
        case ('E'): {
            showMenuEditarPeriodo(periodo);
            break;
        }
        case ('f'): [[fallthrough]];
        case('F'): return;
        default: {
            std::cout << "Input invalido!\n";
            std::getline(std::cin >> std::ws, temp);
        }
        }
    }
}

void Terminal::showMenuEditarPeriodo(Periodo* periodo)
{
    char escolha{};
    while (true) {
        clear();
        textMenuEditar(periodo);
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

void Terminal::textMenuEditar(Periodo* periodo)
{
    std::cout << "Periodo " << periodo->getId();
    std::cout << "\n Gostaria de verificar:\n";
    std::cout << "a) Adicionar Aluno\n";
    std::cout << "b) Remover Aluno\n";
    std::cout << "c) Adicionar Disciplina\n";
    std::cout << "d) Remover Disciplina\n";
    std::cout << "e) Sair\n";
}

void Terminal::showDadosPeriodo(Periodo* periodo)
{
    std::cout << "Periodo " << periodo->getId() << "\n";
    std::cout << "Total de alunos " << periodo->alunos.size() << "\n";
    std::cout << "Total de Disciplinas " << periodo->disciplinas.size() << "\n\n";
}

void Terminal::addAluno(Periodo* periodo)
{
    std::string temp{};
    while (true)
    {
        clear();
        Aluno* novo = new Aluno;
        if (periodo->alunos.find(novo->getId()))
        {
            delete(novo);
            std::cout << "Aluno ja existente!\n"
                << "Caso nao queira adicionar um aluno, digite \"n\" \n(precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp == "n") return;
        }
        else
        {
            periodo->alunos.add(novo);
            std::cout << "Novo Aluno Adicionado!\n(precione enter para continuar)\n";
            std::getline(std::cin, temp);
            return;
        }
    }
}

void Terminal::delAluno(Periodo* periodo)
{
    std::string aluno;
    while (true)
    {
        Aluno* iterator = listaPeriodo->val->alunos.val;
        clear();
        std::cout << "Qual aluno voce deseja deletar?\n";
        while (iterator)
        {
            std::cout << "- " << iterator->getNome() << " (" << iterator->getId() << ")\n";
            iterator = iterator->prox;
        }
        std::getline(std::cin >> std::ws, aluno);
        if (this->listaPeriodo->val->alunos.find(aluno) != nullptr)
        {
            this->clear();
            this->listaPeriodo->val->alunos.del(aluno);
            std::cout << "Aluno Deletado!\n";
            std::getline(std::cin, aluno);
            return;
        }
        else
        {
            this->clear();
            std::cout << "Aluno nao encontrado.\n"
                << "Caso nao queira deletar um aluno, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, aluno);

            if (!(aluno.empty())) if (aluno== "n") return;
        }
    }
}

void Terminal::addDisciplina(Periodo* periodo)
{
    std::string temp{};
    while (true)
    {
        clear();
        Disciplina* novo = new Disciplina;
        if (periodo->disciplinas.find(novo->getId()))
        {
            delete(novo);
            std::cout << "Disciplina ja existente!\n"
                << "Caso nao queira adicionar uma disciplina, digite \"n\" \n(precione enter para continuar)\n";
            std::getline(std::cin, temp);
            if (!(temp.empty())) if (temp == "n") return;
        }
        else
        {
            periodo->disciplinas.add(novo);
            std::cout << "Nova Disciplina Adicionada!\n(precione enter para continuar)\n";
            std::getline(std::cin, temp);
            return;
        }
    }
}

void Terminal::delDisciplina(Periodo* periodo)
{
    std::string disciplina;
    while (true)
    {
        Disciplina* iterator = listaPeriodo->val->disciplinas.val;
        clear();
        std::cout << "Qual disciplina voce deseja deletar?\n";
        while (iterator)
        {
            std::cout << "- " << iterator->getNome() << " (" << iterator->getId() << ")\n";
            iterator = iterator->prox;
        }

        std::getline(std::cin >> std::ws, disciplina);
        if (this->listaPeriodo->val->disciplinas.find(disciplina) != nullptr)
        {
            this->clear();
            this->listaPeriodo->val->disciplinas.del(disciplina);
            std::cout << "Disciplina Deletada!\n";
            std::getline(std::cin, disciplina);
            return;
        }
        else
        {
            this->clear();
            std::cout << "Disciplina nao encontrada.\n"
                << "Caso nao queira deletar uma disciplina, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, disciplina);

            if (!(disciplina.empty())) if (disciplina == "n") return;
        }
    }
    
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
            iterator->printPeriodo();
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
                << "Caso nao queira deletar um periodo, digite \"n\" (precione enter para continuar)\n";
            std::getline(std::cin, periodo);
     
            if (!(periodo.empty())) if (periodo == "n") return;
        }
    }
}

std::ifstream Terminal::findFile()
{
    std::string arquivo{};
    std::ifstream file;
    while (true) {
        std::cout << "Qual nome do arquivo?\n";
        std::getline(std::cin >> std::ws, arquivo);
        file.open(arquivo);
        if (!file) {
            std::cout << "Nao foi possivel abrir o arquivo! (precione enter para continuar)\n";
            std::getline(std::cin, arquivo);
        }
        else {
            break;
        }
    }
    return file;
}

std::ofstream Terminal::getFile()
{
    std::string arquivo{};
    std::ofstream file;
    while (true) {
        std::cout << "Qual nome do arquivo?\n";
        std::getline(std::cin >> std::ws, arquivo);
        file.open(arquivo);
        if (!file) {
            std::cout << "Nao foi possivel abrir o arquivo! (precione enter para continuar)\n";
            std::getline(std::cin, arquivo);
        }
        else {
            break;
        }
    }
    return file;
}

void Terminal::saveState(std::ofstream& file)
{
    if (!file) {
        return;
    }
    
    // Escrever todos Periodos
    Periodo* iteratorPeriodo{listaPeriodo->val};
    intWrite(file, listaPeriodo->size());
    while (iteratorPeriodo) {
        std::string periodoName{iteratorPeriodo->getId()};
        stringWrite(file, periodoName);

        // Escrever todos Alunos
        Aluno* iteratorAlunos{ iteratorPeriodo->alunos.val };
        intWrite(file, iteratorPeriodo->alunos.size());
        while (iteratorAlunos) {
            std::string alunoId{ iteratorAlunos->getId() };
            std::string alunoCpf{ iteratorAlunos->getCpf() };
            std::string alunoName{ iteratorAlunos->getNome() };

            stringWrite(file, alunoId);
            stringWrite(file, alunoCpf);
            stringWrite(file, alunoName);
            iteratorAlunos = iteratorAlunos->prox;
        }

        // Escrever todas Disciplinas
        Disciplina* iteratorDisciplinas{ iteratorPeriodo->disciplinas.val };
        intWrite(file, iteratorPeriodo->disciplinas.size());
        while (iteratorDisciplinas) {
            std::string disciplinaId{ iteratorDisciplinas->getId() };
            std::string disciplinaNome{ iteratorDisciplinas->getNome() };
            std::string disciplinaProfessor{ iteratorDisciplinas->getProfessor() };
            int         disciplinaCreditos{ iteratorDisciplinas->getCreditos() };

            stringWrite(file, disciplinaId);
            stringWrite(file, disciplinaNome);
            stringWrite(file, disciplinaProfessor);
            intWrite(file, disciplinaCreditos);

            iteratorDisciplinas = iteratorDisciplinas->prox;
        }
        iteratorPeriodo = iteratorPeriodo->prox;
    }
    std::cout << "Procedimento concluido!\n";
    std::string temp{};
    std::getline(std::cin, temp);
    file.close();
}



void Terminal::readState()
{
    std::ifstream file = findFile();
    // Periodos
    uploadState(file, true);

}

void Terminal::removeWhiteSpace(std::string& str)
{
    for (char& c : str) {
        if (c == ' ') {
            c = '_';
        }
        else if (c == '_') {
            c = ' ';
        }
    }
}

void Terminal::uploadState(std::ifstream& file, bool print)
{
    int periodoSize{};
    intRead(file, &periodoSize);
    if (print)
        std::cout << "Size Periodo: " << periodoSize << '\n';
    for (int i{}; i < periodoSize; i++) {
        std::string periodoName{};
        stringRead(file, periodoName);
        Periodo* per = new Periodo(periodoName);

        if (print)
            std::cout << "Name Per: " << periodoName << '\n';
        int alunoSize{};
        // Alunos
        ListaEncadeada<Aluno>* alunos = new ListaEncadeada<Aluno>;
        intRead(file, &alunoSize);
        if (print)
            std::cout << "Size Alunos: " << alunoSize << '\n';
        for (int j{}; j < alunoSize; j++) {
            alunos->add(readAluno(file));
        }
        per->alunos = *alunos;
        // Disciplinas
        ListaEncadeada<Disciplina>* disciplinas = new ListaEncadeada<Disciplina>;
        int disciplinaSize{};
        intRead(file, &disciplinaSize);
        if (print)
            std::cout << "Size Disciplinas: " << disciplinaSize << '\n';

        for (int j{}; j < disciplinaSize; j++) {
            disciplinas->add(readDisciplinas(file));
        }
        per->disciplinas = *disciplinas;
        listaPeriodo->add(per);

        alunos->val = nullptr;
        disciplinas->val = nullptr;
        delete alunos;
        delete disciplinas;
    }
    if (print)
        std::cout << "Leitura concluida\n";

    file.close();
    std::string arquivo{};
    if (print)
        std::getline(std::cin, arquivo);
}

bool Terminal::stringWrite(std::ofstream& file, std::string& str)
{
    removeWhiteSpace(str);
    file.write(str.c_str(), str.length());
    writeSeparator(file);
    if (!file.good()) {
        std::cout << "Erro ocorreu na escrita!\n";
        std::getline(std::cin, str);
        return false;
    }
    return true;
}

bool Terminal::intWrite(std::ofstream& file, int val)
{
    file.write(reinterpret_cast<const char*>(&val), sizeof(int));
    writeSeparator(file);
    if (!file.good()) {
        std::string temp{};
        std::cout << "Erro ocorreu na escrita!\n";
        std::getline(std::cin, temp);
        return false;
    }
    return true;
}

void Terminal::intRead(std::ifstream& file, int* val)
{
    if (dumpForInt) {
        dumpByte(file);
        dumpForInt = false;
    }
    file.read((char*) val, sizeof(int));
    dumpByte(file);
}

void Terminal::dumpByte(std::ifstream& file)
{
    int dump;
    file.read((char*)&dump, 1);
}

Aluno* Terminal::readAluno(std::ifstream& file)
{
    std::string id{};
    std::string cpf{};
    std::string name{};
    stringRead(file, id);
    stringRead(file, cpf);
    stringRead(file, name);
    return new Aluno(id, cpf, name);
}

Disciplina* Terminal::readDisciplinas(std::ifstream& file)
{
    std::string id{};
    std::string name{};
    std::string professor{};
    int creditos{};
    stringRead(file, id);
    stringRead(file, name);
    stringRead(file, professor);
    intRead(file, &creditos);
    return new Disciplina(id, name, professor, creditos);
}

void Terminal::stringRead(std::ifstream& file, std::string& str)
{
    file >> str;
    removeWhiteSpace(str);
    dumpForInt = true;
}

void Terminal::writeSeparator(std::ofstream& file)
{
    file.write(m_separator, 1);
}
