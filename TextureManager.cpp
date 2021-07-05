#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(SDL_Surface* tmpSurface){
    if (tmpSurface == nullptr){
        SDL_Log("Failed to load texture from file : %s ", SDL_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(BulletHell::renderer, tmpSurface);
    if (tex == nullptr){
        SDL_Log("Failed to create texture from surface : %s", SDL_GetError());
    }

    SDL_FreeSurface(tmpSurface);    //clear surface
    tmpSurface = nullptr;

    return tex;
}

SDL_Texture* TextureManager::loadText(TTF_Font *font, const char *text, SDL_Color color){

    SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text, color);   //load solid text to surface
    if (tmpSurface == nullptr){
        SDL_Log("Failed to load text from font : %s", SDL_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(BulletHell::renderer, tmpSurface);
    if (tex == nullptr){
        SDL_Log("Failed to create text from surface : %s", SDL_GetError());
    }

    SDL_FreeSurface(tmpSurface);    //clear surface
    tmpSurface = nullptr;

    return tex;
}

void TextureManager::getPixels (SDL_Texture *op_tex, int *buf_width, int *buf_height){
    SDL_QueryTexture(op_tex, NULL, NULL, buf_width, buf_height);
}

void TextureManager::renderTex(SDL_Texture *op_tex, SDL_Rect sourceRec, SDL_Rect desRec){
    //first NULL for entire texture, second NULL for render to entire window
    SDL_RenderCopy(BulletHell::renderer, op_tex, &sourceRec, &desRec);
}

void TextureManager::destroyTex(SDL_Texture *op_tex){   // reduce memory leak
    SDL_DestroyTexture(op_tex);
    op_tex = nullptr;
}

void TextureManager::destroyFont(TTF_Font *op_font){    // reduce memory leak
    TTF_CloseFont(op_font);
    op_font = nullptr;
}
