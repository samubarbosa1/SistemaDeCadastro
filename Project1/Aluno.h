#pragma once

#include "Disciplina.h"

class Aluno {
public:
    Aluno* prox;
    Aluno();
    Aluno(std::string id, std::string nome, std::string cpf);

    //setters
    void setCpf();
    void setId();
    void setNome();

    //getters
    std::string getCpf();
    std::string getId();
    std::string getNome();


    void print();

private:
    std::string id;
    std::string nome;
    std::string cpf;
};

