#include "Counter.h"

Counter::Counter(int start) {
	value = startingValue = start;
}

Counter::~Counter() {

}

void Counter::update() {
	value--;
	if (value < 0)
		value = startingValue;
}

int Counter::getValue() {
	update();
	return value;
}