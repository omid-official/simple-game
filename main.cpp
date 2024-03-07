#include <iostream>
#include <ncurses.h>
#include "Perlin/perlin.hpp"
#include "Engine/Engine.hpp"
#include <string>
#include <unistd.h>
using namespace std;


class Game: public Engine{
    const char SpaceChar = ' ';
    const char PlayerChar = '@';
    const char WallChar = '.';
    const char EnemyChar = 'E';
    const char FruitChar = '$';
    int FruitRespawnTime = 0;
    Point Player;
    int Score;
    Point fruit;
    vector<Point> Enemies;


    void SetupPlayer(){
        bool HaveCollision = true;
        while(HaveCollision){
            Player.y = RandomInt(0, Max.y - 1);
            Player.x = RandomInt(0, Max.x - 1);
            if(!(World[Player.y][Player.x] == WallChar)){
                HaveCollision = false;
            }
        }
    }
    void SpawnFruit(bool Caught = false){
        if(FruitRespawnTime == 0){
            FruitRespawnTime = 150;
            do{
                fruit.y = RandomInt(0, Max.y - 1);
                fruit.x = RandomInt(0, Max.x - 1);
            }while (World[fruit.y][fruit.x] == WallChar || World[fruit.y][fruit.x] == PlayerChar);
        }
        if(Caught){
            Score += 10;
            FruitRespawnTime = 150;
            do{
                fruit.y = RandomInt(0, Max.y - 1);
                fruit.x = RandomInt(0, Max.x - 1);
            }while (World[fruit.y][fruit.x] == WallChar || World[fruit.y][fruit.x] == PlayerChar);
        }
        FruitRespawnTime --;     
    }
    void SetupEnemies(){
        Enemies.resize(5);
        Point enemy;
        for(int i = 0; i < Enemies.size(); i++){
            enemy = Enemies[i];
            do {
                enemy.y = RandomInt(0, Max.y - 1);
                enemy.x = RandomInt(0, Max.x - 1);
            } while (World[enemy.y][enemy.x] == WallChar || World[enemy.y][enemy.x] == PlayerChar);
            Enemies[i] = enemy;
        }
    }
    void MoveEnemies(){
        for(int i = 0; i < Enemies.size(); i++){
            if(RandomInt(0, 50) > 40){
                Point enemy = Enemies[i];
                if(enemy.x > Player.x){
                    enemy.x --;
                    if(!IsInWindow(enemy)){
                        enemy.x ++;
                    }
                    if(CheckCollision(enemy) == WallChar){
                        enemy.x ++;
                    }
                }else{
                    enemy.x ++;
                    if(!IsInWindow(enemy)){
                        enemy.x --;
                    }
                    if(CheckCollision(enemy) == WallChar){
                        enemy.x --;
                    }
                }
                if(enemy.y > Player.y){
                    enemy.y --;
                    if(!IsInWindow(enemy)){
                        enemy.y ++;
                    }
                    if(CheckCollision(enemy) == WallChar){
                        enemy.y ++;
                    }
                }else{
                    enemy.y ++;
                    if(!IsInWindow(enemy)){
                        enemy.y --;
                    }
                    if(CheckCollision(enemy) == WallChar){
                        enemy.y --;
                    }
                }
                if(enemy.x == Player.x && enemy.y == Player.y){
                    StopGame();
                }
                Enemies[i] = enemy;
            }
        }
    }
    void DrawEnemies(){
        for(int i = 0; i < Enemies.size(); i++){
            Point enemy = Enemies[i];
            mvaddch(enemy.y, enemy.x, EnemyChar);
        }
    }
    void InitialVoid(){
        for(int i = 0; i < World.size(); i++){
            for(int j = 0; j < World[i].size(); j++){
                char ch = (RandomFloat(0.001f, 1.0f) > 0.03f) ?  SpaceChar : WallChar;
                World[i][j] = ch;
            }
        }
    }
    void GetInput(){
        char ch = getch();
        switch(ch) {
            case 'w':
                Player.y --;
                if(!IsInWindow(Player)){
                    Player.y ++;
                }
                if(CheckCollision(Player) == WallChar){
                    Player.y ++;
                }
                if(Player.y == fruit.y && Player.x == fruit.x){
                    SpawnFruit(true);
                }
                break;
            case 's':
                Player.y ++;
                if(!IsInWindow(Player)){
                    Player.y --;
                }
                if(CheckCollision(Player) == WallChar){
                    Player.y --;
                }
                if(Player.y == fruit.y && Player.x == fruit.x){
                    SpawnFruit(true);
                }
                break;
            case 'a':
                Player.x --;
                if(!IsInWindow(Player)){
                    Player.x ++;
                }
                if(CheckCollision(Player) == WallChar){
                    Player.x ++;
                }
                if(Player.y == fruit.y && Player.x == fruit.x){
                    SpawnFruit(true);
                }
                break;
            case 'd':
                Player.x ++;
                if(!IsInWindow(Player)){
                    Player.x --;
                }
                if(CheckCollision(Player) == WallChar){
                    Player.x --;
                }
                if(Player.y == fruit.y && Player.x == fruit.x){
                    SpawnFruit(true);
                }
                break;
            case 'q':
                StopGame();
                break;
        }
    }
    void Start() override{
        InitialVoid();
        SetupPlayer();
        SpawnFruit();
        SetupEnemies();
    }
    void Draw() override{
        for(int i = 0; i < World.size(); i++){
            for(int j = 0; j < World[i].size(); j++){
                mvaddch(i, j, World[i][j]);
            }
        }
        mvaddch(Player.y, Player.x, PlayerChar);
        DrawEnemies();
        mvaddch(fruit.y, fruit.x, FruitChar);
        mvaddstr(0, 0, ("Score: " + to_string(Score)).c_str());
        refresh();
    }
    void Update() override{
        GetInput();
        MoveEnemies();
        SpawnFruit();
        Draw();  
    }
    public:
    Game(){
        Score = 0;
    }
};

int main(){
    Game game;
    game.Run();
    return 0;
}