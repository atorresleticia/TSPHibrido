#pragma once

#include <cstdlib>

class cidade
{
public:
	
	cidade (int x, int y, int id)
	{
		this->x_ = x;
		this->y_ = y;
		this->id_ = id;
	}

	cidade(int id)
	{
		this->x_ = rand() % 1000;
		this->y_ = rand() % 1000;
		this->id_ = id;
	}

	int x() const
	{
		return x_;
	}

	void set_x(int x)
	{
		x_ = x;
	}

	int y() const
	{
		return y_;
	}

	void set_y(int y)
	{
		y_ = y;
	}

	int id() const
	{
		return id_;
	}

	void set_id(int id)
	{
		id_ = id;
	}

private:
	int x_;
	int y_;
	int id_;
};
