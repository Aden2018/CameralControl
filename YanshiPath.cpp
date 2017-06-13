// YanshiPath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CameraControl.h"
#include "YanshiPath.h"
#include "afxdialogex.h"

CString pathThird=" ";  //����Ŀ¼��ʱ����

// CYanshiPath �Ի���

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


// CYanshiPath ��Ϣ�������


void CYanshiPath::OnBnClickedpathsecondjia()  //����Ŀ¼����1
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	m_pathSecIndex ++;
	AcqPathSecSequence[m_pathSecIndex]=m_pathSecIndex;
	CString JpgSequence;
	JpgSequence.Format("_%d",AcqPathSecSequence[m_pathSecIndex]);	
	pathSecond = "3dpicture"  + JpgSequence;

	UpdateData(FALSE);
}

void CYanshiPath::OnBnClickedpathsecondjian()  //����Ŀ¼����1
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CYanshiPath::OnBnClickedpaththirdm()   //����Ŀ¼�����ӽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	pathThird=Tmid;
}


void CYanshiPath::OnBnClickedpaththirdu()  //����Ŀ¼�����ӽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ŀ¼
	pathThird=Tup;
}

void CYanshiPath::OnBnClickedOk()  //����ȷ�������ٴ���Ŀ¼
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strPictruefile=pathFirst+"\\"+pathSecond+"\\"+pathThird;
	SuperMkDir(m_strPictruefile);

	//�������ļ�������ֵд��settingD.ini
	CString pathSecIni;
	pathSecIni.Format("%d",m_pathSecIndex);
	//E:\\3Drestructure\\���600D\\settingD.ini
	::WritePrivateProfileString("����Ŀ¼����ֵ","m_pathIndex",pathSecIni,"E:\\3Drestructure\\���600D\\settingD.ini");  

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



