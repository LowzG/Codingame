#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
Game Info:
Map index starts at 0 is the center cell, the next cells spiral outwards
Richness values are: 0 if the cell is unusable, 1-3 for usable cells
Tree sizes: 0-3
*/


// Todo: Update dormant state on tree when tree action is taken

class Tree {
    public:
        int index;
        int size;
        bool isMine;
        bool isDormant;
};

class Cell {
    public:
        int index;
        int richness;
        int neigh0, neigh1, neigh2, neigh3, neigh4, neigh5 = -1;
        bool has_tree;
        vector<int> neigh(){
            vector<int> neighbors {neigh0, neigh1, neigh2, neigh3, neigh4, neigh5};
            sort(neighbors.begin(), neighbors.end());
            return neighbors;
        }
};

int possible_points(int tree_index, int forest_nutrient, vector<Cell> &grid) {
    return forest_nutrient + grid[tree_index].richness;
}

int tree_grow_cost(int tree_size, int size1_trees, int size_2_trees, int size_3_trees){
    int sun_points {};
    int num_trees {};
    if (tree_size == 0){
        sun_points = 1;
        num_trees = size1_trees;
    }
    else if (tree_size == 1){
        sun_points = 3;
        num_trees = size_2_trees;
    } else if (tree_size == 2){
        sun_points = 7;
        num_trees = size_3_trees;
    }
    return sun_points + num_trees;
}

string drop_seed(Tree tree, vector<Cell> &grid){
    int new_cell_index = -1;
    Cell seed_cell = grid[tree.index];
    vector<int> neighbor_cells(6);
    for (int i {0}; i < tree.size; i++){
        neighbor_cells = seed_cell.neigh();
        for (auto cell_index: neighbor_cells){
            if (cell_index == -1)
                continue;
            if (grid[cell_index].has_tree && tree.size - i == 1){
                continue;
            }
            new_cell_index = cell_index;
            break;
        }
        seed_cell = grid[new_cell_index];
    }
    if (new_cell_index == -1){
        return "No available cell to seed within reach";
    } else {
    return "SEED " + to_string(tree.index) + " " + to_string(seed_cell.index);
    }
}

int main(){
    int numberOfCells; // 37
    cin >> numberOfCells; cin.ignore();
    vector<Cell> grid(numberOfCells);
    vector<Tree> trees(numberOfCells);
    vector<Tree> my_trees;
    for (int i = 0; i < numberOfCells; i++) {
        cin >> grid[i].index >> grid[i].richness >> grid[i].neigh0 >> grid[i].neigh1 >> grid[i].neigh2 >> grid[i].neigh3 >> grid[i].neigh4 >> grid[i].neigh5; cin.ignore();
    }

    // game loop
    while (1) {
        int day; // the game lasts 24 days: 0-23
        cin >> day; cin.ignore();
        int nutrients; // the base score you gain from the next COMPLETE action
        cin >> nutrients; cin.ignore();
        int sun; // your sun points
        int score; // your current score
        cin >> sun >> score; cin.ignore();
        int oppSun; // opponent's sun points
        int oppScore; // opponent's score
        bool oppIsWaiting; // whether your opponent is asleep until the next day
        cin >> oppSun >> oppScore >> oppIsWaiting; cin.ignore();
        int numberOfTrees; // the current amount of trees
        cin >> numberOfTrees; cin.ignore();
        trees.resize(numberOfTrees);
        vector<int> my_trees_totals{0,0,0,0,0};
        for (int i = 0; i < numberOfTrees; i++) {
            cin >> trees[i].index >> trees[i].size >> trees[i].isMine >> trees[i].isDormant; cin.ignore();
            if (trees[i].isMine){
                my_trees.push_back(trees[i]);
                my_trees_totals[trees[i].size] += 1;
                my_trees_totals[4] += 1;
            }
            grid[trees[i].index].has_tree = true;
        }
        int numberOfPossibleActions; // all legal actions
        cin >> numberOfPossibleActions; cin.ignore();
        for (int i = 0; i < numberOfPossibleActions; i++) {
            string possibleAction;
            getline(cin, possibleAction); // try printing something from here to start with
        }
        string action = "WAIT";
        for (auto tree: my_trees){
            if (tree.isDormant){
                continue;
            }
            int grow_cost = tree_grow_cost(tree.size, my_trees_totals[1], my_trees_totals[2], my_trees_totals[3]);
            int seed_cost = my_trees_totals[0];
            int complete_cost = 4;
            if (my_trees_totals[3] == 0 && grow_cost < sun && tree.size < 3){
                action = "GROW " + to_string(tree.index);
                break;
            }
            if (tree.size == 0 && sun >= grow_cost){
                action = "GROW " + to_string(tree.index);
                break;
            } else if (tree.size == 3 && (my_trees_totals[3] > 2 || day > 20) && sun >= complete_cost){
                action = "COMPLETE " + to_string(tree.index);
                break;
            } else {
                if (day < 10 && sun >= seed_cost && tree.size != 0){
                action = drop_seed(tree, grid);
                if (action == "No available cell to seed within reach"){
                    action = "WAIT";
                    continue;
                }
                break;
                } else if (sun >= grow_cost && tree.size < 3){
                action = "GROW " + to_string(tree.index);
                break;
                }
            }   
        } 
        // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>
        cout << action << endl;
        trees.clear();
        my_trees.clear();
        my_trees_totals = {0,0,0,0,0};

    }
}