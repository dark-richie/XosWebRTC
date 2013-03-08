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
///   File: XosMacWebRtcClientSocketServer.hh
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTSOCKETSERVER_HH
#define _XOSMACWEBRTCCLIENTSOCKETSERVER_HH

#include "XosWebRtcClientSocketServer.hpp"

#if defined(MACOSX) 
// Mac SocketServer 
#include <Cocoa/Cocoa.h>
#endif // defined(MACOSX) 

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

#undef CDB_CLASS
#define CDB_CLASS "XosMacWebRtcClientSocketServerT"
///////////////////////////////////////////////////////////////////////
///  Class: XosMacWebRtcClientSocketServerT
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
template<class TExtend>
class _EXPORT_CLASS XosMacWebRtcClientSocketServerT
: public TExtend
{
public:
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosMacWebRtcClientSocketServerT
    ///
    ///       Author: $author$
    ///         Date: 1/27/2013
    ///////////////////////////////////////////////////////////////////////
    XosMacWebRtcClientSocketServerT
    (XosWebRtcClientBaseWindow& peerWindow)
    : Extends(peerWindow)
    {
    }
    virtual ~XosMacWebRtcClientSocketServerT()
    {
    }
    virtual bool Wait(int cms, bool process_io) 
    {
#if defined(MACOSX_SOCKETSERVER) 
// Mac SocketServer 
        NSDate *loopUntil = [NSDate dateWithTimeIntervalSinceNow:0.1];
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:loopUntil];
#endif // defined(MACOSX_SOCKETSERVER) 
        return Extends::Wait(cms, process_io);
    }
};
#undef CDB_CLASS

typedef XosWebRtcClientSocketServer
XosMacWebRtcClientSocketServerExtend;

typedef XosMacWebRtcClientSocketServerT
<XosMacWebRtcClientSocketServerExtend>
XosMacWebRtcClientSocketServer;

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSMACWEBRTCCLIENTSOCKETSERVER_HH 
