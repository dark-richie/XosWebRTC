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
///   File: XosWinWebRtcClientLoginWindow.hpp
///
/// Author: $author$
///   Date: 4/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTLOGINWINDOW_HPP
#define _XOSWINWEBRTCCLIENTLOGINWINDOW_HPP

#include "XosWinChildWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientLoginWindowImplement
///
///  Author: $author$
///    Date: 4/8/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinChildWindowImplement
XosWinWebRtcClientLoginWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientLoginWindowExtend
///
///  Author: $author$
///    Date: 4/8/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinChildWindow
XosWinWebRtcClientLoginWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientLoginWindow
///
/// Author: $author$
///   Date: 4/8/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientLoginWindow
: virtual public XosWinWebRtcClientLoginWindowImplement,
  public XosWinWebRtcClientLoginWindowExtend
{
public:
    typedef XosWinWebRtcClientLoginWindowImplement Implements;
    typedef XosWinWebRtcClientLoginWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientLoginWindow
    ///
    ///       Author: $author$
    ///         Date: 4/8/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientLoginWindow()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientLoginWindow
    ///
    ///      Author: $author$
    ///        Date: 4/8/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientLoginWindow()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: RegisterWindowClass
    ///
    ///    Author: $author$
    ///      Date: 4/8/2012
    ///////////////////////////////////////////////////////////////////////
    static XosError RegisterWindowClass
    (HINSTANCE hInstance)
    {
        XosError error = XOS_ERROR_NONE;
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: UnregisterWindowClass
    ///
    ///    Author: $author$
    ///      Date: 4/8/2012
    ///////////////////////////////////////////////////////////////////////
    static XosError UnregisterWindowClass()
    {
        XosError error = XOS_ERROR_NONE;
        return error;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTLOGINWINDOW_HPP 
        

