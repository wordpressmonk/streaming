
// APIExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "APIExample.h"
#include "APIExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAPIExampleDlg dialog



CAPIExampleDlg::CAPIExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APIEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAPIExampleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_MAIN, m_staMainArea);
    DDX_Control(pDX, IDC_LIST_ADVANCED, m_lstAdvanced);
    DDX_Control(pDX, IDC_STATIC_LIST_INFO, m_stalstInfo);
    DDX_Control(pDX, IDC_STATIC_ADVANCE, m_staAdvancedScene);
}

BEGIN_MESSAGE_MAP(CAPIExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

    ON_NOTIFY(NM_CLICK, IDC_LIST_ADVANCED, &CAPIExampleDlg::OnClickListAdvanced)
    ON_NOTIFY(TVN_SELCHANGED, IDC_LIST_ADVANCED, &CAPIExampleDlg::OnSelchangedListAdvanced)
    ON_NOTIFY(TVN_SELCHANGING, IDC_LIST_ADVANCED, &CAPIExampleDlg::OnSelchangingListAdvanced)
END_MESSAGE_MAP()


// CAPIExampleDlg message handlers

BOOL CAPIExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	std::string strAppID = GET_APP_ID;
	if (strcmp(strAppID.c_str(), "") == 0)
	{
		AfxMessageBox(_T("APP ID is not set, you can see readme file on how to get an APP ID."));
		ExitProcess(1);
	}
    InitCtrlText();
    InitSceneDialog();
    InitSceneList();
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAPIExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAPIExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAPIExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAPIExampleDlg::InitCtrlText()
{
    m_staAdvancedScene.SetWindowText(commonAdvanceScene);
}

void CAPIExampleDlg::InitSceneDialog()
{

   //original video process
   m_vecAdvanced.push_back(advancedOriginalVideo);
   m_pOriginalVideoDlg = new CAgoraOriginalVideoDlg(&m_staMainArea);
   m_pOriginalVideoDlg->Create(CAgoraOriginalVideoDlg::IDD);
   
   RECT rcArea, rcWnd;
   m_staMainArea.GetWindowRect(&rcArea);
   m_pOriginalVideoDlg->GetWindowRect(&rcWnd);

   int w = rcWnd.right - rcWnd.left;
   int h = rcWnd.bottom - rcWnd.top;
   rcWnd = { rcArea.left, rcArea.top - MAIN_AREA_TOP, rcArea.left + w, rcArea.top + h};
   
   m_pOriginalVideoDlg->MoveWindow(&rcWnd);
   
   //original video process
   m_vecAdvanced.push_back(advancedOriginalAudio);
   m_pOriginalAudioDlg = new CAgoraOriginalAudioDlg(&m_staMainArea);
   m_pOriginalAudioDlg->Create(CAgoraOriginalAudioDlg::IDD);
   m_pOriginalAudioDlg->MoveWindow(&rcWnd);
     
}

void CAPIExampleDlg::InitSceneList()
{
  
    for (size_t i = 0; i < m_vecAdvanced.size(); i++) {
        TVINSERTSTRUCT tvInsert;
        tvInsert.hParent = NULL;
        tvInsert.hInsertAfter = NULL;
        tvInsert.item.mask = TVIF_TEXT;
        tvInsert.item.pszText = m_vecAdvanced[i].GetBuffer(0);
        m_lstAdvanced.InsertItem(&tvInsert);
    }
}

void CAPIExampleDlg::OnSelchangedListAdvanced(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    *pResult = 0;
    HTREEITEM hItem = m_lstAdvanced.GetSelectedItem();
    m_preSelectedItemText = m_lstAdvanced.GetItemText(hItem);
    CreateScene(m_preSelectedItemText); // JAY
}

HTREEITEM  CAPIExampleDlg::GetHitItem(NMHDR *pNMHDR)
{
    DWORD dwPos = GetMessagePos();
    POINT pt;
    pt.x = LOWORD(dwPos);
    pt.y = HIWORD(dwPos);
    ::ScreenToClient(pNMHDR->hwndFrom, &pt);
    TVHITTESTINFO ht = { 0 };

    ht.flags = TVHT_ONITEM;
    HTREEITEM hitItem = TreeView_HitTest(pNMHDR->hwndFrom, &ht);
   
    return hitItem ;
}

void CAPIExampleDlg::OnClickListAdvanced(NMHDR *pNMHDR, LRESULT *pResult)
{   
    *pResult = 0;
}

void CAPIExampleDlg::OnSelchangingListAdvanced(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    HTREEITEM hOldItem = pNMTreeView->itemOld.hItem;
	CString selectedText = m_lstAdvanced.GetItemText(hOldItem);
	if (m_preSelectedItemText.Compare(selectedText) == 0) {
        ReleaseScene(selectedText);
    }
    *pResult = 0;
}

void CAPIExampleDlg::CreateScene(CString selectedText)
{
    if (selectedText.Compare(advancedOriginalVideo) == 0) {
		m_pOriginalVideoDlg->InitAgora();
		m_pOriginalVideoDlg->ShowWindow(SW_SHOW);
	}else if (selectedText.Compare(advancedOriginalAudio) == 0) {
		m_pOriginalAudioDlg->InitAgora();
		m_pOriginalAudioDlg->ShowWindow(SW_SHOW);
	}
}

void CAPIExampleDlg::ReleaseScene(CString selectedText)
{
	if (selectedText.Compare(advancedOriginalVideo) == 0
		&& m_pOriginalVideoDlg->IsWindowVisible()) {
		m_pOriginalVideoDlg->UnInitAgora();
		m_pOriginalVideoDlg->ShowWindow(SW_HIDE);
	}else if (selectedText.Compare(advancedOriginalAudio) == 0) {
		m_pOriginalAudioDlg->UnInitAgora();
		m_pOriginalAudioDlg->ShowWindow(SW_HIDE);
	}
}

LRESULT CAPIExampleDlg::OnEIDJoinLeaveChannel(WPARAM wParam, LPARAM lParam)
{
    m_bJoinChannel = (BOOL)wParam;
    m_lstAdvanced.EnableWindow(!m_bJoinChannel);
    if (m_bJoinChannel) {
		m_stalstInfo.SetWindowText(L"you can leave channel first.");
    }
    else
        m_stalstInfo.SetWindowText(_T(""));
    return 0;
}

BOOL CAPIExampleDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
