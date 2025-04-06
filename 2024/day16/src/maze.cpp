#include "maze.hpp"
#include <limits.h>
#include <queue>

Maze::Maze() {
    fill_maze();
}

void Maze::show_results() {
    std::cout << "Part A: " << find_lowest_score() << std::endl;
    std::cout << "Part B: " << find_best_sits() << std::endl;
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

    for (int row = 1; row < maze_size; row++) {
        std::getline(std::cin, line);
        for (int col = 0; col < maze_size; col++) {
            maze[row][col] = line[col];
            if (line[col] == 'E') { 
                target_cell.col = col;
                target_cell.row = row;
            } else if (line[col] == 'S') { 
                start_cell.col = col;
                start_cell.row = row;
            }
            
        }
    }
}

bool Maze::can_move_to(int row, int col){
    return maze[row][col] != '#';
}

int Maze::find_cost(int current_dir, int next_dir) {
    if (current_dir == next_dir) {
        return 1;
    }else if (std::abs(current_dir - next_dir ) == 2){
        return COST_DOUBLE_TURN + 1;
    }else {
        return COST_TURN + 1;
    }
}

int Maze::find_lowest_score() {

    Cell current_cell = start_cell;
    Cell next_cell;
    std::vector<std::vector<std::vector<int>>> lowestPoints(maze_size, std::vector<std::vector<int>>(maze_size, std::vector<int>(4,INT_MAX)));
    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> cellsToCheck;

    cellsToCheck.push(current_cell);
    lowestPoints[current_cell.row][current_cell.col][1] = 0;

    while (!cellsToCheck.empty()) {
        current_cell = cellsToCheck.top();
        cellsToCheck.pop();

        for (int direction = 0; direction < 4; direction++) {
            next_cell.col = current_cell.col + D_COL[direction];
            next_cell.row = current_cell.row + D_ROW[direction];
            
            if (!can_move_to(next_cell.row, next_cell.col))continue;

            next_cell.dir = direction;
            int cost_change = find_cost(current_cell.dir, next_cell.dir);
            next_cell.cost = lowestPoints[current_cell.row][current_cell.col][current_cell.dir] + cost_change;

            if (next_cell.cost < lowestPoints[next_cell.row][next_cell.col][next_cell.dir]) {
                lowestPoints[next_cell.row][next_cell.col][next_cell.dir] = next_cell.cost;
                cellsToCheck.push(next_cell);
            }
        }

    }

    int minCost = INT_MAX;
    for (int dir = 0; dir < 4; dir++) {
        if (lowestPoints[target_cell.row][target_cell.col][dir] < minCost) {
            minCost = lowestPoints[target_cell.row][target_cell.col][dir];
        }
    }
    pointsValues = lowestPoints;
    return minCost;
}

int Maze::find_best_sits() {

    int cnt = 0;

    std::vector<std::vector<bool>> visited(maze_size, std::vector<bool>(maze_size, false));
    std::stack<std::pair<int,int>> toVisit;
    int first_row;
    int first_col;
    int second_row;
    int second_col;
    int new_row;
    int new_col;
    int tmp_points;
    int direction;
    int direction_val;

    toVisit.push({target_cell.row,target_cell.col});

    while (!toVisit.empty()){
        std::pair<int,int> current_cell = toVisit.top();
        toVisit.pop();

        first_row = current_cell.first;
        first_col = current_cell.second;
        
        visited[first_row][first_col] = true;
        cnt++;

        direction_val = INT_MAX;
    
        for (int dir = 0; dir < 4; dir++) {
            if (pointsValues[first_row][first_col][dir] < direction_val) {
                direction_val = pointsValues[first_row][first_col][dir];
                direction = dir;
            }
        }
        second_row = first_row;
        second_col = first_col;
        first_row = second_row - D_ROW[direction];
        first_col = second_col - D_COL[direction];
        visited[first_row][first_col] = true;
        cnt++;

        while (pointsValues[first_row][first_col][1] != 0) {
            for (int dir = 0; dir < 4; dir++) {
                new_row = first_row - D_ROW[dir];
                new_col = first_col - D_COL[dir];
                if(!can_move_to(new_row,new_col))continue;
                tmp_points = INT_MAX;

                if (second_row == new_row || second_col == new_col) {
                    tmp_points = pointsValues[first_row][first_col][dir];
                }else {
                    tmp_points = pointsValues[first_row][first_col][dir] + 1000;
                }

                if (tmp_points < direction_val) {
                    direction_val = tmp_points;
                    direction = dir;
                } else if (tmp_points == direction_val && direction_val < INT_MAX) {
                    toVisit.push({new_row, new_col});
                }
            }
            second_row = first_row;
            second_col = first_col;
            first_row = second_row - D_ROW[direction];
            first_col = second_col - D_COL[direction];

            if (visited[first_row][first_col])break;

            visited[first_row][first_col] = true;
            cnt++;
            
        }
    }

    return cnt;
}