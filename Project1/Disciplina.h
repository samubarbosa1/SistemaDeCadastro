#pragma once
#include <iostream>
#include <string>

class Disciplina {
public:
    Disciplina* prox{};

    //construtores e destrutor
    Disciplina();
    Disciplina(std::string id, std::string nome, std::string professor, int creditos);

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
    int getCreditos();
    void print();

private:
    std::string id{};
    std::string nome{};
    std::string professor{};
    int creditos{};
};

