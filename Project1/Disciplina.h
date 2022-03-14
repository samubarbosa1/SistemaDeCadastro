#pragma once
#include <iostream>
#include <string>

class Disciplina {
private:
    std::string nome;
    std::string professor;
    int creditos;
public:
    std::string id;
    Disciplina* prox{};

    //construtor
    Disciplina();

    //destrutor
    virtual ~Disciplina();

};

