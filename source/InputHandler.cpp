/** InputHandler.cpp
 *
 * See header file for details.
 */

#include "InputHandler.h"

#include "CommandListener.h"
#include "raylib.h"

InputHandler::InputHandler() {
	p1GamepadID = 0;
}
	
InputHandler::~InputHandler() {
}

void InputHandler::handleInput(CommandListener &listener) {
	bool moving = false;
	
	// Up/down
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || 
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
		listener.MoveAway();
		moving = true;
	} else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) || 
				IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
		listener.MoveToward();
		moving = true;
	}
	
	// Left/right
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || 
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
		listener.MoveRight();	
		moving = true;
	} else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || 
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
		listener.MoveLeft();
		moving = true;
	}
	
	if(!moving) {
		listener.goNowhere();
	}
	
	// Select, push, pull, etc.
	if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER) || 
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_TRIGGER_1) ||
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) ||
			IsGamepadButtonDown(p1GamepadID, GAMEPAD_BUTTON_LEFT_THUMB)) {
		listener.doInteractWith();
	}
}