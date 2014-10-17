// EmoTractUI.cpp : define los comportamientos de las clases para la aplicación.
//

#include "stdafx.h"
#include "EmoTractUI.h"
#include "EmoTractUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEmoTractUIApp

BEGIN_MESSAGE_MAP(CEmoTractUIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Construcción de CEmoTractUIApp

CEmoTractUIApp::CEmoTractUIApp()
{
	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// El único objeto CEmoTractUIApp

CEmoTractUIApp theApp;


// Inicialización de CEmoTractUIApp

BOOL CEmoTractUIApp::InitInstance()
{
	// Windows XP requiere InitCommonControlsEx() si un manifiesto de
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generará un error al crear ventanas.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Establecer para incluir todas las clases de control comunes que desee utilizar
	// en la aplicación.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inicialización estándar
	// Si no utiliza estas características y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que contenga información correcta
	// como el nombre de su compañía u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));

	CEmoTractUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aquí el código para controlar
		//  cuándo se descarta el cuadro de diálogo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aquí el código para controlar
		//  cuándo se descarta el cuadro de diálogo con Cancelar
	}

	// Dado que el cuadro de diálogo se ha cerrado, devolver FALSE para salir
	//  de la aplicación en vez de iniciar el suministro de mensajes de dicha aplicación.
	return FALSE;
}
