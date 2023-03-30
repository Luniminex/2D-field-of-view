//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_CIRCLE_H
#define LIGHTINGEXAMPLE_CIRCLE_H

#include <iostream>
#include "Entity.h"

class Circle : public Entity {
public:
    Circle(int x, int y, int radius);
    Circle(int x, int y, int radius, SDL_Color color);
    void SetPosition(int x, int y);
    void SetRadius(int radius);
    int GetX();
    int GetY();
    int GetRadius();
    void SetColor(SDL_Color clr);
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void Update(const float& dt) override;
    void Draw(SDL_Renderer* renderer) override;
protected:
    SDL_Color color_;
    int x_;
    int y_;
    int radius_;
};


#endif //LIGHTINGEXAMPLE_CIRCLE_H
