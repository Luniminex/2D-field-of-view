//
// Created by luniminex on 3/24/23.
//

#ifndef LIGHTINGEXAMPLE_SPOTLIGHT_H
#define LIGHTINGEXAMPLE_SPOTLIGHT_H

#include "Circle.h"
/*
 * color_.a is used for brightness
 */
class Spotlight : public Circle {
public:
    Spotlight(int x, int y, int radius, Uint8 brightness);

    void Draw(SDL_Renderer* renderer) override;
};


#endif //LIGHTINGEXAMPLE_SPOTLIGHT_H
