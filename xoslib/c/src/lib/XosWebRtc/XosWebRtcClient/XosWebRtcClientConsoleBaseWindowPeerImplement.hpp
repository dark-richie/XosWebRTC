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
///   File: XosWebRtcClientConsoleBaseWindowPeerImplement.hpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEBASEWINDOWPEERIMPLEMENT_HPP
#define _XOSWEBRTCCLIENTCONSOLEBASEWINDOWPEERIMPLEMENT_HPP

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
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowPeerImplement
: virtual public XosWebRtcClientBaseWindowPeerImplementImplement,
  public XosWebRtcClientBaseWindowPeerImplementExtend
{
public:
    typedef XosWebRtcClientBaseWindowPeerImplementImplement Implements;
    typedef XosWebRtcClientBaseWindowPeerImplementExtend Extends;

    XosWebRtcClientBaseWindow& m_uiWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientBaseWindowPeerImplement
    ///
    ///       Author: $author$
    ///         Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientBaseWindowPeerImplement
    (XosWebRtcClientBaseWindow& uiWindow)
    : m_uiWindow(uiWindow)
    {
        m_uiWindow.AttachWindowPeer(this);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientBaseWindowPeerImplement
    ///
    ///      Author: $author$
    ///        Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientBaseWindowPeerImplement()
    {
        m_uiWindow.DetachWindowPeer();
    }

    virtual bool Open()
    {
        bool isSuccess;
        if ((isSuccess = m_uiWindow.InitUIMessageThread()))
            m_uiWindow.OnOpen();
        return isSuccess;
    }
    virtual bool Close()
    {
        bool isSuccess;
        m_uiWindow.OnClose();
        isSuccess = m_uiWindow.FinishUIMessageThread();
        return isSuccess;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEBASEWINDOWPEERIMPLEMENT_HPP 
