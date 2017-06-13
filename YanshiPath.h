#pragma once


// CYanshiPath 对话框

class CYanshiPath : public CDialogEx
{
	DECLARE_DYNAMIC(CYanshiPath)

public:
	CYanshiPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYanshiPath();

// 对话框数据
	enum { IDD = IDD_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
