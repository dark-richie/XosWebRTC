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
///   File: XosWebRtcClientFBPlugin.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGIN_HPP
#define _XOSWEBRTCCLIENTFBPLUGIN_HPP

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"
#include "PluginEvents/DrawingEvents.h"
#include "PluginCore.h"
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#include "XosWebRtcClientFBPluginInterface.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

FB_FORWARD_PTR(XosWebRtcClientFBPluginAPI)
FB_FORWARD_PTR(XosWebRtcClientFBPlugin)

///////////////////////////////////////////////////////////////////////
// Typedef: XosWebRtcClientFBPluginImplement
//
//  Author: $author$
//    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginInterface
XosWebRtcClientFBPluginImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef FB::PluginCore
XosWebRtcClientFBPluginExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPlugin
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPlugin
: virtual public XosWebRtcClientFBPluginImplement,
  public XosWebRtcClientFBPluginExtend
{
public:
    typedef XosWebRtcClientFBPluginImplement Implements;
    typedef XosWebRtcClientFBPluginExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: StaticInitialize
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    static void StaticInitialize();
    ///////////////////////////////////////////////////////////////////////
    ///  Function: StaticDeinitialize
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    static void StaticDeinitialize();

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPlugin
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPlugin(const std::string& mimeType);
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPlugin
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPlugin();

    ///////////////////////////////////////////////////////////////////////
    ///  Function: onPluginReady
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void onPluginReady();
    ///////////////////////////////////////////////////////////////////////
    ///  Function: shutdown
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void shutdown();

    ///////////////////////////////////////////////////////////////////////
    ///  Function: createJSAPI
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual FB::JSAPIPtr createJSAPI();

    ///////////////////////////////////////////////////////////////////////
    ///  Function: isWindowless
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool isWindowless()
    {
        bool isTrue = false;
        return isTrue;
    }

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        //EVENTTYPE_CASE(FB::RefreshEvent, onWindowRefresh, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent* evt, FB::PluginWindow* wnd);
    virtual bool onMouseUp(FB::MouseUpEvent* evt, FB::PluginWindow* wnd);
    virtual bool onWindowRefresh(FB::RefreshEvent *evt, FB::PluginWindow* wnd);
    virtual bool onWindowAttached(FB::AttachedEvent* evt, FB::PluginWindow* wnd);
    virtual bool onWindowDetached(FB::DetachedEvent* evt, FB::PluginWindow* wnd);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

protected:

    std::string m_mimeType;
    XosWebRtcClientFBPluginAPIWeakPtr m_pluginAPI;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: getPluginAPI
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientFBPluginAPIPtr getPluginAPI();
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGIN_HPP 
        

