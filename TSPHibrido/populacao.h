#ifndef POPULACAO_H
#define POPULACAO_H
#pragma once

#include "individuo.h"
#include "ListaCidades.h"

class populacao
{
public:

	populacao(int tamanho_populacao, int numero_cidades);
	populacao()
	{
		tamanho_populacao_ = 0;
	}

	std::vector<individuo> get_individuos() const
	{
		return rotas_;
	}

	individuo get_individuo_em(const int index) const
	{
		return rotas_.at(index);
	}

	int get_tamanho_populacao() const
	{
		return tamanho_populacao_;
	}

	individuo get_melhor();
	static individuo get_melhor(individuo& a, individuo& b);
	void armazena_individuo(int i, individuo x_i);
	void armazena_individuo(individuo x_i);

private:
	std::vector<individuo> rotas_;
	lista_cidades lista_cidades_;
	individuo melhor_;
	int tamanho_populacao_ = 0;
};


#endif
