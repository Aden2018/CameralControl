

#include "stdafx.h"
#include "CameraControl.h"
#include "EvfZoomButton.h"


/////////////////////////////////////////////////////////////////////////////
// CEvfZoomButton

CEvfZoomButton::CEvfZoomButton()
{
}

CEvfZoomButton::~CEvfZoomButton()
{
}
void CEvfZoomButton::update(Observable* from, CameraEvent *e)
{
	std::string event = e->getEvent();
	//PropertyChanged event
	if (event == "PropertyChanged")
	{
		EdsInt32 proeprtyID = *static_cast<EdsInt32 *>(e->getArg());
		if(proeprtyID==kEdsPropID_Evf_AFMode)
		{
			CameraModel* model = (CameraModel *)from;
			this->EnableWindow(model->getEvfAFMode()!=2);
		}
	}
}

BEGIN_MESSAGE_MAP(CEvfZoomButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
END_MESSAGE_MAP()

//EvfZoomButton  message handler
void CEvfZoomButton::OnClicked() 
{
	CActionButton::OnClicked();
}
