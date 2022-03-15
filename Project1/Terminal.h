#pragma once
#include "Periodo.h"

class Terminal
{
private:
	ListaEncadeada<Periodo>* listaPeriodo = new ListaEncadeada<Periodo>;
	bool inMenu;


public:
	~Terminal();
	void ignoreOtherInputs();

	void clear();
	void showMenu();
	void showMenuAdd();
	void showMenuFind();
	void showMenuPeriodo(Periodo* periodo);
	void addAluno(Periodo* periodo);
	void delAluno(Periodo* periodo);
	void addDisciplina(Periodo* periodo);
	void delDisciplina(Periodo* periodo);
	void showMenuDel();

};

