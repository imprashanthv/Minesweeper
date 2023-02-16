#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Minesweeper.h"
#include "statisticsKeeper.h"
using namespace std;

#define max_delay 9

class Partition {
	Board* bp; 
	Partition *nextp;
	int playTime;
public:
	Partition(Board* bp, int playTime){
		this->bp = bp;
		this->nextp = NULL;
		this->playTime = playTime;
	}
	Partition(Board* bp, Partition *nextp, int playTime){
		this->bp = bp;
		this->nextp = nextp;
		this->playTime = playTime;
	}
	int getPlayTime(){
		return this->playTime;
	}
	Board* getBoard(){
		return this->bp;
	}
	Partition* getNextP(){
		return this->nextp;
	}
	void setNextP(Partition* nextp){
		this->nextp = nextp;
	}
	tuple<int, string> play(){
		tuple<int, string> game_result;
		if(this){
			game_result = this->bp->play(playTime);
			return game_result;
		}
		game_result = {0, "0"};
		return game_result;
	}
};

class TimingWheel {
private: 
	Partition * slot[max_delay + 1]; 
	int current_slot;
public:
	TimingWheel(){
		current_slot = 0;
		for(int i=0;i<max_delay+1;i++){
			slot[i] = NULL;
		}
	}
	void insert(int play_time, Board* p1){
		//p1->test();
		if(slot[play_time%max_delay+1] == NULL){
			slot[play_time%max_delay+1] = new Partition(p1, play_time);
		}
		else{
			//iterate until we find null;
			Partition *cpt = slot[play_time%max_delay+1];
			while (cpt->getNextP() != NULL){
				cpt = cpt->getNextP();
			}
			cpt->setNextP(new Partition(p1, play_time));
		}
	}
	
	void schedule(vector<unique_ptr<Board>>& boards){
		int total_games = boards.size();
		int games_completed = 0;
		tuple<int, string> game_result; 
		StatisticsKeeper stats;
		srand(time(NULL));
		
		for(int i=0; i<boards.size(); i++){
			int play_time = rand()%3+1;
			Board *bp = dynamic_cast<Board*>(boards[i].get());
			insert(play_time, bp);
		}
		while(games_completed != total_games){
			game_result = slot[current_slot%max_delay+1]->play();
			//cout<<get<0>(game_result)<<endl;
			//cout<<get<1>(game_result)<<endl;
			if(get<1>(game_result)=="0"){
				current_slot++;
			}
			if(get<1>(game_result) != ""){
				Partition* cp = slot[current_slot%max_delay+1]->getNextP();
				clear_curr_slot();
				slot[current_slot%max_delay+1]=cp;
				games_completed++;
				stats.setGameNumber(games_completed);
				stats.setStepsTaken(get<0>(game_result));
				stats.setWinStatus(get<1>(game_result));
			}
			else if(slot[current_slot%max_delay+1]->getNextP() != NULL){
				Partition* curr = slot[current_slot%max_delay+1];
				Partition* cp = slot[current_slot%max_delay+1]->getNextP();
				clear_curr_slot();
				slot[current_slot%max_delay+1]=cp;
				curr->setNextP(NULL);
				insert(curr->getPlayTime(), curr->getBoard());
			}
			else{
				current_slot++; 
			}
		}
		ofstream out;
		cout<<stats;
		out<<stats;
		
	}
	
	void clear_curr_slot(){
		slot[current_slot%max_delay+1] = NULL;
	}
};