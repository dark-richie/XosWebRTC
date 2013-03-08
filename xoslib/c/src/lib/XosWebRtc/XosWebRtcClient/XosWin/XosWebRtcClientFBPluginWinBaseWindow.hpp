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
///   File: XosWebRtcClientFBPluginWinBaseWindow.hpp
///
/// Author: $author$
///   Date: 4/14/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINWINBASEWINDOW_HPP
#define _XOSWEBRTCCLIENTFBPLUGINWINBASEWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWinWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosWinWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosWinWebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinBaseWindowImplement
///
///  Author: $author$
///    Date: 4/14/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowImplement
XosWebRtcClientFBPluginWinBaseWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinBaseWindowExtend
///
///  Author: $author$
///    Date: 4/14/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindow
XosWebRtcClientFBPluginWinBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWinBaseWindow
///
/// Author: $author$
///   Date: 4/14/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginWinBaseWindow
: virtual public XosWebRtcClientFBPluginWinBaseWindowImplement,
  public XosWebRtcClientFBPluginWinBaseWindowExtend
{
public:
    typedef XosWebRtcClientFBPluginWinBaseWindowImplement Implements;
    typedef XosWebRtcClientFBPluginWinBaseWindowExtend Extends;

    XosWinWebRtcClientOpenGLVideoRenderer m_glRenderer;
    XosWebRtcClientBaseWindowUIMessageThread m_msgThread;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginWinBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 4/14/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginWinBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents)
    {
        m_postButtonEventUIMessages = true;
        //m_useUIMessageQueue = true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginWinBaseWindow
    ///
    ///      Author: $author$
    ///        Date: 4/14/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginWinBaseWindow()
    {
    }

    //
    // uimessage thread
    //
    virtual bool CreateUIMessageThread()
    {
        bool isSuccess = false;

        if ((m_useUIMessageQueue))
        if (!(isSuccess = InitUIMessageThread()))
            return false;

        if (!(isSuccess = m_msgThread.Create(this)))
        if ((m_useUIMessageQueue))
            FinishUIMessageThread();
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread()
    {
        bool isSuccess = m_msgThread.Destroy();

        if ((m_useUIMessageQueue))
        if (!(FinishUIMessageThread()))
            isSuccess = false;

        return isSuccess;
    }
    virtual UIMessageThreadId GetUIMessageThreadId()
    {
        return &m_msgThread;
    }
    virtual void PostUIThreadMessage
    (UIMessageThreadId tid, int msg_id, int id, void* data)
    {
        if ((m_useUIMessageQueue))
            ui_message_queue_.PostUIMessage(msg_id, id, data);
        else
        if ((tid))
            tid->PostThreadMessage
            (UIMessageThread::UI_MESSAGE_THREAD_UI_MESSAGE, 
             MAKEWPARAM(msg_id, id), (LPARAM)(data));
    }

    //
    // opengl renderer
    //
    virtual XosWebRtcClientOpenGLVideoRenderer*
    AcquireOpenGLRenderer() 
    { 
        XosWebRtcClientOpenGLVideoRenderer* renderer = 0;
        HWND hWnd;
        if ((hWnd = Attached()))
        if ((renderer = (XosWebRtcClientOpenGLVideoRenderer*)(&m_glRenderer)))
            m_glRenderer.init(hWnd);
        return renderer; 
    }
    virtual bool ReleaseOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) 
    { 
        bool isTrue = false;
        if ((isTrue = ((XosWebRtcClientOpenGLVideoRenderer*)(&m_glRenderer) == renderer)))
            m_glRenderer.finish();
        return isTrue; 
    }
    virtual bool ReshapeOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) 
    { 
        HWND hWnd = NULL;
        RECT rc;
        if ((renderer))
        if ((hWnd = Attached()))
        if ((GetClientRect(hWnd, &rc)))
        {
            renderer->reshape(rc.right-rc.left, rc.bottom-rc.top);
            return true;
        }
        return false; 
    }

    //
    // drawing
    //
    virtual bool ValidateWindow() 
    { 
        HWND hWnd = NULL;
        if ((hWnd = Attached()))
        {
            ValidateRect(hWnd, NULL);
            return true;
        }
        return false; 
    }
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    {
        HWND hWnd = NULL;
        if ((hWnd = Attached()))
        {
            InvalidateRect(hWnd, NULL, eraseBackground);
            return true;
        }
        return false; 
    }

    //
    // window messages
    //
    virtual LRESULT OnWindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        XosWebRtcClientBaseWindowPeerImplement* attachedWindowPeer = 0;
        LRESULT lResult = 0;
        if ((attachedWindowPeer = AttachedWindowPeer()))
            lResult = attachedWindowPeer->OnWindowMessage(hWnd, msg, wParam, lParam);
        return lResult;
    }

    //
    // attached
    //
    virtual HWND Attach(HWND detached)
    {
        XosWebRtcClientBaseWindowPeerImplement* attachedWindowPeer = 0;
        HWND attached = NULL;
        if ((attachedWindowPeer = AttachedWindowPeer()))
            attached = attachedWindowPeer->Attach(detached);
        return attached;
    }
    virtual HWND Detach()
    {
        XosWebRtcClientBaseWindowPeerImplement* attachedWindowPeer = 0;
        HWND detached = NULL;
        if ((attachedWindowPeer = AttachedWindowPeer()))
            detached = attachedWindowPeer->Detach();
        return detached;
    }
    virtual HWND Attached() const
    {
        XosWebRtcClientBaseWindowPeerImplement* attachedWindowPeer = 0;
        HWND attached = NULL;
        if ((attachedWindowPeer = AttachedWindowPeer()))
            attached = attachedWindowPeer->Attached();
        return attached;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINWINBASEWINDOW_HPP 
        

