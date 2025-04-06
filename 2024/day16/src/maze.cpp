#include "maze.hpp"
#include <limits.h>
#include <queue>

Maze::Maze() {
    fill_maze();
    search_for_shortest_path();
}

void Maze::fill_maze() {
    std::string line;
    std::getline(std::cin, line);  // Wczytuje całą linię tekstu
    maze_size = line.size();
    // std::cout << line << std::endl;

    maze.resize(maze_size);  // Tworzy wektory w maze
    for (int i = 0; i < maze_size; i++) {
        maze[i].resize(maze_size);  // Inicjuje wektory w każdym wierszu
        maze[0][i] = '#';
    }

    for (int i = 1; i < maze_size; i++) {
        std::getline(std::cin, line);
        // std::cout << line << std::endl;
        for (int j = 0; j < maze_size; j++) {
            maze[i][j] = line[j];
            if (line[j] == 'E') { 
                target_cell.x = i;
                target_cell.y = j;
            } else if (line[j] == 'S') { 
                start_cell.x = i;
                start_cell.y = j;
            }
            
        }
    }
}


bool Maze::can_move_to(int x, int y){
    return maze[x][y] != '#';
}

void Maze::search_for_shortest_path() {
    const int dy[] = {0, 1, 0, -1};  // ↑ → ↓ ←
    const int dx[] = {-1, 0, 1, 0};

    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> cellsToCheck;
    std::vector<std::vector<int>> dist(maze_size, std::vector<int>(maze_size, INT_MAX));
    std::vector<std::vector<int>> direction(maze_size, std::vector<int>(maze_size, INT_MAX));
    std::vector<std::vector<std::pair<int, int>>> previousCell(maze_size, std::vector<std::pair<int, int>>(maze_size, {-1, -1}));


    int startDir = 1;

    cellsToCheck.push({start_cell.x, start_cell.y, startDir, 0});
    dist[start_cell.x][start_cell.y] = 0;

    Cell current;
    while (!cellsToCheck.empty()) {
        current = cellsToCheck.top();
        cellsToCheck.pop();
        for (int dir = 0; dir < 4; dir++) {
            int new_x = current.x + dx[dir];
            int new_y = current.y + dy[dir];
            int new_cost = current.cost;
            if (!can_move_to(new_x,new_y)) continue;
            
            if (current.dir == dir) {
                new_cost += 1;
            }else if (std::abs(current.dir - dir ) == 1){
                new_cost += 1001;
            } else {
                new_cost += 2001;
            }

            if (new_cost < dist[new_x][new_y]){
                dist[new_x][new_y] = new_cost;
                direction[new_x][new_y] = dir;
                cellsToCheck.push({new_x, new_y, dir, new_cost});
        
                previousCell[new_x][new_y] = {current.x,current.y};
                // std::cout << current.dir << " " <<dir << std::endl;
                std::cout << "Current x: " << current.x << " y: " << current.y << " " << current.cost << " " << current.dir << std::endl;
                std::cout << "Next    x: " << new_x << " y: " << new_y << " " << new_cost << " " << dir << std::endl;
            }
        }
    }
    int x = target_cell.x;
    int y = target_cell.y;
    while (x != -1 && y != -1) {
        maze[x][y] = 'X';
        std::cout << x << " " << y << std::endl;
        std::cout << "Prev" << previousCell[x][y].first << " " << previousCell[x][y].second << std::endl;
        x = previousCell[x][y].first;
        y = previousCell[x][y].second;
        
    } 
    // std::cout << "[12][13]" << previousCell[12][13].first << " " << previousCell[12][13].second << std::endl;
    // std::cout << "[13][13]" << previousCell[13][13].first << " " << previousCell[13][13].second << std::endl;
    // std::cout << "[13][12]" << previousCell[13][12].first << " " << previousCell[13][12].second << std::endl;

    // std::cout << "[3][13]" << previousCell[3][13].first << " " << previousCell[3][13].second << std::endl;
    // std::cout << "[4][13]" << previousCell[4][13].first << " " << previousCell[4][13].second << std::endl;
    // std::cout << "[5][13]" << previousCell[5][13].first << " " << previousCell[13][12].second << std::endl;
    
    std::cout << dist[target_cell.x][target_cell.y] << std::endl;
    for (int i = 0; i < maze_size; i++){
        for (int j = 0; j < maze_size; j++){
            //std::cout << maze[i][j];
           
        }
        std::cout << std::endl;
    }

    
    return;
}