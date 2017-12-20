#include "stdafx.h"
#include "Individuo.h"

individuo individuo::get_melhor(individuo& a)
{
	individuo melhor = this->get_aptidao() > a.get_aptidao() ? *this : a;
	return melhor;
}

double individuo::distancia_ate(::cidade a, ::cidade b)
{
	double dx = abs(a.x() - b.x());
	double dy = abs(a.y() - b.y());

	return sqrt(dx * dx + dy * dy);
}

double individuo::distancia()
{
	if (distancia_ == 0)
	{
		for (int i = 0; i < rota_.size() - 1; i++)
		{
			distancia_ += distancia_ate(rota_.at(i), rota_.at(i + 1));
		}
		distancia_ += distancia_ate(rota_.at(0), rota_.at(rota_.size() - 1));
	}
	return distancia_;
}
