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
///   File: XosWebRtcClientFBPluginAPI.hpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINAPI_HPP
#define _XOSWEBRTCCLIENTFBPLUGINAPI_HPP

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "XosWebRtcClientFBPlugin.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginAPIEventsImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginJavaScriptAPI::EventsInterface
XosWebRtcClientFBPluginAPIEventsImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginAPIExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef FB::JSAPIAuto
XosWebRtcClientFBPluginAPIExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginAPI
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPluginAPI
: virtual public XosWebRtcClientFBPluginAPIEventsImplement,
  public XosWebRtcClientFBPluginAPIExtend
{
public:
    typedef XosWebRtcClientFBPluginAPIEventsImplement EventsImplements;
    typedef XosWebRtcClientFBPluginJavaScriptAPI Implements;
    typedef XosWebRtcClientFBPluginAPIExtend Extends;
    typedef XosWebRtcClientFBPluginAPI Derives;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginAPI
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginAPI
    (const XosWebRtcClientFBPluginPtr& plugin, const FB::BrowserHostPtr& host);
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginAPI
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginAPI();

#define XOSWEBRTCCLIENTFBPLUGINJAVASCRIPTAPI_MEMBERS_ONLY
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#undef XOSWEBRTCCLIENTFBPLUGINJAVASCRIPTAPI_MEMBERS_ONLY

protected:

    XosWebRtcClientFBPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
    Implements* m_delegated;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: getPlugin
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientFBPluginPtr getPlugin();
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINAPI_HPP 
        

