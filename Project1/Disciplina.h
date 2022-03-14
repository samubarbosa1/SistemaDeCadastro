#pragma once
#include <iostream>
#include <string>

class Disciplina {
private:
    std::string id;
    std::string nome;
    std::string professor;
    int creditos;


public:
    Disciplina* prox{};

    //construtor e destrutor
    Disciplina();
    virtual ~Disciplina();

    //setter
    void setId();
    void setNome();
    void setProfessor();
    void setCreditos();

};

