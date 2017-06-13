

#pragma once

#include "Observer.h"
#include "ActionSource.h"

// CEVFPictureBox

class CEVFPictureBox : public CStatic, public ActionSource , public Observer
{
	DECLARE_DYNAMIC(CEVFPictureBox)
	
private:
	BOOL active;
	EdsFocusInfo	m_focusInfo;
	EdsBool			m_bDrawZoomFrame;

	void OnDrawImage(CDC *pDC, unsigned char* pbyteImage, int size);
	void OnDrawFocusRect(CDC *pDC, CRect zoomRect, CSize sizeJpegLarge);
public:
	CEVFPictureBox();
	virtual ~CEVFPictureBox();

	//observer
	virtual void update(Observable* from, CameraEvent *e);

protected:
	afx_msg LRESULT OnEvfDataChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


