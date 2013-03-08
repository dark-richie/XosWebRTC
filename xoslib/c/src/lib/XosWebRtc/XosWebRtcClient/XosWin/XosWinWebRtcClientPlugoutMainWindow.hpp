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
///   File: XosWinWebRtcClientPlugoutMainWindow.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGOUTMAINWINDOW_HPP
#define _XOSWINWEBRTCCLIENTPLUGOUTMAINWINDOW_HPP

#include "XosWinWindow.hpp"
#include "XosWinWindowClass.hpp"
#include "XosWinWebRtcClientPluginDLibrary.hpp"

#define XOSWINWEBRTCCLIENTPLUGOUTMAINWINDOW_CLASSNAME \
    L"XosWinWebRtcClientPlugoutMainWindow"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPlugoutMainWindowImplement
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWindowImplement
XosWinWebRtcClientPlugoutMainWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPlugoutMainWindowExtend
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWindow
XosWinWebRtcClientPlugoutMainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPlugoutMainWindow
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPlugoutMainWindow
: virtual public XosWinWebRtcClientPlugoutMainWindowImplement,
  public XosWinWebRtcClientPlugoutMainWindowExtend
{
public:
    typedef XosWinWebRtcClientPlugoutMainWindowImplement Implements;
    typedef XosWinWebRtcClientPlugoutMainWindowExtend Extends;

    static XosWinWindowClass m_windowClass;
    XosWinWebRtcClientPluginInterface* m_plugin;
    XosWinWebRtcClientPluginDLibrary m_dlibrary;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPlugoutMainWindow
    ///
    ///       Author: $author$
    ///         Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPlugoutMainWindow()
    : m_plugin(0)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPlugoutMainWindow
    ///
    ///      Author: $author$
    ///        Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPlugoutMainWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: LoadPlugin
    ///
    ///    Author: $author$
    ///      Date: 12/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWinWebRtcClientPluginInterface* LoadPlugin(XosError& error)
    {
        XosWinWebRtcClientPluginInterface* plugin = 0;
        error = XOS_ERROR_FAILED;
        if (!(error = m_dlibrary.Open()))
            plugin = m_dlibrary.AcquirePlugin(error);
        return plugin;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: UnloadPlugin
    ///
    ///    Author: $author$
    ///      Date: 12/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError UnloadPlugin
    (XosWinWebRtcClientPluginInterface* plugin)
    {
        XosError error = XOS_ERROR_FAILED;
        if (!(error = m_dlibrary.ReleasePlugin(plugin)))
            error = m_dlibrary.Close();
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnOpen
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnOpen()
    {
        XosError error = XOS_ERROR_NONE;
        if (!(m_plugin))
        if ((m_plugin = LoadPlugin(error)))
            m_plugin->OnWindowAttached(Attached());
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnClose
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnClose()
    {
        if ((m_plugin))
        {
            m_plugin->OnWindowDetached(Attached());
            UnloadPlugin(m_plugin);
            m_plugin = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    virtual void SetServerName(const std::string& serverName) {
        if ((m_plugin))
             m_plugin->SetServerName(serverName); 
    }
    virtual void SetServerPort(int serverPort) {
        if ((m_plugin))
             m_plugin->SetServerPort(serverPort); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    /// Function: On_WM_CLOSE_WindowMessage
    ///
    ///   Author: $author$
    ///     Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_CLOSE_WindowMessage
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;
        OnClose();
        PostQuitMessage(0);
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    ///////////////////////////////////////////////////////////////////////
    /// Function: OnWindowMessageDefault
    ///
    ///   Author: $author$
    ///     Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT OnWindowMessageDefault
    (HWND hWnd,
     UINT msg,
     WPARAM wParam,
     LPARAM lParam)
    {
        LRESULT lResult = 0;

        if ((m_plugin))
        if ((m_plugin->OnWindowMessage(hWnd, msg, wParam, lParam)))
            return lResult;

        lResult = Extends::OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Create
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Create(HINSTANCE hInstance)
    {
        XosError error = XOS_ERROR_FAILED;
        LPCTSTR windowClassName;
        if ((windowClassName = m_windowClass.m_windowClassNameChars))
        if (!(error = Extends::Create(hInstance, windowClassName, windowClassName)))
            OnOpen();
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    ///  Function: RegisterWindowClass
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    static XosError RegisterWindowClass
    (HINSTANCE hInstance, HBRUSH hbrBackground = NULL, 
     HCURSOR hCursor = NULL, HICON hIcon = NULL)
    {
        LPCTSTR className = XOSWINWEBRTCCLIENTPLUGOUTMAINWINDOW_CLASSNAME;
        XosError error = XOS_ERROR_NONE;
        XosError error2;

        if (!(hbrBackground))
            hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));

        if ((error2 = m_windowClass.Register
            (hInstance, className, NULL, NULL, hIcon, NULL, hCursor, hbrBackground)))
        if (!error) error = error2;
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: UnregisterWindowClass
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    static XosError UnregisterWindowClass
    (HINSTANCE hInstance)
    {
        XosError error = XOS_ERROR_NONE;
        XosError error2;
        if ((error2 = m_windowClass.Unregister()))
        if (!error) error = error2;
        return error;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGOUTMAINWINDOW_HPP 
        

