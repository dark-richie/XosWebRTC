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
///   File: XosWebRtcClientFBPluginWin.cpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientFBPluginWin.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

static HMODULE s_hModule = 0;

///////////////////////////////////////////////////////////////////////
///  Function: GetThisModuleHandle
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
static HMODULE GetThisModuleHandle()
{
    static const TCHAR VariableInModule = 0; 
    HMODULE hModule = 0;
    GetModuleHandleEx
    (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
     GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
     &VariableInModule, &hModule);
    return hModule;
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPlugin
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticInitialize
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticInitialize()
{
    if ((s_hModule = GetThisModuleHandle()))
        talk_base::Win32Window::SetInstance(s_hModule);
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticDeinitialize
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticDeinitialize()
{
    if ((s_hModule) && (GetThisModuleHandle() == s_hModule))
    {
        talk_base::Win32Window::Shutdown();
        s_hModule = 0;
    }
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWin
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientFBPluginWin::XosWebRtcClientFBPluginWin
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginWin::XosWebRtcClientFBPluginWin
(const std::string& mimeType)
: Extends(mimeType),
  m_window(*this),
  m_windowPeer(m_window)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientFBPluginWin::~XosWebRtcClientFBPluginWin
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginWin::~XosWebRtcClientFBPluginWin()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginWin::onWindowsEvent
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginWin::onWindowsEvent
(FB::WindowsEvent* evt, FB::PluginWindowWin* wnd)
{
    bool handled = false;
    LRESULT lResult;
    if ((wnd->getHWND()) == (m_windowPeer.Attached()))
    if ((lResult = m_windowPeer.OnWindowMessage
        (evt->hWnd, evt->uMsg, evt->wParam, evt->lParam)))
        return true;
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginWin::onWindowAttached
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginWin::onWindowAttached
(FB::AttachedEvent* evt, FB::PluginWindowWin* wnd)
{
    bool handled = false;
    m_windowPeer.OnWindowAttached(wnd->getHWND());
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginWin::onWindowDetached
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginWin::onWindowDetached
(FB::DetachedEvent* evt, FB::PluginWindowWin* wnd)
{
    bool handled = false;
    m_windowPeer.OnWindowDetached(wnd->getHWND());
    return handled;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
