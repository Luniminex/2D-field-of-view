//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_GAME_H
#define LIGHTINGEXAMPLE_GAME_H

#include <vector>
#include <map>
#include "Handle.h"
#include "TextureWrap.h"
#include "Box.h"
#include "Spotlight.h"
#include "Fieldlight.h"

class Game {
public:
    Game();
    void Start();
    ~Game();

private:
    void Play();
    void CheckQuit();
    void HandleEvents();
    void Quit();
private:
    void SpawnBoxes();
    void SpawnSpotlights();
    void UpdateEntities(float dt);
    void DrawBoxes();
    void DrawWalls();
    void DrawSpotlights();
    void ExtractWalls();
private:
    std::shared_ptr<Handle> handle_;
    bool running_;
    bool want_quit_;
    TextureWrap renderTexture_;
    TextureWrap lightTexture_;
    TextureWrap resultTexture_;
    std::vector<Box*> boxes_;
    std::vector<Spotlight*> spotlights_;
    std::vector<Wall> walls_;
    Fieldlight fieldlight_;
    std::map<char, bool> keys_;
};


#endif //LIGHTINGEXAMPLE_GAME_H
