#include "stdafx.h"
#include "XavierEditor.h"
#include "WizardDialog.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDialog::IDD, pParent)
{

}

CWizardDialog::~CWizardDialog()
{
}

void CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CWizardDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CWizardDialog::OnBnClickedOk()
{
	EditorPluginFactory* pSceneFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_SCENEMANAGER);
	if (pSceneFactory)
	{
		SEditorPluginSceneManagerAdp adp;
		adp.pluginName			= EDITOR_SCENEPLUGIN_NAME;
		adp.typeMask			= ST_EXTERIOR_FAR;
		adp.fogMode				= FOG_LINEAR;
		adp.clrFog				= ColourValue(1.0f, 1.0f, 0.8f);
		adp.expDensity			= 0.001;
		adp.linearStart			= 15;
		adp.linearEnd			= 500;
		adp.clrAmbientLight		= ColourValue::White;

		pSceneFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->getRootPlugin());
	}

	EditorPluginFactory* pViewportFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_VIEWPORT);
	if (pViewportFactory)
	{
		SEditorPluginViewportAdp adp;
		adp.pluginName					= EDITOR_VIEWPORT;
		adp.background					= ColourValue::Black;
		
		adp.cameraAdp.pluginName		= EDITOR_VIEWPORT_CAMER;
		adp.cameraAdp.vPos				= Vector3(0, 5, 5);
		adp.cameraAdp.q					= Quaternion::IDENTITY;
		adp.cameraAdp.fFarClipDistance	= 50000.0f;
		adp.cameraAdp.fNearClipDistance	= 0.1f;
		adp.cameraAdp.nQueryFlags		= 0;
		adp.cameraAdp.fFov				= 1.0f;

		pViewportFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->getRootPlugin());
	}

	EditorPluginFactory* pTerrainFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_TERRAIN);
	if (pTerrainFactory)
	{
		SEditorPluginTerrainAdp adp;
		adp.pluginName					= EDITOR_TERRAIN;
		adp.fWorldSize					= 1024;
		adp.nTerrainSize				= 129;
		adp.nLightMapSize				= 1024;
		adp.nLayerBlendMapSize			= 1024;
		adp.nCompositeMapSize			= 1024;
		adp.clrCompositeMapDiffuse		= ColourValue::White;
		adp.fSkirtSize					= 4;
		adp.fCompositeMapDistance		= 2000;
		adp.fMaxPixelError				= 3;

		pTerrainFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME));
	}

	EditorPluginFactory* pPageFactory	= EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_TERRAINPAGE);
	if (pPageFactory)
	{
		SEditorPluginTerrainPageAdp adp;
		adp.nLayerCount					= 1;
		adp.tpl.fLayerWorldSize[0]		= 20.0f;
		adp.tpl.layerDiffuseTexture[0]	= "dirt_grayrocky_diffusespecular.dds";
		adp.tpl.layerNormalTexture[0]	= "dirt_grayrocky_normalheight.dds";
		adp.nMinBatchSize				= 33;
		adp.nMaxBatchSize				= 65;
		adp.nPageX						= 0;
		adp.nPageY						= 0;
		adp.vPos						= Vector3::ZERO;
		adp.bAtOnceLoad					= true;

		char szPluginName[MAX_PATH];
		sprintf_s(szPluginName, "%dx%d", adp.nPageX, adp.nPageY);
		adp.pluginName					= szPluginName;

		pPageFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN));
	}

	EditorPluginFactory* pUnitFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_UNIT);
	if (pUnitFactory)
	{
		SEditorUnitAdp adp;
		adp.szFileName	= "tudorhouse.mesh";
		adp.vPos		= Vector3(0, 2, 0);
		adp.vScale		= Vector3(0.1, 0.1, 0.1);
		adp.fDegree		= 0;

		pUnitFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME));
	}
	
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		// 通知文件窗口
		::SendMessage(pMainFrame->GetActiveView()->m_hWnd,
			WM_WIZARD_FNISHED, NULL, NULL);
	}

	OnOK();
}
