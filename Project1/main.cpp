#include "Terminal.h"

int main()
{
    Terminal *myTerminal = new Terminal;

    myTerminal->showMenu();

    system("PAUSE");

    return 0;
}