
// APIExampleDlg.h : header file
//

#pragma once

#include "OriginalVideo/CAgoraOriginalVideoDlg.h"
#include "OriginalAudio/CAgoraOriginalAudioDlg.h"

#include <vector>
#include <map>
const int MAIN_AREA_BOTTOM = 15;

// CAPIExampleDlg dialog
class CAPIExampleDlg : public CDialogEx
{
// Construction
public:
	CAPIExampleDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APIEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg LRESULT OnEIDJoinLeaveChannel(WPARAM wParam, LPARAM lParam);
   
private:
    void InitSceneDialog();
    void InitSceneList();
    void InitCtrlText();
    HTREEITEM GetHitItem(NMHDR *pNMHDR);
    
    void ReleaseScene(CString selectedText);
    void CreateScene(CString selectedText);

	CAgoraOriginalVideoDlg		*m_pOriginalVideoDlg = nullptr;
	CAgoraOriginalAudioDlg		*m_pOriginalAudioDlg = nullptr;
	
    CString m_preSelectedItemText = _T("");
    std::vector<CString> m_vecAdvanced;

    BOOL m_bJoinChannel = FALSE;
public:
    CStatic m_staMainArea;
    CTreeCtrl m_lstAdvanced;
  
    afx_msg void OnSelchangedListAdvanced(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickListAdvanced(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnSelchangingListAdvanced(NMHDR *pNMHDR, LRESULT *pResult);
    CStatic m_stalstInfo;
    CStatic m_staAdvancedScene;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

