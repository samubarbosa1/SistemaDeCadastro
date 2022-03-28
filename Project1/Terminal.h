#pragma once
#include "Periodo.h"
#include <fstream>


class Terminal
{
private:
	ListaEncadeada<Periodo>* listaPeriodo = new ListaEncadeada<Periodo>;
	bool inMenu;
	const char * m_separator{ "\n" }; // funciona tb se for espaco " "
	bool dumpForInt{ false };

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
	void intRead(std::ifstream& file, int* val);
	void dumpByte(std::ifstream& file);
	Aluno* readAluno(std::ifstream& file);
	Disciplina* readDisciplinas(std::ifstream& file);
	void stringRead(std::ifstream& file, std::string& str);
	void writeSeparator(std::ofstream& file);
};

