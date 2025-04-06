#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>
#include <queue>

class Maze {
    private:

    struct Cell {
        int x, y, dir, cost;
        bool operator>(const Cell &other) const {
            return cost > other.cost;
        }
    };

        std::vector<std::vector<char>> maze;
        int maze_size;
        // 0 - N
        // 1 - E
        // 2 - S
        // 3 - W
        int current_direction;
        Cell start_cell;
        Cell target_cell;
        void fill_maze();
        bool can_move_to(int x, int y);
        void search_for_shortest_path();

    public:
        Maze();
};