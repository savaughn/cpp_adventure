/** Scene.cpp
 *
 * See header file for details.
 */

#include "Scene.h"

#include "Actor.h"
#include "raylib.h"

Scene::Scene() {
	int sceneHeight = GetScreenHeight();
	groundYPos = (2.5 * sceneHeight) / 4;
	gravity = 1;
}
	
Scene::~Scene() {
	freeResources();
}
	
void Scene::loadResources() {
}
	
void Scene::freeResources() {
	playerAvatar.reset();
	actors.clear();
}
	
void Scene::start() {
}
	
std::shared_ptr<Scene> Scene::update() {
	for(auto &actor : actors) {
		actor->position += actor->velocity;
		
		auto boundingRect = actor->getBoundingBox();
		auto distToGround = groundYPos - (boundingRect.y + boundingRect.height);
		bool isOnGround =  distToGround <= 0;
		
		if(isOnGround) {
			actor->velocity.y = 0;
			actor->position.y += distToGround;
		} else {
			actor->velocity.y += gravity;
		}
		actor->update(isOnGround);
	}
	
	return nullptr;
}
	
void Scene::draw() {
	ClearBackground(RAYWHITE);
		
	if(actors.size()) {
		for(auto &actor: actors) {
			actor->draw();
		}
	} else {
		DrawText("This scene has no content. Add some actors, or override Scene::draw()", 20, 20, 20, RED);
	}
}
	
void Scene::MoveAway() {
	if(playerAvatar) {
		playerAvatar->MoveAway();
	}
}
	
void Scene::MoveLeft() {
	if(playerAvatar) {
		playerAvatar->MoveLeft();
	}
}
	
void Scene::MoveRight() {
	if(playerAvatar) {
		playerAvatar->MoveRight();
	}
}
	
void Scene::MoveToward() {
	if(playerAvatar) {
		playerAvatar->MoveToward();
	}
}

void Scene::goNowhere() {
	if(playerAvatar) {
		playerAvatar->goNowhere();
	}
}
	
void Scene::doInteractWith() {
	if(playerAvatar) {
		playerAvatar->doInteractWith();
	}
}