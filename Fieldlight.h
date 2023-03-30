//
// Created by luniminex on 3/24/23.
//

#ifndef LIGHTINGEXAMPLE_FIELDLIGHT_H
#define LIGHTINGEXAMPLE_FIELDLIGHT_H

#include <vector>
#include <tuple>
#include "Wall.h"
#include "Circle.h"


class Fieldlight {
public:
    Fieldlight(int size);
    void SetPos(int x, int y);
    void GenerateRays(std::vector<Wall>& walls);
    void Update();
    void Draw(SDL_Renderer* renderer, bool drawLight, bool drawRays, bool drawIntersections);
    void DrawFOV(SDL_Renderer* renderer);
    void CheckCollision(std::vector<Wall>& walls, bool increaseRays, bool decreaseRays);
private:
    void CastRays(int NORays);
    double CalculateRadian(SDL_Point start, SDL_Point end);
    void OrderIntersectionsByRadian();
    void CheckOffsetCollision(std::vector<Wall>& walls, bool increaseRays, bool decreaseRays);
    void CalcDistToPointInter(double& uA, double& uB, double x1, double x2, double x3, double x4,
                              double y1,double y2, double y3, double y4);

    //returns distance between two points
    double CalculateDistance(double x1, double y1, double x2, double y2);
    void SetTuple(std::tuple<bool, SDL_Point, Wall>& tuple, bool first, SDL_Point intersection, Wall wall);
    void CastOffsetRays(SDL_Point start, SDL_Point end);
    void IncreaseRays(bool increase, bool decrease);
    std::vector<Wall> rays_;
    std::vector<Wall> offsetRays_;
    std::vector<SDL_Point> intersections_;
    SDL_Point pos_;
    int NORays_; // no of rays that are manually cast in a circle, they automatically go to offset rays
    int size_;
};


#endif //LIGHTINGEXAMPLE_FIELDLIGHT_H
