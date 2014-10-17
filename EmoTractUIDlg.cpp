// EmoTractUIDlg.cpp: archivo de implementación
//
#include "stdafx.h"
#include "EmoTractUI.h"
#include "EmoTractUIDlg.h"

// Para el control del tractor
#include "actuador.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "../lib/edk.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void handleCognitivEvent(CEmoTractUIDlg* pDlg, EmoEngineEventHandle cognitivEvent);

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cuadro de diálogo de CEmoTractUIDlg




CEmoTractUIDlg::CEmoTractUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmoTractUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEmoTractUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, TrActionsCB);
	DDX_Control(pDX, IDC_LIST1, m_infoListCtrl);
	DDX_Control(pDX, IDC_PROGRESS_POWER, m_progCtrlPower);
	DDX_Control(pDX, IDC_EDIT_ACTION, m_editAction);
	DDX_Control(pDX, IDC_SLIDER_SENS, m_slider_sens);
}

BEGIN_MESSAGE_MAP(CEmoTractUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CEmoTractUIDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CEmoTractUIDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEmoTractUIDlg::OnCbnSelchangeCombo1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CEmoTractUIDlg::OnBnClickedButton2)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SENS, &CEmoTractUIDlg::OnNMCustomdrawSliderSens)
//ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_SENS, &CEmoTractUIDlg::OnTRBNThumbPosChangingSliderSens)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Controladores de mensaje de CEmoTractUIDlg

BOOL CEmoTractUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// Acciones que se pueden entrenar
	m_actions[0] = "Neutral";
	m_actions[1] = "Right";
	m_actions[2] = "Left";

	m_activeActions[0] = COG_NEUTRAL;
	m_activeActions[1] = COG_RIGHT;
	m_activeActions[2] = COG_LEFT;

	// Inicializacion del combo box
	for(int i=0; i < MAX_ACTIONS; i++) {
		TrActionsCB.InsertString(i,m_actions[i]);
	}

	TrActionsCB.SelectString(0,_T("Neutral"));

	// Inicializacion de la lista
	m_infoListCtrl.InsertColumn(0, _T("Information"), LVCFMT_LEFT, 300);

	// Iniciacion de la barra de potencia
	m_progCtrlPower.SetRange(0, 100);
	m_progCtrlPower.SetPos(0);

	// Iniciacion del cuadro de texto
	m_editAction.SetWindowTextW(_T("No action detected"));

	// Iniciamos el slider
	m_slider_sens.SetRange(1, 7);
	m_slider_sens.SetTicFreq(1);

	// Iniciamos el puerto serie
	// XC_ACT_Cfg Cfg_Act;

	// Falta recoger el error
	// ACTUADOR__P_Inicia(Cfg_Act);
	
	// Iniamos el hilo que se encarga de recoger los mensajes del BCI
	m_pThread = AfxBeginThread(threadMessage,this);
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CEmoTractUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CEmoTractUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CEmoTractUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CEmoTractUIDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Agregue aquí su código de controlador de notificación de control
//	*pResult = 0;
//}

// Comienzo del entrenamiento de una accion
void CEmoTractUIDlg::OnBnClickedButton1()
{
	unsigned int userID = 0;
	if( EE_CognitivSetActiveActions(userID, m_activeActions[1] | m_activeActions[2]) != EDK_OK) {
		imprimirInfo(_T("Error in the supported action activation"));
	}

	// Vemos que accion quiere ser entrenada
	int nChoice = TrActionsCB.GetCurSel();
	if (EE_CognitivSetTrainingAction(userID, m_activeActions[nChoice]) != EDK_OK) {
		imprimirInfo(_T("Error in the training initiation"));
	}

	CString m;
	m.Format(_T("Setting Cognitiv training action for user %d to \"%s\" ..."), userID, m_actions[nChoice]);
	imprimirInfo(m);
	if ( IDOK == AfxMessageBox(_T("Accept to start the training. The training last 8 seconds."), MB_OKCANCEL) ) {
		if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {
			imprimirInfo(_T("Error in the training start"));
		}
		else {
			imprimirInfo(_T("Training..."));
		}
	}
	else {
		imprimirInfo(_T("Training stopped"));
	}
}



void CEmoTractUIDlg::OnCbnSelchangeCombo1()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}

void CEmoTractUIDlg::OnDestroy()
{
 	CDialog::OnDestroy();

	// Desconectamos
	/*EE_EngineDisconnect();
	EE_EmoStateFree(m_eState);
	EE_EmoEngineEventFree(m_eEvent); */

	// Falta recoger el error
	// ACTUADOR__P_Fin();
}

void CEmoTractUIDlg::imprimirInfo(LPCTSTR str)
{
	m_infoListCtrl.InsertItem(0,str);
}

void CEmoTractUIDlg::OnBnClickedButton2()
{
	unsigned int userID = 0;
	if (EE_CognitivSetTrainingControl(userID, COG_ERASE) != EDK_OK) {
		imprimirInfo(_T("Error trying to erase the training"));
	}
}

void CEmoTractUIDlg::printAction(CString action, float power)
{
	m_editAction.SetWindowTextW(action);
	int pos = static_cast<int>(100*power);
	m_progCtrlPower.SetPos(pos);
}


UINT threadMessage(LPVOID v)
{
	// Puntero para acceder al dialogo
	CEmoTractUIDlg* pDlg = static_cast<CEmoTractUIDlg*>(v);

	// String para los mensajes
	CString m;
	
	// Para el control de eventos del BCI
	EmoEngineEventHandle eEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = 0;

	// Para el control del giro del tractor
	// DT_UWord Pos_BAMS;

	if (EE_EngineConnect() != EDK_OK) {
	// if (EE_EngineRemoteConnect("127.0.0.1", 1726) != EDK_OK) {
		pDlg->imprimirInfo(_T("Emotiv Engine connection failed"));
	}
	else {
		pDlg->imprimirInfo(_T("Emotiv Engine started!"));
	}
	
	// Por defecto ponemos nivel de sensibilidad 3
	
	EE_CognitivSetActivationLevel(userID, 3);
	// Actualizar la barra deslizante
	pDlg->m_slider_sens.SetPos(3);

	while (true) {
		int state = EE_EngineGetNextEvent(eEvent);

		// New event needs to be handled
		if (state == EDK_OK) {

			EE_Event_t eventType = EE_EmoEngineEventGetType(eEvent);
			EE_EmoEngineEventGetUserId(eEvent, &userID);
			
			switch (eventType) {

				case EE_UserAdded:
				{
                    pDlg->imprimirInfo(_T("New user ")); // << userID << std::endl;
					break;
				}

				case EE_UserRemoved:
				{
                    pDlg->imprimirInfo(_T("User has been removed" )); // << userID << " has been removed." << std::endl;
					break;
				}
				
				// Se ha recibido un evento cognitivo
				case EE_EmoStateUpdated:
				{
					//std::cout << "New EmoState from user " << userID << "..." << std::endl;
					EE_EmoEngineEventGetEmoState(eEvent, eState);

					EE_CognitivAction_t actionType	= ES_CognitivGetCurrentAction(eState);
					float				actionPower = ES_CognitivGetCurrentActionPower(eState);
					
					switch (actionType) {
						case COG_LEFT:
							// Acciones a realizar cuando sea izquierda.

							// Comunicacion por la lista
							// m.Format(_T("Hacia la izquierda. Potencia: %f"),actionPower);
							// pDlg->imprimirInfo(m);

							// Comunicacion por el cuadro de texto y la barra de progreso
							pDlg->printAction(_T("Left"), actionPower);

							// Falta recoger el error del puerto serie
							// ACTUADOR__P_Set_Direccion(Pos_BAMS);
							break;
						case COG_RIGHT:
							// Acciones a realizar cuando sea derecha
							// m.Format(_T("Hacia la derecha. Potencia: %f"),actionPower);
							// pDlg->imprimirInfo(m);

							// Comunicacion por el cuadro de texto y la barra de progreso
							pDlg->printAction(_T("Right"), actionPower);

							// Falta recoger el error
							// ACTUADOR__P_Set_Direccion(Pos_BAMS);
							break;
						default:
							// pDlg->imprimirInfo(_T("Comando no reconocido " ));

							// Comunicacion por el cuadro de texto y la barra de progreso
							pDlg->printAction(_T("No action"), 0);
							break;
					}
					break;
				}

				// Handle Cognitiv training related event
				case EE_CognitivEvent:
				{
					handleCognitivEvent(pDlg, eEvent);
					break;
				}

				default:
					break;
			}
		}
		else if (state != EDK_NO_EVENT) {
			pDlg->imprimirInfo(_T("Internal error in Emotiv Engine! " ));
			break;
		}

		Sleep(1);
	}
	return 0;
}

void handleCognitivEvent(CEmoTractUIDlg* pDlg, EmoEngineEventHandle cognitivEvent) {

	unsigned int userID = 0;
	EE_EmoEngineEventGetUserId(cognitivEvent, &userID);
	EE_CognitivEvent_t eventType = EE_CognitivEventGetType(cognitivEvent);


	switch (eventType) {

		case EE_CognitivTrainingStarted:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user STARTED!"));
			break;
		}

		case EE_CognitivTrainingSucceeded:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user SUCCEEDED!"));
			if(AfxMessageBox(_T("Accept or reject the session ?"),MB_OKCANCEL) == IDOK) {
				if (EE_CognitivSetTrainingControl(userID, COG_ACCEPT) != EDK_OK) {
					pDlg->imprimirInfo(_T("Error trying to accept the session"));
				}
			}
			else {
				if (EE_CognitivSetTrainingControl(userID, COG_REJECT) != EDK_OK) {
					pDlg->imprimirInfo(_T("Error trying to reject the session"));
				}
			}
			break;
		}

		case EE_CognitivTrainingFailed:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user FAILED!"));
			break;
		}

		case EE_CognitivTrainingCompleted:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user COMPLETED!"));
			EE_CognitivAction_t   pActionOut;
			EE_CognitivGetTrainingAction(userID, &pActionOut);
			for(int i=0; i< MAX_ACTIONS; i++) {
				if(pDlg->m_activeActions[i] == pActionOut) {
					pDlg->imprimirInfo(pDlg->m_actions[i] + _T(" has been trained"));
				}
			}
			break;
		}

		case EE_CognitivTrainingDataErased:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user ERASED!"));
			break;
		}

		case EE_CognitivTrainingRejected:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user REJECTED!"));
			break;
		}

		case EE_CognitivTrainingReset:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user RESET!"));
			break;
		}

		case EE_CognitivAutoSamplingNeutralCompleted:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user COMPLETED!"));
			break;
		}

		case EE_CognitivSignatureUpdated:
		{
			pDlg->imprimirInfo(_T("Cognitiv training for user UPDATED!"));
			break;
		}
		case EE_CognitivNoEvent:
			break;

		default:
			pDlg->imprimirInfo(_T("Cognitiv training: Unhandled event"));
			break;
	}
}


//void CEmoTractUIDlg::OnTRBNThumbPosChangingSliderSens(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// Esta característica requiere Windows Vista o posterior.
//	// El símbolo _WIN32_WINNT debe ser >= 0x0600.
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: Agregue aquí su código de controlador de notificación de control
//	*pResult = 0;
//}

void CEmoTractUIDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Agregue aquí su código de controlador de mensajes o llame al valor predeterminado
	unsigned int userID = 0;
	int pos = m_slider_sens.GetPos();
	EE_CognitivSetActivationLevel(userID, pos);


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
