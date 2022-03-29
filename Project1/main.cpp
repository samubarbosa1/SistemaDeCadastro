#include "Terminal.h"

int main()
{
    Terminal *myTerminal = new Terminal("default.bin");
    myTerminal->showMenu();
    delete(myTerminal);

    system("PAUSE");

    return 0;
}