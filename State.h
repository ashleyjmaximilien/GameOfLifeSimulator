#ifndef STATE_H
#define STATE_H

#include <string>
#include <unordered_map>

using namespace std;

class State {

	public:
		State(string n, bool final, bool initial, bool finalAlive, string a, string b); // string a represents next state on input 0, string b represents next state on input 1
		void setName(string n) { name = n; };
		string getName() { return name; };

		bool isFinalState() { return isFinal; };
		bool isAlive() { return isFinalAlive; };
		bool isInitialState() { return isInitial; };

		string transitionToState(int inputVal) { return umap.at(inputVal); };

	private:
		string name;
		bool isFinal;
		bool isFinalAlive;
		bool isInitial;

		unordered_map<int, string> umap;
};
#endif
