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
        int neigh0;
        int neigh1;
        int neigh2;
        int neigh3;
        int neigh4;
        int neigh5;

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
        vector<int> tree_sizes{0,0,0,0};
        for (int i = 0; i < numberOfTrees; i++) {
            cin >> trees[i].index >> trees[i].size >> trees[i].isMine >> trees[i].isDormant; cin.ignore();
            tree_sizes[trees[i].size] += 1;
        }
        int numberOfPossibleActions; // all legal actions
        cin >> numberOfPossibleActions; cin.ignore();
        for (int i = 0; i < numberOfPossibleActions; i++) {
            string possibleAction;
            getline(cin, possibleAction); // try printing something from here to start with
        }
        int harvest_tree {};
        int grow_tree {};
        int tree_points {};
        int seed_cost {tree_sizes[0]};
        for (int i{0}; i < numberOfPossibleActions; i++){
            for (int j{0}; j < trees.size(); j++){
                if (trees[j].isMine){
                    int tree_index = trees[j].index;
                    int tree_size = trees[j].size;
                    tree_sizes[tree_size] += tree_size;
                    int new_tree_points = possible_points(tree_index, nutrients, grid);
                    if (tree_size < 3){
                        int grow_cost = tree_grow_cost(tree_size, tree_sizes[1], tree_sizes[2], tree_sizes[3]);
                    }
                    if (new_tree_points < tree_points){
                        continue;
                    }
                    harvest_tree = tree_index;
                    tree_points = new_tree_points;
                }
            }
        }
        // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>
        cout << "COMPLETE " << harvest_tree << endl;
        trees.clear();
        tree_points = 0;
        tree_sizes = {0,0,0,0};

    }
}