//
// Created by luniminex on 3/24/23.
//

#include "Wall.h"

Wall::Wall(SDL_Point start, SDL_Point end) {
    start_ = start;
    end_ = end;
    radians_ = 0;
}

void Wall::Update(const float &dt) {

}

void Wall::Draw(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer, start_.x, start_.y, end_.x, end_.y);
}

void Wall::MakeFromRect(SDL_Rect rect, Side side) {
    switch (side) {
        case Side::top:
            start_.x = rect.x;
            start_.y = rect.y;
            end_.x = rect.x + rect.w;
            end_.y = rect.y;
            break;
        case Side::right:
            start_.x = rect.x + rect.w;
            start_.y = rect.y;
            end_.x = rect.x + rect.w;
            end_.y = rect.y + rect.h;
            break;
        case Side::down:
            start_.x = rect.x + rect.w;
            start_.y = rect.y + rect.h;
            end_.x = rect.x;
            end_.y = rect.y + rect.h;
            break;
        case Side::left:
            start_.x = rect.x;
            start_.y = rect.y + rect.h;
            end_.x = rect.x;
            end_.y = rect.y;
            break;
    }
}

Wall::Wall() {

}

void Wall::Make(int x1, int y1, int x2, int y2) {
    start_.x = x1;
    start_.y = y1;
    end_.x = x2;
    end_.y = y2;
}

SDL_Point Wall::GetStart() {
    return start_;
}

SDL_Point Wall::GetEnd() {
    return end_;
}

void Wall::SetStart(int x1, int y1) {
    start_.x = x1;
    start_.y = y1;
}

void Wall::CastWall(int x, int y, int size, double radians) {
    double dirX = cos(radians);
    double dirY = sin(radians);

    start_.x = x;
    start_.y = y;

    end_.x = static_cast<int>(static_cast<double>(x) + dirX * static_cast<double>(size));
    end_.y = static_cast<int>(static_cast<double>(y) + dirY * static_cast<double>(size));
}

void Wall::CastWall(int x, int y, int size, double radians, bool offsetRight) {
    double offset = 0.05;
    if(offsetRight){
       offset *= -1;
   }

    double dirX = cos(radians + offset);
    double dirY = sin(radians + offset);

    start_.x = x;
    start_.y = y;

    end_.x = static_cast<int>(static_cast<double>(x) + dirX * static_cast<double>(size));
    end_.y = static_cast<int>(static_cast<double>(y) + dirY * static_cast<double>(size));
}

void Wall::SetTarget(int x1, int y1) {
    target_.x = x1;
    target_.y = y1;
}

SDL_Point Wall::GetTarget() {
    return target_;
}

void Wall::SetEnd(int x2, int y2) {
    end_.x = x2;
    end_.y = y2;
}

double Wall::GetRadians() const {
    return radians_;
}

void Wall::CalculateMyRadians() {
    radians_ = atan2(end_.y - start_.y, end_.x - start_.x);
}
