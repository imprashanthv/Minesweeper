#include "Minesweeper.h"
int Board::getNeighboringMines(int row, int col){
	int neighborMines = 0;

			//middle
			if(row!=0 && col!=0 && row!=len-1 && col!=width-1){
				if(board[row-1][col-1]=='*') neighborMines++;
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col+1]=='*') neighborMines++;
				
				if(board[row][col-1]=='*') neighborMines++;
				if(board[row][col+1]=='*') neighborMines++;
				
				if(board[row+1][col-1]=='*') neighborMines++;
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col+1]=='*') neighborMines++;
				
			}
			
			//left upper corner
			if(row==0&&col==0){
				if(board[row][col+1]=='*') neighborMines++;
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col+1]=='*') neighborMines++;
				
			}
			
			//right upper corner
			if(row==0&&col==width-1){
				if(board[row][col-1]=='*') neighborMines++;
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col-1]=='*') neighborMines++;
				
				
			}
			
			//left lower corner
			if(row==len-1&&col==0){
				if(board[row][col+1]=='*') neighborMines++;
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col+1]=='*') neighborMines++;
				
			}
			
			//right lower corner
			if(row==len-1&&col==width-1){
				if(board[row][col-1]=='*') neighborMines++;
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col-1]=='*') neighborMines++;
				
				
			}
			
			//top row except corners
			if(row==0 && (col!=0 && col!=width-1)){
				if(board[row][col-1]=='*') neighborMines++;
				if(board[row][col+1]=='*') neighborMines++;
				
				if(board[row+1][col-1]=='*') neighborMines++;
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col+1]=='*') neighborMines++;
				
			}
			
			//bottom row except corners
			if(row==len-1 && (col!=0 && col!=width-1)){
				if(board[row-1][col-1]=='*') neighborMines++;
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col+1]=='*') neighborMines++;
				
				if(board[row][col-1]=='*') neighborMines++;
				if(board[row][col+1]=='*') neighborMines++;
				
				
				
				
				
			}
			
			//left most column except corners
			if(col==0 && (row!=0 && row!=len-1)){
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col+1]=='*') neighborMines++;
				
				if(board[row][col+1]=='*') neighborMines++;
				
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col+1]=='*') neighborMines++;
				
				
			}
			
			//right most column except corners
			if(col==width-1 && (row!=0 && row!=len-1)){
				if(board[row-1][col]=='*') neighborMines++;
				if(board[row-1][col-1]=='*') neighborMines++;
				
				if(board[row][col-1]=='*') neighborMines++;
				
				if(board[row+1][col]=='*') neighborMines++;
				if(board[row+1][col-1]=='*') neighborMines++;
				
				
			}


	return neighborMines;
}
