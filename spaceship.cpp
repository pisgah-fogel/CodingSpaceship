#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {int x; int y;} Position;

const float gravity = 3.711;
const int speedx_max = 20;
const int speedy_max = 40;

struct {
    Position* map; // Map
    Position position; // Position of the orbiters
    Position speed; // speed (in m/s), can be negative.
    int fuel; // the quantity of remaining fuel in liters.
    int rotation; // the rotation angle in degrees (-90 to 90).
    int thrust; // the thrust power (0 to 4).
} GameData;



int clamp_int(const int val, const int min, const int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

double cos_deg(int angle) {
    return cos(3.1415*angle/180.0);
}

double sin_deg(int angle) {
    return sin(3.1415*angle/180.0);
}

Position predict_landing() {
    int x = GameData.position.x;
    int y = GameData.position.y;
    int vx = GameData.speed.x;
    int vy = GameData.speed.y;
    int thrust = GameData.thrust;
    int angle = GameData.rotation;
    double time = 0;
    const double dt = 1.0;
    for (;;) {
        vx = vx + thrust*dt*sin_deg(angle);
        x = x + dt*vx;

        vy = vy + thrust*dt*cos_deg(angle) + dt*gravity;
        y = y - dt*vy;
        time += dt;
    }
}

// If true, need to set thrust = 4
bool need_braking(...) {

}

int main()
{
    int N; // the number of points used to draw the surface of Mars.
    cin >> N; cin.ignore();

    GameData.map = malloc(N*sizeof(Position));

    if (GameData.map == NULL) {
        cout<<"Error: cannot allocate memory"<<endl;
    }

    for (int i = 0; i < N; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        GameData.map[i] = Position {.x = landX, .y = landY};
    }

    // game loop
    while (1) {
        cin >> GameData.position.x >> GameData.position.y >> GameData.speed.x >> GameData.speed.y >> GameData.fuel >> GameData.rotation >> GameData.thrust; cin.ignore();

        int cmd_rot = clamp_int(-R/2, -15, 15);
        // cerr << "Debug messages..." << endl;
        int cmd_thrust = 2;

        // R P. R is the desired rotation angle. P is the desired thrust power.
        cout << cmd_rot << " " << cmd_thrust << endl;
    }

    delete (GameData.map);
}