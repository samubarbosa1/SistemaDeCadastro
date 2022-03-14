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
    std::string periodo{};

    ignoreOtherInputs();
    clear();
    listaPeriodo->add();

    showMenu();
}

void Terminal::showMenuFind()
{

}
