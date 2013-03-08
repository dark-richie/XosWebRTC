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
///   File: XosWinWebRtcClientBaseWindowPeerImplement.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTBASEWINDOWPEERIMPLEMENT_HPP
#define _XOSWINWEBRTCCLIENTBASEWINDOWPEERIMPLEMENT_HPP

#include "XosWinWebRtcClientBaseWindowUIMessageThread.hpp"
#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWinWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientBaseWindowPeerImplementImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWindowImplement
XosWebRtcClientBaseWindowPeerImplementImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientBaseWindowPeerImplementExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWindow
XosWebRtcClientBaseWindowPeerImplementExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowPeerImplement
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowPeerImplement
: virtual public XosWebRtcClientBaseWindowPeerImplementImplement,
  public XosWebRtcClientBaseWindowPeerImplementExtend
{
public:
    typedef XosWebRtcClientBaseWindowPeerImplementImplement Implements;
    typedef XosWebRtcClientBaseWindowPeerImplementExtend Extends;
    typedef XosWebRtcClientBaseWindow UIWindow;

    UIWindow& m_uiWindow;

    XosWebRtcClientBaseWindowPeerImplement
    (UIWindow& uiWindow,
     HBRUSH hbrBackground=NULL,
     HWND attached=NULL,
     bool isCreated=false)
    : Extends(attached, isCreated),
      m_uiWindow(uiWindow)
    {
        m_uiWindow.AttachWindowPeer(this);
    }
    virtual ~XosWebRtcClientBaseWindowPeerImplement()
    {
        m_uiWindow.DetachWindowPeer();
    }

    virtual void OnOpen()
    {
        m_uiWindow.InitUIMessageThread();
        m_uiWindow.OnOpen();
    }
    virtual void OnClose()
    {
        m_uiWindow.OnClose();
        m_uiWindow.FinishUIMessageThread();
    }

    virtual LRESULT On_WM_CREATE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        OnOpen();
        return lResult;
    }
    virtual LRESULT On_WM_CLOSE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        PostQuitMessage(0);
        OnClose();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_LBUTTONUP_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_uiWindow.OnLButtonUp();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_RBUTTONUP_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_uiWindow.OnRButtonUp();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_SIZE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_uiWindow.OnSize();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_PAINT_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = true;
        m_uiWindow.OnPaint();
        return lResult;
    }
    virtual LRESULT On_WM_ERASEBKGND_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = true;
        return lResult;
    }
    virtual LRESULT OnWindowMessageDefault
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        if ((msg == UIWindow::UIMessageThread::UI_MESSAGE_THREAD_UI_MESSAGE))
        {
            int msg_id = LOWORD(wParam);
            int id = HIWORD(wParam);
            void *data = (void*)(lParam);
            m_uiWindow.OnDefaultAction(msg_id, id, data);
        }
        lResult = OnDefWindowProc(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT OnDefWindowProc
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = DefWindowProc(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual bool PreTranslateMessage(MSG* msg)
    {
        if ((msg))
        if (!(msg->hwnd))
        switch ((msg->message))
        {
        case UIWindow::UIMessageThread::UI_MESSAGE_THREAD_UI_MESSAGE:
            m_uiWindow.OnDefaultAction
            (LOWORD(msg->wParam), HIWORD(msg->wParam), (void*)(msg->lParam));
            return true;

        case UIWindow::UIMessageThread::UI_MESSAGE_THREAD_UI_CALLBACK:
            m_uiWindow.OnDefaultAction
            (UIWindow::UI_THREAD_CALLBACK, (int)(msg->wParam), (void*)(msg->lParam));
            return true;
        }
        return false;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTBASEWINDOWPEERIMPLEMENT_HPP 
