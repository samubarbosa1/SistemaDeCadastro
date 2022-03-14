#pragma once

#include "Disciplina.h"

class Aluno {
private:
    std::string nome;
    std::string cpf;
public:
    std::string id;
    Aluno* prox;
    Aluno();
    void print();
};

