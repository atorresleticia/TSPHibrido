#ifndef GENETICOCONFIG_H
#define GENETICOCONFIG_H
#pragma once
#include "populacao.h"

class genetico_hibrido
{
public:

	genetico_hibrido(const bool elitismo) :
		elitismo_(elitismo)
	{
	}
	genetico_hibrido() = default;
	~genetico_hibrido() = default;

	static individuo torneio(populacao& p);
	static individuo cruzamento(individuo& a, individuo& b);
	void mutacao(individuo a) const;
	populacao evolucao(populacao p);
	populacao evolucao_annealing(populacao p);

private:
	float tx_mutacao_;
	float tx_cruzamento_;
	bool elitismo_;
	std::vector<individuo> rotas_;
};

#endif
