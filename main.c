#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
#define QUEEN 2

int **createMatrix(){
	int **matrix = NULL;
	int i;

	matrix = (int **) malloc(sizeof(int *) * SIZE);

	for(i = 0; i < SIZE; i++)
		matrix[i] = (int *) calloc(SIZE, sizeof(int));

	return matrix;
}

void printMatrix(int **matrix){
	int i, j;
	printf("\n");
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++)
			printf("%d ", matrix[i][j] == 2 ? 2 : 0);
		printf("\n");
	}
}

void freeMatrix(int ***matrix){
	int i;

	for(i = 0; i < SIZE; i++)
		free((*matrix)[i]);

	free(*matrix);
	*matrix = NULL;
}

int countAttempts(int **matrix, int lin){
	int i;
	int counter = 0;

	for(i = 0; i < SIZE; i++){
		if(matrix[lin][i] == 1)
			counter++;
	}

	return counter;
}

int checkColumn(int **matrix, int col){
	int i;

	for(i = 0; i < SIZE; i++){
		//if theres a queen in the same column, return -1
		if(matrix[i][col] == QUEEN)
			return -1;
	}

	return col;
}

int checkDiagonals(int **matrix, int lin, int col){
	int i, j;

	for(i = lin, j = col; i < SIZE && j < SIZE; i++, j++){
		if(matrix[i][j] == QUEEN)
			return 0;
	}

	for(i = lin, j = col; i >= 0 && j >= 0; i--, j--){
		if(matrix[i][j] == QUEEN)
			return 0;
	}

	for(i = lin, j = col; i >= 0 && j < SIZE; i--, j++){
		if(matrix[i][j] == QUEEN)
			return 0;
	}

	for(i = lin, j = col; i < SIZE && j >= 0; i++, j--){
		if(matrix[i][j] == QUEEN)
			return 0;
	}

	return 1;
}

int findPosition(int **matrix, int lin){
	int i, col;

	for(i = 0; i < SIZE; i++){

		//if the position wasn't attempted yet and the column can afford the queen
		if(matrix[lin][i] != 1 && (col = checkColumn(matrix, i)) != -1){
			//if that diagonal is also clear
			if(checkDiagonals(matrix, lin, col)){
				matrix[lin][col] = QUEEN;
				return 1;
			}
		}

		//mark as attempted
		matrix[lin][i] = 1;
	}

	return 0;
}

void remakeLine(int **matrix, int lin){
	int i;
	printf("Remaking line %d...\n", lin);
	for(i = 0; i < SIZE; i++){
		if(matrix[lin][i] == QUEEN)
			matrix[lin][i] = 1;
		matrix[lin + 1][i] = 0;
	}
}

int _backtracking(int **matrix, int lin){
	//vector to check attempted places
	int result;

	//if all the queens were placed, return success
	if(lin == SIZE)
		return 1;

	//if there are possibillities for this line
	while(countAttempts(matrix, lin) < SIZE){
		//try to find a position to place the queen
		if(findPosition(matrix, lin)){
			//if succeed, try to do the same to the next line
			printf("Attempting line %d...\n", lin + 1);
			printMatrix(matrix);
			result = _backtracking(matrix, lin + 1);

			//success achieved
			if(result == 1)
				return 1;
			//could not fit the queen in the new line, remake the last line and try a different position to the queen
			else
				remakeLine(matrix, lin);
		}
	}

	printf("out\n");
	//the line was remade but still couldn't fit the queen, try to the line before
	return 0;
}

int backtracking(int **matrix){
	return _backtracking(matrix, 0);
}

int main(int argc, char *argv[]){

	int **matrix;
	int result;

	matrix = createMatrix();

	result = backtracking(matrix);

	printMatrix(matrix);

	printf("%s\n", result == 1 ? "Sucess" : "Failure");

	freeMatrix(&matrix);

	return 0;
}