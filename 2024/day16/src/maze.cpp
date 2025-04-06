#include "maze.hpp"
#include <limits.h>
#include <queue>

Maze::Maze() {
    fill_maze();
    search_for_shortest_path();
}

void Maze::fill_maze() {
    std::string line;
    std::getline(std::cin, line);  // Read first line
    maze_size = line.size();

    maze.resize(maze_size);
    for (int i = 0; i < maze_size; i++) {
        maze[i].resize(maze_size);
        maze[0][i] = '#';
    }

    for (int y = 1; y < maze_size; y++) {
        std::getline(std::cin, line);
        for (int x = 0; x < maze_size; x++) {
            maze[y][x] = line[x];
            if (line[x] == 'E') { 
                target_cell.x = x;
                target_cell.y = y;
            } else if (line[x] == 'S') { 
                start_cell.x = x;
                start_cell.y = y;
            }
            
        }
    }
}


bool Maze::can_move_to(int x, int y){
    return maze[y][x] != '#';
}

int Maze::search_for_shortest_path() {

    int dx[] = {0, 1, 0, -1}; // up, right, down, left
    int dy[] = {-1, 0, 1, 0}; 

    Cell current_cell = start_cell;
    Cell next_cell;
    std::vector<std::vector<std::vector<int>>> lowestPoints(maze_size, std::vector<std::vector<int>>(maze_size, std::vector<int>(4,INT_MAX)));
    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> cellsToCheck;

    cellsToCheck.push(current_cell);
    lowestPoints[current_cell.x][current_cell.y][0] = 1000;
    lowestPoints[current_cell.x][current_cell.y][1] = 0;
    lowestPoints[current_cell.x][current_cell.y][2] = 1000;
    lowestPoints[current_cell.x][current_cell.y][3] = 2000;

    while (!cellsToCheck.empty()) {
        current_cell = cellsToCheck.top();
        cellsToCheck.pop();

        for (int direction = 0; direction < 4; direction++) {
            next_cell.x = current_cell.x + dx[direction];
            next_cell.y = current_cell.y + dy[direction];
            
            if (!can_move_to(next_cell.x, next_cell.y))continue;
            next_cell.dir = direction;
            

            if (current_cell.dir == next_cell.dir) {
                next_cell.cost = lowestPoints[current_cell.x][current_cell.y][current_cell.dir] + 1;
            }else if (std::abs(current_cell.dir - next_cell.dir ) == 2){
                next_cell.cost = lowestPoints[current_cell.x][current_cell.y][current_cell.dir] + 2001;
            } else {
                next_cell.cost = lowestPoints[current_cell.x][current_cell.y][current_cell.dir] + 1001;
            }

            if (next_cell.cost < lowestPoints[next_cell.x][next_cell.y][next_cell.dir]) {
                lowestPoints[next_cell.x][next_cell.y][next_cell.dir] = next_cell.cost;
                cellsToCheck.push(next_cell);
            }
        }

    }

    int tmp = INT_MAX;
    for (int dir = 0; dir < 4; dir++) {
        if (lowestPoints[target_cell.x][target_cell.y][dir] < tmp) {
            tmp = lowestPoints[target_cell.x][target_cell.y][dir];
        }
    }
    
    // Nagłówki tabeli
    std::cout << "-------------------- Tabela Lowest Points --------------------\n";
    std::cout << "Row | Col | Value 1 | Value 2 | Value 3 | Value 4\n";
    std::cout << "-------------------------------------------------------------\n";

    // Wyświetlamy tabelę
    for (int i = 1; i < maze_size-1; ++i) {
        for (int j = 1; j < maze_size-1; ++j) {
            if (!can_move_to(i,j))continue;
            std::cout << std::setw(7) << i << " | " << std::setw(7) << j;  // Wyświetlanie numerów wiersza i kolumny
            for (int k = 0; k < 4; ++k) {
                std::cout << " | " << std::setw(12) << lowestPoints[i][j][k];  // Wyświetlanie wartości w kolumnach
            }
            std::cout << "\n";
        }
    }



    std::cout << tmp << std::endl;
    return tmp;
}