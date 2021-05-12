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
            return vector<int> {neigh0, neigh1, neigh2, neigh3, neigh4, neigh5};
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
    int richness {0};
    int new_cell_index = -1;
    Cell seed_cell = grid[tree.index];
    Cell temp_cell {};
    vector<int> neighbor_cells(6);
    for (int i {0}; i < tree.size; i++){
        neighbor_cells = seed_cell.neigh();
        for (auto cell_index: neighbor_cells){;
            if (cell_index == -1)
                continue;
            temp_cell = grid[cell_index];
            if (temp_cell.richness > richness && !temp_cell.has_tree){
                richness = temp_cell.richness;
                new_cell_index = cell_index;
            }
        }
        seed_cell = grid[new_cell_index];
    }
    return "SEED " + to_string(tree.index) + " " + to_string(seed_cell.index);
}

int main(){
    int numberOfCells; // 37
    cin >> numberOfCells; cin.ignore();
    vector<Cell> grid(numberOfCells);
    vector<Tree> trees(numberOfCells);
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
        vector<int> my_trees{0,0,0,0,0};
        for (int i = 0; i < numberOfTrees; i++) {
            cin >> trees[i].index >> trees[i].size >> trees[i].isMine >> trees[i].isDormant; cin.ignore();
            if (trees[i].isMine){
                my_trees[trees[i].size] += 1;
                my_trees[4] += 1;
            }
            grid[trees[i].index].has_tree = true;
        }
        int numberOfPossibleActions; // all legal actions
        cin >> numberOfPossibleActions; cin.ignore();
        for (int i = 0; i < numberOfPossibleActions; i++) {
            string possibleAction;
            getline(cin, possibleAction); // try printing something from here to start with
        }
        Tree harvest_tree;
        int grow_tree {};
        int tree_points {};
        int seed_cost {my_trees[0]};
        string action = "WAIT";
        for (int j{0}; j < trees.size(); j++){
            if (trees[j].isMine && !trees[j].isDormant){
                int tree_index = trees[j].index;
                int tree_size = trees[j].size;
                int new_tree_points = possible_points(tree_index, nutrients, grid);
                if (tree_size < 3){
                    int grow_cost = tree_grow_cost(tree_size, my_trees[1], my_trees[2], my_trees[3]);
                    if (grow_cost < (sun / 2)){
                        action = "GROW " + to_string(tree_index);
                        break;
                    }
                }
                if (new_tree_points < tree_points){
                    continue;
                }
                harvest_tree = trees[j];
                tree_points = new_tree_points;
            }
        }
        if (action == "WAIT" && (my_trees[3] > 0)){
            if (day > 15 && sun >= 4){
                action = "COMPLETE " + to_string(harvest_tree.index);
            } else {
                action = drop_seed(harvest_tree, grid);
            }
        }   
        // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>
        cout << action << endl;
        trees.clear();
        tree_points = 0;
        my_trees = {0,0,0,0,0};

    }
}