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
///   File: XosWebRtcClientConsolePluginWindowPeer.hpp
///
/// Author: $author$
///   Date: 1/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOWPEER_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOWPEER_HPP

#include "XosWebRtcClientConsoleWindowPeerImplement.hpp"
#include "XosWebRtcClientConsolePluginWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientBaseWindowPeerImplementImplement
XosWebRtcClientConsolePluginWindowPeerImplement;

typedef XosWebRtcClientBaseWindowPeerImplement
XosWebRtcClientConsolePluginWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePluginWindowPeer
///
/// Author: $author$
///   Date: 1/2/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePluginWindowPeer
: virtual public XosWebRtcClientConsolePluginWindowPeerImplement,
  public XosWebRtcClientConsolePluginWindowPeerExtend
{
public:
    typedef XosWebRtcClientConsolePluginWindowPeerImplement Implements;
    typedef XosWebRtcClientConsolePluginWindowPeerExtend Extends;

    XosWebRtcClientConsolePluginWindow& m_uiWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePluginWindowPeer
    ///
    ///       Author: $author$
    ///         Date: 1/2/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePluginWindowPeer
    (XosWebRtcClientConsolePluginWindow& uiWindow)
    : Extends(uiWindow),
      m_uiWindow(uiWindow)
    {
    }
    virtual ~XosWebRtcClientConsolePluginWindowPeer()
    {
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOWPEER_HPP 
        

