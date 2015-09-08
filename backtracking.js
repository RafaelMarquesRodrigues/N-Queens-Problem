var QUEEN = 2;
var SIZE = 8;
var fn = [];
var nm = [];
var count = 0;

function printMatrix(matrix){
	document.write("<br>");

	for(var i = 0; i < SIZE; i++){
		for(var j = 0; j < SIZE; j++){
			var number = (i*8) + j;
			document.write("<span id=\"" + number + "\"> " + matrix[i][j] + "  </span>");
			document.write(" ");
		}
		document.write("<br>");
	}
}

function initMatrix(){
	var matrix = [];

	for(var i = 0; i < SIZE; i++){
		matrix[i] = [];
		for(var j = 0; j < SIZE; j++){
			matrix[i][j] = 0;
		}
	}

	return matrix;
}

function countAttempts(matrix, lin){
	var i;
	var counter = 0;

	for(i = 0; i < SIZE; i++){
		if(matrix[lin][i] == 1)
			counter++;
	}

	return counter;
}

function checkColumn(matrix, col){
	var i;

	for(i = 0; i < SIZE; i++){
		//if theres a queen in the same column, return -1
		if(matrix[i][col] == QUEEN)
			return -1;
	}

	return col;
}

function checkDiagonals(matrix, lin, col){
	var i, j;

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

function findPosition(matrix, lin){

	for(var i = 0; i < SIZE; i++){
		var n = (lin * 8) + i;

		if(matrix[lin][i] != 1){
			var col = checkColumn(matrix, i);

			if(col != -1 && checkDiagonals(matrix, lin, col) == 1){
				matrix[lin][col] = QUEEN;
				
				
				fn[count] = function(arg) {
					document.getElementById(arg).innerHTML = "2";
				};

				nm[count] = n;
				count++;

				return 1;
			}
		}

		matrix[lin][i] = 1;
		
		fn[count] = function(arg) {
			document.getElementById(arg).innerHTML = "1";
		};

		nm[count] = n;
		count++;
	}

	return 0;
}

function removeQueen(matrix, lin){

	for(var i = 0; i < SIZE; i++){
		var n = (lin * 8) + i;

		if(matrix[lin][i] == QUEEN){
			matrix[lin][i] = 1;
			
			fn[count] = function(arg) {
				document.getElementById(arg).innerHTML = "1";
			};

			nm[count] = n;
			count++;
		}

		
		fn[count] = function(arg) {
			document.getElementById(arg + 8).innerHTML = "0";
		};

		nm[count] = n;
		count++;

		matrix[lin + 1][i] = 0;
	}
}

function _backtracking(matrix, lin){
	var result;

	if(lin == 8){
		return 1;
	}

	while(countAttempts(matrix, lin) < SIZE){
		if(findPosition(matrix, lin) == 1){
			result = _backtracking(matrix, lin + 1);

			if(result == 1)
				return 1;
			else
				removeQueen(matrix, lin);
		}
	}

	return 0;


}

function backtracking(matrix){
	_backtracking(matrix, 0);
	var i = 0;

	setInterval(function() {
		fn[i](nm[i]);
		i++;
	}, 10);
}