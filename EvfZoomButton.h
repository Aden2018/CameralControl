

#pragma once

#include "ActionButton.h"
#include "Observer.h"
// CEvfZoomButton

class CEvfZoomButton : public CActionButton , public Observer
{

public:
	CEvfZoomButton();
	virtual void update(Observable* from, CameraEvent *e);

public:
	virtual ~CEvfZoomButton();

protected:
	void OnClicked();
	DECLARE_MESSAGE_MAP()
};
