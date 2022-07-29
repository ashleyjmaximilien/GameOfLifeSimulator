#include "State.h"
#include <iostream>
using namespace std;

State::State(string n, bool final, bool initial, bool finalAlive, string a, string b)
{
	name = n;
	isFinal = final;
	isFinalAlive = finalAlive;
	isInitial = initial;

	umap.emplace(0, a);
	umap.emplace(1, b);
}