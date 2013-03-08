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
///   File: XosWebRtcClientFBPluginWinWindowPeer.hpp
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINWINWINDOWPEER_HPP
#define _XOSWEBRTCCLIENTFBPLUGINWINWINDOWPEER_HPP

#include "XosWinWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosWebRtcClientFBPluginWinWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowPeerImplement
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowPeerImplementImplement
XosWebRtcClientFBPluginWinWindowPeerImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowPeerExtend
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowPeerImplement
XosWebRtcClientFBPluginWinWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWinWindowPeer
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginWinWindowPeer
: virtual public XosWebRtcClientFBPluginWinWindowPeerImplement,
  public XosWebRtcClientFBPluginWinWindowPeerExtend
{
public:
    typedef XosWebRtcClientFBPluginWinWindowPeerImplement Implements;
    typedef XosWebRtcClientFBPluginWinWindowPeerExtend Extends;

    XosWebRtcClientFBPluginWinWindow& m_uiWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginWinWindowPeer
    ///
    ///       Author: $author$
    ///         Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginWinWindowPeer
    (XosWebRtcClientFBPluginWinWindow& uiWindow,
     HBRUSH hbrBackground=NULL,
     HWND attached=NULL,
     bool isCreated=false)
    : Extends(uiWindow, hbrBackground, attached, isCreated),
      m_uiWindow(uiWindow)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginWinWindowPeer
    ///
    ///      Author: $author$
    ///        Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginWinWindowPeer()
    {
        XosError error;
        if ((error = Destroyed()))
            throw(error);
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowAttached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(HWND hWnd)
    {
        m_uiWindow.OnWindowAttached(hWnd);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowDetached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowDetached(HWND hWnd)
    {
        m_uiWindow.OnWindowDetached(hWnd);
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnDefWindowProc
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT OnDefWindowProc
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        return lResult;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINWINWINDOWPEER_HPP 
        

