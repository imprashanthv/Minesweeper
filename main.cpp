#include <iostream>
#include <fstream>
#include <vector>

#include "Minesweeper.h"
#include "statisticsKeeper.h"
#include "timingWheel.h"
using namespace std;

int main(int argc, char *argv[]) {
	//Perfectly working game without timing wheel
	/*
	ifstream in;
	ofstream out;
	
	string filename = "input.txt";
	GameGenerator g(in, filename);
	vector<unique_ptr<Board>> bp = g.generateGames();
	StatisticsKeeper stats;
	
	tuple<int, string> game_result; 
	for(int i=0; i<bp.size(); i++){
		bp[i]->generateMines();
		game_result	= bp[i]->play(0);
		stats.setGameNumber(i+1);
		stats.setStepsTaken(get<0>(game_result)); //no. of steps taken
		stats.setWinStatus(get<1>(game_result)); //game status = win/lost
		cout<<endl;
	}
	
	stats.displayResults();
	out<<stats;
	*/
	
	//part-3 with timing wheel.
	
	ifstream in;
	ofstream out;
	
	string filename = "input.txt";
	GameGenerator g(in, filename);
	TimingWheel t;
	
	vector<unique_ptr<Board>> bp = g.generateGames();
	for(int i=0; i<bp.size(); i++){
		bp[i]->generateMines();
	}
	
	
	t.schedule(bp);

}