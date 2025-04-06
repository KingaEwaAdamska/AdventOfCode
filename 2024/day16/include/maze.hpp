#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>
#include <queue>
#include <climits>
#include <iomanip>
#include <stack> 

class Maze {
    private:

    struct Cell {
        int col;
        int row;
        int dir = 1;
        int cost;
        bool operator>(const Cell &other) const {
            return cost > other.cost;
        }
    };

        std::vector<std::vector<char>> maze;
        std::vector<std::vector<std::vector<int>>> pointsValues;
        int maze_size;
        Cell start_cell;
        Cell target_cell;
        void fill_maze();
        bool can_move_to(int x, int y);
        int search_for_shortest_path();
        int analyze_shortest_paths();

    public:
        Maze();
        void show_results();
};