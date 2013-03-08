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
///   File: XosWinWebRtcClientMainWindowPeer.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTMAINWINDOWPEER_HPP
#define _XOSWINWEBRTCCLIENTMAINWINDOWPEER_HPP

#include "XosWinWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosWinWebRtcClientLoginWindow.hpp"
#include "XosWinWebRtcClientCallWindow.hpp"
#include "XosWinWebRtcClientSettingsWindow.hpp"

#define XOSWINWEBRTCCLIENTMAINWINDOWPEER_CLASSNAME \
    L"XosWinWebRtcClientMainWindowPeer"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientMainWindowPeerImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowPeerImplementImplement
XosWinWebRtcClientMainWindowPeerImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientMainWindowPeerExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowPeerImplement
XosWinWebRtcClientMainWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientMainWindowPeer
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientMainWindowPeer
: virtual public XosWinWebRtcClientMainWindowPeerImplement,
  public XosWinWebRtcClientMainWindowPeerExtend
{
public:
    typedef XosWinWebRtcClientMainWindowPeerImplement Implements;
    typedef XosWinWebRtcClientMainWindowPeerExtend Extends;

protected:
    static XosWinWindowClass m_windowClass;

    XosWinWebRtcClientLoginWindow m_loginWindow;
    XosWinWebRtcClientCallWindow m_callWindow;
    XosWinWebRtcClientSettingsWindow m_settingsWindow;

public:
    XosWinWebRtcClientMainWindowPeer
    (UIWindow& uiWindow,
     HBRUSH hbrBackground=NULL,
     HWND attached=NULL,
     bool isCreated=false)
    : Extends(uiWindow, hbrBackground, attached, isCreated)
    {
    }
    virtual ~XosWinWebRtcClientMainWindowPeer()
    {
        XosError error;
        if ((error = Destroyed()))
            throw(error);
    }

    virtual XosError Create(HINSTANCE hInstance)
    {
        XosError error = XOS_ERROR_FAILED;

        LPCTSTR windowClassName;
        if ((windowClassName = m_windowClass.m_windowClassNameChars))
            error = Extends::Create(hInstance, windowClassName, windowClassName);
        return error;
    }

    static XosError RegisterWindowClass
    (HINSTANCE hInstance, HBRUSH hbrBackground = NULL, 
     HCURSOR hCursor = NULL, HICON hIcon = NULL)
    {
        XosError error = XOS_ERROR_FAILED;

        if (!(error = m_windowClass.Register
            (hInstance, NULL, NULL, NULL, hIcon, NULL, hCursor, hbrBackground)))
        {
            if (!(error = XosWinWebRtcClientLoginWindow::RegisterWindowClass(hInstance)))
            {
                if (!(error = XosWinWebRtcClientCallWindow::RegisterWindowClass(hInstance)))
                {
                    if (!(error = XosWinWebRtcClientSettingsWindow::RegisterWindowClass(hInstance)))
                    {
                        return error;
                    }
                    XosWinWebRtcClientCallWindow::UnregisterWindowClass();
                }
                XosWinWebRtcClientLoginWindow::UnregisterWindowClass();
            }
            m_windowClass.Unregister();
        }
        return error;
    }
    static XosError UnregisterWindowClass
    (HINSTANCE hInstance)
    {
        XosError error = XOS_ERROR_NONE;
        XosError error2;

        if ((error2 = XosWinWebRtcClientSettingsWindow::UnregisterWindowClass()))
        if (!error) error = error2;

        if ((error2 = XosWinWebRtcClientCallWindow::UnregisterWindowClass()))
        if (!error) error = error2;

        if ((error2 = XosWinWebRtcClientLoginWindow::UnregisterWindowClass()))
        if (!error) error = error2;

        if ((error2 = m_windowClass.Unregister()))
        if (!error) error = error2;
        return error;
    }

    virtual LRESULT On_WM_CREATE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = Extends::On_WM_CREATE_WindowMessage(hWnd,msg,wParam,lParam);
        CREATESTRUCT* cs;
        HINSTANCE hInstance;
        RECT rect;
        if ((cs = (CREATESTRUCT*)(lParam)))
        if ((hInstance = cs->hInstance))
        if ((GetClientRect(hWnd, &rect)))
        {
            m_loginWindow.Create
            (hInstance, hWnd, 1, rect.bottom,rect.top, rect.right,rect.bottom);

            m_callWindow.Create
            (hInstance, hWnd, 1, rect.bottom,rect.top, rect.right,rect.bottom);

            m_settingsWindow.Create
            (hInstance, hWnd, 1, rect.bottom,rect.top, rect.right,rect.bottom);
        }
        return lResult;
    }
    virtual LRESULT OnWindowMessageDefault
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;

        if ((m_onWindowMessageDefaultObserver))
            m_onWindowMessageDefaultObserver->OnWindowMessageDefaultObserve(hWnd, msg, wParam, lParam);

        lResult = Extends::OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTMAINWINDOWPEER_HPP 
        

