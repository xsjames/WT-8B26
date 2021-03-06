/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END
#define WT_WINDOWS_TEST_GLOBALS

#include "DIALOG.h"
#include "wt_bsp.h"
#include "wt_task_gui.h"
#include "main.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0     		(GUI_ID_USER + 0x00)
#define ID_LISTBOX_0    		(GUI_ID_USER + 0x01)
#define ID_TEXT_0     			(GUI_ID_USER + 0x02)
#define ID_TREEVIEW_0     	(GUI_ID_USER + 0x03)
#define ID_BUTTON_OK     		(GUI_ID_USER + 0x04)
#define ID_BUTTON_CANCEL    (GUI_ID_USER + 0x05)
#define ID_TEXT_1     			(GUI_ID_USER + 0x06)
#define ID_DROPDOWN_0    		(GUI_ID_USER + 0x07)



// USER START (Optionally insert additional defines)
// USER END
extern void WT_StudyFiles_Read(void);
static char filename[80];
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static void Init_Dialog(WM_MESSAGE * pMsg);
// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 50, 0, 380, 222, 0, 0x0, 0 },
	{ LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 30, 60, 320, 120, 0, 0x0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 135, 30, 80, 19, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Filebowser", ID_TEXT_0, 40, 30, 100, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "FileInfo", ID_TEXT_1, 240,  32,  120,  20, 0, 0x0, 0 },
	{	BUTTON_CreateIndirect, "确定", ID_BUTTON_OK, 90, 195, 100, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "取消", ID_BUTTON_CANCEL, 190, 195, 100, 20, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN                hItem;
	WM_MESSAGE             Msg;
	WM_HWIN                hIteminfo;
	int 									  i;
	int 	     					sel;
	uint8_t     					items;
	FRESULT res;

	hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, GUI_LIGHTGRAY);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
	//WM_SetFocus(hItem);
	
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    
    Init_Dialog(pMsg);
    break;
	case MY_MESSAGE_CLICK:
		GUI_SendKeyMsg(GUI_KEY_TAB, 1);//改变输入焦点
		break;
	case MY_MESSAGE_DOWN:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		if(WM_HasFocus(hItem))
		{
			LISTBOX_IncSel(hItem);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		if(WM_HasFocus(hItem))
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel<1)
			{
				DROPDOWN_IncSel(hItem);
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,0);		
			}	

			store_dev=DROPDOWN_GetSel(hItem);
			WT_TestFolder_Init();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
			items = LISTBOX_GetNumItems(hItem);
			for(i=0;i<items;i++)
			{
				LISTBOX_DeleteItem(hItem,0);
			}
			for(i=0;i<TestFolder->number_TotalFile;i++)
			{
				LISTBOX_AddString(hItem, (char *)TestFolder->FilesName[i]);
			}
		}	
		break;
	case MY_MESSAGE_UP:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		if(WM_HasFocus(hItem))
		{
			LISTBOX_DecSel(hItem);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		if(WM_HasFocus(hItem))
		{
			sel=DROPDOWN_GetSel(hItem);
			if(sel>0)
			{
				DROPDOWN_DecSel(hItem);
			}					
			else //sel>=1 
			{
				DROPDOWN_SetSel(hItem,1);		
			}	

			store_dev=DROPDOWN_GetSel(hItem);
			WT_TestFolder_Init();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
			items = LISTBOX_GetNumItems(hItem);
			for(i=0;i<items;i++)
			{
				LISTBOX_DeleteItem(hItem,0);
			}
			for(i=0;i<TestFolder->number_TotalFile;i++)
			{
				LISTBOX_AddString(hItem, (char *)TestFolder->FilesName[i]);
			}
		}
		break;
	case MY_MESSAGE_CANCEL://取消
		GUI_EndDialog(pMsg->hWin,0);
		break;
	case MY_MESSAGE_OK:
		hIteminfo = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetText(hIteminfo, (char *)"打开文件中……");
		WM_ShowWindow(hIteminfo);
	  GUI_Exec();
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		TestFolder->number_CurrentFile=LISTBOX_GetSel(hItem);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		store_dev=DROPDOWN_GetSel(hItem);
		WT_TestItem_Read((char *)TestFolder->FilesName[TestFolder->number_CurrentFile]);
		//WT_TestFile_Write2Flash((char *)TestFolder->FilesName[TestFolder->number_CurrentFile将文件内容复制到Flash
	  //WT_TestFiles_Write2card((char *)TestFolder->FilesName[TestFolder->number_CurrentFile]);//将文件内容复制到SD card

	  if(TestFile->file_status == 1)//文件读取OK
		{
			Msg.MsgId = MY_MESSAGE_BUTTONOK;
			WM_SendMessage(pMsg->hWinSrc,&Msg);
			GUI_EndDialog(pMsg->hWin,0);
		}
		else
		{
			TEXT_SetText(hIteminfo, (char *)"读取文件错误！");
			WM_ShowWindow(hIteminfo);
		}
		Msg.MsgId = MY_MESSAGE_BUTTONOK;
		WM_SendMessage(pMsg->hWinSrc,&Msg);
		GUI_EndDialog(pMsg->hWin,0);

		break;
	case MY_MESSAGE_BUTTONDELETE:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		store_dev=DROPDOWN_GetSel(hItem);
		if(store_dev==0) //usb
		strcpy(filename,path_testfile);
		//f_opendir(&dir, path_testfile);
		if(store_dev==1) //sd
		strcpy(filename,path_testfile_sd);
		//f_opendir(&dir, path_testfile_sd);
		//res = f_opendir(&dir, "1:/LZY_WireTester/Test Files");
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		strcat(filename,"/");
		sel = LISTBOX_GetSel(hItem);
		if(sel < 0) break;
		strcat(filename,(char *)TestFolder->FilesName[LISTBOX_GetSel(hItem)]);
		res=f_unlink((const TCHAR*)filename);
		if(res == FR_OK)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
			store_dev=DROPDOWN_GetSel(hItem);
			WT_TestFolder_Init();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
			items = LISTBOX_GetNumItems(hItem);
			for(i=0;i<items;i++)
			{
				LISTBOX_DeleteItem(hItem,0);
			}
			for(i=0;i<TestFolder->number_TotalFile;i++)
			{
				LISTBOX_AddString(hItem, (char *)TestFolder->FilesName[i]);
			}
			WM_SetFocus(hItem);
			if(sel > 0) LISTBOX_SetSel(hItem,sel - 1);
			else LISTBOX_SetSel(hItem,0);
		}
		break;
	case WM_PAINT://绘制标题栏
		GUI_SetColor(GUI_DARKBLUE);
		GUI_FillRect(0,0,380,22);
		GUI_SetColor(GUI_DARKGRAY);
		GUI_SetPenSize(8);
		GUI_DrawRect(0,0,378,220);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN Create_EditDlgWindow( WM_HWIN hWin_para);
WM_HWIN Create_EditDlgWindow( WM_HWIN hWin_para) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, hWin_para, 0, 0);
  return hWin;
}

static void Init_Dialog(WM_MESSAGE * pMsg)
{
	  WM_HWIN                hItem;
		WM_HWIN                hIteminfo;
	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem,&GUI_FontHZ12);
    TEXT_SetText(hItem, "自学习文件选择");  
	
		hIteminfo = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hIteminfo,&GUI_FontHZ12);
		TEXT_SetTextColor(hIteminfo,GUI_RED);
		TEXT_SetText(hIteminfo, (char *)"打开文件……");
		WM_HideWindow(hIteminfo);
	  //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		DROPDOWN_SetFont(hItem,&GUI_FontHZ12);
    DROPDOWN_AddString(hItem, "U盘");
    DROPDOWN_AddString(hItem, "SD卡");
		if(k_StorageGetStatus(MSD_DISK_UNIT) != 0)
		DROPDOWN_SetSel(hItem,1);
		else DROPDOWN_SetSel(hItem,0);
		//
    // Initialization of 'Treeview'
    //
		store_dev=DROPDOWN_GetSel(hItem);
		WT_TestFolder_Init();
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		for(int i=0;i<TestFolder->number_TotalFile;i++)
		{
			LISTBOX_AddString(hItem, (char *)TestFolder->FilesName[i]);
		}
		LISTBOX_SetFont(hItem,GUI_FONT_20_1);
		LISTBOX_SetSel(hItem,TestFolder->number_CurrentFile);
    
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_GREEN);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CANCEL);
		BUTTON_SetFont(hItem,&GUI_FontHZ12);
		BUTTON_SetSkinClassic(hItem);
		BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED, GUI_RED);
		BUTTON_SetFocussable(hItem,0);//不接收焦点
}

/*************************** End of file ****************************/
