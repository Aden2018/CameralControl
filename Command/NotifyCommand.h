

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"



class NotifyCommand : public Command
{
	std::string	_notifyString;

public:
	NotifyCommand(CameraModel *model, std::string notifyString)
		: Command(model) , _notifyString(notifyString){}

    // Execute command	
	virtual bool execute()
	{
		CameraEvent e(_notifyString, NULL);
		_model->notifyObservers(&e);

		return true;
	}

};