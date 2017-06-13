

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

class DriveLensCommand : public Command
{
private:
	EdsUInt32 _parameter;


public:
	DriveLensCommand(CameraModel *model, EdsUInt32 parameter)
		:_parameter(parameter), Command(model){}


	// Execute command	
	virtual bool execute()
	{
		EdsError err = EDS_ERR_OK;

		// Drive lens
		if(err == EDS_ERR_OK)
		{		
			err = EdsSendCommand(_model->getCameraObject(),
								 kEdsCameraCommand_DriveLensEvf,
								 _parameter);
		}

		//Notification of error
		if(err != EDS_ERR_OK)
		{
			// It doesn't retry it at device busy
			if(err == EDS_ERR_DEVICE_BUSY)
			{
				CameraEvent e("DeviceBusy");
				_model->notifyObservers(&e);
				return true;
			}

			CameraEvent e("error", &err);
			_model->notifyObservers(&e);
		}

		return true;
	}

};