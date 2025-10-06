//----------------------


#include <iostream>

#define N 4

void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << sol[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y)) {
        sol[x][y] = 1;

        if (solveMazeUtil(maze, x + 1, y, sol)) {
            return true;
        }

        if (solveMazeUtil(maze, x, y + 1, sol)) {
            return true;
        }

        sol[x][y] = 0;
        return false;
    }

    return false;
}

void solveMaze(int maze[N][N]) {
    int sol[N][N] = {{0, 0, 0, 0},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0}};

    if (solveMazeUtil(maze, 0, 0, sol) == false) {
        std::cout << "Solution doesn't exist" << std::endl;
        return;
    }

    printSolution(sol);
}

int main() {
    int maze[N][N] = {{1, 0, 0, 0},
                      {1, 1, 0, 1},
                      {0, 1, 0, 0},
                      {1, 1, 1, 1}};

    solveMaze(maze);
    return 0;
}


//----------


#include <iostream>
#include <climits>

#define N 4

int min_health_lost = INT_MAX;
int best_sol[N][N] = {0};

void copySolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            best_sol[i][j] = sol[i][j];
        }
    }
}

void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << sol[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] != 0);
}

void solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N], int current_health_lost) {
    if (x == N - 1 && y == N - 1) {
        int final_cost = current_health_lost + (maze[x][y] == 2 ? 5 : 0);
        
        if (final_cost < min_health_lost) {
            min_health_lost = final_cost;
            sol[x][y] = 1;
            copySolution(sol);
            sol[x][y] = 0;
        }
        return;
    }

    if (isSafe(maze, x, y)) {
        int cost_of_this_cell = (maze[x][y] == 2 ? 5 : 0);
        
        if (current_health_lost + cost_of_this_cell >= min_health_lost) {
            return;
        }

        sol[x][y] = 1;
        
        solveMazeUtil(maze, x + 1, y, sol, current_health_lost + cost_of_this_cell);
        
        solveMazeUtil(maze, x, y + 1, sol, current_health_lost + cost_of_this_cell);
        
        sol[x][y] = 0;
    }
}

void solveMaze(int maze[N][N]) {
    int sol[N][N] = {0};
    
    solveMazeUtil(maze, 0, 0, sol, 0);

    if (min_health_lost == INT_MAX) {
        std::cout << "Solution doesn't exist" << std::endl;
    } else {
        std::cout << "The path with the minimum health loss (" << min_health_lost << "):" << std::endl;
        printSolution(best_sol);
    }
}

int main() {
    int maze[N][N] = {{1, 1, 2, 1},
                      {0, 1, 2, 1},
                      {1, 1, 0, 1},
                      {2, 1, 1, 1}};
    
    solveMaze(maze);
    return 0;
}



//-----------


#include <iostream>
//
#define N 4

void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(board[i][j])
                std::cout << "Q ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    for (j = 0; j < col; j++) {
        if (board[row][j]) {
            return false;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(int board[N][N], int col) {
    if (col >= N) {
        return true;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;

            if (solveNQueensUtil(board, col + 1)) {
                return true;
            }

            board[i][col] = 0; 
        }
    }
    
    return false;
}

void solveNQueens() {
    int board[N][N] = { {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0} };

    if (solveNQueensUtil(board, 0) == false) {
        std::cout << "Solution does not exist" << std::endl;
        return;
    }

    printSolution(board);
}

int main() {
    solveNQueens();
    return 0;
}

//---------------------------------------------------------------------------------------------

// Word Search Puzzle
// Given an NxM grid of letters and K words,
// find the starting index (row,col) of each word
// if it exists in UP, DOWN, LEFT, RIGHT directions only.
// If the word does not exist, output "n".

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;               // grid size
vector<string> grid;    // puzzle grid

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Check if a word exists starting from (i,j)
bool findWord(int i, int j, string word) {
    int len = word.length();

    for (int dir = 0; dir < 4; dir++) {
        int x = i, y = j;
        int k;

        for (k = 0; k < len; k++) {
            if (x < 0 || y < 0 || x >= n || y >= m) break;   // out of bounds
            if (grid[x][y] != word[k]) break;                // mismatch
            x += dx[dir];
            y += dy[dir];
        }

        if (k == len) return true; // full match found
    }
    return false;
}

int main() {
    cin >> n >> m;
    grid.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int k;
    cin >> k;
    vector<string> words(k);
    for (int i = 0; i < k; i++) {
        cin >> words[i];
    }

    for (int w = 0; w < k; w++) {
        bool found = false;

        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < m && !found; j++) {
                if (grid[i][j] == words[w][0]) { // first letter match
                    if (findWord(i, j, words[w])) {
                        cout << i << " , " << j << endl;
                        found = true;
                    }
                }
            }
        }

        if (!found) cout << "n" << endl;
    }

    return 0;
}