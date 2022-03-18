#include <iostream>
#include <string>
using namespace std;


int ctoi(char c){
	return c - '0';
}

int main(){
	//input
	int maze_size, peserta;
	string jalur;	
	cin >> maze_size;
	string maze[maze_size][maze_size];
	getline(cin >> ws, jalur);
	
	//process
	//rumus mencari ukuran array x dan y
	int jalur_size = jalur.length()/4 + 1;
	int x[jalur_size], y[jalur_size];
	int x_index = 0, y_index = 0;
	for(int i = 0; i < jalur.length(); i++){
		if(i == jalur.length()-1) y[y_index] = ctoi(jalur[i]);
		else if(i == 0) x[x_index++] = ctoi(jalur[i]);
		else{
			if(jalur[i-1] == ',') y[y_index++] = ctoi(jalur[i]);
			else if(jalur[i+1] == ',') x[x_index++] = ctoi(jalur[i]);
			else continue;
		}
	}
	
	//check
//	cout << jalur_size << endl;
//	for(int i = 0; i < jalur_size; i++){
//		cout << x[i] << ',' << y[i] << " ";
//	}
	//endcheck
	
	for(int i = 0; i < maze_size; i++){
		for(int j = 0; j < maze_size; j++){
			maze[i][j] = "[XX]";
		}
	}
	
	for(int i = 0; i < jalur_size; i++){
		maze[x[i]][y[i]] = "[OO]";
	}
	
	
	for(int i = maze_size-1; i >= 0  ; i--){
		for(int j = 0; j < maze_size; j++){
			cout << maze[j][i];
		}
		cout << endl;
	}	
}


