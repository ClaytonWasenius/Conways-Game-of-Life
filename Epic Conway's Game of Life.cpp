#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>

using namespace std; 

struct coordinates{
	
	int x;
	int y; 
	
}; 
struct neighbors{
	
	bool up; 
	bool down; 
	bool left;
	bool right; 
	bool upright;
	bool downright;
	bool upleft; 
	bool downleft; 
	
}; 
struct Cell{
	
	bool active; 
	bool activated; 
	coordinates coordinates; 
	neighbors neighbors; 
	
}; 

void updateInitialSubGrid(vector<vector<Cell> >&, int, int); 
void printGridInitial(void); 
void initializeInitialGrid(vector<vector<Cell> >&); 
void emergeGrid(vector<vector<Cell> >&, vector<vector<Cell> >&); 
int checkNeighbors(vector<vector<Cell> >&, int, int); 
void printGridProcess(vector<vector<Cell> >&); 
void updateFinalGrid(vector<vector<Cell> >&); 	
void activateOrDeactive(vector<vector<int> >&, vector<vector<Cell> >&, int, int); 
void finalActivate(vector<vector<Cell> >&); 

Cell genericCell; 

int main() {

	int x = 0, y = 0; 
	
	//100 by 100 cells
	vector<vector<Cell> > cellMap(100, vector<Cell>(100, genericCell));
	int speed = 0; 
	
	initializeInitialGrid(cellMap);

	
	cout << "Welcome to the Conway's Game of Life demonstration! (Make sure to enlarge the text on your screen beforehand.)" << endl << endl; 
	
	cout << "To begin, enter in the coordinates below using sub-grid and key. " << endl;
	
	
	
	printGridInitial(); 
	cout << endl;
	
	cout << "Row: "; 
	cin >> x; 
	cout << "Column: "; 
	cin >> y; 
	
	while((x < 1 || x > 20 ) || (y < 1 || y > 20)){
		
		cout << "Invalid coordinates... Please try again\n" << endl; 
		cout << "Row: "; 
		cin >> x; 
		cout << "Column: "; 
		cin >> y; 
	}
	cout << endl; 
	
	cellMap[x - 1][y - 1].coordinates.x = x; 
	cellMap[x - 1][y - 1].coordinates.y = y; 
	cellMap[x - 1][y - 1].active = true; 
	cellMap[x - 1][y - 1].activated = false; 
	
	updateInitialSubGrid(cellMap, x, y); 

		
		cout << "Great job, keeping adding! \n"; 
		
		cout << "Row: "; 
		cin >> x; 
		cout << "Column: "; 
		cin >> y; 
		
		while((x < 1 || x > 20 ) || (y < 1 || y > 20)){
			
			cout << "Invalid coordinates... Please try again\n" << endl; 
			cout << "Row: "; 
			cin >> x; 
			cout << "Column: "; 
			cin >> y; 
			
		}
		
		cellMap[x - 1][y - 1].coordinates.x = x; 
		cellMap[x - 1][y - 1].coordinates.y = y; 
		cellMap[x - 1][y - 1].active = true; 
		cellMap[x - 1][y - 1].activated = false; 
		
		updateInitialSubGrid(cellMap, x, y); 
	
		
		cout << "Continue adding as many as you would like, enter -10 for either row or column to start the game!\n" << endl; 
		do{ 
			
			cout << "Row: "; 
			cin >> x; 
			cout << "Column: "; 
			cin >> y; 
			
		    if(x == -10 || y == -10){
		   	     break; 
			}else{
			
		      	while((x < 1 || x > 20 ) || (y < 1 || y > 20)){
				
					if(x == -10 || y == -10){
						break; 
				    }else{
						cout << "Invalid coordinates... Please try again\n" << endl; 
						cout << "Row: "; 
						cin >> x; 
						cout << "Column: "; 
						cin >> y; 
				    }
			   }
				cellMap[x - 1][y - 1].coordinates.x = x; 
				cellMap[x - 1][y - 1].coordinates.y = y; 
				cellMap[x - 1][y - 1].active = true; 
				cellMap[x - 1][y - 1].activated = false; 
		   }
			
		updateInitialSubGrid(cellMap, x, y); 
		
	}while(x != -10 && y != -10);
	
	vector<vector<Cell> > enlargedCellMap(100, vector<Cell>(100, genericCell)); 
	initializeInitialGrid(enlargedCellMap); 
	
	cout << "Emerging Grid...."; 
	emergeGrid(cellMap, enlargedCellMap); 
	
	cout << "\nLife Cycles Beginning in...." << endl; 
	usleep(800000); 
	cout << "3...." << endl;
	usleep(800000); 
	cout << "2...." << endl;
	usleep(800000); 
	cout << "1...." << endl;
	
	

	while(1){
		
		usleep(200000); 
		updateFinalGrid(enlargedCellMap); 
	}
	

return 0; 
}
void updateInitialSubGrid(vector<vector<Cell> >& cellGrid, int x, int y){
	
		cout << endl;
		
		cout << "Key: \n|Row, Column| = |  x, y  |" << endl << endl;; 
		
		cout << "                 ------------------ SubGrid -------------------" << endl; 
		
		for(int i = 0; i < 20; i++){
			
			cout << endl; 
			
			for(int j = 0; j < 20; j++){
				
				if(cellGrid[i][j].activated == true){
					
					cout << "|&&&&&&&&|"; 
					
				}else if(cellGrid[i][j].activated == false && cellGrid[i][j].coordinates.x == x && cellGrid[i][j].coordinates.y == y){
					
					cout << "|&&&&&&&&|"; 
					cellGrid[i][j].activated = true; 
					
				}else{
		
					if(i < 9 && j < 9){
						cout << "|  " << i+1 << ", " << j+1 << "  |";
					}else if(i >= 9 && j < 9){
						cout << "| " << i+1 << ", " << j+1 << "  |";
					}else if(i < 9 && j >= 9){
						
						cout << "|  " << i+1 << ", " << j+1 << " |";
						
					}else{
						cout << "| " << i+1 << ", " << j+1 << " |";

						
					}
				
				}
			
			}
				
		}
	cout << endl; 
}
void printGridInitial(){
	
	for(int i = 0; i < 20; i++){
		
		cout << endl;
		
		for(int j = 0; j < 20; j++){
			
			if(i < 9 && j < 9){
				cout << "|  " << i+1 << ", " << j+1 << "  |";
			}else if(i >= 9 && j < 9){
				cout << "| " << i+1 << ", " << j+1 << "  |";
			}else if(i < 9 && j >= 9){
				
				cout << "|  " << i+1 << ", " << j+1 << " |";
				
			}else{
				cout << "| " << i+1 << ", " << j+1 << " |";
				
				
			}
				
			}
		}
	
	cout << endl; 
}
int checkNeighbors(vector<vector<Cell> >& cellGrid, int i, int j){ //this is correct 
	
	int neighbors = 0; 
	
	if(i > 0 && i < 50 && j > 0 && j < 50){
		
		if(cellGrid[i-1][j].activated == true){
			cellGrid[i][j].neighbors.up = true; 
			neighbors++; 
			
		}
		if(cellGrid[i][j-1].activated == true){
			cellGrid[i][j].neighbors.left = true; 
			neighbors++; 
			
		}
		if(cellGrid[i][j+1].activated == true){
			cellGrid[i][j].neighbors.right = true; 
			neighbors++; 
			
		}
		if(cellGrid[i+1][j].activated == true){
			cellGrid[i][j].neighbors.down = true; 
			neighbors++; 
			
		}
		if(cellGrid[i-1][j-1].activated == true){
			cellGrid[i][j].neighbors.upleft = true; 
			neighbors++; 
			
		}
		if(cellGrid[i-1][j+1].activated == true){
			cellGrid[i][j].neighbors.upright = true; 
			neighbors++; 
			
		}
		if(cellGrid[i+1][j-1].activated == true){
			cellGrid[i][j].neighbors.downleft = true; 
			neighbors++; 
			
		}
		if(cellGrid[i+1][j+1].activated == true){
			cellGrid[i][j].neighbors.downright = true; 
			neighbors++; 
			
		}
	}
		
	return neighbors; 
}
void initializeInitialGrid(vector<vector<Cell> >& cellGrid){ 

	for(int i = 0; i < 100; i++){
		
		for(int j = 0; j < 100; j++){
			
			cellGrid[i][j].active = false; 
			cellGrid[i][j].activated = false; 
			
			cellGrid[i][j].neighbors.up = false; 
			cellGrid[i][j].neighbors.down = false; 
			cellGrid[i][j].neighbors.left = false; 
			cellGrid[i][j].neighbors.right = false; 
			cellGrid[i][j].neighbors.upright = false; 
			cellGrid[i][j].neighbors.upleft = false; 
			cellGrid[i][j].neighbors.downright = false; 
			cellGrid[i][j].neighbors.downleft = false; 
			
			cellGrid[i][j].coordinates.x = -10; 
			cellGrid[i][j].coordinates.y = -10; 
			
		}
	}
}
void emergeGrid(vector<vector<Cell> >& initialGrid, vector<vector<Cell> >& finalGrid){ //this is giong 
	
	for(int i = 0; i < 20; i++){
		
		for(int j = 0; j < 20; j++){
			
			finalGrid[i + 14][j + 14] = initialGrid[i][j]; 
			
		}
	}
	printGridProcess(finalGrid); 
}
void printGridProcess(vector<vector<Cell> >& finalGrid){
	
	for(int i = 0; i < 56; i++){
		
		cout << endl; 
		
		for(int j = 0; j < 56; j++){
			
			if(finalGrid[i][j].activated == true && finalGrid[i][j].active == true){
				
				cout << "|&&|"; 
				
			}else{
				
				cout << "|  |"; 
				
			}
		}
	}
}
void updateFinalGrid(vector<vector<Cell> >& finalGrid){ 

	vector<vector<int> > numberOfNeighbors(100, vector<int>(100, 0));
	for(int i = 0; i < 50; i++){
		
		
		for(int j = 0; j < 50; j++){
			
			numberOfNeighbors[i][j] = checkNeighbors(finalGrid, i, j); 
			activateOrDeactive(numberOfNeighbors, finalGrid, i, j); 
			
		}
	}
	
	cout << endl << endl << endl;
	finalActivate(finalGrid); 
	printGridProcess(finalGrid); 
	
}
void activateOrDeactive(vector<vector<int> >& numberOfNeighbors, vector<vector<Cell> >& finalGrid, int i, int j){
		
		if(finalGrid[i][j].activated == true && (numberOfNeighbors[i][j] > 3 || numberOfNeighbors[i][j] < 2)){ //turn nodes off either by overpopulation or underpopulation 
			finalGrid[i][j].activated = true; 
			finalGrid[i][j].active = false; //deactivate 
				
		}else if(numberOfNeighbors[i][j] == 3 && finalGrid[i][j].activated == false){ //turns a dead one, into an alive one by reproduction 
			finalGrid[i][j].activated = false; 
			finalGrid[i][j].active = true; 
		}
	
} 
void finalActivate(vector<vector<Cell> >& finalGrid){
	
	for(int i = 0; i < 50; i++){
		
		for(int j = 0; j < 50; j++){
			
			if(finalGrid[i][j].active == true){
				
				finalGrid[i][j].activated = true; 
				
			}else if(finalGrid[i][j].active == false){
				
				finalGrid[i][j].activated = false; 
				
			}
		}
	}
}