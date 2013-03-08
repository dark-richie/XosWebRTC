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
///   File: XosWebRtcClientFBPluginMac.hh
///
/// Author: $author$
///   Date: 4/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINMAC_HH
#define _XOSWEBRTCCLIENTFBPLUGINMAC_HH

#include "Mac/PluginWindowMac.h"
#include "Mac/PluginWindowMacCG.h"
#include "Mac/PluginWindowMacCA.h"
#include "Mac/PluginWindowMacICA.h"
#include "PluginEvents/MacEventCarbon.h"
#include "PluginEvents/MacEventCocoa.h"

#include "XosWebRtcClientFBPlugin.hpp"
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#include "XosWebRtcClientFBPluginMacWindow.hh"
#include "XosWebRtcClientFBPluginMacWindowPeer.hh"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosMacWindowMouseUpEventImplemented
: public FB::MouseUpEvent {};

class _EXPORT_CLASS XosMacWindowResizedEventImplemented
: public FB::ResizedEvent {};

class _EXPORT_CLASS XosMacWindowRefreshEventImplemented
: public FB::RefreshEvent {};

class _EXPORT_CLASS XosMacWindowDrawCGEventImplemented
: public FB::CoreGraphicsDraw {};

class _EXPORT_CLASS XosFBPluginMacWindowImplemented
: public XosMacWindowImplemented 
{
public:
    FB::PluginWindowMac* m_wnd;

    XosFBPluginMacWindowImplemented
    (FB::PluginWindowMac* wnd=0): m_wnd(wnd) {}

    virtual bool InvalidateWindow
    (bool eraseBackground = true)
    {
        bool handled = false;
        if ((handled = (m_wnd != 0)))
            m_wnd->InvalidateWindow();
        return handled;
    }
};

FB_FORWARD_PTR(XosWebRtcClientFBPluginMac)
typedef XosWebRtcClientFBPluginImplement XosWebRtcClientFBPluginMacImplement;
typedef XosWebRtcClientFBPlugin XosWebRtcClientFBPluginMacExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginMac
///
/// Author: $author$
///   Date: 4/11/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPluginMac
: virtual public XosWebRtcClientFBPluginMacImplement,
  public XosWebRtcClientFBPluginMacExtend
{
public:
    typedef XosWebRtcClientFBPluginMacImplement Implements;
    typedef XosWebRtcClientFBPluginMacExtend Extends;

    XosWebRtcClientFBPluginMacWindow m_window;
    XosWebRtcClientFBPluginMacWindowPeer m_windowPeer;
    XosFBPluginMacWindowImplemented m_wnd;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginMac
    ///
    ///       Author: $author$
    ///         Date: 4/11/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginMac(const std::string& mimeType);
    virtual ~XosWebRtcClientFBPluginMac();

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::ResizedEvent, onWindowResized, FB::PluginWindowMac)
        //EVENTTYPE_CASE(FB::RefreshEvent, onWindowRefresh, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::CoreGraphicsDraw, onDrawCG, FB::PluginWindowMacCG)
        PLUGIN_EVENT_MAP_CASCADE(XosWebRtcClientFBPlugin)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseUp(FB::MouseUpEvent* evt, FB::PluginWindowMac* wnd);
    virtual bool onWindowAttached(FB::AttachedEvent* evt, FB::PluginWindowMac* wnd);
    virtual bool onWindowDetached(FB::DetachedEvent* evt, FB::PluginWindowMac* wnd);
    virtual bool onWindowResized(FB::ResizedEvent *evt, FB::PluginWindowMac* wnd);
    virtual bool onWindowRefresh(FB::RefreshEvent *evt, FB::PluginWindowMac* wnd);
    virtual bool onDrawCG(FB::CoreGraphicsDraw* evt, FB::PluginWindowMacCG* cg);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

    virtual Implements::Implements* Delegate(EventsInterface* events=0)
    { return m_window.Delegate(events); }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINMAC_HH 
