


#pragma once

#include  "CameraModel.h"

class Command {

protected:
	// Camera Model
	CameraModel* _model;

public:
	Command(CameraModel *model) : _model(model) {}

	CameraModel* getCameraModel(){return _model;}

	// Execute command	
	virtual bool execute() = 0;
};

