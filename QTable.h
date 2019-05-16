#pragma once
#include <vector>

class QTable {
private:
	double qtable[512][6];
	double a, y;

	std::vector<int> queuei;
	std::vector<int> queuej;

	void movQueue(int, int);

	int n;

public:
	void init(double, double, int);
	int getAction(int);
	void reward(int);
	void saveTab();
	QTable();
	~QTable();
};