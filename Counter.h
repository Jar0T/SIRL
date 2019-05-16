#pragma once

class Counter {
private:
	int startingValue;
	int value;

	void update();

public:
	Counter(int);
	~Counter();

	int getValue();

};