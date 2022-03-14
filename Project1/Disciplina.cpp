#include "Disciplina.h"

Disciplina::Disciplina()
{
	std::string temp{};
	while (true) {
		std::cout << "Qual e o codigo da Disciplina (xxxx)?\n";
		std::getline(std::cin >> std::ws, temp);
		if (temp.length() != 4) {
			std::cout << "Formatacao incorreta, digite enter para continuar?\n";
			std::getline(std::cin, temp);
		}
		else {
			break;
		}
	}
	this->id = temp;

	std::cout << "Qual e o nome da Disciplina?\n";
	std::getline(std::cin >> std::ws, this->nome);

	std::cout << "Qual e o nome do Professor desta Disciplina?\n";
	std::getline(std::cin >> std::ws, this->professor);
}

Disciplina::~Disciplina()
{

}
