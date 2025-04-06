#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>
#include <queue>
#include <climits>
#include <iomanip> 

class Maze {
    private:

    struct Cell {
        int x;
        int y;
        int dir = 1;
        int cost;
        bool operator>(const Cell &other) const {
            return cost > other.cost;
        }
    };

        std::vector<std::vector<char>> maze;
        int maze_size;
        Cell start_cell;
        Cell target_cell;
        void fill_maze();
        bool can_move_to(int x, int y);
        int search_for_shortest_path();

    public:
        Maze();
};