#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include "./../header/rpg_definitions.hpp"
#include "./../header/debug.hpp"
#include "./../header/texture.hpp"

texture::texture(SDL_Renderer* renner){
    this->renner = renner;
    for(int i = 0; i < 5; i++){this->textureVector.push_back(nullptr);} // 0: map, 1: player, 2: npcs, 3: objects, 4: ui
}

void texture::renderTexture(int textureID, uint8_t kindOfTexture, SDL_Rect dst, int hight, int width){
    if(this->textureVector[kindOfTexture] == nullptr){
        this->textureVector[kindOfTexture] = SDL_CreateTextureFromSurface(this->renner, IMG_Load(this->filepaths[kindOfTexture].c_str()));
    }
    int w, h;
    SDL_QueryTexture(this->textureVector[kindOfTexture], NULL, NULL, &w, &h);
    this->rectangle.x = (textureID % (w/width))*width;
    this->rectangle.y = ((textureID*width)/(w))*hight;
    DEB_MSG_3(_T(this->rectangle.y/hight) + " " + _T(this->rectangle.x/width))
    DEB_MSG_3(_T(textureID) + "/" + _T(w) + "*" + _T(hight))
    this->rectangle.h = hight;
    this->rectangle.w = width;
    DEB_MSG_3("loading at x: " + _T(this->rectangle.x) + " y: " + _T(this->rectangle.y))
    SDL_RenderCopy(this->renner, this->textureVector[kindOfTexture], &this->rectangle, &dst);
}

void texture::changeFilePath(uint8_t kindOfTexture, std::string newPath){
    this->filepaths[kindOfTexture] = "./resources/" + newPath;
    this->textureVector[kindOfTexture] = nullptr;
}

#endif