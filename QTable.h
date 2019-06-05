#pragma once
#include <vector>

class QTable {
private:
	double qtable[512][6];
	double a, y;

	int maxRand;
	int randRange;

	bool isRising;
	double step;
	double maxVal;
	int licznik;
	int speed;

	std::vector<int> queuei;
	std::vector<int> queuej;

	void movQueue(int, int);

	int n;

	int log_number;

public:
	void init(double, double, int, int, int, bool, double s = 0, double m = 0, int sp = 0);
	int getAction(int);
	void reward(double);
	void saveTab();
	void saveLog();
	QTable();
	~QTable();
};