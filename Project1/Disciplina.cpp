#include "Disciplina.h"

Disciplina::Disciplina(std::string id, std::string nome, std::string professor) :
	id{id}, nome{nome}, professor{professor} 
{}

Disciplina::Disciplina()
{
	setId();
	setNome();
	setProfessor();
}

Disciplina::~Disciplina()
{

}

void Disciplina::setId()
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
}

void Disciplina::setNome()
{
	std::cout << "Qual e o nome da Disciplina?\n";
	std::getline(std::cin >> std::ws, this->nome);
}

void Disciplina::setProfessor()
{
	std::cout << "Qual e o nome do Professor dessa Disciplina?\n";
	std::getline(std::cin >> std::ws, this->professor);
}

void Disciplina::setCreditos()
{
}
