//
// Created by luniminex on 3/24/23.
//

#include "Fieldlight.h"

Fieldlight::Fieldlight(int size) {
    pos_ = { 0, 0 };
    size_ = size;
    NORays_ = 50;
}

void Fieldlight::SetPos(int x, int y) {
    pos_.x = x;
    pos_.y = y;
}

void Fieldlight::GenerateRays(std::vector<Wall> &walls) {
    Wall ray;
    for(auto& wall : walls){
        ray.Make(pos_.x, pos_.y, wall.GetStart().x, wall.GetStart().y);
        ray.SetTarget(wall.GetStart().x, wall.GetStart().y);
        rays_.push_back(ray);
    }
}


void Fieldlight::DrawFOV(SDL_Renderer *renderer) {
    auto* vertices = new float[6];
    auto* color = new SDL_Color[3];
    color[0] = {255, 255, 255, 0};
    color[1] = {255, 255, 255, 0};
    color[2] = {255, 255, 255, 255};
    vertices[4] = static_cast<float>(pos_.x);
    vertices[5] = static_cast<float>(pos_.y);
    int result;
    Uint8 alpha;
    double distance;
    for(int i = 0; i < intersections_.size() - 1; i++){
        vertices[0] = static_cast<float>(intersections_.at(i).x);
        vertices[1] = static_cast<float>(intersections_.at(i).y); // calculates how far away from the centre is the vertex
        distance = CalculateDistance(pos_.x, pos_.y, intersections_.at(i).x, intersections_.at(i).y);
        result = static_cast<int>(255 * (1.f - (distance / size_))); //and assigns alpha to it
        if(result < 0){
            alpha = 0;
        }
        else{
            alpha = result;
        }
        color[0] = {255, 255, 255, alpha};

        vertices[2] = static_cast<float>(intersections_.at(i+1).x);
        vertices[3] = static_cast<float>(intersections_.at(i+1).y);
        distance = CalculateDistance(pos_.x, pos_.y, intersections_.at(i+1).x, intersections_.at(i+1).y);
        result = static_cast<int>(255 * (1 - distance / size_));
        if(result < 0){
            alpha = 0;
        }
        else{
            alpha = result;
        }
        color[1] = {255, 255, 255, alpha};

        SDL_RenderGeometryRaw(renderer, nullptr, vertices, 8, color, 4, vertices, 4, 3, nullptr, 0, 0);
    }
    //draws triangle between last and first
    vertices[0] = static_cast<float>(intersections_.at(0).x);
    vertices[1] = static_cast<float>(intersections_.at(0).y);
    vertices[2] = static_cast<float>(intersections_.at(intersections_.size() - 1).x);
    vertices[3] = static_cast<float>(intersections_.at(intersections_.size() - 1).y);
    SDL_RenderGeometryRaw(renderer, nullptr, vertices, 8, color, 4, vertices, 4, 3, nullptr, 0, 0);

    delete[] vertices;
    delete[] color;
}

void Fieldlight::Draw(SDL_Renderer *renderer, bool drawLight, bool drawRays, bool drawIntersections) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    OrderIntersectionsByRadian();
    if(drawRays) {
        for (auto &ray: rays_) {
            ray.Draw(renderer);
        }
        for (auto &ray: offsetRays_) {
            ray.Draw(renderer);
        }
    }
    if(drawIntersections){
        Circle circle(0, 0, 3, {255, 0, 0, 255});
        for(auto& hit : intersections_){
            circle.SetPosition(hit.x, hit.y);
            circle.Draw(renderer);
        }
    }
    if(drawLight)
        DrawFOV(renderer);
}

void Fieldlight::Update() {
    for(auto& ray : rays_){
        ray.SetStart(pos_.x, pos_.y);
    }
    offsetRays_.clear();
}

void Fieldlight::CheckCollision(std::vector<Wall> &walls, bool increaseRays, bool decreaseRays) {
    intersections_.clear();
    std::tuple<bool, SDL_Point, Wall> previousIntersection;
    double distFirst, distSecond;
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double interX, interY, uA, uB;
    x1 = static_cast<double>(rays_.at(0).GetStart().x);
    y1 = static_cast<double>(rays_.at(0).GetStart().y);
    for(auto& ray : rays_){
        x2 = static_cast<double>(ray.GetEnd().x);
        y2 = static_cast<double>(ray.GetEnd().y);
        std::get<0>(previousIntersection) = false;
        for(auto& wall : walls){
            x3 = static_cast<double >(wall.GetStart().x);
            y3 = static_cast<double>(wall.GetStart().y);
            x4 = static_cast<double>(wall.GetEnd().x);
            y4 = static_cast<double>(wall.GetEnd().y);
            CalcDistToPointInter(uA, uB, x1, x2, x3, x4, y1, y2, y3, y4);
            if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
                interX = x1 + (uA * (x2-x1)); // calculates intersection point
                interY = y1 + (uA * (y2-y1));
                distFirst = CalculateDistance(interX, interY, x1, y1);
                if(distFirst > size_) // if distance is greater than size, continue
                    continue;

                if(std::get<0>(previousIntersection)){ //if there was a previous intersection for this ray before
                    distFirst = CalculateDistance(interX, interY, x1, y1);
                    distSecond = CalculateDistance( std::get<1>(previousIntersection).x,std::get<1>(previousIntersection).y ,x1, y1);

                    if(distFirst < distSecond){ //if the new one is closer, set it as previous
                        SetTuple(previousIntersection, true, {static_cast<int>(interX), static_cast<int>(interY)}, wall);
                    }
                } // if there was no intersection for this ray before, add it to previous one
                if(!std::get<0>(previousIntersection)){
                    SetTuple(previousIntersection, true, {static_cast<int>(interX), static_cast<int>(interY)}, wall);
                }
            }
        }
        if(std::get<0>(previousIntersection)){ //set the closest intersection as the intersection point
            intersections_.push_back(std::get<1>(previousIntersection));
            CastOffsetRays({static_cast<int>(x1), static_cast<int>(y1)}, intersections_.back());
            ray.SetEnd(ray.GetTarget().x, ray.GetTarget().y); // if there was intersection, set ray end to target
        }
        else{ // if there wasn't any intersection, imitate the ray by casting it using angle to its target
            ray.CastWall(ray.GetStart().x, ray.GetStart().y, size_, CalculateRadian(ray.GetStart(), ray.GetTarget()));
            intersections_.push_back(ray.GetEnd());
        }
    }
    CheckOffsetCollision(walls, increaseRays, decreaseRays);
}

void Fieldlight::CheckOffsetCollision(std::vector<Wall> &walls, bool increaseRays, bool decreaseRays) {
    IncreaseRays(increaseRays, decreaseRays);
    CastRays(NORays_); // i have found that about 100 rays makes visual artefacts quite rare

    std::tuple<bool, SDL_Point, Wall> previousIntersection;
    double distFirst, distSecond;
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double interX, interY, uA, uB;
    x1 = static_cast<double>(rays_.at(0).GetStart().x);
    y1 = static_cast<double>(rays_.at(0).GetStart().y);
    for(auto& ray : offsetRays_){
        x2 = static_cast<double>(ray.GetEnd().x);
        y2 = static_cast<double>(ray.GetEnd().y);
        std::get<0>(previousIntersection) = false;
        for(auto& wall : walls){
            x3 = static_cast<double >(wall.GetStart().x);
            y3 = static_cast<double>(wall.GetStart().y);
            x4 = static_cast<double>(wall.GetEnd().x);
            y4 = static_cast<double>(wall.GetEnd().y);
            CalcDistToPointInter(uA, uB, x1, x2, x3, x4, y1, y2, y3, y4);
            if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
                interX = x1 + (uA * (x2-x1)); // calculates intersection point
                interY = y1 + (uA * (y2-y1));
                distFirst = CalculateDistance(interX, interY, x1, y1);
                if(distFirst > size_) // if distance is greater than size, continue
                    continue;

                if(std::get<0>(previousIntersection)){ //if there was a previous intersection for this ray before
                    distFirst = CalculateDistance(interX, interY, x1, y1);
                    distSecond = CalculateDistance( std::get<1>(previousIntersection).x,std::get<1>(previousIntersection).y ,x1, y1);

                    if(distFirst < distSecond){ //if the new one is closer, set it as previous
                        SetTuple(previousIntersection, true, {static_cast<int>(interX), static_cast<int>(interY)}, wall);
                    }
                } // if there was no intersection for this ray before, add it to previous one
                if(!std::get<0>(previousIntersection)){
                    SetTuple(previousIntersection, true, {static_cast<int>(interX), static_cast<int>(interY)}, wall);
                }
            }
        }
        if(std::get<0>(previousIntersection)) { //set the closest intersection as the intersection point
            intersections_.push_back(std::get<1>(previousIntersection));
        }
        else{
            intersections_.push_back({static_cast<int>(x2), static_cast<int>(y2)});
        }
    }
}

void Fieldlight::OrderIntersectionsByRadian() {
    std::vector<double> interRadians;
    for(auto& inter : intersections_){ //calculates for each intersection radian between intersection and pos
        interRadians.push_back(CalculateRadian(pos_, inter));
    }
        for (int i = 0; i < intersections_.size(); i++) {
            for (int j = 0; j < intersections_.size(); j++) { //orders intersections by radian
                if (interRadians.at(i) > interRadians.at(j)) {
                    std::swap(interRadians[i], interRadians[j]);
                    std::swap(intersections_[i], intersections_[j]);
                }
            }
        }
}

void Fieldlight::CalcDistToPointInter(double &uA, double &uB, double x1, double x2, double x3, double x4,
                                      double y1, double y2, double y3, double y4) {
    uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
}

double Fieldlight::CalculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(abs((pow(x2 - x1, 2)) + (pow(y2 - y1, 2))));
}

void Fieldlight::SetTuple(std::tuple<bool, SDL_Point, Wall>& tuple, bool first, SDL_Point intersection, Wall wall) {
    std::get<0>(tuple) = first;
    std::get<1>(tuple) = {static_cast<int>(intersection.x), static_cast<int>(intersection.y)};
    std::get<2>(tuple) = std::move(wall);
}

void Fieldlight::CastOffsetRays(SDL_Point start, SDL_Point end) {
    Wall wall;
    wall.CastWall(start.x, start.y, size_, CalculateRadian(start, end), true);
    offsetRays_.push_back(wall);
    wall.CastWall(start.x, start.y, size_, CalculateRadian(start, end), false);
    offsetRays_.push_back(wall);
}

double Fieldlight::CalculateRadian(SDL_Point start, SDL_Point end) {
    return atan2(end.y - start.y, end.x - start.x);
}

void Fieldlight::CastRays(int NORays) {
    Wall ray;
    double increment = (2 * M_PI) / static_cast<double>(NORays);
    for(int i = 0; i < NORays; i++){
        ray.CastWall(pos_.x, pos_.y, size_, i * increment);
        offsetRays_.push_back(ray);
    }
}

void Fieldlight::IncreaseRays(bool increase, bool decrease) {
    if(increase)
        NORays_++;
    if(increase)
        NORays_--;
    if(NORays_ < 0)
        NORays_ = 0;
    if(increase || decrease)
        std::cout<<"No rays: " << NORays_  <<std::endl;
}

