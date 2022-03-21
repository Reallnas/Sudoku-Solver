#include "sudoku.h"

#include <iostream>

Sudoku::Sudoku(const std::array<std::array<int,9>,9>& grid)
{
    if(isInputValid(grid))
    {
        m_grid = grid;
        m_initial_grid = grid;
    }
    else
        throw "Non valid data";
}

int Sudoku::getField(int x, int y)
{
    return m_grid[x][y];
}

void Sudoku::setField(int x, int y, int value)
{
    m_grid[x][y] = value;
}

std::array<int,9> Sudoku::getColumn(int x)
{
    return m_grid[x];
}

std::array<int,9> Sudoku::getLine(int y)
{
    std::array<int,9> line = {};
    for(int i = 0;i<9;i++)
    {
        line[i] = m_grid[i][y];
    }
    return line;
}

std::array<int,9> Sudoku::getSquare(int x,int y)
{
    std::array<int,9> square = {};
    const int square_x = x / 3;
    const int square_y = y / 3;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
            square[i*3 + j] = m_grid[3*square_x + i][3*square_y +j];
    }
    return square;
}

void Sudoku::reset()
{
    m_grid = m_initial_grid;
}

bool Sudoku::isColumnValid(int x)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<9;i++)
    {
        validity[m_grid[x][i]] = true;
    }
    for(int i = 1;i<10;i++)
    {
        if(!validity[i])
            return false;
    }
    return true;
}

bool Sudoku::isLineValid(int y)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<9;i++)
    {
        validity[m_grid[i][y]] = true;
    }
    for(int i = 1;i<10;i++)
    {
        if(!validity[i])
            return false;
    }
    return true;
}
bool Sudoku::isSquareValid(int sx,int sy)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            validity[m_grid[3*sx + i][3*sy + j]] = true;
        }
    }
    for(int i = 1;i<10;i++)
    {
        if(!validity[i])
            return false;
    }
    return true;
}

bool Sudoku::isSolved()
{
    for(int i = 0;i<9;i++)
    {
        if(!isLineValid(i))
            return false;
        if(!isColumnValid(i))
            return false;

        const int sx = i%3;
        const int sy = i/3;
        if(!isSquareValid(sx,sy))
            return false;
    }
    return true;
}

bool Sudoku::isColumnSolvable(int x)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<9;i++)
    {
        if(m_grid[x][i] != 0 && validity[m_grid[x][i]])
            return false;
        else
            validity[m_grid[x][i]] = true;
    }
    return true;
}

bool Sudoku::isLineSolvable(int y)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<9;i++)
    {
        if(m_grid[i][y] != 0 && validity[m_grid[i][y]])
            return false;
        else
            validity[m_grid[i][y]] = true;
    }
    return true;
}

bool Sudoku::isSquareSolvable(int sx, int sy)
{
    std::array<bool,10> validity {};
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            if(m_grid[3*sx + i][3*sy + j] != 0 && validity[m_grid[3*sx + i][3*sy + j]])
                return false;
            else
                validity[m_grid[3*sx + i][3*sy + j]] = true;
        }
    }
    return true;
}

bool Sudoku::isSolvable()
{
    for(int i = 0;i<9;i++)
    {
        //std::cout << "Ligne " << i << ": " << isLineSolvable(i) << std::endl;
        if(!isLineSolvable(i))
            return false;
        //std::cout << "Colonne " << i << ": " << isColumnSolvable(i) << std::endl;
        if(!isColumnSolvable(i))
            return false;

        const int sx = i%3;
        const int sy = i/3;
        //std::cout << "Carre " << i << ": " << isSquareSolvable(sx,sy) << std::endl;
        if(!isSquareSolvable(sx,sy))
            return false;
    }
    return true;
}

bool Sudoku::isFieldSet(int x, int y)
{
    return  m_grid[x][y] != 0;
}

bool Sudoku::isInputValid(const std::array<std::array<int,9>,9>& grid)
{
    for(int x = 0;x<9;x++)
    {
        for(int y = 0;y<9;y++)
        {
            if(grid[x][y] < 0 || grid[x][y]>9)
                return false;
        }
    }
    return true;
}

void Sudoku::setCurrentGridAsInitial()
{
    m_initial_grid = m_grid;
}

void Sudoku::clear()
{
    m_grid = {};
    m_initial_grid = {};
}

