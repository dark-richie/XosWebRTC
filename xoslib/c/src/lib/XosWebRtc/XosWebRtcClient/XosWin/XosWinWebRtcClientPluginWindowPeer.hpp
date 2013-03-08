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
///   File: XosWinWebRtcClientPluginWindowPeer.hpp
///
/// Author: $author$
///   Date: 12/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGINWINDOWPEER_HPP
#define _XOSWINWEBRTCCLIENTPLUGINWINDOWPEER_HPP

#include "XosWebRtcClientFBPluginWinWindowPeer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginWindowPeerImplement
///
///  Author: $author$
///    Date: 12/11/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginWinWindowPeerImplement
XosWinWebRtcClientPluginWindowPeerImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginWindowPeerExtend
///
///  Author: $author$
///    Date: 12/11/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginWinWindowPeer
XosWinWebRtcClientPluginWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginWindowPeer
///
/// Author: $author$
///   Date: 12/11/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPluginWindowPeer
: virtual public XosWinWebRtcClientPluginWindowPeerImplement,
  public XosWinWebRtcClientPluginWindowPeerExtend
{
public:
    typedef XosWinWebRtcClientPluginWindowPeerImplement Implements;
    typedef XosWinWebRtcClientPluginWindowPeerExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPluginWindowPeer
    ///
    ///       Author: $author$
    ///         Date: 12/11/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPluginWindowPeer
    (XosWebRtcClientFBPluginWinWindow& uiWindow,
     HBRUSH hbrBackground=NULL,
     HWND attached=NULL,
     bool isCreated=false)
    : Extends(uiWindow, hbrBackground, attached, isCreated)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPluginWindowPeer
    ///
    ///      Author: $author$
    ///        Date: 12/11/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPluginWindowPeer()
    {
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGINWINDOWPEER_HPP 
        

