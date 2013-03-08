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
///   File: XosX11WebRtcClientBaseWindow.hpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSX11WEBRTCCLIENTBASEWINDOW_HPP
#define _XOSX11WEBRTCCLIENTBASEWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosX11WebRtcClientBaseWindowUIMessageThread.hpp"
//#include "XosX11WebRtcClientBaseWindowPeerImplement.hpp"
#include "XosX11WebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientBaseWindowImplement
XosX11WebRtcClientBaseWindowImplement;

typedef XosWebRtcClientBaseWindow
XosX11WebRtcClientBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosX11WebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosX11WebRtcClientBaseWindow
: virtual public XosX11WebRtcClientBaseWindowImplement,
  public XosX11WebRtcClientBaseWindowExtend
{
public:
    typedef XosX11WebRtcClientBaseWindowImplement Implements;
    typedef XosX11WebRtcClientBaseWindowExtend Extends;

    XosWebRtcClientBaseWindowUIMessageThread m_msgThread;
    XosX11WebRtcClientBaseWindowSocketServer* m_socketServer;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosX11WebRtcClientBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    XosX11WebRtcClientBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_socketServer(0)
    {
    }
    virtual ~XosX11WebRtcClientBaseWindow()
    {
    }

    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XosWebRtcClientVideoRenderer* renderer = 0;
        renderer = new XosX11WebRtcClientVideoRenderer
        (*this, width, height, isRemote);
        return renderer; 
    }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) 
    { 
        if ((renderer))
        {
            delete renderer;
            return true;
        }
        return false; 
    }

    virtual bool InitUIMessageThread()
    {
        bool isSuccess = InitUIMessageQueue();
        return isSuccess;
    }
    virtual bool FinishUIMessageThread()
    {
        bool isSuccess = FinishUIMessageQueue();
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
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSX11WEBRTCCLIENTBASEWINDOW_HPP 
