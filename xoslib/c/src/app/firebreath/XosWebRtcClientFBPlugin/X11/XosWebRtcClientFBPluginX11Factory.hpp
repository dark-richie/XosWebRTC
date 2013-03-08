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
///   File: XosWebRtcClientFBPluginX11Factory.hpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINX11FACTORY_HPP
#define _XOSWEBRTCCLIENTFBPLUGINX11FACTORY_HPP

#include "FactoryBase.h"
#include <boost/make_shared.hpp>
#include "XosWebRtcClientFBPluginX11.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginX11FactoryExtends
///
///  Author: $author$
///    Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
typedef FB::FactoryBase
XosWebRtcClientFBPluginX11FactoryExtends;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginX11Factory
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPluginX11Factory
: public XosWebRtcClientFBPluginX11FactoryExtends
{
public:
    typedef XosWebRtcClientFBPluginX11FactoryExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: createPlugin
    ///
    ///    Author: $author$
    ///      Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    virtual FB::PluginCorePtr createPlugin
    (const std::string& mimetype)
    {
        FB::PluginCorePtr plugin 
        = boost::make_shared<XosWebRtcClientFBPluginX11>(mimetype);
        return plugin;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: globalPluginInitialize
    ///
    ///    Author: $author$
    ///      Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void globalPluginInitialize()
    {
        XosWebRtcClientFBPlugin::StaticInitialize();
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: globalPluginDeinitialize
    ///
    ///    Author: $author$
    ///      Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void globalPluginDeinitialize()
    {
        XosWebRtcClientFBPlugin::StaticDeinitialize();
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINX11FACTORY_HPP 
        

