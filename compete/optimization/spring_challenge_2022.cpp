#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Entity {
    public:
        int id; // Unique identifier
        int type; // 0=monster, 1=your hero, 2=opponent hero
        int x; // Position of this entity
        int y;
        int shield_life; // Ignore for this league; Count down until shield spell fades
        int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
        int health; // Remaining health of this monster
        int vx; // Trajectory of this monster
        int vy;
        int near_base; // 0=monster with no target yet, 1=monster targeting a base
        int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
};

int main()
{
    int base_x; // The corner of the map representing your base
    int base_y;
    cin >> base_x >> base_y; cin.ignore();
    int heroes_per_player; // Always 3
    cin >> heroes_per_player; cin.ignore();

    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            int health; // Your base health
            int mana; // Ignore in the first league; Spend ten mana to cast a spell
            cin >> health >> mana; cin.ignore();
        }
        int entity_count; // Amount of heros and monsters you can see
        cin >> entity_count; cin.ignore();
        for (int i = 0; i < entity_count; i++) {
            Entity new_entity;
            cin >> new_entity.id >> new_entity.type >> new_entity.x >> new_entity.y >> new_entity.shield_life >> new_entity.is_controlled >> new_entity.health >> new_entity.vx >> new_entity.vy >> new_entity.near_base >> new_entity.threat_for; cin.ignore();

            switch (new_entity.type){
                case 0:
                    cerr << "Entity is a monster" << endl;
                    break;
                case 1:
                    cerr << "Entity is a hero" << endl;
                    break;
                case 2:
                    cerr << "Entity is an opponent hero" << endl;
                    break;
            }
        }
        for (int i = 0; i < heroes_per_player; i++) {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;


            // In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
            cout << "WAIT" << endl;
        }
    }
}