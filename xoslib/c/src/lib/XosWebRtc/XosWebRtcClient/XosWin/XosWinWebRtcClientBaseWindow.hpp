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
///   File: XosWinWebRtcClientBaseWindow.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTBASEWINDOW_HPP
#define _XOSWINWEBRTCCLIENTBASEWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWinWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosWinWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosWinWebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientBaseWindowImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowImplement
XosWinWebRtcClientBaseWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientBaseWindowExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindow
XosWinWebRtcClientBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientBaseWindow
: virtual public XosWinWebRtcClientBaseWindowImplement,
  public XosWinWebRtcClientBaseWindowExtend
{
public:
    typedef XosWinWebRtcClientBaseWindowImplement Implements;
    typedef XosWinWebRtcClientBaseWindowExtend Extends;

    XosWinWebRtcClientOpenGLVideoRenderer m_glRenderer;
    XosWebRtcClientBaseWindowUIMessageThread m_msgThread;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientBaseWindow
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientBaseWindow()
    {
    }

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

    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XosWebRtcClientVideoRenderer* renderer = 0;
        HWND hWnd = NULL;
        if ((hWnd = Attached()))
            renderer = new XosWebRtcClientVideoRendererImplemented
            (hWnd, width, height, isRemote);
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

    virtual void OnSize()
    {
        Extends::OnSize();
        InvalidateWindow();
    }
    virtual bool OnPaintBlank();
    virtual bool OnRenderImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height, 
     bool is_local = false);

    virtual void DrawWhiteText
    (HDC dc, RECT& rect, const char* text, int flags);

    virtual HFONT GetDefaultFont();

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

    virtual void QueueUIThreadCallback
    (int msg_id, void* data)
    {
        bool usePostUIThreadMessage = true;
        DWORD tid;

        if ((ui_thread_id_))

        if ((usePostUIThreadMessage))
            PostUIThreadMessage
            (ui_thread_id_, UI_THREAD_CALLBACK, (msg_id), (data));
        else
        if ((tid = ui_thread_id_->GetCurrentThreadId()))
            PostThreadMessage
            (tid, UIMessageThread::UI_MESSAGE_THREAD_UI_CALLBACK, 
             (WPARAM)(msg_id), (LPARAM)(data));
    }
    virtual void PostUIThreadMessage
    (UIMessageThreadId tid, int msg_id, int id, void* data)
    {
        if ((tid))
            tid->PostUIThreadMessage(msg_id, id, data);
            //tid->PostThreadMessage
            //(UIMessageThread::UI_MESSAGE_THREAD_UI_MESSAGE, 
            // MAKEWPARAM(msg_id, id), (LPARAM)(data));
    }
    virtual bool InitUIMessageThread()
    {
        bool isSuccess = true;
        m_msgThread.SetCurrentThreadId(GetCurrentThreadId());
        return isSuccess;
    }
    virtual bool FinishUIMessageThread()
    {
        bool isSuccess = true;
        m_msgThread.SetCurrentThreadId(0);
        return isSuccess;
    }
    virtual bool CreateUIMessageThread()
    {
        bool isSuccess = false;
        HWND hWnd;
        if ((hWnd = Attached()))
            isSuccess = m_msgThread.CreateMessageThread(hWnd);
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

    virtual LRESULT OnWindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        XosWebRtcClientBaseWindowPeerImplement* attachedWindowPeer = 0;
        LRESULT lResult = 0;
        if ((attachedWindowPeer = AttachedWindowPeer()))
            lResult = attachedWindowPeer->OnWindowMessage(hWnd, msg, wParam, lParam);
        return lResult;
    }
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

#endif // _XOSWINWEBRTCCLIENTBASEWINDOW_HPP 
        

