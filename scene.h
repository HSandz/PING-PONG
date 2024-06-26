#ifndef PONG_SCENE_H
#define PONG_SCENE_H

#include <memory>

struct SDL_KeyboardEvent;
struct SDL_Renderer;

namespace pong
{
	class Scene
	{
	public:
		virtual void onDraw(SDL_Renderer& renderer) = 0;
		virtual void onUpdate() = 0;
		virtual void onEnter() = 0;
		virtual void onExit() = 0;
		virtual void onKeyDown(SDL_KeyboardEvent& event) = 0;
		virtual void onKeyUp(SDL_KeyboardEvent& event) = 0;
	};
	typedef std::shared_ptr<Scene> ScenePtr;
}

#endif
