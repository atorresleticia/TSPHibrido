#include "stdafx.h"
#include "populacao.h"

populacao::populacao(const int tamanho_populacao, const int numero_cidades)
{
	tamanho_populacao_ = tamanho_populacao;

	for (int i = 0; i < numero_cidades; i++)
	{
		lista_cidades_.adiciona_cidade(cidade(i));
	}
	for (int i = 0; i < tamanho_populacao_; i++)
	{
		rotas_.push_back(lista_cidades_.get_cidades());
	}
	tamanho_populacao_ = rotas_.size();
}

individuo populacao::get_melhor()
{
	individuo melhor = rotas_.at(0);
	for (int i = 1; i < tamanho_populacao_; i++)
	{
		if (melhor.get_aptidao() < get_individuo_em(i).get_aptidao())
		{
			melhor = get_individuo_em(i);
		}
	}
	return melhor;
}

individuo populacao::get_melhor(individuo& a, individuo& b)
{
	individuo melhor = a.get_aptidao() > b.get_aptidao() ? a : b;
	return melhor;
}

void populacao::armazena_individuo(int i, individuo x_i)
{
	rotas_.at(i) = x_i;
}

void populacao::armazena_individuo(individuo x_i)
{
	rotas_.push_back(x_i);
	tamanho_populacao_++;
}
