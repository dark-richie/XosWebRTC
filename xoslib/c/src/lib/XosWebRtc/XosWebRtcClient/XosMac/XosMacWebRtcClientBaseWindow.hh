///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
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
///   File: XosMacWebRtcClientBaseWindow.hh
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTBASEWINDOW_HH
#define _XOSMACWEBRTCCLIENTBASEWINDOW_HH

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosMacWebRtcClientBaseWindowUIMessageThread.hh"
#include "XosMacWebRtcClientVideoRenderer.hh"
#include "XosDebug.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientBaseWindowImplement
XosMacWebRtcClientBaseWindowImplement;

typedef XosWebRtcClientBaseWindow
XosMacWebRtcClientBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosMacWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacWebRtcClientBaseWindow
: virtual public XosMacWebRtcClientBaseWindowImplement,
  public XosMacWebRtcClientBaseWindowExtend
{
public:
    typedef XosMacWebRtcClientBaseWindowImplement Implements;
    typedef XosMacWebRtcClientBaseWindowExtend Extends;

    XosWebRtcClientBaseWindowUIMessageThread m_msgThread;
    XosMacWebRtcClientBaseWindowSocketServer* m_socketServer;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosMacWebRtcClientBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    XosMacWebRtcClientBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_socketServer(0)
    {
    }
    virtual ~XosMacWebRtcClientBaseWindow()
    {
    }

    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XOS_DBT(("() ...\n"));
        XosWebRtcClientVideoRenderer* renderer = 0;
        renderer = new XosMacWebRtcClientVideoRenderer
        (*this, width, height, isRemote);
        return renderer; 
    }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) 
    { 
        XOS_DBT(("() ...\n"));
        if ((renderer))
        {
            delete renderer;
            return true;
        }
        return false; 
    }

    virtual bool InitUIMessageThread()
    {
        XOS_DBT(("() ...\n"));
        bool isSuccess = InitUIMessageQueue();
        return isSuccess;
    }
    virtual bool FinishUIMessageThread()
    {
        XOS_DBT(("() ...\n"));
        bool isSuccess = FinishUIMessageQueue();
        return isSuccess;
    }

    virtual bool CreateUIMessageThread()
    {
        XOS_DBT(("() ...\n"));
        bool isSuccess = m_msgThread.CreateMessageThread(this);
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread()
    {
        XOS_DBT(("() ...\n"));
        bool isSuccess = m_msgThread.DestroyMessageThread();
        return isSuccess;
    }

    virtual UIMessageThreadId GetUIMessageThreadId()
    {
        return &m_msgThread;
    }
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSMACWEBRTCCLIENTBASEWINDOW_HH 
        

