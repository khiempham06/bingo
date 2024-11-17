#ifndef BINGO_H_INCLUDED
#define BINGO_H_INCLUDED
#include <utility>
#include <iostream>

using namespace std;

class Matrix
{
protected:
    int n;
    int grid[11][11];

public:
    Matrix(int _n): n{_n} {
    }

    void display() const;
    bool select(int _n);
    bool win() const;
    void init(int l, int r);
};

class Machine: public Matrix
{
private:
    struct pointw
    {
        int x, y, w;
    };

    pair<int, int> bfs(pair<int, int> point, pair<int, int> dxy) const;
    pointw movee() const;
public:
    Machine(int _n): Matrix{_n} {
    }
    int choose() const;
};

class Player: public Matrix
{
public:
    Player(int _n): Matrix{_n} {
    }
    void input_matrix();
};

class Bingo {
private:
    Machine machine;
    Player player;
    int n;
public:
    Bingo(int _n): n(_n), machine{_n}, player{_n} {
        player.input_matrix();
        machine.init(1, n * n);
    }

    void play();
};

#endif // BINGO_H_INCLUDED
