#include "Engine.hpp"
#include "ncurses.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;

void Engine::Draw(){
    for(int i = 0; i < World.size(); i++){
        for(int j = 0; j < World[i].size(); j++){
            mvaddch(i, j, World[i][j]);
        }
    }
    refresh();
}
void Engine::StopGame(){
    Playing = false;
}
void Engine::Run(){
    Start();
    while (Playing){
        Update();
    }
    endwin();
    // if(exitMode == QuitMode){
    //     cout << "Come soon and play with us!" << endl;
    // }
}

Engine::Engine(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    timeout(200);
    clear();
    refresh();

    int x, y;
    Playing = true;
    getmaxyx(stdscr, y, x);
    Max.x = x - 1;
    Max.y = y - 1;

    World.resize(Max.y, vector<char>(Max.x));
}


int Engine::RandomInt(int min, int max){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis(min, max);
    int random_number = dis(gen);
    return random_number;
}
float Engine::RandomFloat(float min, float max){
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<float> dis(min, max);

    float random_float = dis(gen);
    return random_float;
}

bool Engine::IsInWindow(Point point){
    if(point.x > Max.x - 1 || point.x < 0 || point.y > Max.y - 1 || point.y < 0){
        return false;
    }
    return true;
}

char Engine::CheckCollision(Point point){
    return World[point.y][point.x];
}

void Engine::Update(){

}

void Engine::Start(){

}