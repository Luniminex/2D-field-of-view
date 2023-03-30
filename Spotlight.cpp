//
// Created by luniminex on 3/24/23.
//

#include "Spotlight.h"

Spotlight::Spotlight(int x, int y, int radius, Uint8 brightness) : Circle(x, y, radius){
    color_.a = brightness;
}

void Spotlight::Draw(SDL_Renderer *renderer) {
    int dx, dy;
    float distance;
    for (int x = x_ - radius_; x <= x_ + radius_; x++) { //chatgpt be like: here is solution for you
        for (int y = y_ - radius_; y <= y_ + radius_; y++) {
            // Calculate the distance from the pixel to the center of the circle
            dx = x - x_;
            dy = y - y_;
            distance = std::sqrt(dx * dx + dy * dy);

            // Calculate the alpha value for the pixel based on its distance from the center
            Uint8 alpha = color_.a * (1 - distance / radius_);

            // Set the renderer's draw color to a fully opaque color with the calculated alpha value
            SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, alpha);
            if ((dx*dx + dy*dy) <= (radius_ * radius_)) {
                // Draw a point at the current pixel location
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}
