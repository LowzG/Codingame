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
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    int x {0};
    int y {0};
    int xmin {-1};
    int xmax {W + 1};
    int ymin {-1};
    int ymax {H + 1};

    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for (int i = 0; i < bombDir.length(); i++){
            string direction {bombDir[i]};
            if (direction == "U"){
                y = Y0 - (Y0 - ymin) / 2;
                ymax = Y0;
                Y0 = y;
                }
            else if (direction == "D"){
                y = (ymax - Y0) / 2 + Y0;
                ymin = Y0;
                Y0 = y;
            }
            else if (direction == "L"){
                x = X0 - (X0 - xmin) / 2;
                xmax = X0;
                X0 = x;
            }
            else if (direction == "R") {
                x = (xmax - X0) / 2 + X0;
                xmin = X0;
                X0 = x;
            }
        }

        // the location of the next window Batman should jump to.
        cout << x << " " << y << endl;
    }
}
