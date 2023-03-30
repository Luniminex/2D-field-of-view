//
// Created by luniminex on 3/24/23.
//

#ifndef LIGHTINGEXAMPLE_WALL_H
#define LIGHTINGEXAMPLE_WALL_H

#include <iostream>
#include <cmath>
#include "Entity.h"


enum class Side {top, right, down, left};

class Wall : public Entity{
public:
    Wall(SDL_Point start, SDL_Point end);
    Wall();
    SDL_Point GetStart();
    SDL_Point  GetEnd();
    double GetRadians() const;
    void SetStart(int x1, int y1);
    void SetEnd(int x2, int y2);
    void SetTarget(int x1, int y1);
    SDL_Point GetTarget();
    void MakeFromRect(SDL_Rect rect, Side side);
    void CastWall(int x, int y, int size, double radians);
    void CastWall(int x, int y, int size, double radians, bool offsetRight);
    void Make(int x1, int y1, int x2, int y2);
    void Update(const float& dt) override;
    void Draw(SDL_Renderer* renderer) override;
    void CalculateMyRadians();
private:
    SDL_Point start_;
    SDL_Point end_;
    SDL_Point target_;
    double radians_;
};


#endif //LIGHTINGEXAMPLE_WALL_H
