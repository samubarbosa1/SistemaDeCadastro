#pragma once

#include "Aluno.h"
#include "ListaEncadeada.h"

class Periodo
{
private:
	std::string id{};

public:
	Periodo* prox{};
	ListaEncadeada<Aluno> alunos{};
	ListaEncadeada<Disciplina> disciplinas{};

	// construtor e destrutor
	Periodo();
	Periodo(std::string id);
	~Periodo();

	//funcao
	void printPeriodo();

	//setter
	void setId();
	//getter
	std::string getId();
};

