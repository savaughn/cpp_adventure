#include "TestScene.h"

TestScene::TestScene(){}

void TestScene::loadResources() {
	std::shared_ptr<Frog> frog = std::make_shared<Frog>();
	
	int sceneWidth = GetScreenWidth();
	frog->position = raylib::Vector2(sceneWidth / 2, groundYPos);

	
	playerAvatar = frog;
	actors.emplace_back(frog);
}
