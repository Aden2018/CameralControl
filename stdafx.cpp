// stdafx.cpp : source file that includes just the standard includes
// CameraControl.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


CString m_strImageName="3dIMG_";
int m_nImageIndex=0;	
int AcqSequence[256]={0};

int m_pathSecIndex=0;	
int AcqPathSecSequence[256]={0};

CString m_strPictruefile=" ";  //岩石对应的文件夹

CString filename = "m_strPictruefile\\3dIMG_0.jpg"; //初始化
