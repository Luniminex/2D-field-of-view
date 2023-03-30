//
// Created by luniminex on 3/16/23.
//

#include "Circle.h"

Circle::Circle(int x, int y, int radius) {
    x_ = x;
    y_ = y;
    radius_ = radius;
    color_ = {255, 255, 255, 255};
}

Circle::Circle(int x, int y, int radius, SDL_Color color) {
    x_ = x;
    y_ = y;
    radius_ = radius;
    color_ = color;
}

int Circle::GetX() {
    return x_;
}

int Circle::GetY() {
    return y_;
}

int Circle::GetRadius() {
    return radius_;
}

void Circle::SetColor(SDL_Color clr) {
    color_ = clr;
}

void Circle::Update(const float &dt) {

}

void Circle::Draw(SDL_Renderer *renderer) { //https://stackoverflow.com/questions/65723827/sdl2-function-to-draw-a-filled-circle
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    for (int x = x_ - radius_; x <= x_ + radius_; x++) { //chatgpt be like: here is solution for you
        for (int y = y_ - radius_; y <= y_ + radius_; y++) {
            // Calculate the distance from the pixel to the center of the circle
            int dx = x - x_;
            int dy = y - y_;
            // Set the renderer's draw color to a fully opaque color with the calculated alpha value
            if ((dx*dx + dy*dy) <= (radius_ * radius_)) {
                // Draw a point at the current pixel location
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Circle::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color_.r = r;
    color_.g = g;
    color_.b = b;
    color_.a = a;
}

void Circle::SetPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Circle::SetRadius(int radius) {
    radius_ = radius;
}
