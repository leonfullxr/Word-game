# Word-game
This project is a basic word game, where there is a solver that gives the best possible word combination depending on the score each word has, therefore you can always check if your solution is correct.

## How to play
The objective is to form the best possible word (depending on one of the two criteria that we explain below) from a set of randomly drawn letters from a bag. For example, given the following letters:

O D Y R M E T

A good possible solution would be METRO. The number of letters played in each game is decided beforehand, and the available letters can be repeated. There are two game modes:
* **Length game**: In this game mode, only the length of the words is taken into account, and the longest word found wins.
* **Point game**: In this game mode, each letter is assigned a score, and the word's score will be equal to the sum of the scores of the letters that make it up.


### Execution
**Solver programm - partida_letras_eficiente.cpp**
> ./build/partida_letras_eficiente <dictionary> <letters> <L/P> <numLetters> 

For instance, an example of the execution of this programm is:

> ./build/partida_letras_eficiente data/diccionario.txt data/letras.txt L
9

AVAILABLE WORDS: D S N T D A I E N

SOLUTIONS:
dentina
entidad
sentina

SCORE:
7

## Instalation
Install and export the project, then open it on VSCode (or any other application) and open the terminal in the /$/estudiante/
