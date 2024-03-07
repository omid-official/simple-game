#ifndef ENGINE_H
#define ENGINE_H
#include <vector>

struct Point
{
    int x, y;
};
// enum ExitMode{
//     GameOverMode,
//     QuitMode
// };

class Engine
{
    public:
    bool Playing;
    Point Max;
    // ExitMode exitMode;
    std::vector<std::vector<char>> World;
    Engine();
    void Run();
    void StopGame();
    int RandomInt(int min, int max);
    float RandomFloat(float min, float max);
    char CheckCollision(Point point);
    bool IsInWindow(Point point);

    virtual void Draw();
    virtual void Start();
    virtual void Update();
};


#endif