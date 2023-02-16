
#ifndef _Minesweeper_h_
#define _Minesweeper_h_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <set>
using namespace std;

class Board{
private:
	int len;
	int width;
	int num_of_mines;
	char** board;
	string type;
	int steps_taken = 0;
	string status="";
	
	bool is_playing = false;
public:
	//default constructor
	Board();
	
	//this constructor will be set by child classes.
	Board(int, int,int);
	
	void mark_open();
	bool is_mine();
	virtual void display_board();
	
	void ready();
	int getlen();
	int getwidth();
	int getmines();
	void generateMines();
	int getNeighboringMines(int row, int col);
	tuple<int, string> play(int);
	bool has_lost(int row, int col);
	friend ostream& operator<<(ostream&, const Board&);
	
};


class Beginner: public Board{
private:
	int n_opened;
public:
	Beginner();
	void display_board();
};

class Intermediate: public Board{
private:
	int n_opened;
public:
	Intermediate();
	void display_board();
};

class Expert: public Board{
private:
	int n_opened;
public:
	Expert();
	void display_board();
};


class GameGenerator{
private:
	int n_games;
	double beg_percent;
	double int_percent;
	double exp_percent;
public:
	GameGenerator(ifstream& in, string filename);
	vector<unique_ptr<Board>> generateGames();
};

#endif