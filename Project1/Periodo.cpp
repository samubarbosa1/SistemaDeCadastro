#include "Periodo.h"


Periodo::Periodo()
{
	setId();
}

Periodo::Periodo(std::string id) :
	id{id}
{}

Periodo::~Periodo()
{
}

void Periodo::printPeriodo()
{
	std::cout << "Periodo: " << this->id << "\n"
		<< "Disciplina(s): " << this->disciplinas.size() << "\n"
		<< "Aluno(s): " << this->alunos.size() << "\n\n";
}

void Periodo::setId()
{
	std::string periodo{};
	while (true) {
		std::cout << "Qual nome do periodo (xxxx.x)?\n";
		std::getline(std::cin >> std::ws, periodo);
		if (periodo.length() != 6 || periodo[4] != '.') {
			std::cout << "Formatacao incorreta, digite enter para continuar?\n";
			std::getline(std::cin, periodo);
		}
		else {
			break;
		}
	}
	this->id = periodo;
}

std::string Periodo::getId()
{
	return this->id;
}
