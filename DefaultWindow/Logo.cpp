#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include"PngMrg.h"
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	//PngMrg::Get_Instance()->Insert_Png
	

}

void CLogo::Update()
{
	if ( CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

}

void CLogo::Late_Update()
{
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{

}

void CLogo::DrawXmlFile(HDC hdc, const WCHAR* xmlFilePath)
{
}
//    // Load XML document
//    CoInitialize(NULL);
//    IXMLDOMDocument* pDoc = NULL;
//    HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDoc));
//    if (SUCCEEDED(hr)) {
//        VARIANT_BOOL vbSuccess = VARIANT_FALSE;
//        hr = pDoc->load(CComVariant(xmlFilePath), &vbSuccess);
//        if (SUCCEEDED(hr) && vbSuccess == VARIANT_TRUE) {
//            // Initialize GDI+
//            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
//            ULONG_PTR gdiplusToken;
//            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//
//            // Create bitmap and graphics objects
//            Gdiplus::Bitmap bitmap(800, 600, PixelFormat32bppARGB);
//            Gdiplus::Graphics graphics(&bitmap);
//
//            // Draw XML content
//            IXMLDOMNode* pNode = NULL;
//            pDoc->get_firstChild(&pNode);
//            while (pNode != NULL) {
//                BSTR bstrNodeName = NULL;
//                pNode->get_nodeName(&bstrNodeName);
//                if (wcscmp(bstrNodeName, L"rectangle") == 0) {
//                    BSTR bstrX = NULL, bstrY = NULL, bstrWidth = NULL, bstrHeight = NULL;
//                    pNode->get_attributes()->getNamedItem(L"x")->get_text(&bstrX);
//                    pNode->get_attributes()->getNamedItem(L"y")->get_text(&bstrY);
//                    pNode->get_attributes()->getNamedItem(L"width")->get_text(&bstrWidth);
//                    pNode->get_attributes()->getNamedItem(L"height")->get_text(&bstrHeight);
//                    graphics.DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0, 255), 2),
//                        _wtoi(bstrX), _wtoi(bstrY), _wtoi(bstrWidth), _wtoi(bstrHeight));
//                    SysFreeString(bstrX);
//                    SysFreeString(bstrY);
//                    SysFreeString(bstrWidth);
//                    SysFreeString(bstrHeight);
//                }
//                SysFreeString(bstrNodeName);
//                pNode->get_nextSibling(&pNode);
//            }
//
//            // Clean up
//            Gdiplus::GdiplusShutdown(gdiplusToken);
//            graphics.ReleaseHDC(hdc);
//            delete pDoc;
//        }
//    }
//    CoUninitialize();
//}
