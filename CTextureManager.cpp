#include "CTextureManager.h"
std::vector<SDL_Texture *> CTextureManager::texture;
TTF_Font *CTextureManager::font = nullptr;
void CTextureManager::init(SDL_Renderer *renderer, std::vector<const char *> paths)
{
	for (const char *path : paths)
	{
		SDL_Surface *surface = SDL_LoadBMP(path);
		SDL_Texture *_texture = SDL_CreateTextureFromSurface(renderer, surface);
		texture.push_back(_texture);
		SDL_FreeSurface(surface);
	}
}
SDL_Texture *CTextureManager::renderText(SDL_Renderer *renderer,
										 TTF_Font *font,
										 const std::string &text,
										 SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (!surface)
		return nullptr;

	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return tex;
}
void CTextureManager::destroy()
{
	for (SDL_Texture *_texture : texture)
	{
		SDL_DestroyTexture(_texture);
	}
}