#include "Minesweeper.h"

/*				Board Class 			*/
Board::Board(int len, int width, int n_mines){
	this->len = len;
	this->width = width;
	this->num_of_mines = n_mines;
	
	//create mines array
	board = new char* [len];
	for(int i=0; i<len; i++){
		board[i] = new char[width];
	}
	
	for(int i=0; i<len; i++){
		for(int j=0; j<width; j++){
			board[i][j] = '.';
		}
	}
	
	
	//set the type:
	switch(num_of_mines){
		case 10:
			type = "Beginner";
			break;
		case 40:
			type = "Intermediate";
			break;
		case 99:
			type = "Expert";
			break;
		default:
			type = "Custom";
			break;
	}
}


int Board::getlen(){
	return len;
}
int Board::getwidth(){
	return width;
}

int Board::getmines(){
	return num_of_mines;
}



void Board::generateMines(){
	//select n_mines random locations
	set<int> row_set;
	set<int> col_set;
	int row;
	int col;
	int inserted = 0;
	
	while(inserted != num_of_mines){
		row = -1;
		col = -1;
		//if (while) row not in row_set
		while(row_set.find(row)==row_set.end()){
			//get a random row
			row = rand()%len+0;
			
			//duplicates are not inserted in set.
			//insert it.
			row_set.insert(row);
			
			//loop breaks when it can find
		}
		
		
		
		//similarly select a column
		while(col_set.find(col)==col_set.end()){
			col = rand()%width+0;
			col_set.insert(col);
		}
		
		
		//add to mines array
		if(board[row][col] != '*'){
			board[row][col] = '*';
			inserted++;
		}
		//loop
	}
	
}

void Board::display_board(){
	if(is_playing){
		for(int i=0; i<getlen(); i++){
			cout<<i<<"\t";
			for(int j=0; j<getwidth(); j++){
				if(board[i][j]=='*'){
					cout<<'.';
				}
				else{
					cout<<board[i][j];
				}
			}
			cout<<endl;
		}
	}
	else{
		for(int i=0; i<getlen(); i++){
			for(int j=0; j<getwidth(); j++){
				cout<<board[i][j];
			}
			cout<<endl;
		}
	}
}


void Board::ready(){
	is_playing = true;
	string dummy;
	cout<<endl;
	
	cout<<"Your "<<type<<" type board is ready."<<endl;
	cout<<"Press return/enter key to start playing";
	cin.ignore();
}

bool Board::has_lost(int row, int col){
	return board[row][col] == '*';
}



tuple<int, string> Board::play(int playTime ){
	
	int row;
	int col;
	int opened=0;
	int time_keeper = 0;
	
	if(steps_taken==0){
		ready();
	}
	else{
		cout<<"Welcome back!"<<endl;
		cout<<"Picking up where we left off"<<endl;
	}
	cout<<"Your playTime is "<<playTime<<endl;
	cout<<endl;
	
	bool no_timingWheel = (playTime == 0);

	while( (is_playing && time_keeper != playTime) || (is_playing && no_timingWheel)){
		time_keeper++;
		this->display_board();
		cout<<"Select your row and column"<<endl;
		cout<<"Row # ";
		
		//assuming user input is always valid
		cin>>row;
		
		cout<<"Col # ";
		cin>>col;
		
		steps_taken++;
		
		if(has_lost(row, col)){
			cout<<"You lost"<<endl;
			is_playing = !is_playing;
			display_board();
			status = "Lost";
		}
		else{
			string nm = to_string(getNeighboringMines(row, col));
			board[row][col] = nm[0];
			opened++;
			if(opened == len*width-num_of_mines){
				is_playing = !is_playing;
				display_board();
				cout<<"You have won!";
				status = "Won";
			}
		}
	}
	
	if(time_keeper==playTime){
		display_board();
		cout<<"Your play time completed!"<<endl;
	}
	return make_tuple(steps_taken, status);
}

Beginner::Beginner():Board(9,9, 10){};

	
void Beginner::display_board(){
	//cout<<"This is a beginner board with"<<getlen()<<"x"<<getwidth()<< " cells and "<<getmines()<< " mines";
	cout<<endl;
	Board::display_board();
}

Intermediate::Intermediate():Board(16,16, 40){};

void Intermediate::display_board(){
	//cout<<"This is an intermediate board with"<<getlen()<<"x"<<getwidth()<< " cells and "<<getmines()<< " mines";
	cout<<endl;
	Board::display_board();
}

Expert::Expert():Board(16,30, 99){};

void Expert::display_board(){
	//cout<<"This is an expert board with"<<getlen()<<"x"<<getwidth()<< " cells and "<<getmines()<< " mines";
	cout<<endl;
	Board::display_board();
}

/*				GameGenerator Class 			*/

GameGenerator::GameGenerator(ifstream& in, string filename){
	in.open(filename);
	in>>n_games;
	in>>beg_percent;
	in>>int_percent;
	in>>exp_percent;
}

vector<unique_ptr<Board>> GameGenerator::generateGames(){
	string dummy;
	
	vector<unique_ptr<Board>> bp;
	srand(time(NULL));
	int b=0, intr=0, e=0;
	for(int i=0; i<n_games; i++){
		float r = rand() % 100+1;
		r/=100;
		
		if(r<=beg_percent){
			bp.emplace_back(new Beginner());
			b++;
		}
		else if(r<=int_percent){
			bp.emplace_back(new Intermediate());
			intr++;
		}
		else{
			bp.emplace_back(new Expert());
			e++;
		}
	}
	
	cout<<"You will be playing:"<<endl;
	cout<<" "<<b<<" Beginner boards"<<endl;
	cout<<" "<<intr<<" Intermediate boards and"<<endl;
	cout<<" "<<e<<" Expert boards"<<endl;
	cout<<endl;
	cout<<"Ready? Tap return/enter key to continue.";
	cin.ignore();
	return bp;
}