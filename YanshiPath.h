#pragma once


// CYanshiPath �Ի���

class CYanshiPath : public CDialogEx
{
	DECLARE_DYNAMIC(CYanshiPath)

public:
	CYanshiPath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYanshiPath();

// �Ի�������
	enum { IDD = IDD_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString pathFirst;
	CString pathSecond;
	CString Tmid;
	CString Tup;
	afx_msg void OnBnClickedpathsecondjia();
	afx_msg void OnBnClickedpaththirdm();
	afx_msg void OnBnClickedpaththirdu();
	afx_msg bool FolderExists(CString s);
	afx_msg bool SuperMkDir(CString P);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedpathsecondjian();
};
