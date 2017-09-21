// YanshiPath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CameraControl.h"
#include "YanshiPath.h"
#include "afxdialogex.h"

CString pathThird=" ";  //����Ŀ¼��ʱ����

// CYanshiPath �Ի���

IMPLEMENT_DYNAMIC(CYanshiPath, CDialogEx)

CYanshiPath::CYanshiPath(CString rootPath,CString SaveType,int SaveIdx,CString SaveName,CWnd* pParent)
	: CDialogEx(CYanshiPath::IDD, pParent)
	, m_rootPath(rootPath)
	, m_SaveName(SaveName)
	, m_SaveType(SaveType)
	, m_SaveIdx(SaveIdx)
{
	m_secPath.Format("%s_%02d",m_SaveName,m_SaveIdx);
	if(m_SaveType== "MidView")
		m_nSaveType = 0;
	else m_nSaveType = 1;
	//UpdateData(TRUE);
}

CYanshiPath::~CYanshiPath()
{
}

void CYanshiPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_pathFirst, m_rootPath);
	DDX_Text(pDX, IDC_pathSecond, m_secPath);
	DDX_Radio(pDX, IDC_pathThirdM, m_nSaveType);
}


BEGIN_MESSAGE_MAP(CYanshiPath, CDialogEx)
	ON_BN_CLICKED(IDC_pathSecondJia, &CYanshiPath::OnBnClickedpathsecondjia)
	ON_BN_CLICKED(IDC_pathThirdM, &CYanshiPath::OnBnClickedpaththirdm)
	ON_BN_CLICKED(IDC_pathThirdU, &CYanshiPath::OnBnClickedpaththirdu)
	ON_BN_CLICKED(IDOK, &CYanshiPath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CYanshiPath::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_pathSecondJian, &CYanshiPath::OnBnClickedpathsecondjian)
END_MESSAGE_MAP()


// CYanshiPath ��Ϣ�������


void CYanshiPath::OnBnClickedpathsecondjia()  //����Ŀ¼����1
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	m_SaveIdx++;
	m_secPath.Format("%s_%02d",m_SaveName,m_SaveIdx);
	UpdateData(FALSE);

}

void CYanshiPath::OnBnClickedpathsecondjian()  //����Ŀ¼����1
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	if(m_SaveIdx >=2)
	{
		m_SaveIdx--;
		m_secPath.Format("%s_%02d",m_SaveName,m_SaveIdx);
		UpdateData(FALSE);
	}
}


void CYanshiPath::OnBnClickedpaththirdm()   //����Ŀ¼�����ӽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	m_SaveType = "MidView";
}


void CYanshiPath::OnBnClickedpaththirdu()  //����Ŀ¼�����ӽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	m_SaveType = "UpView";
}


CString CYanshiPath::GetAppPath1()
{
	//ȡ��Ӧ�ó���·��	
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString pathName(exeFullPath);

	//����ֵ����Դ�'\\'
	int index =pathName.ReverseFind('\\');
	return pathName.Left(index+1);
}

void CYanshiPath::OnBnClickedOk()  //����ȷ�������ٴ���Ŀ¼
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_pathFirst)->GetWindowTextA(m_rootPath);
	GetDlgItem(IDC_pathSecond)->GetWindowTextA(m_secPath);
	m_SaveIdx = atoi(m_secPath.Right(2));
	m_SaveName = m_secPath.Left(m_secPath.GetLength()-3);
	CString iniPath = GetAppPath1() + "settingD.ini";
	WritePrivateProfileString("setting","RootPath",m_rootPath,iniPath);
	WritePrivateProfileString("setting","Type",m_SaveType,iniPath);
	WritePrivateProfileString("setting","Name",m_SaveName,iniPath);
	CString idx;
	idx.Format("%d",m_SaveIdx);
	WritePrivateProfileString("setting","Index",idx,iniPath);
	CDialogEx::OnOK();
}


void CYanshiPath::OnBnClickedCancel()  //ȡ����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


// �ж�Ŀ¼�Ƿ����  
bool CYanshiPath::FolderExists(CString s)  
{  
	DWORD attr;   
	attr = GetFileAttributes(s);   
	return (attr != (DWORD)(-1) ) &&  
		( attr & FILE_ATTRIBUTE_DIRECTORY);   
}  

// �ݹ鴴��Ŀ¼�� ���Ŀ¼�Ѿ����ڻ��ߴ����ɹ�����TRUE  
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



