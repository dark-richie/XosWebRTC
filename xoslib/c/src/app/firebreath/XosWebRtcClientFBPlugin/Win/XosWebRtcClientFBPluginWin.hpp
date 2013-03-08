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
///   File: XosWebRtcClientFBPluginWin.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINWIN_HPP
#define _XOSWEBRTCCLIENTFBPLUGINWIN_HPP

#include "talk/base/win32window.h"
#include "PluginEvents/WindowsEvent.h"
#include "Win/PluginWindowWin.h"

#include "XosWebRtcClientFBPlugin.hpp"
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#include "XosWebRtcClientFBPluginWinWindow.hpp"
#include "XosWebRtcClientFBPluginWinWindowPeer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginImplement
XosWebRtcClientFBPluginWinImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWin
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPlugin
XosWebRtcClientFBPluginWinExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWin
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPluginWin
: virtual public XosWebRtcClientFBPluginWinImplement,
  public XosWebRtcClientFBPluginWinExtend
{
public:
    typedef XosWebRtcClientFBPluginWinImplement Implements;
    typedef XosWebRtcClientFBPluginWinExtend Extends;

    XosWebRtcClientFBPluginWinWindow m_window;
    XosWebRtcClientFBPluginWinWindowPeer m_windowPeer;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginWin
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginWin(const std::string& mimeType);
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginWin
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginWin();

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::WindowsEvent, onWindowsEvent, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowWin)
        PLUGIN_EVENT_MAP_CASCADE(Extends)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowsEvent(FB::WindowsEvent* evt, FB::PluginWindowWin* wnd);
    virtual bool onWindowAttached(FB::AttachedEvent* evt, FB::PluginWindowWin* wnd);
    virtual bool onWindowDetached(FB::DetachedEvent* evt, FB::PluginWindowWin* wnd);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

    ////////////////////////////////////////////////////////////////////////
    ///  Function: Delegate
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual Implements::Implements* Delegate(EventsInterface* events=0)
    { return m_window.Delegate(events); }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINWIN_HPP 
        

