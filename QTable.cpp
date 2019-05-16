#include "QTable.h"
#include <time.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>

QTable::QTable(){}

QTable::~QTable(){}

void QTable::movQueue(int a, int b) {
	if (queuei.size() >= 100) {
		queuei.pop_back();
		queuej.pop_back();

		queuei.insert(queuei.begin(), a);
		queuej.insert(queuej.begin(), b);
	}
	else {
		queuei.insert(queuei.begin(), a);
		queuej.insert(queuej.begin(), b);
	}
}

void QTable::init(double q, double p, int x) {
	srand(time(NULL));

	n = x;

	std::ifstream file("QTable.txt");

	if (file.is_open()) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				file >> qtable[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				qtable[i][j] = rand() % 100;
			}
		}
	}

	a = q;
	y = p;

	file.close();
}

int QTable::getAction(int i) {
	int index = 0;
	double max = 0;

	for (int j = 0; j < 6; j++) {
		if (qtable[i][j] > max) {
			max = qtable[i][j];
			index = j;
		}
	}

	switch (rand() % 3) {
	case 1:
		break;
	case 2:
		index++;
		break;
	case 3:
		index--;
		break;
	default:
		break;
	}

	if (index > 5)
		index = 0;
	if (index < 0)
		index = 5;

	movQueue(i, index);

	return index;
}

void QTable::reward(int r) {
	std::vector<int>::iterator iti;
	std::vector<int>::iterator itj;

	iti = queuei.begin();
	itj = queuej.begin();

	for (iti; iti != queuei.end();) {
		if (iti == queuei.begin())
			qtable[*iti][*itj] = qtable[*iti][*itj] * (a - 1) + a * r;
		else
			qtable[*iti][*itj] = qtable[*iti][*itj] * (a - 1) + a * (r + y * qtable[*(iti - 1)][*(itj - 1)]);

		iti++;
		itj++;
	}
}

void QTable::saveTab() {
	std::ofstream file("QTable.txt");

	if (file.is_open()) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				file << std::to_string(qtable[i][j]) << std::endl;
			}
		}
	}

	file.close();
}