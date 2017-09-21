

#include "stdafx.h"
#include <map>

#include "CameraControl.h"
#include "CameraControlDlg.h"
#include ".\CameraControldlg.h"

#include "EDSDK.h"
#include "EDSDKTypes.h"

#include "YanshiPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_USER_DOWNLOAD_COMPLETE		WM_APP+1
#define WM_USER_PROGRESS_REPORT			WM_APP+2


// CCameraControlDlg 

CString CCameraControlDlg::GetAppPath()
{
	//取得应用程序路径	
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString pathName(exeFullPath);

	//返回值最后自带'\\'
	int index =pathName.ReverseFind('\\');
	return pathName.Left(index+1);
}

CCameraControlDlg::CCameraControlDlg(CWnd* pParent )
	: CDialog(CCameraControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strIniPath = GetAppPath() + "settingD.ini";
	
	GetPrivateProfileString("Setting","RootPath","E:\\3DData",m_strSaveRootPath,100,m_strIniPath);
	GetPrivateProfileString("Setting","Type","MidView",m_strSaveType,100,m_strIniPath);
	GetPrivateProfileString("Setting","Name","3dPicture",m_strSaveName,100,m_strIniPath);
	m_nSaveIdx = GetPrivateProfileInt("Setting","Index",1,m_strIniPath);
	g_savePath = findAndCreateValidPath();

}

CString CCameraControlDlg::GenerateFullPath()
{
	CString path;
	path.Format("%s\\%s_%02d\\%s",m_strSaveRootPath,m_strSaveName,m_nSaveIdx,m_strSaveType);
	return path;
}

int CCameraControlDlg::GetFileName(const string &strFolder, vector<string> &strVecFileNames)
{
	strVecFileNames.clear();
	struct _finddata_t filefind;   
	string  curr=strFolder + "\\*.*";   
	int  done=0;
	int  handle;   
	if((handle=_findfirst(curr.c_str(),&filefind))==-1)
		return -1; 
	string tempfolder = strFolder + "\\";
	while(!(done=_findnext(handle,&filefind)))   
	{   
		if(!strcmp(filefind.name,".."))  //用此方法第一个找到的文件名永远是".."，所以需要单独判断
			continue;
		strVecFileNames.push_back(tempfolder + filefind.name);
	}
	_findclose(handle);  
	return strVecFileNames.size();
}

CString CCameraControlDlg::findAndCreateValidPath()
{
	CString path;
	while(true)
	{
		path=GenerateFullPath();	
		if(!FolderExists(path))
		{
			SuperMkDir1(path);
			return path;
		}

		if(FolderExists(path) && GetFileName(path.GetBuffer(),vector<string>())==0)
		{
			return path;
		}

		++m_nSaveIdx;
	}
	AfxMessageBox("未找到可以存档目录，请修改配置文件。");
	return "";
}

void CCameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON1, _btnTakePicture);
	DDX_Control(pDX, IDC_PROGRESS1, _progress);
	DDX_Control(pDX, IDC_EDIT1, _edit);
	DDX_Control(pDX, IDC_PICT, _pictureBox);
	DDX_Control(pDX, IDC_COMBO1, _comboAEMode);
	DDX_Control(pDX, IDC_COMBO2, _comboTv);
	DDX_Control(pDX, IDC_COMBO3, _comboAv);
	DDX_Control(pDX, IDC_COMBO4, _comboIso);
	DDX_Control(pDX, IDC_COMBO5, _comboMeteringMode);
	DDX_Control(pDX, IDC_COMBO6, _comboExposureComp);
	DDX_Control(pDX, IDC_COMBO7, _comboImageQuality);
	DDX_Control(pDX, IDC_BUTTON2, _btnStartEVF);
	DDX_Control(pDX, IDC_BUTTON3, _btnEndEVF);
	DDX_Control(pDX, IDC_BUTTON4, _btnFocusNear3);
	DDX_Control(pDX, IDC_BUTTON5, _btnFocusNear2);
	DDX_Control(pDX, IDC_BUTTON6, _btnFocusNear1);
	DDX_Control(pDX, IDC_BUTTON7, _btnFocusFar1);
	DDX_Control(pDX, IDC_BUTTON8, _btnFocusFar2);
	DDX_Control(pDX, IDC_BUTTON9, _btnFocusFar3);
	DDX_Control(pDX, IDC_BUTTON10, _btnFocusUp);
	DDX_Control(pDX, IDC_BUTTON11, _btnFocusLeft);
	DDX_Control(pDX, IDC_BUTTON12, _btnFocusRight);
	DDX_Control(pDX, IDC_BUTTON13, _btnFocusDown);
	DDX_Control(pDX, IDC_BUTTON14, _btnZoomFit);
	DDX_Control(pDX, IDC_BUTTON15, _btnZoomZoom);
	DDX_Control(pDX, IDC_BUTTON16, _btnPressingHalfway);
	DDX_Control(pDX, IDC_BUTTON17, _btnPressingCompletely);
	DDX_Control(pDX, IDC_BUTTON18, _btnPressingOff);
	DDX_Control(pDX, IDC_BUTTON21, _btnEvfAfON);
	DDX_Control(pDX, IDC_BUTTON22, _btnEvfAfOFF);
	DDX_Control(pDX, IDC_COMBO8, _comboEvfAFMode);
}

BEGIN_MESSAGE_MAP(CCameraControlDlg, CDialog)
	ON_MESSAGE(WM_USER_DOWNLOAD_COMPLETE, OnDownloadComplete)
	ON_MESSAGE(WM_USER_PROGRESS_REPORT, OnProgressReport)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SET_PATH, &CCameraControlDlg::OnBnClickedBtnSetPath)
	ON_STN_CLICKED(IDC_TXT_PATH, &CCameraControlDlg::OnStnClickedTxtPath)
	ON_BN_CLICKED(IDC_BTN_OPEN_SAVEPATH, &CCameraControlDlg::OnBnClickedBtnOpenSavepath)
	ON_BN_CLICKED(IDC_BTN_TAKESOMEPICS, &CCameraControlDlg::OnBnClickedBtnTakesomepics)
	ON_BN_CLICKED(IDC_BTN_STOP, &CCameraControlDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CCameraControlDlg message handlers

BOOL CCameraControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	setupListener(_controller);
	setupObserver(getCameraModel());

	//Execute controller
	_controller->run();

	// A set value of the camera is acquired. 
	// The value to which the camera can be set is acquired. 
	CString curPath = "当前路径:";
	curPath += g_savePath;
	

	SetDlgItemText(IDC_TXT_PATH,curPath);

	return TRUE;   // return TRUE  unless you set the focus to a control
}

void CCameraControlDlg::setupListener(ActionListener* listener)
{
	addActionListener(listener);
	
	_comboAEMode.setActionCommand("set_AEMode");
	_comboAEMode.addActionListener(listener);
	_comboTv.setActionCommand("set_Tv");
	_comboTv.addActionListener(listener);
	_comboAv.setActionCommand("set_Av");
	_comboAv.addActionListener(listener);
	_comboIso.setActionCommand("set_ISOSpeed");
	_comboIso.addActionListener(listener);
	_comboMeteringMode.addActionListener(listener);
	_comboExposureComp.setActionCommand("set_ExposureCompensation");
	_comboExposureComp.addActionListener(listener);
	_comboImageQuality.setActionCommand("set_ImageQuality");
	_comboImageQuality.addActionListener(listener);
	_comboEvfAFMode.setActionCommand("set_EvfAFMode");
	_comboEvfAFMode.addActionListener(listener);

	_btnTakePicture.setActionCommand("TakePicture");
	_btnTakePicture.addActionListener(listener);
	_btnStartEVF.setActionCommand("startEVF");
	_btnStartEVF.addActionListener(listener);
	_btnEndEVF.setActionCommand("endEVF");
	_btnEndEVF.addActionListener(listener);
	_btnFocusNear3.setActionCommand("focus_Near3");
	_btnFocusNear3.addActionListener(listener);
	_btnFocusNear2.setActionCommand("focus_Near2");
	_btnFocusNear2.addActionListener(listener);
	_btnFocusNear1.setActionCommand("focus_Near1");
	_btnFocusNear1.addActionListener(listener);
	_btnFocusFar3.setActionCommand("focus_Far3");
	_btnFocusFar3.addActionListener(listener);
	_btnFocusFar2.setActionCommand("focus_Far2");
	_btnFocusFar2.addActionListener(listener);
	_btnFocusFar1.setActionCommand("focus_Far1");
	_btnFocusFar1.addActionListener(listener);
	_btnFocusUp.setActionCommand("focus_Up");
	_btnFocusUp.addActionListener(listener);
	_btnFocusLeft.setActionCommand("focus_Left");
	_btnFocusLeft.addActionListener(listener);
	_btnFocusRight.setActionCommand("focus_Right");
	_btnFocusRight.addActionListener(listener);
	_btnFocusDown.setActionCommand("focus_Down");
	_btnFocusDown.addActionListener(listener);
	_btnZoomFit.setActionCommand("zoom_Fit");
	_btnZoomFit.addActionListener(listener);
	_btnZoomZoom.setActionCommand("zoom_Zoom");
	_btnZoomZoom.addActionListener(listener);
	_btnPressingHalfway.setActionCommand("pressingHalfway");
	_btnPressingHalfway.addActionListener(listener);
	_btnPressingCompletely.setActionCommand("pressingCompletely");
	_btnPressingCompletely.addActionListener(listener);
	_btnPressingOff.setActionCommand("pressingOff");
	_btnPressingOff.addActionListener(listener);
	_btnEvfAfON.setActionCommand("evfAFOn");
	_btnEvfAfON.addActionListener(listener);
	_btnEvfAfOFF.setActionCommand("evfAFOff");
	_btnEvfAfOFF.addActionListener(listener);

	_pictureBox.setActionCommand("downloadEVF");
	_pictureBox.addActionListener(listener);
}


void CCameraControlDlg::setupObserver(Observable* ob)
{
	ob->addObserver(static_cast<Observer*>(&_comboAEMode));
	ob->addObserver(static_cast<Observer*>(&_comboTv));
	ob->addObserver(static_cast<Observer*>(&_comboAv));
	ob->addObserver(static_cast<Observer*>(&_comboIso));
	ob->addObserver(static_cast<Observer*>(&_comboMeteringMode));
	ob->addObserver(static_cast<Observer*>(&_comboExposureComp));
	ob->addObserver(static_cast<Observer*>(&_comboImageQuality));
	ob->addObserver(static_cast<Observer*>(&_pictureBox));
	ob->addObserver(static_cast<Observer*>(&_comboEvfAFMode));
	ob->addObserver(static_cast<Observer*>(&_btnZoomZoom));
}

void CCameraControlDlg::OnClose()
{
	// TODO : The control notification handler code is added here or Predetermined processing is called. 
	fireEvent("closing");

	_btnTakePicture.EnableWindow(FALSE);	
	_progress.EnableWindow(FALSE);
	_edit.EnableWindow(FALSE);
	_comboAEMode.EnableWindow(FALSE);
	_comboTv.EnableWindow(FALSE);
	_comboAv.EnableWindow(FALSE);
	_comboIso.EnableWindow(FALSE);	
	_comboImageQuality.EnableWindow(FALSE);	
	_btnPressingHalfway.EnableWindow(FALSE);	
	_btnPressingCompletely.EnableWindow(FALSE);	
	_btnPressingOff.EnableWindow(FALSE);	
	_comboEvfAFMode.EnableWindow(FALSE);	
	_btnEvfAfON.EnableWindow(FALSE);
	_btnEvfAfOFF.EnableWindow(FALSE);

	
	//_controller->doCloseEVFAction();


	__super::OnClose();
}


void CCameraControlDlg::update(Observable* from, CameraEvent *e)
{
	std::string event = e->getEvent();

	//End of download of image
	if(event == "DownloadComplete")
	{
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_DOWNLOAD_COMPLETE, NULL, NULL);
	}

	//Progress of download of image
	if(event == "ProgressReport")
	{
		EdsInt32 percent = *static_cast<EdsInt32 *>(e->getArg());
		
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_PROGRESS_REPORT, percent, NULL);
	}

	//shutdown event
	if(event == "shutDown")
	{
		::PostMessage(this->m_hWnd, WM_CLOSE, 0, NULL);
	}
}


LRESULT CCameraControlDlg::OnDownloadComplete(WPARAM wParam, LPARAM lParam)
{
	//End of download of image
	_progress.SetPos(0);
	if(--m_nCount > 0)
		fireEvent("TakePicture");
	return 0;
}

LRESULT CCameraControlDlg::OnProgressReport(WPARAM wParam, LPARAM lParam)
{
	_progress.SetPos((int)wParam);
	return 0;
}

CString GetAppPath()
{
	//取得应用程序路径	
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString pathName(exeFullPath);

	//返回值最后自带'\\'
	int index =pathName.ReverseFind('\\');
	return pathName.Left(index+1);
}

bool CCameraControlDlg::SuperMkDir1(CString P)  
{  
	int len=P.GetLength();  
	if ( len <2 ) return false;   

	if('\\'==P[len-1])  
	{  
		P=P.Left(len-1);  
		len=P.GetLength();  
	}  
	if ( len <=0 ) return false;  

	if (len <=3)   
	{  
		if (FolderExists(P))return true;  
		else return false;   
	}  

	if (FolderExists(P))return true;  

	CString Parent;  
	Parent=P.Left(P.ReverseFind('\\') );  

	if(Parent.GetLength()<=0)return false;   

	bool Ret=SuperMkDir1(Parent);   

	if(Ret)   
	{  
		SECURITY_ATTRIBUTES sa;  
		sa.nLength=sizeof(SECURITY_ATTRIBUTES);  
		sa.lpSecurityDescriptor=NULL;  
		sa.bInheritHandle=0;  
		Ret=(CreateDirectory(P,&sa)==TRUE);  
		return Ret;
	}
	else  
		return false;  
}  

void CCameraControlDlg::OnBnClickedBtnSetPath()
{
	// TODO: Add your control notification handler code here
	// TODO: 在此添加控件通知处理程序代码
	CYanshiPath YSpathDlg(m_strSaveRootPath,m_strSaveType,m_nSaveIdx,m_strSaveName);
	if(YSpathDlg.DoModal()==IDCANCEL)   //弹出存储路径对话框
		return;
	g_imgIdx = 0;
	GetPrivateProfileString("Setting","RootPath","E:\\3DData",m_strSaveRootPath,100,m_strIniPath);
	GetPrivateProfileString("Setting","Type","MidView",m_strSaveType,100,m_strIniPath);
	GetPrivateProfileString("Setting","Name","3dPicture",m_strSaveName,100,m_strIniPath);
	m_nSaveIdx = YSpathDlg.m_SaveIdx;
	g_savePath = findAndCreateValidPath();

	CString curPath = "当前路径:";
	curPath += g_savePath;
	SetDlgItemText(IDC_TXT_PATH,curPath);
}


void CCameraControlDlg::OnStnClickedTxtPath()
{
	// TODO: Add your control notification handler code here
}


void CCameraControlDlg::OnBnClickedBtnOpenSavepath()
{
	// TODO: Add your control notification handler code here

	system("explorer " + g_savePath);

	//WinExec("explorer \"" + g_savePath + "\"",SW_HIDE);
}


void CCameraControlDlg::OnBnClickedBtnTakesomepics()
{
	// TODO: Add your control notification handler code here
	m_nCount = 30;
	fireEvent("TakePicture");
}


void CCameraControlDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	m_nCount = 0;
}
