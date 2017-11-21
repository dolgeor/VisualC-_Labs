
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	afx_msg void OnEnChangeEdit1();
	float m_P;
	afx_msg void OnEnChangeEditProb();
	int m_U;
	int m_FREQ;
	float m_L;
	
	BOOL m_Ant;
	afx_msg void OnBnClickedCheckAntivir();
	float m_res;
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnStnClickedStaticProb2();
	CEdit m_Sq;
	afx_msg void OnEnChangeEditSeq();
	int nrClicks = 0;
};
