#pragma once
#include <iostream>
#include <string>

class Disciplina {
private:
    std::string id{};
    std::string nome{};
    std::string professor{};
    int creditos{};


public:
    Disciplina* prox{};

    //construtor e destrutor
    Disciplina();
    Disciplina(std::string id, std::string nome, std::string professor);

    virtual ~Disciplina();

    //setter
    void setId();
    void setNome();
    void setProfessor();
    void setCreditos();

    //getter
    std::string getId();
    std::string getNome();
    std::string getProfessor();
    int         getCreditos();



    void print();
};

