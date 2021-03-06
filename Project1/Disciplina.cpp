#include "Disciplina.h"

Disciplina::Disciplina()
{
	setId();
	setNome();
	setProfessor();
	setCreditos();
}

Disciplina::Disciplina(std::string id, std::string nome, std::string professor, int creditos) :
	id{ id }, nome{ nome }, professor{ professor }, creditos{ creditos }
{}

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

std::string Disciplina::getId()
{
	return this->id;
}

std::string Disciplina::getNome()
{
	return nome;
}

std::string Disciplina::getProfessor()
{
	return professor;
}

int			Disciplina::getCreditos()
{
	return creditos;
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
	std::cout << "Quantos creditos tem a disciplina?\n";
	std::cin >> creditos;
}

void Disciplina::print()
{
	std::cout << "Codigo " << this->id << "\n";
	std::cout << "Materia " << this->nome << "\n";
	std::cout << "Professor " << this->professor << "\n";
	std::cout << "Creditos " << this->creditos << "\n\n";
}
