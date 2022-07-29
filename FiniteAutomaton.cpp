#include "FiniteAutomaton.h"
#include "State.h"
#include <iostream>

FiniteAutomaton::FiniteAutomaton(string input) {

	for (int i = 0; i < INPUT_SIZE; i++)
		inputStringQ.push(input[i]);

	if (inputStringQ.front() == '0')
	{
		q0 = new State("q0", true, false, false, "q1", "q5");
		states.push_back(q0);

		q1 = new State("q1", false, false, false, "q2", "q5");
		states.push_back(q1);

		q2 = new State("q2", false, false, false, "q5", "q3");
		states.push_back(q2);

		q3 = new State("q3", false, false, false, "q5", "q4");
		states.push_back(q3);

		q4 = new State("q4", false, true, true, "q4", "q4");
		states.push_back(q4);

		q5 = new State("q5", false, true, false, "q5", "q5");
		states.push_back(q5);
	}

	else if (inputStringQ.front() == '1')
	{
		q0 = new State("q0", true, false, false, "q1", "q5");
		states.push_back(q0);

		q1 = new State("q1", false, false, false, "q2", "q5");
		states.push_back(q1);

		q2 = new State("q2", false, false, false, "q5", "q3");
		states.push_back(q2);

		q3 = new State("q3", false, false, false, "q4", "q4");
		states.push_back(q3);

		q4 = new State("q4", false, true, true, "q4", "q4");
		states.push_back(q4);

		q5 = new State("q5", false, true, false, "q5", "q5");
		states.push_back(q5);
	}

	current_state = q0;
}

FiniteAutomaton::~FiniteAutomaton() {
	delete current_state;
	delete q0;
	delete q1;
	delete q2;
	delete q3;
	delete q4;
	delete q5;
}

void FiniteAutomaton::nextState() {
	string tmp;

	if (inputStringQ.size() == 5)
		inputStringQ.pop();

	State *p = current_state;

	if (inputStringQ.front() == '0')
		tmp = p->transitionToState(0);

	if (inputStringQ.front() == '1')
		tmp = p->transitionToState(1);

	current_state = states[tmp[1] - 48];
}

State *FiniteAutomaton::predictNextState() {
	while (inputStringQ.size() != 0)
	{
		nextState();
		inputStringQ.pop();
	}

	return current_state;
}