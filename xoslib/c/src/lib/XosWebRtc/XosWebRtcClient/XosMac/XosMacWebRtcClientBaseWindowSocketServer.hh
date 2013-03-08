///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
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
///   File: XosMacWebRtcClientBaseWindowSocketServer.hh
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTBASEWINDOWSOCKETSERVER_HH
#define _XOSMACWEBRTCCLIENTBASEWINDOWSOCKETSERVER_HH

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosMacWebRtcClientSocketServer.hh"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientSocketServerT
<talk_base::PlatformSocketServer>
XosMacWebRtcClientBaseWindowSocketServerExtend;

typedef XosMacWebRtcClientSocketServerT
<XosMacWebRtcClientBaseWindowSocketServerExtend>
XosMacWebRtcClientBaseWindowSocketServer;

typedef XosMacWebRtcClientBaseWindowSocketServer
XosWebRtcClientBaseWindowSocketServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowSocketServer
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowSocketServer
: public XosWebRtcClientBaseWindowSocketServerExtend
{
public:
    typedef XosWebRtcClientBaseWindowSocketServerExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientBaseWindowSocketServer
    ///
    ///       Author: $author$
    ///         Date: 1/27/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientBaseWindowSocketServer
    (XosWebRtcClientBaseWindow& peerWindow)
    : Extends(peerWindow)
    {
    }
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSMACWEBRTCCLIENTBASEWINDOWSOCKETSERVER_HH 
