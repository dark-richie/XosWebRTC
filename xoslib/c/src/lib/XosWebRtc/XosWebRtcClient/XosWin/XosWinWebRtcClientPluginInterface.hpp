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
///   File: XosWinWebRtcClientPluginInterface.hpp
///
/// Author: $author$
///   Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGININTERFACE_HPP
#define _XOSWINWEBRTCCLIENTPLUGININTERFACE_HPP

#include "XosWebRtcClientPluginInterface.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginInterfaceImplement
///
///  Author: $author$
///    Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientPluginInterface
XosWinWebRtcClientPluginInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginInterface
///
/// Author: $author$
///   Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
class _INTERFACE_CLASS XosWinWebRtcClientPluginInterface
: virtual public XosWinWebRtcClientPluginInterfaceImplement
{
public:
    typedef XosWinWebRtcClientPluginInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////

    virtual void SetServerName(const std::string& serverName) {
    }
    virtual void SetServerPort(int serverPort) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowAttached
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(HWND hWnd)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowDetached
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowDetached(HWND hWnd)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    /// Function: OnWindowMessage
    ///
    ///   Author: $author$
    ///     Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT OnWindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: AcquireTheInstance
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    static XosWinWebRtcClientPluginInterface* 
    AcquireTheInstance(XosError& error);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: ReleaseTheInstance
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    static XosError ReleaseTheInstance
    (XosWinWebRtcClientPluginInterface* instance);
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGININTERFACE_HPP 
