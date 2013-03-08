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
///   File: XosWebRtcClientFBPluginX11WindowPeer.hpp
///
/// Author: $author$
///   Date: 4/21/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINX11WINDOWPEER_HPP
#define _XOSWEBRTCCLIENTFBPLUGINX11WINDOWPEER_HPP

#include "XosX11WebRtcClientBaseWindowPeerImplement.hpp"
#include "XosWebRtcClientFBPluginX11Window.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientBaseWindowPeerImplementImplement
XosWebRtcClientFBPluginX11WindowPeerImplement;

typedef XosWebRtcClientBaseWindowPeerImplement
XosWebRtcClientFBPluginX11WindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginX11WindowPeer
///
/// Author: $author$
///   Date: 4/21/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginX11WindowPeer
: virtual public XosWebRtcClientFBPluginX11WindowPeerImplement,
  public XosWebRtcClientFBPluginX11WindowPeerExtend
{
public:
    typedef XosWebRtcClientFBPluginX11WindowPeerImplement Implements;
    typedef XosWebRtcClientFBPluginX11WindowPeerExtend Extends;

    XosWebRtcClientFBPluginX11Window& m_uiWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginX11WindowPeer
    ///
    ///       Author: $author$
    ///         Date: 4/21/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginX11WindowPeer
    (XosWebRtcClientFBPluginX11Window& uiWindow)
    : Extends(uiWindow),
      m_uiWindow(uiWindow)
    {
    }
    virtual ~XosWebRtcClientFBPluginX11WindowPeer()
    {
    }

    virtual void OnWindowAttached
    (XosX11WindowImplemented* attached)
    {
        m_uiWindow.OnWindowAttached(attached);
    }
    virtual void OnWindowDetached
    (XosX11WindowImplemented* attached)
    {
        m_uiWindow.OnWindowDetached(attached);
    }

    virtual bool OnX11Event
    (XosX11WindowX11EventImplemented* x11Event)
    {
        bool handled = m_uiWindow.OnX11Event(x11Event);
        return handled;
    }

    virtual bool OnLMouseUp
    (XosX11WindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = m_uiWindow.OnLMouseUp(mouseUpEvent);
        return handled;
    }
    virtual bool OnRMouseUp
    (XosX11WindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = m_uiWindow.OnRMouseUp(mouseUpEvent);
        return handled;
    }

    virtual bool OnWindowResized
    (int x, int y, int width, int height,
     XosX11WindowResizedEventImplemented* resizedEvent)
    {
        XOS_DBT(("()...\n"));
        bool handled = m_uiWindow.OnWindowResized
        (x,y, width,height, resizedEvent);
        return handled;
    }
    virtual bool OnWindowRefresh
    (int x, int y, int width, int height,
     XosX11WindowRefreshEventImplemented* refreshEvent)
    {
        XOS_DBT(("()...\n"));
        bool handled = m_uiWindow.OnWindowRefresh
        (x,y, width,height, refreshEvent);
        return handled;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINX11WINDOWPEER_HPP 
        

