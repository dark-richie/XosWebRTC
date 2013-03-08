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
///   File: XosWebRtcClientConsolePlugin.cpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientConsolePlugin.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugin
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePluginInterface
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
static XosWebRtcClientConsolePlugin g_plugin;
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientConsolePluginInterface::AcquireInstance
///
///    Author: $author$
///      Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientConsolePluginInterface* 
XosWebRtcClientConsolePluginInterface::AcquireInstance
(XosError& error)
{
    XosWebRtcClientConsolePluginInterface* plugin = 0;
    error = 1;
    if ((plugin = (&g_plugin)))
        error = 0;
    return plugin;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientConsolePluginInterface::ReleaseInstance
///
///    Author: $author$
///      Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientConsolePluginInterface::ReleaseInstance
(XosWebRtcClientConsolePluginInterface* plugin)
{
    XosError error = 1;
    if ((plugin == (&g_plugin)))
        error = 0;
    return error;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

        

