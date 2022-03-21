# 🔢 Sudoku solver 🔎

## Presentation

Automatic sudoku solver.

It features the ability to input your own sudoku, play it or 
let the program solve it for you. 
The program can also tell you if the grid is solvable or not.

⚠️ While being in a working state, 
it is still very rough and pretty much a WIP. ⚠️

## Controls

You can click on a box and input a number from 1 to 9 in it.

By pressing the `F` key, you set the current grid as the starting grid. 
It means that the game will fallback to this grid if you decide to reset.

By pressing the `A` key, the auto-solver will fill a square with 
the only possible solution given the current grid.
(If the grid is not deterministic i.e. there is no square with only 
one possible number remaining, it does nothing)

## Requirements

The program uses C++ and Qt5 for the rendering.

## Author

Project done by Reallnas [(github link)](https://github.com/Reallnas) in 2021.
