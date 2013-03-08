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
///   File: XosWebRtcClientConsoleWindowPeerImplement.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEWINDOWPEERIMPLEMENT_HPP
#define _XOSWEBRTCCLIENTCONSOLEWINDOWPEERIMPLEMENT_HPP

#include "XosWebRtcClientConsoleWindow.hpp"
#include "XosWebRtcClientBaseWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosInterfaceBase
XosWebRtcClientBaseWindowPeerImplementImplement;

typedef XosExportBase
XosWebRtcClientBaseWindowPeerImplementExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowPeerImplement
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowPeerImplement
: virtual public XosWebRtcClientBaseWindowPeerImplementImplement,
  public XosWebRtcClientBaseWindowPeerImplementExtend
{
public:
    typedef XosWebRtcClientBaseWindowPeerImplementImplement Implements;
    typedef XosWebRtcClientBaseWindowPeerImplementExtend Extends;

    XosWebRtcClientConsoleWindow& m_uiWindow;
    XosWebRtcClientWindowPeerImplement* m_window;

    XosWebRtcClientBaseWindowPeerImplement
    (XosWebRtcClientConsoleWindow& uiWindow)
    : m_uiWindow(uiWindow),
      m_window(0)
    {
    }
    virtual ~XosWebRtcClientBaseWindowPeerImplement()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (XosWebRtcClientWindowPeerImplement* window=0)
    {
        m_window = window;
        return OnOpen();
    }
    virtual bool Close
    (XosWebRtcClientWindowPeerImplement* window=0)
    {
        bool isSuccess = OnClose();
        m_window = 0;
        return isSuccess;
    }

    virtual bool Attach
    (XosWebRtcClientWindowPeerImplement* window=0)
    {
        m_window = window;
        return OnAttach();
    }
    virtual bool Detach
    (XosWebRtcClientWindowPeerImplement* window=0)
    {
        bool isSuccess = OnDetach();
        m_window = 0;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnOpen()
    {
        return m_uiWindow.OnWindowOpened(this);
    }
    virtual bool OnClose()
    {
        return m_uiWindow.OnWindowClosed(this);
    }

    virtual bool OnAttach()
    {
        return m_uiWindow.OnWindowAttached(this);
    }
    virtual bool OnDetach()
    {
        return m_uiWindow.OnWindowDetached(this);
    }

    virtual void OnDefaultAction(int msg_id, int id, void* data)
    {
        m_uiWindow.OnDefaultAction(msg_id, id, data);
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEWINDOWPEERIMPLEMENT_HPP 
