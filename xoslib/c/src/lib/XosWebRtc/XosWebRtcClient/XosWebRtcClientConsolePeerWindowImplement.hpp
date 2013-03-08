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
///   File: XosWebRtcClientConsolePeerWindowImplement.hpp
///
/// Author: $author$
///   Date: 2/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPEERWINDOWIMPLEMENT_HPP
#define _XOSWEBRTCCLIENTCONSOLEPEERWINDOWIMPLEMENT_HPP

#include "XosWebRtcClientConsoleWindow.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientConsoleWindowImplement 
XosWebRtcClientBasePeerWindowImplementImplement;

typedef XosWebRtcClientConsoleWindow 
XosWebRtcClientBasePeerWindowImplementExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBasePeerWindowImplement
///
/// Author: $author$
///   Date: 2/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBasePeerWindowImplement
: virtual public XosWebRtcClientBasePeerWindowImplementImplement,
  public XosWebRtcClientBasePeerWindowImplementExtend
{
public:
    typedef XosWebRtcClientBasePeerWindowImplementImplement Implements;
    typedef XosWebRtcClientBasePeerWindowImplementExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientBasePeerWindowImplement
    ///
    ///       Author: $author$
    ///         Date: 2/10/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientBasePeerWindowImplement
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents)
    {
    }
    virtual ~XosWebRtcClientBasePeerWindowImplement()
    {
    }
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPEERWINDOWIMPLEMENT_HPP 
