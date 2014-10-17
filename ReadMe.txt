================================================================================
    BIBLIOTECA MICROSOFT FOUNDATION CLASS: Información general del proyectoEmotivTractUI
===============================================================================

El Asistente para aplicaciones ha creado esta aplicación EmotivTractUI.  Esta aplicación no sólo muestra los fundamentos del uso de Microsoft 
Foundation Classes sino que también supone un punto de partida para el desarrollo de la propia aplicación.

Este archivo incluye un resumen acerca del contenido de los archivos que
constituyen su aplicación EmotivTractUI.

EmotivTractUI.vcproj
    Éste es el archivo de proyecto principal para los proyectos de VC++ generados mediante un asistente para aplicaciones. 
    Contiene información acerca de la versión de Visual C++ con la que se generó el archivo, así como
    información acerca de las plataformas, configuraciones y características del proyecto seleccionadas en el
    Asistente para aplicaciones.

EmotivTractUI.h
    Éste es el archivo de encabezado principal para la aplicación.  Incluye otros encabezados
    específicos del proyecto y declara la clase de aplicación
    CEmotivTractUIApp.

EmotivTractUI.cpp
    Éste es el archivo fuente principal de la aplicación contenido en la clase de 
    la aplicación CEmotivTractUIApp.

EmotivTractUI.rc
    Ésta es una lista de todos los recursos de Microsoft Windows que utiliza el 
    programa.  Incluye los iconos, mapas de bits y cursores almacenados en el 
    subdirectorio RES.  Este archivo puede editarse directamente en Microsoft
    Visual C++. Los recursos de su proyecto se encuentran en 3082.

res\EmotivTractUI.ico
    Éste es un archivo de icono, que se utiliza como el icono de la aplicación.     Éste
    icono está incluido en el archivo principal de recursos EmotivTractUI.rc.

res\EmotivTractUI.rc2
    Este archivo incluye recursos no editados por Microsoft 
    Visual C++. Debe colocar todos los recursos que no se pueden editar en 
    los editores de recursos de este archivo.


/////////////////////////////////////////////////////////////////////////////

El Asistente para aplicaciones crea una sola clase de cuadro de diálogo:

EmotivTractUIDlg.h, EmotivTractUIDlg.cpp – el cuadro de diálogo
    Estos archivos contienen su clase CEmotivTractUIDlg.  Esta clase define 
    el comportamiento del cuadro de diálogo principal de su aplicación.  La plantilla del cuadro de diálogo está en 
    EmotivTractUI.rc, que puede editarse en Microsoft Visual C++.


/////////////////////////////////////////////////////////////////////////////

Otras características:

Controles ActiveX
    La aplicación es compatible con el uso de los controles ActiveX.

/////////////////////////////////////////////////////////////////////////////

Otros archivos estándar:

StdAfx.h, StdAfx.cpp
    Estos archivos se utilizan para generar un archivo de encabezado precompilado (PCH) 
    denominado EmotivTractUI.pch y un archivo de tipos precompilado llamado StdAfx.obj.

Resource.h
    Éste es el archivo de encabezado estándar, que define nuevos identificadores de recurso.
    Microsoft Visual C++ lee y actualiza este archivo.

EmotivTractUI.manifest
	Windows XP utiliza los archivos de manifiesto de la aplicación para describir la dependencia de una aplicación en versiones específicas de ensamblados simultáneos. El cargador utiliza esta información para cargar el ensamblado adecuado desde la caché de ensamblados o desde el directorio privado de la aplicación. El manifiesto de la aplicación puede incluirse para su redistribución como un archivo .manifest instalado en la misma carpeta que el ejecutable de la aplicación o puede incluirse en el ejecutable en forma de recurso. 
/////////////////////////////////////////////////////////////////////////////

Otras notas:

El Asistente para aplicaciones utiliza "TODO:" para indicar partes del código fuente que debería agregar o personalizar.

Si su aplicación utiliza MFC en un archivo DLL compartido, tendrá que copiar
los archivos DLL MFC. Si el idioma de su aplicación es distinto al idioma actual
del sistema operativo, también tendrá que copiar los recursos localizados correspondientes
MFC90XXX.DLL. Para obtener mas información sobre ambos temas, consulte la sección que trata
sobre al copia de aplicaciones de Visual C++ en la documentación de MSDN.

/////////////////////////////////////////////////////////////////////////////
