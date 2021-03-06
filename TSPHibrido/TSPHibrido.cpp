﻿#include "stdafx.h"
#include "TSPHibrido.h"
#include <unordered_set>
#include <iostream>

individuo individuo_selecionado_1;
individuo individuo_selecionado_2;
individuo filho;

individuo solucao_nova;
individuo solucao_atual;

cidade cidade_1;
cidade cidade_2;

individuo genetico_hibrido::torneio(populacao& p)
{
	int tamanhoTorneio = 5;
	populacao aux;

	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));

	return aux.get_melhor();
}

individuo genetico_hibrido::cruzamento(individuo& a, individuo& b)
{
	individuo filho = individuo();
	const int size = a.get_tamanho_rota();
	std::unordered_set<int> cidades;

	const int start = rand() % (size / 2);
	int end = rand() % (size / 2);

	end = size - end;

	for (int i = 0; i < start; i++)
	{
		filho.set_cidade(a.cidade(i));
		cidades.insert(a.cidade(i).id());
	}

	for (int i = end; i < size; i++)
	{
		filho.set_cidade(a.cidade(i));
		cidades.insert(a.cidade(i).id());
	}

	int i = 0;

	while (filho.get_tamanho_rota() != size)
	{
		if (cidades.count(b.cidade(i).id()) == 0)
		{
			filho.set_cidade(b.cidade(i));
		}
		i++;
	}

	return filho;
}

void genetico_hibrido::mutacao(individuo a) const
{
	const int tamanho = a.get_tamanho_rota();
	for (int i = 0; i < tamanho; i++)
	{
		float m = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (m <= tx_mutacao_)
		{
			int j = rand() % tamanho;
			const cidade cidade_1 = a.cidade(i);
			const cidade cidade_2 = a.cidade(j);
			a.set_cidade(j, cidade_1);
			a.set_cidade(i, cidade_2);
		}
	}
}

populacao genetico_hibrido::evolucao(populacao p)
{
	populacao nova_p = populacao();

	auto j = 0;

	if (elitismo_)
	{
		nova_p.armazena_individuo(p.get_melhor());
		j = 1;
	}

	for (auto i = j; i < p.get_tamanho_populacao(); i++)
	{
		individuo individuo_selecionado_1 = torneio(p);
		individuo individuo_selecionado_2 = torneio(p);
		individuo filho = cruzamento(individuo_selecionado_1, individuo_selecionado_2);

		nova_p.armazena_individuo(filho);
	}
	for (int i = j; i < p.get_tamanho_populacao(); i++)
	{
		mutacao(p.get_individuo_em(i));
	}
	return nova_p;
}

populacao genetico_hibrido::evolucao_annealing(populacao p)
{
	double ls = 50.0;
	double li = 25.0;
	double t = ls;
	double t_min = li;
	double const_r = 0.9;

	populacao nova_p = populacao();

	while (t > t_min)
	{
		for (auto i = 0; i < p.get_tamanho_populacao(); i++)
		{
			solucao_atual = torneio(p);
			solucao_nova = torneio(p);

			int tamanho = solucao_nova.get_tamanho_rota();

			int index1 = rand() % tamanho;
			int index2 = rand() % tamanho;

			cidade_1 = solucao_nova.cidade(index1);
			cidade_2 = solucao_nova.cidade(index2);

			solucao_nova.set_cidade(index2, cidade_1);
			solucao_nova.set_cidade(index1, cidade_2);

			const double delta = solucao_nova.distancia() - solucao_atual.distancia();

			if (delta <= 0)
			{
				nova_p.armazena_individuo(solucao_nova);
			}
			else
			{
				const double rnd = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (rnd < exp(-delta / t))
				{
					nova_p.armazena_individuo(solucao_nova);
				}
				else
				{
					nova_p.armazena_individuo(solucao_atual);
				}
			}

		}
		t *= const_r;
	}
	return nova_p;
}