#pragma once


// CYanshiPath �Ի���

class CYanshiPath : public CDialogEx
{
	DECLARE_DYNAMIC(CYanshiPath)

public:
	CYanshiPath(CString rootPath,CString SaveType,int SaveIdx,CString SaveName,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYanshiPath();

// �Ի�������
	enum { IDD = IDD_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_rootPath;
	CString m_SaveName;
	int m_SaveIdx;
	CString m_SaveType;
	CString m_secPath;

	afx_msg void OnBnClickedpathsecondjia();
	afx_msg void OnBnClickedpaththirdm();
	afx_msg void OnBnClickedpaththirdu();
	afx_msg bool FolderExists(CString s);
	afx_msg bool SuperMkDir(CString P);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedpathsecondjian();
	CString GetAppPath1();
	int m_nSaveType;
};
