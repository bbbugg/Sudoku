#include<bits/stdc++.h>
#include<stack>
using namespace std;
clock_t start, stop;
double duration;

struct nodeOnBoard {
	int line, row;
	int maybeNum[9] = { 0,0,0,0,0,0,0,0,0 };
	int num;
};

class Sudoku {
public:
	int board[9][9];
	int maybeNumBoard[9][9];
	stack<nodeOnBoard, list<nodeOnBoard>> node;
	Sudoku() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = 0;
				maybeNumBoard[i][j] = 0;
			}
		}
	}
	void Print(int board[9][9]) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	}

	void MaybeNum1(int board[9][9], int line, int row, nodeOnBoard* n) {
		int a[9] = { 0,0,0,0,0,0,0,0,0 };
		for (int i = 0; i < 9; i++) {
			if (board[i][row] != 0) a[board[i][row] - 1]++;
			if (board[line][i] != 0) a[board[line][i] - 1]++;
		}
		int b = line / 3;
		int c = row / 3;
		for (int i = 3 * b; i < 3 * b + 3; i++) {
			for (int j = 3 * c; j < 3 * c + 3; j++) {
				if (board[i][j] != 0) a[board[i][j] - 1]++;
			}
		}
		for (int i = 0; i < 9; i++) {
			if (a[i] == 0) {
				n->num++;
				n->maybeNum[n->num] = i + 1;
			}
		}
	}
	bool CheckFinsh(int board[9][9]) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == 0) return false;
			}
		}
		return true;
	}
	int MaybeNum(int board[9][9], int MaybeNumBoard[9][9]) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (board[x][y] != 0) {
					MaybeNumBoard[x][y] = -1;
					continue;
				}
				int a[9] = { 0,0,0,0,0,0,0,0,0 };
				for (int i = 0; i < 9; i++) {
					if (board[i][y] != 0) a[board[i][y] - 1]++;
					if (board[x][i] != 0) a[board[x][i] - 1]++;
				}
				int b = x / 3;
				int c = y / 3;
				for (int i = 3 * b; i < 3 * b + 3; i++) {
					for (int j = 3 * c; j < 3 * c + 3; j++) {
						if (board[i][j] != 0) a[board[i][j] - 1]++;
					}
				}
				int n = 0;
				for (int i = 0; i < 9; i++) {
					if (a[i] == 0) n++;
				}
				MaybeNumBoard[x][y] = n;
			}
		}
		return 1;
	}
};

int play2(int board[9][9], int MaybeNumBoard[9][9], Sudoku S) {
	int line, row, i, flag[9] = { 0,0,0,0,0,0,0,0,0 };
	if (S.CheckFinsh(board)) return 1;
	for (line = 0; line < 9; line++) {
		for (row = 0; row < 9; row++) {
			if (MaybeNumBoard[line][row] == 0) return 0;
		}
	}
	for (i = 0; i < 9; i++) {
		for (line = 0; line < 9; line++) {
			for (row = 0; row < 9; row++) {
				if (MaybeNumBoard[line][row] == i + 1) {
					flag[i] = 1;
					nodeOnBoard* n = (nodeOnBoard*)malloc(sizeof(nodeOnBoard));
					n->num = -1;
					n->line = line;
					n->row = row;
					S.MaybeNum1(board, line, row, n);
					S.node.push(*n);
					break;
				}
			}
			if (flag[i] == 1) break;
		}
		if (flag[i] == 1) break;
	}

	//if (flag[i] == 0) return 0;
	//if (S.node.top().num == -1) return 0;
	cout << line << ' ' << row << ' ' << S.node.top().maybeNum[S.node.top().num] << endl;
	board[line][row] = S.node.top().maybeNum[S.node.top().num];
	S.Print(board);
	cout << endl;
	S.MaybeNum(board, MaybeNumBoard);
	S.Print(MaybeNumBoard);
	cout << endl;
	while (play2(board, MaybeNumBoard, S) == 0) {
		if (S.CheckFinsh(board)) return 1;
		if (S.node.empty() == true) {
			cout << "错误";
			return 0;
		}
		while (S.node.top().num == 0) {
			nodeOnBoard* d = &S.node.top();
			board[d->line][d->row] = 0;
			S.node.pop();
			if (S.node.empty() == true) {
				cout << "错误";
				return 0;
			}
		}
		S.node.top().num--;
		line = S.node.top().line;
		row = S.node.top().row;
		cout << line << ' ' << row << ' ' << S.node.top().maybeNum[S.node.top().num] << endl;
		board[line][row] = S.node.top().maybeNum[S.node.top().num];
		S.Print(board);
		cout << endl;
		S.MaybeNum(board, MaybeNumBoard);
		S.Print(MaybeNumBoard);
		cout << endl;
	}
	return 1;
}

void Play(int board[9][9], Sudoku S) {

	S.MaybeNum(board, S.maybeNumBoard);
	S.Print(S.maybeNumBoard);
	cout << endl;
	if (play2(board, S.maybeNumBoard, S) == 0) {
		cout << "错误";
	}

}

int main() {
	Sudoku S;
	int line, row, num;

	//////////////////////////////////////////////第一种输入方式(第一行个数，第一列行，第二列列，第三列数)
	//25
	//1 3 8
	//2 5 3
	//2 7 4
	//3 4 6
	//3 7 5
	//3 9 7
	//4 7 1
	//4 8 5
	//4 9 2
	//5 1 5
	//5 4 8
	//6 5 4
	//6 6 6
	//6 7 9
	//6 8 7
	//7 2 1
	//7 4 3
	//7 6 4
	//7 7 7
	//8 5 6
	//8 7 3
	//8 8 2
	//9 2 2
	//9 3 9
	//9 6 5
	//int n;//给出的个数
	//cin >> n;
	//for (int i = 0; i < n; i++) {
	//	cin >> line >> row >> num;
	//	S.board[line - 1][row - 1] = num;
	//}


	///////////////////////////////////////////////第二种输入方式（pta期末）
	//0 6 1 0 3 0 0 2 0
	//0 5 0 0 0 8 1 0 7
	//0 0 0 0 0 7 0 3 4
	//0 0 9 0 0 6 3 7 8
	//0 0 3 2 7 9 5 0 0
	//5 7 0 3 0 0 9 0 2
	//1 9 0 7 6 0 0 0 0
	//8 0 2 4 0 0 7 6 0
	//6 4 0 0 1 0 2 5 0

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> num;
			S.board[i][j] = num;
		}
		cin.get();
	}
	//////////////////////////////////////////////////////

	start = clock();

	Play(S.board, S);
	cout << endl;
	S.Print(S.board);

	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << endl << "耗时：" << duration;
	return 0;
}