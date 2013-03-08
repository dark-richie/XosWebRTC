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
///   File: XosWebRtcClientConsoleBaseWindow.hpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEBASEWINDOW_HPP
#define _XOSWEBRTCCLIENTCONSOLEBASEWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWebRtcClientConnectorPair.hpp"
#include "XosWebRtcClientConsoleBaseWindowUIMessageThread.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientBaseWindowImplement XosWebRtcClientConsoleBaseWindowImplement;
typedef XosWebRtcClientBaseWindow XosWebRtcClientConsoleBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsoleBaseWindow
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsoleBaseWindow
: virtual public XosWebRtcClientConsoleBaseWindowImplement,
  public XosWebRtcClientConsoleBaseWindowExtend
{
public:
    typedef XosWebRtcClientConsoleBaseWindowImplement Implements;
    typedef XosWebRtcClientConsoleBaseWindowExtend Extends;

    std::string m_webrtcClientTraceFileName;
    std::string m_webrtcClientTraceFileDir;
    std::string m_webrtcClientTraceFileEnv;
    XosWebRtcClientTraceLevel m_webrtcClientTraceLevels;
    XosWebRtcClientVideoCodecMode m_webrtcVideoVideoCodecMode;

    XosWebRtcClientBaseWindowPeerImplement* m_windowPeer;
    XosWebRtcClientBaseWindowSocketServer* m_socketServer;
    XosWebRtcClientConnectorPair* m_clientPair;
    XosWebRtcClientConsoleBaseWindowUIMessageThread m_msgThread;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsoleBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsoleBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),

      m_webrtcClientTraceFileName
      (XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILENAME),

      m_webrtcClientTraceFileDir
      (XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILEDIR),

      m_webrtcClientTraceFileEnv
      (XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILEENV),

      m_webrtcClientTraceLevels
      (XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS),
    
      m_webrtcVideoVideoCodecMode
      (XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE),

      m_windowPeer(0),
      m_socketServer(0),
      m_clientPair(0)
    {
        m_useUIMessageQueue = true;
        m_useOpenGLRenderer = false;
        m_autoConnectToPeerOn = true;
        m_autoConnectToPeerAfterOn = true;
    }
    virtual ~XosWebRtcClientConsoleBaseWindow()
    {
    }

    virtual bool OnWindowOpened
    (XosWebRtcClientBaseWindowPeerImplement* windowPeer)
    {
        bool isSuccess = false;
        if ((isSuccess = InitUIMessageThread()))
        {
            m_windowPeer = windowPeer;
            OnOpen();
        }
        return isSuccess;
    }
    virtual bool OnWindowClosed
    (XosWebRtcClientBaseWindowPeerImplement* windowPeer)
    {
        bool isSuccess = false;
        OnClose();
        m_windowPeer = 0;
        isSuccess = FinishUIMessageThread();
        return isSuccess;
    }

    virtual bool OnWindowAttached
    (XosWebRtcClientBaseWindowPeerImplement* windowPeer)
    {
        bool isSuccess = false;

        std::string webrtcClientTraceFileName
        (GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));

        if ((isSuccess = CreateConnectionPair(webrtcClientTraceFileName)))
        {
            if ((isSuccess = InitUIMessageThread()))
            {
                m_windowPeer = windowPeer;
                OnOpen();
                if ((isSuccess = CreateUIMessageThread()))
                    return isSuccess;
                FinishUIMessageThread();
                OnClose();
                m_windowPeer = 0;
            }
            DestroyConnectionPair();
        }
        return isSuccess;
    }
    virtual bool OnWindowDetached
    (XosWebRtcClientBaseWindowPeerImplement* windowPeer)
    {
        bool isSuccess = DestroyUIMessageThread();
        OnClose();
        m_windowPeer = 0;
        if (!(FinishUIMessageThread()))
            isSuccess = false;
        if (!(DestroyConnectionPair()))
            isSuccess = false;
        return isSuccess;
    }

    virtual bool CreateConnectionPair
    (const std::string& webrtcClientTraceFileName)
    {
        bool isSuccess = true;
        if ((isSuccess = CreateSocketServer(*this)))
        {
            if ((isSuccess = (0 != (m_clientPair = new XosWebRtcClientConnectorPair
                (*this, webrtcClientTraceFileName, 
                 m_webrtcClientTraceLevels, m_webrtcVideoVideoCodecMode)))))
                return isSuccess;
            DestroySocketServer();
        }
        return isSuccess;
    }
    virtual bool DestroyConnectionPair()
    {
        bool isSuccess = false;
        if ((isSuccess = (0 != (m_clientPair))))
        {
            delete m_clientPair;
            m_clientPair = 0;
        }
        if (!(DestroySocketServer()))
            isSuccess = false;
        return isSuccess;
    }

    virtual bool CreateSocketServer
    (XosWebRtcClientBaseWindow& peerWindow)
    {
        bool isSuccess = true;
        if ((isSuccess = (0 != (m_socketServer = new XosWebRtcClientBaseWindowSocketServer(peerWindow)))))
            XosWebRtcClientConnection::SetSocketServer(m_socketServer);
        return isSuccess;
    }
    virtual bool DestroySocketServer()
    {
        bool isSuccess = true;
        if ((isSuccess = (0 != (m_socketServer))))
        {
            XosWebRtcClientConnection::SetSocketServer(0);
            delete m_socketServer;
            m_socketServer = 0;
        }
        return isSuccess;
    }

    virtual bool CreateUIMessageThread()
    {
        bool isSuccess = m_msgThread.CreateMessageThread(this, m_socketServer);
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread()
    {
        bool isSuccess = m_msgThread.DestroyMessageThread();
        return isSuccess;
    }
    virtual UIMessageThreadId GetUIMessageThreadId()
    {
        return &m_msgThread;
    }

    virtual void OnEvent(const std::string& eventName) 
    { XOS_DBT(("(%s)...\n", eventName.c_str())); }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEBASEWINDOW_HPP 
        

