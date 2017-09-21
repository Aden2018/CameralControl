

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

class DownloadCommand : public Command
{
private:
	EdsDirectoryItemRef _directoryItem;

public:
	DownloadCommand(CameraModel *model, EdsDirectoryItemRef dirItem) 
			: _directoryItem(dirItem), Command(model){}


	virtual ~DownloadCommand()
	{
		//Release item
		if(_directoryItem != NULL)
		{
			EdsRelease( _directoryItem);
			_directoryItem = NULL;
		}
	}


	// Execute command 	
	virtual bool execute()
	{
		EdsError				err = EDS_ERR_OK;
		EdsStreamRef			stream = NULL;

		//����ÿ�������ͼƬ��
		
		/*m_nImageIndex ++;
		AcqSequence[m_nImageIndex]=m_nImageIndex;
		CString JpgSequence;
		JpgSequence.Format("%02d.jpg",AcqSequence[m_nImageIndex]);
		filename = m_strPictruefile + "\\" + m_strImageName + JpgSequence;*/
		CString strIdx;
		strIdx.Format("%02d",++g_imgIdx);
		CString fileName = g_savePath + "\\" + g_imgPreFix + strIdx + ".jpg";

		//Acquisition of the downloaded image information
		EdsDirectoryItemInfo	dirItemInfo;
		err = EdsGetDirectoryItemInfo( _directoryItem, &dirItemInfo);
	
		//Make the file stream at the forwarding destination
		if(err == EDS_ERR_OK)
		{	
			err = EdsCreateFileStream(fileName, kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);
			//err = EdsCreateFileStream(dirItemInfo.szFileName, kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);

			//֪ͨ�����濪ʼ����
			if(err == EDS_ERR_OK)
			{
				CameraEvent e("DownloadStart");
				_model->notifyObservers(&e);
			}
			//err = EdsDownload( _directoryItem, dirItemInfo.size, stream);
		}
		//Set Progress
		if(err == EDS_ERR_OK)
		{
			err = EdsSetProgressCallback(stream, ProgressFunc, kEdsProgressOption_Periodically, this);
		}

		//Download image
		if(err == EDS_ERR_OK)
		{
			err = EdsDownload( _directoryItem, dirItemInfo.size, stream);
		}

		//Forwarding completion
		if(err == EDS_ERR_OK)  //�洢������
		{
			err = EdsDownloadComplete( _directoryItem);
			//AfxMessageBox("�������");
		}

		//Release Item
		if(_directoryItem != NULL)
		{
			err = EdsRelease( _directoryItem);
			_directoryItem = NULL;
		}

		//Release stream
		if(stream != NULL)
		{
			err = EdsRelease(stream);
			stream = NULL;
		}		
		
		// Forwarding completion notification
		if( err == EDS_ERR_OK)
		{
			CameraEvent e("DownloadComplete", &err);
			_model->notifyObservers(&e);
		}

		//Notification of error
		if( err != EDS_ERR_OK)
		{
			CameraEvent e("error", &err);
			_model->notifyObservers(&e);
		}

		return true;
	}

private:
	static EdsError EDSCALLBACK ProgressFunc (
						EdsUInt32	inPercent,
						EdsVoid *	inContext,
						EdsBool	*	outCancel
						)
	{
		Command *command = (Command *)inContext;
		CameraEvent e("ProgressReport", &inPercent);
		command->getCameraModel()->notifyObservers(&e);
		return EDS_ERR_OK;
	}


};