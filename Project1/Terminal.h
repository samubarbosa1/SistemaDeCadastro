#pragma once
#include "Periodo.h"
#include <fstream>


class Terminal
{
public:
	Terminal();
	Terminal(std::string arquivo);
	~Terminal();
	void ignoreOtherInputs();

	void clear();
	void showMenu();
	void showMenuAdd();
	void showMenuFind();
	void showMenuPeriodo(Periodo* periodo);
	void showMenuEditarPeriodo(Periodo* periodo);
	void textMenuEditar(Periodo* periodo);
	void showDadosPeriodo(Periodo* periodo);
	void addAluno(Periodo* periodo);
	void delAluno(Periodo* periodo);
	void addDisciplina(Periodo* periodo);
	void delDisciplina(Periodo* periodo);
	void showMenuDel();



private:
	ListaEncadeada<Periodo>* listaPeriodo = new ListaEncadeada<Periodo>;
	const char* m_separator{ "\n" }; // funciona tb se for espaco " "
	bool dumpForInt{ false };
	std::string default_arq{};

	//funcoes para salvar
	std::ifstream findFile();
	std::ofstream getFile();
	void saveState(std::ofstream& file);
	void readState();
	void removeWhiteSpace(std::string& str);
	void uploadState(std::ifstream& file, bool print);
	bool stringWrite(std::ofstream& file, std::string& str);
	bool intWrite(std::ofstream& file, int val);
	void intRead(std::ifstream& file, int* val);
	void dumpByte(std::ifstream& file);
	Aluno* readAluno(std::ifstream& file);
	Disciplina* readDisciplinas(std::ifstream& file);
	void stringRead(std::ifstream& file, std::string& str);
	void writeSeparator(std::ofstream& file);
};

