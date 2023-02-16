#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class StatisticsKeeper{
private:
	vector<int> game_num;
	vector<int> steps_taken;
	vector<string> win_status;
public:
	void setGameNumber(int n){
		game_num.push_back(n);
	}
	
	void setStepsTaken(int n){
		steps_taken.push_back(n);
	}
	
	void setWinStatus(string n){
		win_status.push_back(n);
	}
	
	int getGameNumber(int n){
		return game_num[n];
	}
	
	int getStepsTaken(int n){
		return steps_taken[n];
	}
	
	string getWinStatus(int n){
		return win_status[n];
	}
	
	void displayResults(){
		cout<<"GameNumber"<<setw(18)<<"Steps Taken"<<setw(18)<<"Won/Lost"<<endl;
		for(int i=0;i<game_num.size();i++){
			cout<<game_num[i]<<setw(17)<<steps_taken[i]<<setw(24)<<win_status[i]<<endl;
		}
	}
	
	void writeResultsToFile(string filename){
		ofstream out;
		out.open(filename);
		out<<"GameNumber"<<setw(18)<<"Steps Taken"<<setw(18)<<"Won/Lost"<<endl;
		for(int i=0;i<game_num.size();i++){
			out<<game_num[i]<<setw(17)<<steps_taken[i]<<setw(24)<<win_status[i]<<endl;
		}
		cout<<"File write complete. Results available in "<<filename<<endl;
	}
	
	friend ofstream& operator<<(ofstream& out, StatisticsKeeper& s){
		out<<"Your games summary!"<<endl;
		out.open("finalResults.txt");
		out<<"GameNumber"<<setw(18)<<"Steps Taken"<<setw(18)<<"Won/Lost"<<endl;
		for(int i=0;i<s.game_num.size();i++){
			out<<s.game_num[i]<<setw(18)<<s.steps_taken[i]<<setw(24)<<s.win_status[i]<<endl;
		}
		cout<<endl<<"File write complete. Results available in "<<"finalResults.txt"<<endl;
		return out;
	}
	
	friend ostream& operator<<(ostream& out, StatisticsKeeper& s){
		cout<<"Your games summary!"<<endl;
		cout<<"GameNumber"<<setw(18)<<"Steps Taken"<<setw(18)<<"Won/Lost"<<endl;
		for(int i=0;i<s.game_num.size();i++){
			cout<<s.game_num[i]<<setw(18)<<s.steps_taken[i]<<setw(24)<<s.win_status[i]<<endl;
		}
		return out;
	}
};