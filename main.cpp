#include <cassert>
#include <algorithm>
#include <SDL.h>

int screenWidth = 800;
int screenHeight = 640;

int main(int argc, char* args[])
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0 && "Unable to init SDL");

	SDL_Window* window = SDL_CreateWindow("Invaders SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	assert(window != nullptr && "Unable to create window");

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);
	assert(renderer != nullptr && "Unable to create renderer");

	bool running = true;

	SDL_Rect r1{ screenWidth / 2,screenHeight / 2 , 250, 250 };
	SDL_Rect r2{ 100, 100, 250, 250 };

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{


				case SDLK_LEFT: r2.x -= 20; break;
				case SDLK_RIGHT: r2.x += 20; break;
				case SDLK_DOWN: r2.y += 20; break;
				case SDLK_UP: r2.y -= 20; break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);
		SDL_RenderDrawRect(renderer, &r2);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
		SDL_RenderDrawRect(renderer, &r1);

		auto intersectX = std::max(r1.x, r2.x);
		auto intersectY = std::max(r1.y, r2.y);
		auto intersectW = std::min(r1.x + r1.w, r2.x + r2.w) - intersectX;
		auto intersectH = std::min(r1.y + r1.h, r2.y + r2.h) - intersectY;

		if (intersectW > 0 && intersectH > 0)
		{
			SDL_Rect intersectRect = { intersectX, intersectY, intersectW, intersectH };
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
			SDL_RenderFillRect(renderer, &intersectRect);
		}

		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}