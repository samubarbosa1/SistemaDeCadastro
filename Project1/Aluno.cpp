#include "Aluno.h"

Aluno::Aluno()
{
	setId();
	setCpf();
	setNome();
}

Aluno::Aluno(std::string id, std::string nome, std::string cpf) :
	id{ id }, nome{ nome }, cpf{ cpf }
{}

void Aluno::setCpf()
{
	std::string temp;

	while (true) {
		std::cout << "Qual e o cpf do Aluno (xxx.xxx.xxx-xx)?\n";
		std::getline(std::cin >> std::ws, temp);

		if (temp.length() != 14 || temp[3] != '.' || temp[7] != '.' || temp[11] != '-') {
			std::cout << "Formatacao incorreta?\n";
			std::getline(std::cin, temp);
		}
		else {
			break;
		}
	}

	this->cpf = temp;
}

void Aluno::setId()
{
	std::string temp{};
	while (true) {
		std::cout << "Qual e o codigo do Aluno (xxxxx)?\n";
		std::getline(std::cin >> std::ws, temp);
		if (temp.length() != 5) {
			std::cout << "Formatacao incorreta, digite enter para continuar?\n";
			std::getline(std::cin, temp);
		}
		else {
			break;
		}
	}
	this->id = temp;
}

void Aluno::setNome()
{
	std::cout << "Qual e o nome do Aluno?\n";
	std::getline(std::cin >> std::ws, this->nome);
}

std::string Aluno::getCpf()
{
	return this->cpf;
}

std::string Aluno::getId()
{
	return this->id;
}

std::string Aluno::getNome()
{
	return this->nome;
}

void Aluno::print()
{
	std::cout << "ID: " << id << "\n"
		<< "Nome: " << nome << "\n"
		<< "CPF: " << cpf << "\n\n";
}
