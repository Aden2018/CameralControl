

#pragma once

#include <map>
#include "Observer.h"
#include "CameraController.h"
#include <string>
#include <vector>
#include <io.h>
using std::vector;
using std::string;

#include "AEMode.h"
#include "Tv.h"
#include "Av.h"
#include "Iso.h"
#include "MeteringMode.h"
#include "ExposureComp.h"
#include "ImageQuality.h"
#include "EVFPictureBox.h"
#include "EvfAFMode.h"

#include "ActionButton.h"
#include "EvfZoomButton.h"

// CCameraControlDlg Dialog
class CCameraControlDlg : public CDialog, public ActionSource, public Observer
{
	
// Construction
private:
	void setupListener(ActionListener* listener);
	void setupObserver(Observable* ob);
	void changeEnableWindow();

public:
	CCameraControlDlg(CWnd* pParent = NULL);	// standard constructor
	void setCameraController(CameraController* controller){_controller = controller;}


public:
	// Observer 
	virtual void update(Observable* from, CameraEvent *e);

	//Dialog data
	enum { IDD = IDD_CAMERACONTROL_DIALOG };
	
	CActionButton	_btnTakePicture;
	CActionButton	_btnStartEVF;
	CActionButton	_btnEndEVF;
	CActionButton	_btnFocusNear3;
	CActionButton	_btnFocusNear2;
	CActionButton	_btnFocusNear1;
	CActionButton	_btnFocusFar3;
	CActionButton	_btnFocusFar2;
	CActionButton	_btnFocusFar1;
	CActionButton	_btnFocusUp;
	CActionButton	_btnFocusDown;
	CActionButton	_btnFocusLeft;
	CActionButton	_btnFocusRight;
	CActionButton	_btnZoomFit;
	CEvfZoomButton	_btnZoomZoom;
	CProgressCtrl	_progress;
	CEdit			_edit;
	CEVFPictureBox	_pictureBox;
	CAEMode			_comboAEMode;
	CTv				_comboTv;
	CAv				_comboAv;
	CIso			_comboIso;
	CMeteringMode	_comboMeteringMode;
	CExposureComp	_comboExposureComp;
	CImageQuality	_comboImageQuality;
	CActionButton	_btnPressingHalfway;
	CActionButton	_btnPressingCompletely;
	CActionButton	_btnPressingOff;
	CEvfAFMode		_comboEvfAFMode;
	CActionButton	_btnEvfAfON;
	CActionButton	_btnEvfAfOFF;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDownloadComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressReport(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CameraController* _controller;

public:
	afx_msg void OnClose();


private:
	char m_strSaveRootPath[256];
	CString m_strIniPath;
	char m_strSaveType[256];
	int		m_nSaveIdx;
	char m_strSaveName[256]; //子文件夹的名称 3dpicture
	int m_nCount;
	//CString m_strSavePath; //最终保存的文件夹全路径
	CString GetAppPath();
	CString findAndCreateValidPath();
	CString CCameraControlDlg::GenerateFullPath();
	int GetFileName(const string &strFolder, vector<string> &strVecFileNames);
	bool SuperMkDir1(CString P);
	// 判断目录是否存在  
	bool FolderExists(CString s)
	{  
		DWORD attr;   
		attr = GetFileAttributes(s);   
		return (attr != (DWORD)(-1) ) &&  
			( attr & FILE_ATTRIBUTE_DIRECTORY);   
	} 
public:
	afx_msg void OnBnClickedBtnSetPath();
	afx_msg void OnStnClickedTxtPath();
	afx_msg void OnBnClickedBtnOpenSavepath();
	afx_msg void OnBnClickedBtnTakesomepics();
	afx_msg void OnBnClickedBtnStop();
};
