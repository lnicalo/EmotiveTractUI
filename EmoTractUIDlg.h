// EmoTractUIDlg.h: archivo de encabezado
//
#define MAX_ACTIONS 3

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// Necesarios para el control del BCI mediante la API dada por emotiv
#include "edk.h"
#include "edkErrorCode.h"
#include "EmoStateDLL.h"

// Cuadro de diálogo de CEmoTractUIDlg
class CEmoTractUIDlg : public CDialog
{
// Construcción
public:
	CEmoTractUIDlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_EMOTRACTUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	// Combo Box con las diferentes acciones que se pueden entrenar
	CComboBox TrActionsCB;

	// Hilo que se encarga de recoger los mensajes
	CWinThread *m_pThread;

	friend UINT threadMessage(LPVOID v);
	afx_msg void OnCbnSelchangeCombo1();

	// Lista donde se anotan los eventos sucedidos para mostrarlos al usuario
	CListCtrl m_infoListCtrl;
	afx_msg void OnDestroy();

	void imprimirInfo(LPCTSTR str);

	CString m_actions[MAX_ACTIONS];
	EE_CognitivAction_enum m_activeActions[MAX_ACTIONS];
	afx_msg void OnBnClickedButton2();
	CProgressCtrl m_progCtrlPower;
	CEdit m_editAction;
	void printAction(CString action, float power);
//	afx_msg void OnNMCustomdrawSliderSens(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTRBNThumbPosChangingSliderSens(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slider_sens;
};
