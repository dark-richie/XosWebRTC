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
///   File: XosWebRtcClientFBPlugin.cpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientFBPluginAPI.hpp"
#include "XosWebRtcClientFBPlugin.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPlugin
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientFBPlugin::XosWebRtcClientFBPlugin
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPlugin::XosWebRtcClientFBPlugin
(const std::string& mimeType)
: m_mimeType(mimeType)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientFBPlugin::~XosWebRtcClientFBPlugin
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPlugin::~XosWebRtcClientFBPlugin()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onPluginReady
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::onPluginReady()
{
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::shutdown
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::shutdown()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::createJSAPI
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
FB::JSAPIPtr XosWebRtcClientFBPlugin::createJSAPI()
{
    XosWebRtcClientFBPluginAPIPtr pluginAPI 
    = boost::make_shared<XosWebRtcClientFBPluginAPI>
    (FB::ptr_cast<XosWebRtcClientFBPlugin>(shared_from_this()), m_host);
    m_pluginAPI = pluginAPI;
    return pluginAPI;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::getPluginAPI
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginAPIPtr XosWebRtcClientFBPlugin::getPluginAPI()
{
    XosWebRtcClientFBPluginAPIPtr plugin(m_pluginAPI.lock());
    return plugin;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onMouseDown
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPlugin::onMouseDown
(FB::MouseDownEvent* evt, FB::PluginWindow* wnd)
{
    bool handled = false;
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onMouseUp
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPlugin::onMouseUp
(FB::MouseUpEvent* evt, FB::PluginWindow* wnd)
{
    bool handled = false;
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onWindowAttached
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPlugin::onWindowAttached
(FB::AttachedEvent* evt, FB::PluginWindow* wnd)
{
    bool handled = false;
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onWindowDetached
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPlugin::onWindowDetached
(FB::DetachedEvent* evt, FB::PluginWindow* wnd)
{
    bool handled = false;
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::onWindowRefresh
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPlugin::onWindowRefresh
(FB::RefreshEvent *evt, FB::PluginWindow* wnd)
{
    bool handled = false;
    XOS_DBT(("()...\n"));
    return handled;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
        

