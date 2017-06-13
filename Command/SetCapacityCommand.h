

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

class SetCapacityCommand : public Command
{
private:
	EdsCapacity _capacity;

public:
	SetCapacityCommand(CameraModel *model) : Command(model){}
	SetCapacityCommand(CameraModel *model, EdsCapacity capacity) : Command(model), _capacity(capacity) {}

	void setCapacity(EdsCapacity capacity)
	{
		_capacity = capacity;
	}

	// Execute command	
	virtual bool execute()
	{
		// It is a function only of the model since 30D.
		if(! _model->isLegacy())
		{
			EdsError err = EDS_ERR_OK;

			//Acquisition of the number of sheets that can be taken a picture
			if(err == EDS_ERR_OK)
			{
				err = EdsSetCapacity( _model->getCameraObject(), _capacity);
			}

			//Notification of error
			if(err != EDS_ERR_OK)
			{
				CameraEvent e("error", &err);
				_model->notifyObservers(&e);
			}
		}

		return true;
	}


};