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
///   File: XosWinWebRtcClientDialogWindow.hpp
///
/// Author: $author$
///   Date: 5/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTDIALOGWINDOW_HPP
#define _XOSWINWEBRTCCLIENTDIALOGWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWinDialogWindow.hpp"
#include "resource.h"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientDialogWindowImplement
///
///  Author: $author$
///    Date: 5/11/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWindow::OnWindowMessageDefaultObserver
XosWinWebRtcClientDialogWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientDialogWindowExtend
///
///  Author: $author$
///    Date: 5/11/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinDialogWindow
XosWinWebRtcClientDialogWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientDialogWindow
///
/// Author: $author$
///   Date: 5/11/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientDialogWindow
: virtual public XosWinWebRtcClientDialogWindowImplement,
  public XosWinWebRtcClientDialogWindowExtend
{
public:
    typedef XosWinWebRtcClientDialogWindowImplement Implements;
    typedef XosWinWebRtcClientDialogWindowExtend Extends;

    XosWinWindow& m_window;
    XosWebRtcClientBaseWindow& m_client;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientDialogWindow
    ///
    ///       Author: $author$
    ///         Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientDialogWindow
    (XosWinWindow& window,
     XosWebRtcClientBaseWindow& client)
    : m_window(window),
      m_client(client)
    {
        m_window.RegisterOnWindowMessageDefaultObserver(this);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientDialogWindow
    ///
    ///      Author: $author$
    ///        Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientDialogWindow()
    {
        m_window.UnregisterOnWindowMessageDefaultObserver();
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: On_WM_INITDIALOG_WindowMessage
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_INITDIALOG_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam) 
    {
        LRESULT lResult = FALSE;
        GetParams();
        return lResult;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: On_WM_CLOSE_WindowMessage
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_CLOSE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam) 
    {
        LRESULT lResult = FALSE;
        ShowWindow(Attached(), SW_HIDE);
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: On_WM_COMMAND_IDC_TRUE_WindowMessage
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_COMMAND_IDC_TRUE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam) 
    {
        LRESULT lResult = FALSE;
        SetParams();
        GetParams();
        return lResult;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: On_WM_COMMAND_IDC_FALSE_WindowMessage
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_COMMAND_IDC_FALSE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam) 
    {
        LRESULT lResult = FALSE;
        GetParams();
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: On_WM_COMMAND_WindowMessage
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_COMMAND_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam) 
    {
        LRESULT lResult = FALSE;
        lResult = Extends::On_WM_COMMAND_WindowMessage
        (hWnd, msg, wParam, lParam);
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    /// Function: OnWindowMessageDefaultObserve
    ///
    ///   Author: $author$
    ///     Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT OnWindowMessageDefaultObserve
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        switch(msg)
        {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
            case IDM_MENU_PROPS:
                ShowWindow(Attached(), SW_SHOWNORMAL);
                break;

            case IDM_MENU_CONNECT:
                m_client.ConnectToServer();
                break;

            case IDM_MENU_DISCONNECT:
                m_client.DisconnectFromServer();
                break;

            case IDM_MENU_CONNECT_PEER:
                m_client.ConnectToPeer();
                break;

            case IDM_MENU_DISCONNECT_PEER:
                m_client.DisconnectFromPeer();
                break;

            case IDM_MENU_GL_OFF:
                m_client.DontUseOpenGLRenderer();
                break;

            case IDM_MENU_GL_ON:
                m_client.UseOpenGLRenderer();
                break;
            }
            break;
        }
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetParams
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void GetParams()
    {
        int codecWidth=0, codecHeight=0, frameRate=0, minBitrate=0;

        m_client.GetVideoCodecOptions(codecWidth, codecHeight, frameRate, minBitrate);

        SetItemText(IDC_EDIT_USER, m_client.GetThisPeerName());
        SetItemText(IDC_EDIT_SERVER, m_client.GetServerName());
        SetItemText(IDC_EDIT_PORT, m_client.GetServerPort());

        SetItemText(IDC_EDIT_MODE, m_client.GetVideoCodecModeName());
        SetItemText(IDC_EDIT_WIDTH, codecWidth);
        SetItemText(IDC_EDIT_HEIGHT, codecHeight);
        SetItemText(IDC_EDIT_FRAME, frameRate);
        SetItemText(IDC_EDIT_BIT, minBitrate);
        SetItemText(IDC_EDIT_DEV, m_client.GetVideoCaptureDevice());

        SetIsButtonChecked(IDC_CHECK_AUTO, m_client.GetAutoConnectToPeerOn());
        SetIsButtonChecked(IDC_CHECK_AUTO2, m_client.GetAutoConnectToPeerAfterOn());
        SetIsButtonChecked(IDC_CHECK_GL, m_client.GetUseOpenGLRendererOn());

        SetIsButtonChecked(IDC_CHECK_ALT, m_client.GetUseAlternateServerAddresses());
        SetIsButtonChecked(IDC_CHECK_NUM, m_client.GetUseNumericServerAddresses());
        SetIsButtonChecked(IDC_CHECK_RELAY, m_client.GetUseRelayServer());
        SetItemText(IDC_EDIT_STUN_HOST, m_client.GetPortServerHost());
        SetItemText(IDC_EDIT_STUN_PORT, m_client.GetStunServerPort());
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: SetParams
    ///
    ///    Author: $author$
    ///      Date: 5/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void SetParams()
    {
        int codecWidth=0, codecHeight=0, frameRate=0, minBitrate=0;
        std::string codecModeName;

        m_client.GetVideoCodecOptions(codecWidth, codecHeight, frameRate, minBitrate);

        m_client.SetThisPeerName(GetItemTextA(IDC_EDIT_USER));
        m_client.SetServerName(GetItemTextA(IDC_EDIT_SERVER));
        m_client.SetServerPort(GetItemInt(IDC_EDIT_PORT));

        codecModeName = GetItemTextA(IDC_EDIT_MODE);
        if (0 < (codecModeName.length()))
        {
            m_client.SetVideoCodecModeName(codecModeName);
            m_client.GetVideoCodecOptions
            (codecWidth, codecHeight, frameRate, minBitrate);
        }
        else
        {
            codecWidth = GetItemInt(IDC_EDIT_WIDTH);
            codecHeight = GetItemInt(IDC_EDIT_HEIGHT);
        }
        frameRate = GetItemInt(IDC_EDIT_FRAME);
        minBitrate = GetItemInt(IDC_EDIT_BIT);

        m_client.SetVideoCodecOptions
        (codecWidth, codecHeight, frameRate, minBitrate);

        m_client.SetVideoCaptureDevice(GetItemTextA(IDC_EDIT_DEV));

        m_client.SetAutoConnectToPeerOn(GetIsButtonChecked(IDC_CHECK_AUTO));
        m_client.SetAutoConnectToPeerAfterOn(GetIsButtonChecked(IDC_CHECK_AUTO2));
        m_client.SetUseOpenGLRendererOn(GetIsButtonChecked(IDC_CHECK_GL));

        m_client.SetUseAlternateServerAddresses(GetIsButtonChecked(IDC_CHECK_ALT));
        m_client.SetUseNumericServerAddresses(GetIsButtonChecked(IDC_CHECK_NUM));
        m_client.SetUseRelayServer(GetIsButtonChecked(IDC_CHECK_RELAY));
        m_client.SetPortServerHost(GetItemTextA(IDC_EDIT_STUN_HOST));
        m_client.SetStunServerPort(GetItemInt(IDC_EDIT_STUN_PORT));
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTDIALOGWINDOW_HPP 
