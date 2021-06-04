#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


int main()
{
    int W, H; // width/height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0, Y0; // Batman starting position.
    cin >> X0 >> Y0; cin.ignore();
    int x {0}, y {0};
    int xmin {-1}, xmax {W + 1};
    int ymin {-1}, ymax {H + 1};

    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for (int i = 0; i < bombDir.length(); i++){
            switch(bombDir[i]){
                case 'U':
                    y = (Y0 + ymin) / 2;
                    ymax = Y0;
                    Y0 = y;
                    break;
                case 'D':
                    y = (Y0 + ymax) / 2;
                    ymin = Y0;
                    Y0 = y;
                    break;
                case 'L':
                    x = (X0 + xmin) / 2;
                    xmax = X0;
                    X0 = x;
                    break;
                case 'R':
                    x = (X0 + xmax) / 2;
                    xmin = X0;
                    X0 = x;
                    break;
            }
        }
        // DEBUG: cerr << "Xmin: " << xmin << " Xmax: " << xmax << endl;
        // the location of the next window Batman should jump to.
        cout << x << " " << y << endl;
    }
}
