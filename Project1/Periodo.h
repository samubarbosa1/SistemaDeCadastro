#pragma once

#include "Aluno.h"
#include "ListaEncadeada.h"

class Periodo
{
public:
	ListaEncadeada<Aluno> alunos{};
	ListaEncadeada<Disciplina> disciplinas{};
	Periodo* prox{};
	std::string id{};
	void setId();
	Periodo();
	~Periodo();
};

