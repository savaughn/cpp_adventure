#include "Frog.h"

static const int jumpUpFrame = 3;
static const int jumpDownFrame = 4;
static const int footstepFrame1 = 1;
static const int footstepFrame2 = 4;

static bool isFootstepFrame(int frameIndex) {
	
	if(frameIndex == footstepFrame1 || frameIndex == footstepFrame2) {
		return true;
	} else {
		return false;
	}
}

Frog::Frog() {
	
	numFrames = 4;
	frameWidth = texture->width / numFrames;
	frameRect = raylib::Rectangle(0.0f, 0.0f, (float)frameWidth, (float)texture->height);
	
	frameDelay = 5;
	frameDelayCounter = 0;
	frameIndex = 0;
	
	walkSpeed = 10;
	jumpSpeed = 2 * walkSpeed;
	
	isOnGround = true;

	scale = 8.f;
}
	
bool Frog::update(bool onGround) {
	bool frogMoving = velocity != raylib::Vector2(0.0f, 0.0f);
			
	bool wasOnGround = isOnGround;
	isOnGround = onGround;
	
	if(isOnGround && !wasOnGround) {
		PlaySound(landingSound);
	}
	
	++frameDelayCounter;
	if(frameDelayCounter > frameDelay) {
		frameDelayCounter = 0;
		
		if(frogMoving) {
			if(isOnGround) {
				++frameIndex;
				frameIndex %= numFrames;
				
				if(isFootstepFrame(frameIndex)) {
					PlaySound(footstepSound);
				}
			} else {
				if(velocity.y < 0) {
					frameIndex = jumpUpFrame;
				} else {
					frameIndex = jumpDownFrame;
				}
			}
			frameRect.x = (float) frameWidth * frameIndex;
		}
	}
	
	return true;
}
	
void Frog::draw() {
	DrawTexturePro(static_cast<Texture2D>(*texture), frameRect, {
		position.x,
		position.y,
		texture->width,
		scale * texture->height
	}, {}, 0.f, WHITE);
}
	
raylib::Rectangle Frog::getBoundingBox() {
	raylib::Vector2 ulPosition = getUpperLeftPosition();
	return raylib::Rectangle(ulPosition.x, ulPosition.y, texture->width, texture->height);
}
	
void Frog::MoveAway() {
	if(isOnGround) {
		velocity.y = -jumpSpeed;
	}
}
	
void Frog::MoveLeft() {
	if(isOnGround) {
		velocity.x = -walkSpeed;
		if(frameRect.width > 0) {
			frameRect.width = -frameRect.width;
		}
	}
}
	
void Frog::MoveRight() {
	if(isOnGround) {
		velocity.x = walkSpeed;
		if(frameRect.width < 0) {
			frameRect.width = -frameRect.width;
		}
	}
}

void Frog::goNowhere() {
	if(isOnGround) {
		velocity.x = 0;
	}
}
	
void Frog::MoveToward() {
}
	
void Frog::doInteractWith() {
}

raylib::Vector2 Frog::getUpperLeftPosition() {
	return raylib::Vector2(position.x - frameWidth / 2, position.y - texture->height);
}