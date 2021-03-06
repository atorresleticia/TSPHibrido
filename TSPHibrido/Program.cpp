// AG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <chrono>
#include <conio.h>
#include <fstream>
#include "TSPHibrido.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	float tamanho_populacao;
	int elitismo;
	int numero_cidades;
	int numero_geracoes;
	double li = 25;
	double ls = 600;
	double const_r = 0.9;

	cout << "Parametros: numero_geracoes tamanho_populacao numero_cidades elitismo (0-sem 1-com)" << endl;
	cin >> numero_geracoes >> tamanho_populacao >> numero_cidades >> elitismo;

	cout << "\nPARAMETROS: " << endl;
	cout << "Numero de geracoes: " << numero_geracoes << endl;
	cout << "Tamanho populacao: " << tamanho_populacao << endl;
	cout << "Numero de cidades por rota: " << numero_cidades << endl;
	cout << (elitismo == 1 ? "Com elitismo" : "Sem elitismo") << endl;

	cout << "\nPARAMETROS ANNEALING:" << endl;
	cout << "Temperatura inicial: " << ls << endl;
	cout << "Temperatura final: " << li << endl;
	cout << "Constante de resfriamento: " << const_r << endl;

	unsigned long g_count = 0;
	const auto init = chrono::high_resolution_clock::now();

	populacao pop = populacao(tamanho_populacao, numero_cidades);
	const double distancia_inicial = pop.get_melhor().distancia();

	cout << "\n\nPRE HIBRIDIZACAO: " << endl;
	cout << "Tamanho populacao: " << pop.get_tamanho_populacao() << endl;
	cout << "Numero cidades: " << numero_cidades << endl;
	cout << "Distancia inicial: " << distancia_inicial << endl;
	
	genetico_hibrido gen = genetico_hibrido(elitismo);

	int local_count = 0;

	while (g_count < numero_geracoes)
	{
		if (g_count % 50 == 0)
		{
			cout << "\n" << pop.get_melhor().distancia() << "\b\b\b\b\b\b\b\b\b\b\b\b";
		}

		const double dist_anterior = pop.get_melhor().distancia();
		pop = gen.evolucao(pop);
		const double dist_posterior = pop.get_melhor().distancia();

		if (dist_anterior == dist_posterior)
		{
			local_count++;
			if (local_count == 100)
			{
				const double dist_anterior_annealing = pop.get_melhor().distancia();
				pop = gen.evolucao_annealing(pop);
				const double dist_posterior_annealing = pop.get_melhor().distancia();
				
				if(dist_anterior_annealing == dist_posterior_annealing)
				{
					pop = gen.evolucao_annealing(pop);
				}

				local_count = 0;
			}
		}
		else
		{
			local_count = 0;
		}
		
		g_count++;
	}

	const auto end = chrono::high_resolution_clock::now();

	const double melhoria = distancia_inicial - pop.get_melhor().distancia();
	
	cout << "\nRESULTADOS: " << endl;
	cout << "Numero de geracoes: " << g_count << endl;
	cout << "Menor distancia encontrada: " << pop.get_melhor().distancia() << endl;
	cout << "Melhoria de distancia: " << melhoria << endl;
	cout << "Qualidade da Solucao: " << melhoria / distancia_inicial * 100.0 << "% melhor que a distancia inicial" << endl;
	cout << "Duracao: " << chrono::duration_cast<chrono::duration<double>>(end - init).count() << "s" << endl;
	cout << endl;
	
	return 0;
}

