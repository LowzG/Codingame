#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Save humans, destroy zombies!
 **/

 vector<int> closest_zombie(int youx, int youy, vector<vector<int>> &zombies) {
     vector<int> closest_zombiecords;
     int closest {0};

     for (auto zombie: zombies) {
         int zombiex {zombie[1]};
         int zombiey {zombie[2]};
         cerr << "x: " << youx << endl;
         cerr << "y: " << youy << endl;
         cerr << "zombiex: " << zombiex << endl;
         cerr << "zombiey: " << zombiey << endl;
         int diff {(abs(zombiex - youx)) + (abs(zombiey - youy))};
         cerr << "diff: " << diff << "closest: " << closest << endl;
         if (closest && diff > closest) {
             continue;
         }
        closest = diff;
        closest_zombiecords.push_back(zombiex);
        closest_zombiecords.push_back(zombiey);
     }
     return closest_zombiecords;
 }

int main() { 

    // game loop
    while (1) {
        vector<vector<int>> zombies; 
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        int humanCount;
        cin >> humanCount; cin.ignore();
        for (int i = 0; i < humanCount; i++) {
            int humanId;
            int humanX;
            int humanY;
            cin >> humanId >> humanX >> humanY; cin.ignore();
        }
        int zombieCount;
        cerr << "Zombie count: " << zombieCount << endl;
        cin >> zombieCount; cin.ignore();
        for (int i = 0; i < zombieCount; i++) {
            int zombieId;
            int zombieX;
            int zombieY;
            int zombieXNext;
            int zombieYNext;
            cin >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; cin.ignore();
            vector<int> zombie {zombieId, zombieX, zombieY, zombieXNext, zombieYNext};
            zombies.push_back(zombie);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << zombies.size() << endl;

        vector<int> nextzombie = closest_zombie(x, y, zombies);

        cout << nextzombie[0] << " " << nextzombie[1] << endl; // Your destination coordinates
    }
}
