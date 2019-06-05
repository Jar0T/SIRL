#include "QTable.h"
#include <time.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>

QTable::QTable(){}

QTable::~QTable(){}

void QTable::movQueue(int a, int b) {
	if (queuei.size() >= 50) {
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

void QTable::init(double q, double p, int x, int range, int max, bool rising, double s, double m, int sp) {
	srand(time(NULL));

	maxRand = max;
	randRange = range;

	isRising = rising;
	step = s;
	maxVal = m;
	licznik = 0;
	speed = sp;

	n = x;

	log_number = 0;

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
				qtable[i][j] = ((double)(rand() % 2000 - 1000)) / 1000;
				//qtable[i][j] = 0.0;
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

	int random = rand() % maxRand;
	if (random < randRange)
		index++;
	if (random > maxRand - randRange)
		index--;

	if (index > 5)
		index = 0;
	if (index < 0)
		index = 5;

	movQueue(i, index);

	if (isRising)
		if (a < maxVal)
			if (licznik < speed)
				licznik++;
			else {
				a += step;
				licznik = 0;
			}

	std::cout << a << "\n";

	return index;
}

void QTable::reward(double r) {
	std::vector<int>::iterator iti;
	std::vector<int>::iterator itj;

	iti = queuei.begin();
	itj = queuej.begin();

	for (iti; iti != queuei.end();) {
		if (iti == queuei.begin())
			qtable[*iti][*itj] = qtable[*iti][*itj] * (1 - a) + a * r;
		else
			qtable[*iti][*itj] = qtable[*iti][*itj] * (1 - a) + a * (r + y * qtable[*(iti - 1)][*(itj - 1)]);

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

void QTable::saveLog() {
	std::ofstream file("Logs/log" + std::to_string(log_number) + ".txt");

	if (file.is_open()) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				file << std::to_string(qtable[i][j]) << "\t";
			}
			file << "\n";
		}
	}

	log_number++;

	file.close();
}