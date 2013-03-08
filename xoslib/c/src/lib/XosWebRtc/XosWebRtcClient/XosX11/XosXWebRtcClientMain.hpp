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
///   File: XosXWebRtcClientMain.hpp
///
/// Author: $author$
///   Date: 6/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTMAIN_HPP
#define _XOSXWEBRTCCLIENTMAIN_HPP

#include "XosWebRtcClientXMainLibJingleSocketServer.hpp"
#include "XosXMainLibJingleSocketServer.hpp"
#include "XosXLibJingleMain.hpp"
#include "XosXWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosXWebRtcClientBasePeerWindowImplement.hpp"
#include "XosXWebRtcClientWindowPeerImplement.hpp"
#include <signal.h>

#define XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_NAME "localhost"
#define XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_PORT 8888

#define XOSWEBRTCCLIENTMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES false
#define XOSWEBRTCCLIENTMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES true

#define XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE

#define XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE \
    XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientWindowPeerImplement
XosXWebRtcClientMainWindow;

typedef XosWebRtcClientBasePeerWindowImplement
XosXWebRtcClientPeerWindow;

typedef XosWebRtcClientBaseWindowPeerImplement
XosXWebRtcClientWindowPeer;

typedef XosWebRtcClientXMainLibJingleSocketServer
XosXWebRtcClientSocketServer;

typedef XosXLibJingleMainImplement
XosXWebRtcClientMainImplement;

typedef XosXLibJingleMain
XosXWebRtcClientMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXWebRtcClientMain
///
/// Author: $author$
///   Date: 6/11/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXWebRtcClientMain
: virtual public XosXWebRtcClientMainImplement,
  public XosXWebRtcClientMainExtend
{
public:
    typedef XosXWebRtcClientMainImplement Implements;
    typedef XosXWebRtcClientMainExtend Extends;

    XosXWebRtcClientMainWindow m_mainWindow;

    std::string m_serverName;
    int m_serverPort;

    XosWebRtcClientVideoCodecMode m_webrtcVideoVideoCodecMode;
    std::string m_webrtcClientTraceFileName;
    std::string m_webrtcClientTraceFileDir;
    std::string m_webrtcClientTraceFileEnv;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosXWebRtcClientMain
    ///
    ///       Author: $author$
    ///         Date: 6/11/2012
    ///////////////////////////////////////////////////////////////////////
    XosXWebRtcClientMain()
    : m_mainWindow(*this),
      
      m_serverName(XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_PORT),
    
      m_webrtcVideoVideoCodecMode
      (XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE),

      m_webrtcClientTraceFileName
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcClientTraceFileDir
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcClientTraceFileEnv
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV)
    {}
    virtual ~XosXWebRtcClientMain(){}

    ///////////////////////////////////////////////////////////////////////
    // Create/Destroy MainWindow
    ///////////////////////////////////////////////////////////////////////
    virtual XosXWindowInterface* CreateMainWindow
    (Display& xDisplay, Window xWindow, 
     int argc, char** argv, char** env)
    {
        XosXWindowInterface* mainWindow = 0;
        XosError error;
        XOS_DBI(("() ...\n"));
        if (!(error = m_mainWindow.CreateSimple
            (xDisplay, xWindow, 
             m_mainWindowX,m_mainWindowY, m_mainWindowWidth,m_mainWindowHeight, 
             m_mainWindowBorderWidth, m_mainWindowBorderColor, m_mainWindowBackgroundColor))) 
        {
            mainWindow = &m_mainWindow;
            m_mainWindow.OnWindowOpen();
        }
        return mainWindow;
    }
    virtual int DestroyMainWindow
    (XosXWindowInterface* mainWindow,
     int argc, char** argv, char** env)
    {
        int err = 1;
        XosError error;
        XOS_DBI(("() ...\n"));
        if ((mainWindow == &m_mainWindow))
        {
            m_mainWindow.OnWindowClose();
            if (!(error = m_defaultMainWindow.Destroy()))
                err = 0;
        }
        return err;
    }
    virtual Pixel GetMainWindowBackgroundColor() const {
        XOS_DBI(("() ...\n"));
        return WhiteColor();
    }

    ///////////////////////////////////////////////////////////////////////
    // XEvents
    ///////////////////////////////////////////////////////////////////////
    virtual XosError On_WM_DELETE_WINDOW_ClientMessageXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        SignalQuit(0);
        error = Extends::On_WM_DELETE_WINDOW_ClientMessageXEvent(xEvent);
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    // Process XEvents
    ///////////////////////////////////////////////////////////////////////
    virtual int ProcessXEvents
    (int argc, char** argv, char** env)
    {
        int sigNum = SIGINT;
        void (*sigHandler)(int) = signal(sigNum, SignalQuit);
        int err = 0;

        XosXWebRtcClientPeerWindow peerWindow
        (m_serverName.c_str(), m_serverPort, true, true);

        XosXWebRtcClientWindowPeer windowPeer(peerWindow);

        XosXWebRtcClientSocketServer socketServer(peerWindow, *this);

        std::string webrtcClientTraceFileName
        (peerWindow.GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));

        XosWebRtcClientTraceLevel webrtcClientTraceLevels
        = XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS;

        //if ((windowPeer.Open()))
        if ((m_mainWindow.Open(&peerWindow, &windowPeer)))
        {
            XosWebRtcClientVideoCodec webrtcVideoVideoCodec(m_webrtcVideoVideoCodecMode);

            XosWebRtcClientTrace webrtcClientTrace
            (webrtcClientTraceFileName, webrtcClientTraceLevels);

            XosWebRtcClientConnection client;

            XosWebRtcClientConductor conductor
            (webrtcVideoVideoCodec, webrtcClientTrace, 
             &client, &peerWindow, 
             XOSWEBRTCCLIENTMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
             XOSWEBRTCCLIENTMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);

            //peerWindow.ConnectToServer();
            socketServer.Run();
            //windowPeer.Close();
            m_mainWindow.Close(&peerWindow, &windowPeer);
        }
        signal(sigNum, sigHandler);
        return err;
    }
    static void SignalQuit(int signum)
    {
        XosXWebRtcClientSocketServer::SignalQuit();
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTMAIN_HPP 
