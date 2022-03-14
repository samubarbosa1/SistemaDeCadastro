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
        std::cout << "Qual operacao deseja realizar? (a/b/c)\n";
        std::cout << "a) Criar Periodo\n";
        std::cout << "b) Consultar Periodo\n";
        std::cout << "c) Remover Periodo\n";
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

    this->menuPeriodo(procurado);
}

void Terminal::menuPeriodo(Periodo* periodo)
{
}
