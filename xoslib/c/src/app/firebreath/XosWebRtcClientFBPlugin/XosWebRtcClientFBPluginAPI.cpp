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
///   File: XosWebRtcClientFBPluginAPI.cpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "XosWebRtcClientFBPluginAPI.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginAPI
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientFBPluginAPI::XosWebRtcClientFBPluginAPI
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginAPI::XosWebRtcClientFBPluginAPI
(const XosWebRtcClientFBPluginPtr& plugin, const FB::BrowserHostPtr& host)
: m_plugin(plugin), m_host(host), m_delegated(0)
{
    RegisterMethods();
    RegisterProperties();
    if ((plugin))
        m_delegated = plugin->Delegate((EventsImplements*)(this));
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientFBPluginAPI::~XosWebRtcClientFBPluginAPI
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginAPI::~XosWebRtcClientFBPluginAPI()
{
    XosWebRtcClientFBPluginPtr plugin;
    if ((plugin = getPlugin()))
        plugin->Delegate(0);
    m_delegated = 0;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginAPI::getPlugin
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginPtr XosWebRtcClientFBPluginAPI::getPlugin()
{
    XosWebRtcClientFBPluginPtr plugin(m_plugin.lock());
    return plugin;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginAPI::Delegated
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginAPI::Implements* 
XosWebRtcClientFBPluginAPI::Delegated()
{
    return m_delegated;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
        

