//Word Search

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


//Maize 

#include <iostream>
using namespace std;

#define N 4

int maze[N][N] = {
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 1}
};

int sol[N][N];

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N &&
            maze[x][y] == 1 && sol[x][y] == 0);
}

bool solveMazeUtil(int x, int y, int targetX, int targetY) {
    if (x == targetX && y == targetY) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(x, y)) {
        sol[x][y] = 1;

        if (solveMazeUtil(x + 1, y, targetX, targetY)) return true; // Down
        if (solveMazeUtil(x, y + 1, targetX, targetY)) return true; // Right
        if (solveMazeUtil(x, y - 1, targetX, targetY)) return true; // Left
        if (solveMazeUtil(x - 1, y, targetX, targetY)) return true; // Up

        sol[x][y] = 0;
    }
    return false;
}

bool solveMaze(int targetX, int targetY) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sol[i][j] = 0;

    if (!solveMazeUtil(0, 0, targetX, targetY)) {
        cout << "No solution exists" << endl;
        return false;
    }

    cout << "Path found:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
    return true;
}

int main() {
    solveMaze(2, 0);
}

//N-queen

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

//Maize-Health
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
