#include "EventListener.h"
#include "../Core/CoreEngine.h"
#include "KeyEventListener.h"

bool EventListener::KEY_UP = false;
bool EventListener::KEY_DOWN = false;
bool EventListener::KEY_LEFT = false;
bool EventListener::KEY_RIGHT = false;
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
			KeyEventListener::PressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			KeyEventListener::ReleaseKey(sdlEvent.key.keysym.sym);
			break;
		default:
			break;
		}
	}
}
