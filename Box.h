//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_BOX_H
#define LIGHTINGEXAMPLE_BOX_H

#include "Entity.h"

class Box : public Entity {
public:
    Box(int x, int y, int w, int h);
    Box(int x, int y, int w, int h, SDL_Color clr);
    SDL_Rect& GetBody();
    SDL_Color& GetColor();
    void SetColor(SDL_Color clr);
    void Update(const float& dt) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    SDL_Rect body_;
    SDL_Color color_;
};


#endif //LIGHTINGEXAMPLE_BOX_H
