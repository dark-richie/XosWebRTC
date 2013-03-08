///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: XosWinWebRtcClientPeerWindowMain.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPEERWINDOWMAIN_HPP
#define _XOSWINWEBRTCCLIENTPEERWINDOWMAIN_HPP

#include "XosWinWebRtcClientMainWindowPeer.hpp"
#include "XosWinWebRtcClientBaseWindow.hpp"
#include "XosWinWebRtcClientDialogWindow.hpp"
#include "XosWinDialogWindow.hpp"
#include "XosWinHMENUAttached.hpp"
#include "XosWinMENUITEMINFO.hpp"
#include "XosWinMain.hpp"
#include "resource.h"

#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_SERVER_NAME "localhost"
#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_SERVER_PORT 8888

#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES false
#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES false

#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE

#define XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE \
    XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPeerWindowMainImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinMainImplement
XosWinWebRtcClientPeerWindowMainImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPeerWindowMainExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinMain
XosWinWebRtcClientPeerWindowMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPeerWindowMain
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS XosWinWebRtcClientPeerWindowMain
: virtual public XosWinWebRtcClientPeerWindowMainImplement,
  public XosWinWebRtcClientPeerWindowMainExtend
{
public:
    typedef XosWinWebRtcClientPeerWindowMainImplement cImplements;
    typedef XosWinWebRtcClientPeerWindowMainExtend cExtends;

    XosWebRtcClientVideoCodecMode m_webrtcVideoVideoCodecMode;
    std::string m_webrtcClientTraceFileName;
    std::string m_webrtcClientTraceFileDir;
    std::string m_webrtcClientTraceFileEnv;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPeerWindowMain
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPeerWindowMain()
    : m_webrtcVideoVideoCodecMode
      (XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE),

      m_webrtcClientTraceFileName
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcClientTraceFileDir
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcClientTraceFileEnv
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPeerWindowMain
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPeerWindowMain()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWinMain
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int OnWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance,
     LPSTR cmdLine, int cmdShow)
    {
        int result = 0;
        XosError error;
        XosWinDialogWindowClass dlgClass;

        if (!(error = dlgClass.Register(hInstance)))
        {
            if (!(error = XosWinWebRtcClientMainWindowPeer::
                RegisterWindowClass
                (hInstance, NULL, NULL, LoadIcon
                 (hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON)))))
            {
                XosWinWebRtcClientBaseWindow uiWindow
                (XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_SERVER_NAME,
                 XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_SERVER_PORT,
                 true, true);
                XosWinWebRtcClientMainWindowPeer window(uiWindow);

                std::string webrtcClientTraceFileName
                (uiWindow.GenerateWebRtcClientTraceFileName
                 (m_webrtcClientTraceFileEnv, 
                  m_webrtcClientTraceFileDir, 
                  m_webrtcClientTraceFileName));

                XosWebRtcClientTraceLevel webrtcClientTraceLevels
                = XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS;

                if (!(error = window.Create(hInstance)))
                {
                    XosWebRtcClientVideoCodec webrtcVideoVideoCodec(m_webrtcVideoVideoCodecMode);
                    XosWebRtcClientTrace webrtcClientTrace
                    (webrtcClientTraceFileName, webrtcClientTraceLevels);
                    XosWebRtcClientConnection client;
                    XosWebRtcClientConductor conductor
                    (webrtcVideoVideoCodec, webrtcClientTrace, 
                     &client, &uiWindow, 
                     XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
                     XOSWINWEBRTCCLIENTPEERWINDOWMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);

                    XosWinMENUITEMINFO item("Properties", IDM_MENU_PROPS);
                    XosWinMENUITEMINFO item1("Connect Server", IDM_MENU_CONNECT);
                    XosWinMENUITEMINFO item2("Disconnect Server", IDM_MENU_DISCONNECT);
                    XosWinMENUITEMINFO item3("Connect Peer", IDM_MENU_CONNECT_PEER);
                    XosWinMENUITEMINFO item4("Disconnect Peer", IDM_MENU_DISCONNECT_PEER);
                    XosWinMENUITEMINFO item5("OpenGL OFF", IDM_MENU_GL_OFF);
                    XosWinMENUITEMINFO item6("OpenGL ON", IDM_MENU_GL_ON);
                    XosWinHMENUCreatedAttached menu;

                    XosWinWebRtcClientDialogWindow dialog(window, uiWindow);

                    if (!(error = menu.Create()))
                    {
                        if (!(error = menu.InsertItemsL
                            (0, TRUE, &item, &item1, &item2, 
                             &item3, &item4, &item5, &item6, 0)))
                        {
                            HWND hWnd = window.Attached();
                            HMENU hMenu = menu.Attached();

                            if ((SetMenu(hWnd, hMenu)))
                                menu.Detach();

                            if (!(error = dialog.Create(hInstance, hWnd, IDD_MAIN_DIALOG)))
                            {
                                if (!(error))
                                {
                                    MSG msg;
                                    while((GetMessage(&msg, 0, 0, 0)))
                                    if (!(window.PreTranslateMessage(&msg)))
                                    {
                                        TranslateMessage(&msg);
                                        DispatchMessage(&msg);
                                    }
                                }
                                dialog.Destroy();
                            }
                        }
                        menu.Destroy();
                    }
                    window.Destroy();
                }
                XosWinWebRtcClientMainWindowPeer::
                UnregisterWindowClass(hInstance);
            }
            dlgClass.Unregister();
        }
        return result;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPEERWINDOWMAIN_HPP 
        

