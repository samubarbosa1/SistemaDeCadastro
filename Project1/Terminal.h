#pragma once
#include "Periodo.h"
#include <fstream>


class Terminal
{
private:
	ListaEncadeada<Periodo>* listaPeriodo = new ListaEncadeada<Periodo>;
	bool inMenu;


public:
	Terminal();
	~Terminal();
	void ignoreOtherInputs();

	void clear();
	void showMenu();
	void showMenuAdd();
	void showMenuFind();
	void showMenuPeriodo(Periodo* periodo);
	void showMenuEditarPeriodo(Periodo* periodo);
	void showDadosPeriodo(Periodo* periodo);
	void addAluno(Periodo* periodo);
	void delAluno(Periodo* periodo);
	void addDisciplina(Periodo* periodo);
	void delDisciplina(Periodo* periodo);
	void showMenuDel();
	void menuPeriodo(Periodo*);
	auto getFile();
	void saveState();
	void readState();
	bool stringWrite(std::ofstream& file, std::string& str);
	bool intWrite(std::ofstream& file, int val);
};

