#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int cell_data_size {8};
int tree_data_size {4};

int grid_walk(int grid_index, int cell_index){
    // Wrote this to avoid creating 2D vectors
    return cell_index + (grid_index * cell_data_size);
} 

int possible_points(int tree_index, int forest_nutrient, vector<int> &grid) {
    return forest_nutrient + grid[grid_walk(tree_index, 1)];
}

int main(){
    int numberOfCells; // 37
    cin >> numberOfCells; cin.ignore();
    vector<int> grid(numberOfCells * cell_data_size);
    vector<int> trees(numberOfCells * tree_data_size);
    for (int i = 0; i < numberOfCells; i++) {
        // int index; // 0 is the center cell, the next cells spiral outwards
        // int richness; // 0 if the cell is unusable, 1-3 for usable cells
        // int neigh0; // the index of the neighbouring cell for each direction
        // int neigh1;
        // int neigh2;
        // int neigh3;
        // int neigh4;
        // int neigh5;
        // cin >> index >> richness >> neigh0 >> neigh1 >> neigh2 >> neigh3 >> neigh4 >> neigh5; cin.ignore();
        vector<int> cell(cell_data_size);
        for (int j{0}; j < cell_data_size; j++) {
            cin >> grid[grid_walk(i, j)];
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
            // int cellIndex; // location of this tree
            // int size; // size of this tree: 0-3
            // bool isMine; // 1 if this is your tree
            // bool isDormant; // 1 if this tree is dormant
            // cin >> cellIndex >> size >> isMine >> isDormant; cin.ignore();
            for (int j{0}; j < tree_data_size; j++){
                cin >> trees[grid_walk(i, j)];
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
                if (trees[grid_walk(j, 2)]){
                    int tree_index = trees[grid_walk(j, 0)];
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