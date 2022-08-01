# GameOfLifeSimulator
<b>C++</b> Implementation of Conway's Game of Life using SDL2 <br><br>
This was a Final Project I completed in Fall of 2020 for an elective CS course titled Automata Theory. 
<br/>

<hr>
<p><b> Table of Contents </b></p>

[Background](https://github.com/ashleyjmaximilien/GameOfLifeSimulator/#Background)<br>
[Installation](https://github.com/ashleyjmaximilien/GameOfLifeSimulator/#Installation)</br>
[Usage](https://github.com/ashleyjmaximilien/GameOfLifeSimulator/#Usage)

<h2>Background</h2>
<p><i>"Conway's Game of Life"</i>, or more simply <i>"Life"</i>, is a cellular automaton created by mathematician John Horton Conway. <i>Life</i> occurs in an infinite 
two-dimensional grid of squares or cells. At every step of a generation, each cell can exist in one of two possible states: alive or dead. The status and future of a 
particular cell depends on the eight neighbors that are vertically, horizontally, or diagonally adjacent to it. While <i>Life</i> automatically "plays" itself, it does require an initial state from which future generations are derived from. The <i>Game of Life</i> is Turing Complete, meaning it can compute anything that can be computed algorithmically. This is largely due to the following set of rules which determine the status of a cell in the next generation.</p>


```
• A live cell with less than two live neighbors will die (underpopulation).

• A live cell with two or three live neighbors will live in the next generation.

• A dead cell with exactly three live neighbors will become a live cell in the next generation (reproduction).

• A live cell with more than three live neighbors will die in the next generation (overpopulation).
```

The initial configuration of Life can result in a wide range of developments including ecosystems that quickly die out, ecosystems that remain in persistant or oscillating states, and ecosytems that would grow infinitely if memory constraints were nonexistent.
<br><br>

<h2>Installation</h2>

<p>You will need an IDE of your preference and a <b>C++</b> compiler installed on your machine.</p>

This project requires [SDL](https://www.libsdl.org/download-2.0.php/). You can install SDL on your system globally or setup SDL within the project directory using ```MinGW``` on Windows. Downloads and Installation for MinGw can be found [here](https://www.mingw-w64.org/downloads/).

Using SDL globally: 
> Download SDL (An in-depth installation guide [can be found here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).)
>
> Follow the installation instructions for your machine's operating system and IDE
>
> Download the GameOfLifeSimulator project files. If you downloaded the zip, extract the GameOfLifeSimulator folder to any location
>
> Using a terminal or IDE, navigate to the GameOfLifeSimulator folder
>
> Compile with: ```g++ -o sim *.cpp```
>
> Run with ```sim```
  
  
<br>

Set up SDL inside the project directory (requires ```MinGW``` and Windows OS):
> Download the GameOfLifeSimulator project files. If you downloaded the zip, extract the GameOfLifeSimulator folder to any location
>
> Inside the GameOfLifeSimulator folder, create a new folder called ```src```
>
> Download ```SDL2-devel-2.0.22-mingw.tar.gz (MinGW 32/64-bit)``` from [SDL's download page](https://www.libsdl.org/download-2.0.php/)
>
> Extract the folder from the tar.gz zip.
>
> Inside the SDL2 folder, open the ```i686-w64-mingw32``` folder
>
> Drag (or copy and paste) the ```include``` and ```lib``` folders into ```src```
>
> The bin folder and drag (or copy and paste) the file named ```SDL2.dll``` into the main GameOfLifeSimulator folder. 
>
> Compile with ```g++ -Isrc/Include -Lsrc/lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2```
>
> Run with ```sim```
<br>

<h2>Usage</h2>
<br>

<p>One the run command is entered, a GUI with a 12 x 12 grid will open. Remember that the <i>Game of Life</i> requires an initial state. Right click any number of cells to set them as alive for this initial state and then start the generation progression by pressing the spacebar. Below is a full description of controls for the simulator.</p>
<br>

| Control               | Function                                                                                                                                  |
| ----------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| Right Click           | Set cell's state to ```live```                                                                                                            |
| Left Click            | Generates cellular automaton for the cell clicked. The automaton uses the current state of the grid to predict the next state of the cell. The prediction appears in the console                                                                                                                               |
| Middle Click          | Set cell's state to ```dead```                                                                                                            |
| E key                 | Clears grid                                                                                                                               |
| Spacebar              | Start/Stop generation progression and animation                                                                                           |                                                                                           
