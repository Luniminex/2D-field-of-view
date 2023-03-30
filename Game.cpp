//
// Created by luniminex on 3/16/23.
//

#include "Game.h"

Game::Game() : fieldlight_(300){
    handle_ = Handle::GetInstance();
    keys_['+'] = false; //increase rays
    keys_['-'] = false; //decrease rays
    keys_['l'] = true; //show lights
    keys_['w'] = false; //show walls
    keys_['r'] = false; //show rays
    keys_['b'] = true; //show boxes
    keys_['f'] = true; //show field lights
    keys_['i'] = false; //show intersections
}

void Game::Start() {
    handle_->Init();
    handle_->CreateWindow("Lighting example", 960, 544, SDL_WINDOW_SHOWN);
    handle_->CreateRenderer(SDL_RENDERER_ACCELERATED);

    renderTexture_.CreateBlankTexture(handle_->GetWindowInfo().width, handle_->GetWindowInfo().height, handle_->GetRenderer(), SDL_TEXTUREACCESS_TARGET);
    renderTexture_.SetBlendMode(SDL_BLENDMODE_BLEND);

    lightTexture_.CreateBlankTexture(handle_->GetWindowInfo().width, handle_->GetWindowInfo().height, handle_->GetRenderer(), SDL_TEXTUREACCESS_TARGET);
    lightTexture_.SetBlendMode(SDL_BLENDMODE_MOD);

    resultTexture_.CreateBlankTexture(handle_->GetWindowInfo().width, handle_->GetWindowInfo().height, handle_->GetRenderer(), SDL_TEXTUREACCESS_TARGET);
    resultTexture_.SetBlendMode(SDL_BLENDMODE_BLEND);

    running_ = true;
    want_quit_ = false;
    Play();
}

void Game::Play() {

    SpawnBoxes();
    SpawnSpotlights();
    ExtractWalls();
    fieldlight_.GenerateRays(walls_);
    TextureWrap bgr;
    //https://www.pinterest.com/pin/349521621082908149/
    bgr.LoadFromFile("../resources/bgr.png", handle_->GetRenderer());

    const float fps = 60.f;
    const float delay = 1000.f / fps;
    Uint64 lastUpdate = SDL_GetTicks64();
    while(running_){
        Uint64 current = SDL_GetTicks64();

        HandleEvents();

        float dt = static_cast<float>((current - lastUpdate)) / 1000.f;

        //update
        UpdateEntities(dt);

        //draw
        //draws to background layer
        renderTexture_.SetAsRenderTarget(handle_->GetRenderer());
        SDL_SetRenderDrawColor(handle_->GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(handle_->GetRenderer());
        bgr.RenderTextureAt(0, 0, handle_->GetWindowInfo().width, handle_->GetWindowInfo().height, handle_->GetRenderer());
        if(keys_['b'])
            DrawBoxes();
        if(keys_['w'])
            DrawWalls();

        //draws light
        lightTexture_.SetAsRenderTarget(handle_->GetRenderer());
        SDL_SetRenderDrawColor(handle_->GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(handle_->GetRenderer());
        fieldlight_.Draw(handle_->GetRenderer(), keys_['f'], keys_['r'], keys_['i']);
        if(keys_['l'])
            DrawSpotlights();

        //merge together background and light layer
        resultTexture_.SetAsRenderTarget(handle_->GetRenderer());
        SDL_SetRenderDrawColor(handle_->GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(handle_->GetRenderer());
        renderTexture_.RenderTextureAt(0, 0, handle_->GetRenderer(), nullptr, 0, nullptr);
        lightTexture_.RenderTextureAt(0, 0, handle_->GetRenderer(), nullptr, 0, nullptr);
        SDL_SetRenderTarget(handle_->GetRenderer(), nullptr);
        resultTexture_.RenderTextureAt(0, 0, handle_->GetRenderer(), nullptr, 0, nullptr);
        SDL_RenderPresent(handle_->GetRenderer());

        Uint64 frameTime = SDL_GetTicks64() - current;
        if(static_cast<float>(frameTime) < delay){
            SDL_Delay(static_cast<Uint32>(delay - static_cast<float>(frameTime)));
        }
        CheckQuit();
    }
    Quit();
}

void Game::HandleEvents() {
    keys_['+'] = false;
    keys_['-'] = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            std::cout<<"Wants to end"<<std::endl;
            want_quit_ = true;
        }
        else if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    std::cout << "increasing rays" << std::endl;
                    keys_['+'] = true;
                    break;
                case SDLK_DOWN:
                    std::cout << "decreasing rays" << std::endl;
                    keys_['-'] = true;
                    break;
                case SDLK_b:
                    std::cout << "boxes" << std::endl;
                    keys_['b'] = !keys_['b'];
                    break;
                case SDLK_r:
                    std::cout << "rays" << std::endl;
                    keys_['r'] = !keys_['r'];
                    break;
                case SDLK_w:
                    std::cout << "walls" << std::endl;
                    keys_['w'] = !keys_['w'];
                    break;
                case SDLK_l:
                    std::cout << "lights" << std::endl;
                    keys_['l'] = !keys_['l'];
                    break;
                case SDLK_f:
                    std::cout << "field lights" << std::endl;
                    keys_['f'] = !keys_['f'];
                    break;
                case SDLK_i:
                    std::cout << "intersections" << std::endl;
                    keys_['i'] = !keys_['i'];
                    break;
            }
        }
    }
}

void Game::CheckQuit() {
    if(want_quit_){
        running_ = false;
    }
}

void Game::Quit() {
    SDL_Quit();
}

void Game::SpawnBoxes() {
    SDL_Color clr;
    clr = {.r = 125, .g = 125, .b = 255, .a = 255};
    boxes_.push_back(new Box(30, 250, 300, 100, clr));
    boxes_.push_back(new Box(400, 400, 200, 200, clr));
    boxes_.push_back(new Box(450, 50, 80, 200, clr));
    boxes_.push_back(new Box(30, 30, 100, 100, clr));
    boxes_.push_back(new Box(600, 300, 100, 100, clr));
    boxes_.push_back(new Box(450, 430, 100, 100, clr));
    boxes_.push_back(new Box(550, 180, 100, 100, clr));
    boxes_.push_back(new Box(800, 250, 50, 300, clr));
    boxes_.push_back(new Box(600, 80, 10, 10, clr));
    boxes_.push_back(new Box(620, 80, 10, 10, clr));
    boxes_.push_back(new Box(640, 80, 10, 10, clr));
    boxes_.push_back(new Box(660, 80, 10, 10, clr));
    boxes_.push_back(new Box(680, 80, 10, 10, clr));
    boxes_.push_back(new Box(700, 80, 10, 10, clr));
    clr = {.r = 0, .g = 0, .b = 0, .a = 0};
    boxes_.push_back(new Box(0, 0, handle_->GetWindowInfo().width - 1, handle_->GetWindowInfo().height - 1, clr));
}

void Game::SpawnSpotlights() {
    spotlights_.push_back(new Spotlight(600, 400, 100, 255));
    spotlights_.back()->SetColor({255, 255, 255, 255});
    spotlights_.push_back(new Spotlight(600, 200, 150, 200));
    spotlights_.back()->SetColor({0, 0, 255, 255});
    spotlights_.push_back(new Spotlight(120, 60, 60, 150));
    spotlights_.back()->SetColor({255, 200, 200, 255});
    spotlights_.push_back(new Spotlight(300, 300, 100, 255));
    spotlights_.back()->SetColor({0, 255, 0, 255});
}

void Game::UpdateEntities(float dt) {
    for(auto& entity : boxes_){
        entity->Update(dt);
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    fieldlight_.SetPos(x, y);
    fieldlight_.Update();
    fieldlight_.CheckCollision(walls_, keys_['+'], keys_['-']);
}

void Game::DrawBoxes() {
    for(auto& box : boxes_){
        box->Draw(handle_->GetRenderer());
    }
}

void Game::DrawSpotlights() {
    for(auto& spotlight : spotlights_){
        spotlight->Draw(handle_->GetRenderer());
    }
}

void Game::ExtractWalls() {
    Wall wall;
    SDL_Rect body;
    for(auto& box : boxes_){
        body = box->GetBody();
        wall.MakeFromRect(body, Side::top);
        walls_.push_back(wall);
        wall.MakeFromRect(body, Side::right);
        walls_.push_back(wall);
        wall.MakeFromRect(body, Side::down);
        walls_.push_back(wall);
        wall.MakeFromRect(body, Side::left);
        walls_.push_back(wall);
    }
}

void Game::DrawWalls() {
    SDL_SetRenderDrawColor(handle_->GetRenderer(), 0, 255, 0, 255);
    for(auto& wall : walls_){
        wall.Draw(handle_->GetRenderer());
    }
}

Game::~Game() { //lazy to rewrite it without using new...
    for(auto& box : boxes_){
       delete box;
    }
    for(auto& spotlight : spotlights_){
        delete spotlight;
    }
}


