//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_ENTITY_H
#define LIGHTINGEXAMPLE_ENTITY_H

#include <SDL2/SDL.h>

class Entity {

public:
    virtual void Update(const float& dt) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
};

#endif //LIGHTINGEXAMPLE_ENTITY_H
