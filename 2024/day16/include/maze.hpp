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

        static constexpr int D_COL[] = {0, 1, 0, -1}; // up, right, down, left
        static constexpr int D_ROW[] = {-1, 0, 1, 0}; 

        static constexpr int COST_DOUBLE_TURN = 2000;
        static constexpr int COST_TURN = 1000;

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
        bool can_move_to(int row, int col);
        int find_cost(int current_dir, int next_dir);
        int find_lowest_score();
        int find_best_sits();

    public:
        Maze();
        void show_results();
};