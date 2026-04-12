#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class CTextureManager
{
public:
	static std::vector<SDL_Texture *> texture;
	static TTF_Font *font;
	static void init(SDL_Renderer *renderer,
					 std::vector<const char *> paths = {"sprite.bmp", "sprite1.bmp", "sprite2.bmp", "sprite3.bmp",
														"sprite4.bmp", "sprite5.bmp", "sprite6.bmp", "sprite7.bmp",
														"sprite8.bmp", "player.bmp", "bot.bmp", "menu.bmp",
														"options.bmp"});
	static SDL_Texture *renderText(SDL_Renderer *renderer,
								   TTF_Font *font,
								   const std::string &text,
								   SDL_Color color);
	static void destroy();
};
