// YanshiPath.cpp : 实现文件
//

#include "stdafx.h"
#include "CameraControl.h"
#include "YanshiPath.h"
#include "afxdialogex.h"

CString pathThird=" ";  //三级目录临时变量

// CYanshiPath 对话框

IMPLEMENT_DYNAMIC(CYanshiPath, CDialogEx)

CYanshiPath::CYanshiPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYanshiPath::IDD, pParent)
	, pathFirst(_T("E:\\3dDataD"))
	, pathSecond(_T(" "))
	, Tmid(_T("midview"))
	, Tup(_T("upview"))
{

}

CYanshiPath::~CYanshiPath()
{
}

void CYanshiPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_pathFirst, pathFirst);
	DDX_Text(pDX, IDC_pathSecond, pathSecond);
}


BEGIN_MESSAGE_MAP(CYanshiPath, CDialogEx)
	ON_BN_CLICKED(IDC_pathSecondJia, &CYanshiPath::OnBnClickedpathsecondjia)
	ON_BN_CLICKED(IDC_pathThirdM, &CYanshiPath::OnBnClickedpaththirdm)
	ON_BN_CLICKED(IDC_pathThirdU, &CYanshiPath::OnBnClickedpaththirdu)
	ON_BN_CLICKED(IDOK, &CYanshiPath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CYanshiPath::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_pathSecondJian, &CYanshiPath::OnBnClickedpathsecondjian)
END_MESSAGE_MAP()


// CYanshiPath 消息处理程序


void CYanshiPath::OnBnClickedpathsecondjia()  //二级目录名加1
{
	// TODO: 在此添加控件通知处理程序代码
	//二级目录
	m_pathSecIndex ++;
	AcqPathSecSequence[m_pathSecIndex]=m_pathSecIndex;
	CString JpgSequence;
	JpgSequence.Format("_%d",AcqPathSecSequence[m_pathSecIndex]);	
	pathSecond = "3dpicture"  + JpgSequence;

	UpdateData(FALSE);
}

void CYanshiPath::OnBnClickedpathsecondjian()  //二级目录名减1
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pathSecIndex>0)
	{
		m_pathSecIndex --;
		AcqPathSecSequence[m_pathSecIndex]=m_pathSecIndex;
		CString JpgSequence;
		JpgSequence.Format("_%d",AcqPathSecSequence[m_pathSecIndex]);	
		pathSecond = "3dpicture"  + JpgSequence;
	} 
	else
	{
		m_pathSecIndex=0;
	}
	UpdateData(FALSE);
}


void CYanshiPath::OnBnClickedpaththirdm()   //三级目录，中视角
{
	// TODO: 在此添加控件通知处理程序代码
	//三级目录
	pathThird=Tmid;
}


void CYanshiPath::OnBnClickedpaththirdu()  //三级目录，上视角
{
	// TODO: 在此添加控件通知处理程序代码
	//三级目录
	pathThird=Tup;
}

void CYanshiPath::OnBnClickedOk()  //按下确定键后再创建目录
{
	// TODO: 在此添加控件通知处理程序代码
	m_strPictruefile=pathFirst+"\\"+pathSecond+"\\"+pathThird;
	SuperMkDir(m_strPictruefile);

	//将二级文件夹索引值写入settingD.ini
	CString pathSecIni;
	pathSecIni.Format("%d",m_pathSecIndex);
	//E:\\3Drestructure\\相机600D\\settingD.ini
	::WritePrivateProfileString("二级目录索引值","m_pathIndex",pathSecIni,"E:\\3Drestructure\\相机600D\\settingD.ini");  

	CDialogEx::OnOK();
}


void CYanshiPath::OnBnClickedCancel()  //取消键
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


// 判断目录是否存在  
bool CYanshiPath::FolderExists(CString s)  
{  
	DWORD attr;   
	attr = GetFileAttributes(s);   
	return (attr != (DWORD)(-1) ) &&  
		( attr & FILE_ATTRIBUTE_DIRECTORY);   
}  

// 递归创建目录， 如果目录已经存在或者创建成功返回TRUE  
bool CYanshiPath::SuperMkDir(CString P)  
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

	bool Ret=SuperMkDir(Parent);   

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



