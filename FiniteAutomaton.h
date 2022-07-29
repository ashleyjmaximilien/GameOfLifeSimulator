#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

#include <queue>
#include <vector>
#include <string>
#include "State.h"
using namespace std;

const int INPUT_SIZE = 5;

class FiniteAutomaton {

public:
	FiniteAutomaton(string input);
	~FiniteAutomaton();
	State *getCurrentState() { return current_state; };
	void nextState();
	State *predictNextState();

private:
	State *current_state;
	queue<char> inputStringQ;
	vector<State *> states;
	State *q0;
	State *q1;
	State *q2;
	State *q3;
	State *q4;
	State *q5;
};
#endif
