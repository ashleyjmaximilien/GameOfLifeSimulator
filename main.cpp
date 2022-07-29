
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include "FiniteAutomaton.h"
#include "State.h"
#undef main

using namespace std;

// CELL CONSTANTS
const int DEAD = 0;				   // Dead Cell
const int ALIVE = 1;			   // Living cell
const int REPRODUCTION_VAL = 3;	   // Number of live neighbors needed to generate a live cell
const int OVERPOPULATION_VAL = 3;  // More neighbors than this value results in death (starvation)
const int UNDERPOPULATION_VAL = 2; // Less neighbors than this value results in death (lonliness)

// ANIMATION CONSTANTS
const int MATRIX_SIZE = 12;
const int SCREEN_SIZE = 700;
const int ANIMATION_RATE = 600;					 // Milliseconds before matrix updates
const int CELL_SIZE = SCREEN_SIZE / MATRIX_SIZE; // pixel size of cells

// Window functions
bool initialize_window();
void display_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s);
void close_window();
void next_generation(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s);
void handle_event(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s);
string generate_string(int status, int neighbors);

// Cell functions
int get_live_neighbors(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y); // (x, y) is position on screen
void update_cell(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y, int neighbors);
void set_cell(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y, int status); // status: alive/dead -> 1/0

/* GAME CONTROLS */
bool is_animating = false;
bool user_has_quit = false;

/* TITLE & GENERATION COUNTER */
const char title[] = "Conway's Game of Life as Cellular Automaton";
int gen_count = 0;

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

int main()
{

	int matrix[MATRIX_SIZE][MATRIX_SIZE];

	// Initialize all cells to DEAD state
	for (int x = 0; x < MATRIX_SIZE; x++)
		for (int y = 0; y < MATRIX_SIZE; y++)
			matrix[x][y] = DEAD;

	Uint32 game_ticks = SDL_GetTicks(); // Used to set an acceptable framerate

	if (initialize_window() == false)
		throw runtime_error("Cannot open a window.");

	cout << "-----------------------------------------" << endl;
	cout << "CONWAY'S GAME OF LIFE AS FINITE AUTOMATA" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\n"
		 << endl;
	cout << "Instructions: \n"
		 << endl;
	cout << "Right click " << setw(25) << "Bring cell to life" << endl;
	cout << "Middle click" << setw(23) << "Kill a live cell" << endl;
	cout << "Left click " << setw(26) << "Generate automaton" << endl;
	cout << "E key" << setw(26) << "Clear matrix" << endl;
	cout << "Spacebar" << setw(32) << "Start/Stop animation\n"
		 << endl;

	while (user_has_quit == false)
	{

		handle_event(matrix, MATRIX_SIZE);

		display_matrix(matrix, MATRIX_SIZE);

		int tick_diff = SDL_GetTicks() - game_ticks;

		if (is_animating && tick_diff > ANIMATION_RATE)
		{
			next_generation(matrix, MATRIX_SIZE);
			cout << "Generation " << gen_count << ": >" << endl;
			game_ticks = SDL_GetTicks();
		}
	}

	cout << "Thanks for playing." << endl;

	close_window();

	return 0;
}

void display_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int size) {

	SDL_SetWindowTitle(window, title);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White backgrond
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black matrix lines

	for (int x = 0; x < size; x++)
		SDL_RenderDrawLine(renderer, CELL_SIZE * x, 0, CELL_SIZE * x, SCREEN_SIZE);

	for (int x = 0; x < size; x++)
		SDL_RenderDrawLine(renderer, 0, CELL_SIZE * x, SCREEN_SIZE, CELL_SIZE * x);

	SDL_SetRenderDrawColor(renderer, 0, 103, 71, SDL_ALPHA_OPAQUE); // fill squares with USF green

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (matrix[x][y] == ALIVE)
			{
				SDL_Rect rect;

				rect.x = x * CELL_SIZE; // x position of upper left corner
				rect.y = y * CELL_SIZE; // y position of upper left corner
				rect.w = CELL_SIZE;		// width
				rect.h = CELL_SIZE;		// height

				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

bool initialize_window() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return false;

	if (SDL_CreateWindowAndRenderer(SCREEN_SIZE, SCREEN_SIZE, 0, &window, &renderer) != 0)
		return false;

	return true;
}

void close_window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

void next_generation(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s) {

	int neighbors[MATRIX_SIZE][MATRIX_SIZE];

	// count number of live neighbors for each cell
	for (int x = 0; x < s; x++)
		for (int y = 0; y < s; y++)
			neighbors[x][y] = get_live_neighbors(matrix, s, x, y);

	for (int x = 0; x < s; x++)
		for (int y = 0; y < s; y++)
		{
			int num_neighbors = neighbors[x][y];
			update_cell(matrix, s, x, y, num_neighbors);
		}

	gen_count++;
}

void handle_event(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s){

	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
			// User pressed X
			case SDL_QUIT:
			{
				user_has_quit = true;
				break;
			}

			// Mouse clicks
			case SDL_MOUSEBUTTONDOWN:
			{
				// Left mouse button sets live cell
				if (event.button.button == SDL_BUTTON_LEFT)
					set_cell(matrix, s, event.button.x / CELL_SIZE, event.button.y / CELL_SIZE, ALIVE);

				// Right button generates cell finite automaton
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					cout << "Generating the finite automaton for the selected cell..." << endl;
					int status = matrix[event.button.x / CELL_SIZE][event.button.y / CELL_SIZE];
					int live_neighbors = get_live_neighbors(matrix, MATRIX_SIZE, event.button.x / CELL_SIZE, event.button.y / CELL_SIZE);

					string input_string = generate_string(status, live_neighbors);

					FiniteAutomaton *FA = new FiniteAutomaton(input_string);

					State *p = FA->predictNextState();

					if (status == 1)
					{
						if (p->isAlive())
							cout << "The selected cell will remain ALIVE in the next generation" << endl;
						else
							cout << "The selected cell will be DEAD in the next generation" << endl;
					}
					
					else if (status == 0)
					{
						if (p->isAlive())
							cout << "The selected cell will be ALIVE in the next generation" << endl;
						else
							cout << "The selected cell will remain DEAD in the next generaiton" << endl;
					}

					cout << "\n" << endl;
				}

				// Middle button kills cell
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					set_cell(matrix, s, event.button.x / CELL_SIZE, event.button.y / CELL_SIZE, DEAD);

				break;
			}

			case SDL_KEYDOWN:
			{
				// Spacebar toggles animation play
				if (event.key.keysym.sym == SDLK_SPACE)
					is_animating = !is_animating;

				// E key ends simulation
				else if (event.key.keysym.sym == SDLK_e)
				{
					for (int x = 0; x < MATRIX_SIZE; x++)
						for (int y = 0; y < MATRIX_SIZE; y++)
							matrix[x][y] = DEAD;

					gen_count = 0;
					is_animating = false;
				}
			}
		}
	}
}

string generate_string(int status, int neighbors) {
	string str;
	int binary = 0;
	int i = 1;
	
	while (neighbors != 0)
	{
		binary = binary + (neighbors % 2) * i;
		neighbors = neighbors / 2;
		i = i * 10;
	}

	str = to_string(binary);

	if (str.length() < 5)
	{
		while (str.length() != 4)
			str = "0" + str;
	}

	if (status == 0)
		str = "0" + str;
	else
		str = "1" + str;
		
	return str;
}

/* CELL FUNCTION IMPLEMENTATIONS */
int get_live_neighbors(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y) {
	int count = 0;

	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (i >= 0 && i < s)
				if (j >= 0 && j < s)
					if (matrix[i][j] == ALIVE)
						count++;

	if (matrix[x][y] != DEAD)
		count--;

	return count;
}

void update_cell(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y, int neighbors) {
	
	// Cells die of starvation
	if (neighbors > OVERPOPULATION_VAL)
		matrix[x][y] = DEAD;

	// Cells die of lonliness
	else if (neighbors < UNDERPOPULATION_VAL)
		matrix[x][y] = DEAD;

	// Cells reproduce
	else if (neighbors == REPRODUCTION_VAL)
		matrix[x][y] = ALIVE;
}

void set_cell(int matrix[MATRIX_SIZE][MATRIX_SIZE], int s, int x, int y, int status) {

	if (x >= 0 && x < s)
		if (y >= 0 && y < s)
			matrix[x][y] = status;
}
