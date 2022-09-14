/** CommandListener.h
 *
 * @author Hans de Ruiter
 *
 * @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
 *
 * See License.txt for license.
 */

#pragma once

/** Base class for objects that need to listen to user (or AI) commands.
 */
class CommandListener {
public:
	CommandListener();
	
	virtual ~CommandListener();
	
	// Child classes, override the methods below that you need to respond
	// to user/AI commands
	
	virtual void MoveAway();
	
	virtual void MoveLeft();
	
	virtual void MoveRight();
	
	virtual void MoveToward();
	
	/** Called when none of the other go*() are called. 
	 */
	virtual void goNowhere();
	
	/** Select, push, pull, punch, fire, etc.
	 */
	virtual void doInteractWith();
};
