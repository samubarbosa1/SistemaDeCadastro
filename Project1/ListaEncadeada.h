#pragma once
#include <string>
template <typename Type>
class ListaEncadeada
{
public:
	Type* val{nullptr};
	void add();
	Type* find(std::string ident);
	void del(std::string ident);
	void print();
	~ListaEncadeada();
};


template<typename Type>
inline void ListaEncadeada<Type>::add()
{
	Type* newElement = new Type();
	std::string temp{};

	if (find(newElement->getId()) != nullptr) {
		std::cout << "Periodo ja existente!(precione enter para continuar)\n";
		delete(newElement);
		std::getline(std::cin, temp);
	}
	else {
		newElement->prox = this->val;
		this->val = newElement;
		std::cout << "\nPeriodo " << newElement->getId() << " criado! (precione enter para continuar)\n";
		std::getline(std::cin, temp);
	}
}

template<typename Type>
inline Type* ListaEncadeada<Type>::find(std::string ident)
{
	Type* iterator{ this->val };

	while (iterator != nullptr && iterator->getId() != ident)
	{
		iterator = iterator->prox;
	}
	return iterator;
}

template<typename Type>
inline void ListaEncadeada<Type>::del(std::string ident)
{
	Type* atual = this->val, *ant = nullptr;
	
	while (atual && atual->getId() != ident) {
		ant = atual;
		atual = atual->prox;
	}

	if (atual)
	{
		if (atual == this->val)
			this->val = this->val->prox;
		else
			ant->prox = atual->prox;
		delete atual;
	}
}

template<typename Type>
inline void ListaEncadeada<Type>::print()
{
	Type* iterator{ this->val };
	while (iterator) {
		iterator->print();
		iterator = iterator->prox;
	}
}

template<typename Type>
inline ListaEncadeada<Type>::~ListaEncadeada()
{
	Type* iterator{ this->val }, * temp;
	while (iterator) {
		temp = iterator;
		iterator = iterator->prox;
		delete(temp);
	}
}

