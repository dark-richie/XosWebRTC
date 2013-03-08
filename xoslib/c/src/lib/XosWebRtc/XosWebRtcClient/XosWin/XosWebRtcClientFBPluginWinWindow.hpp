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
///   File: XosWebRtcClientFBPluginWinWindow.hpp
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP
#define _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP

#include "XosWebRtcClientFBPluginWindow.hpp"
#include "XosWinWebRtcClientBaseWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowImplement
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginWindowImplement
XosWebRtcClientFBPluginWinWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowExtend
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginWindowT
<XosWinWebRtcClientBaseWindow>
XosWebRtcClientFBPluginWinWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWinWindow
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginWinWindow
: virtual public XosWebRtcClientFBPluginWinWindowImplement,
  public XosWebRtcClientFBPluginWinWindowExtend
{
public:
    typedef XosWebRtcClientFBPluginWinWindowImplement Implements;
    typedef XosWebRtcClientFBPluginWinWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginWinWindow
    ///
    ///       Author: $author$
    ///         Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginWinWindow
    (XosWebRtcClientFBPluginInterface& plugin,
     const char* serverName=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(plugin, serverName, serverPort, showConnectionState, handleButtonEvents)
    {
        m_postButtonEventUIMessages = true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginWinWindow
    ///
    ///      Author: $author$
    ///        Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginWinWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowAttached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(HWND hWnd)
    {
        std::string webrtcClientTraceFileName
        (GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));
        HWND attached = 0;
        if ((attached = Attached()))
            OnWindowDetached(attached);
        m_clientPair = new ClientPair
        (*this, webrtcClientTraceFileName);
        hWnd = Attach(hWnd);
        CreateUIMessageThread();
        OnOpen();
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowDetached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowDetached(HWND hWnd)
    {
        HWND attached = 0;
        if ((attached = Attached()) 
            && (hWnd == attached))
        {
            OnClose();
            DestroyUIMessageThread();
            hWnd = Detach();
            if ((m_clientPair))
            {
                delete m_clientPair;
                m_clientPair = 0;
            }
        }
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP 
