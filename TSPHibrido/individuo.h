#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#pragma once

#include <string>
#include "Cidade.h"
#include <vector>
#include <algorithm>

class individuo
{
public:

	individuo()
	{
		tamanho_rota_ = 0;
	}

	individuo(const std::vector<cidade> cidades)
	{
		gera_individuo(cidades);
	}

	~individuo() = default;

	individuo get_melhor(individuo& a);
	double distancia_ate(cidade a, cidade b) const;
	double distancia();

	void gera_individuo(const std::vector<cidade> cidades)
	{
		rota_ = cidades;
		random_shuffle(rota_.begin(), rota_.end());		
	}

	cidade cidade(const int index)
	{
		return rota_.at(index);
	}

	void set_cidade(const ::cidade cidade)
	{
		rota_.push_back(cidade);
		tamanho_rota_++;
	}

	void set_cidade(const int index, const ::cidade cidade)
	{
		rota_.at(index) = cidade;
	}

	void set_aptidao(const int aptidao)
	{
		aptidao_ = aptidao;
	}
	
	double get_aptidao()
	{
		aptidao_ = 1 / distancia();
		return aptidao_;
	}

	int get_tamanho_rota()
	{
		tamanho_rota_ = rota_.size();
		return tamanho_rota_;
	}
	
private:
	std::vector<::cidade> rota_;
	double aptidao_;
	double distancia_ = 0;
	int tamanho_rota_;
};

#endif

