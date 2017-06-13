

#include "stdafx.h"
#include "CameraControl.h"
#include "Tv.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CTv

IMPLEMENT_DYNAMIC(CTv, CPropertyComboBox)
CTv::CTv()
{
	setActionCommand("set_Tv");

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0c,"Bulb"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x10,"30''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x13,"25''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x14,"20''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x15,"20''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x18,"15''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1B,"13''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1C,"10''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1D,"10''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x20,"8''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x23,"6''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x24,"6''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x25,"5''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x28,"4''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2B,"3''2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2C,"3''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2D,"2''5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x30,"2''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x33,"1''6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x34,"1''5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x35,"1''3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x38,"1''"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3B,"0''8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3C,"0''7"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3D,"0''6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x40,"0''5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x43,"0''4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x44,"0''3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x45,"0''3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x48,"1/4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4B,"1/5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4C,"1/6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4D,"1/6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x50,"1/8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x53,"1/10"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x54,"1/10"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x55,"1/13"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x58,"1/15"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5B,"1/20"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5C,"1/20"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5D,"1/25"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x60,"1/30"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x63,"1/40"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x64,"1/45"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x65,"1/50"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x68,"1/60"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6B,"1/80"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6C,"1/90"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6D,"1/100"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x70,"1/125"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x73,"1/160"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x74,"1/180"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x75,"1/200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x78,"1/250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7B,"1/320"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7C,"1/350"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7D,"1/400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x80,"1/500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x83,"1/640"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x84,"1/750"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x85,"1/800"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x88,"1/1000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8B,"1/1250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8C,"1/1500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8D,"1/1600"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x90,"1/2000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x93,"1/2500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x94,"1/3000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x95,"1/3200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x98,"1/4000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9B,"1/5000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9C,"1/6000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9D,"1/6400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xA0,"1/8000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CTv::~CTv()
{
}


BEGIN_MESSAGE_MAP(CTv, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()


// CTv message handler
void CTv::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CTv::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Tv)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Tv)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CTv::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getTv());
	return 0;
}

LRESULT CTv::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getTvDesc());
	return 0;
}


