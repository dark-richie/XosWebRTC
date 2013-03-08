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
///   File: XosWebRtcClientFBPluginMacWindowPeer.hh
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINMACWINDOWPEER_HH
#define _XOSWEBRTCCLIENTFBPLUGINMACWINDOWPEER_HH

#include "XosMacWebRtcClientBaseWindowPeerImplement.hh"
#include "XosWebRtcClientFBPluginMacWindow.hh"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientBaseWindowPeerImplementImplement
XosWebRtcClientFBPluginMacWindowPeerImplement;

typedef XosWebRtcClientBaseWindowPeerImplement
XosWebRtcClientFBPluginMacWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginMacWindowPeer
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginMacWindowPeer
: virtual public XosWebRtcClientFBPluginMacWindowPeerImplement,
  public XosWebRtcClientFBPluginMacWindowPeerExtend
{
public:
    typedef XosWebRtcClientFBPluginMacWindowPeerImplement Implements;
    typedef XosWebRtcClientFBPluginMacWindowPeerExtend Extends;

    XosWebRtcClientFBPluginMacWindow& m_uiWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginMacWindowPeer
    ///
    ///       Author: $author$
    ///         Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginMacWindowPeer
    (XosWebRtcClientFBPluginMacWindow& uiWindow)
    : Extends(uiWindow),
      m_uiWindow(uiWindow)
    {
    }
    virtual ~XosWebRtcClientFBPluginMacWindowPeer()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // Attached
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(XosMacWindowAttached attached)
    {
        m_uiWindow.OnWindowAttached(attached);
    }
    virtual void OnWindowDetached(XosMacWindowAttached attached)
    {
        m_uiWindow.OnWindowDetached(attached);
    }

    ///////////////////////////////////////////////////////////////////////
    // Mouse events
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnLMouseUp
    (XosMacWindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = m_uiWindow.OnLMouseUp(mouseUpEvent);
        return handled;
    }
    virtual bool OnRMouseUp
    (XosMacWindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = m_uiWindow.OnRMouseUp(mouseUpEvent);
        return handled;
    }

    ///////////////////////////////////////////////////////////////////////
    // Window events
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowResized
    (int x, int y, int width, int height,
     XosMacWindowResizedEventImplemented* resizedEvent)
    {
        bool handled = m_uiWindow.OnWindowResized
        (x,y, width,height, resizedEvent);
        return handled;
    }
    virtual bool OnWindowRefresh
    (int x, int y, int width, int height,
     XosMacWindowRefreshEventImplemented* refreshEvent)
    {
        bool handled = m_uiWindow.OnWindowRefresh
        (x,y, width,height, refreshEvent);
        return handled;
    }
    virtual bool OnWindowDrawCG
    (int x, int y, int width, int height,
     XosMacWindowCGImplemented* cg,
     XosMacWindowDrawCGEventImplemented* drawCGEvent)
    {
        bool handled = m_uiWindow.OnWindowDrawCG
        (x,y, width,height, cg, drawCGEvent);
        return handled;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINMACWINDOWPEER_HH 
