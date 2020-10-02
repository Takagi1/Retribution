#include "EventListener.h"
#include "../Core/CoreEngine.h"

bool EventListener::KEY_UP = false;
bool EventListener::KEY_DOWN = false;
bool EventListener::KEY_LEFT = false;
bool EventListener::KEY_RIGHT = false;
bool EventListener::KEY_A = false;
bool EventListener::KEY_B = false;
bool EventListener::KEY_C = false;

EventListener::~EventListener()
{

}

void EventListener::Update()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			CoreEngine::GetInstance()->Exit();
		}
		
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
			break;
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym) {

			}
			break;
		case SDL_KEYUP:
			switch (sdlEvent.key.keysym.sym) {
			case SDLK_LEFT:
				KEY_LEFT = false;
				break;
			case SDLK_RIGHT:
				KEY_RIGHT = false;
				break;
			case SDLK_UP:
				KEY_UP = false;
				break;
			case SDLK_DOWN:
				KEY_DOWN = false;
				break;
			case SDLK_a:
				KEY_A = false;
				break;
			case SDLK_b:
				KEY_B = false;
				break;
			case SDLK_c:
				KEY_C = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}
