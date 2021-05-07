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

int cell_data_size {8};
int tree_data_size {4};
int index = 0;
int richness, tree_size = 1;
int neigh0, tree_isMine = 2;
int neigh1, tree_isDormant = 3;
int neigh2 = 4;
int neigh3 = 5;
int neigh4 = 6;
int neigh5= 7;
// Todo add step for tree iteration (8)

int vec_walk(string vec, int item_index, int data_index){
    // Wrote this to avoid creating 2D vectors

    int data_size {};
    if (vec == "map"){
        data_size = cell_data_size;
    } else if (vec == "tree"){
        data_size = tree_data_size;
    } else return;
    
    return data_index + (item_index * data_size);
} 

int possible_points(int tree_index, int forest_nutrient, vector<int> &grid) {
    return forest_nutrient + grid[vec_walk("map", tree_index, richness)];
}

int main(){
    int numberOfCells; // 37
    cin >> numberOfCells; cin.ignore();
    vector<int> grid(numberOfCells * cell_data_size);
    vector<int> trees(numberOfCells * tree_data_size);
    for (int i = 0; i < numberOfCells; i++) {
        vector<int> cell(cell_data_size);
        for (int j{0}; j < cell_data_size; j++) {
            cin >> grid[vec_walk("map", i, j)];
        }
        cin.ignore();
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
        trees.resize(numberOfTrees * tree_data_size);
        for (int i = 0; i < numberOfTrees; i++) {
            
            for (int j{0}; j < tree_data_size; j++){
                cin >> trees[vec_walk("tree", i, j)];
            }
            cin.ignore();
        }
        int numberOfPossibleActions; // all legal actions
        cin >> numberOfPossibleActions; cin.ignore();
        for (int i = 0; i < numberOfPossibleActions; i++) {
            string possibleAction;
            getline(cin, possibleAction); // try printing something from here to start with
        }
        int harvest_tree {};
        int tree_points {};
        for (int i{0}; i < numberOfPossibleActions; i++){
            for (int j{0}; j < numberOfTrees; j++){
                if (trees[vec_walk("tree", j, tree_isMine)]){
                    int tree_index = trees[vec_walk("tree", j, index)];
                    int new_tree_points = possible_points(tree_index, nutrients, grid);
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

    }
}