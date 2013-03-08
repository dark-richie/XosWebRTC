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
///   File: XosWebRtcClientConsolePeerWindow.hpp
///
/// Author: $author$
///   Date: 1/22/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPEERWINDOW_HPP
#define _XOSWEBRTCCLIENTCONSOLEPEERWINDOW_HPP

#include "XosWebRtcClientConsoleBaseWindow.hpp"

#if defined(WINDOWS)  
// Windows 
#include "XosWinWebRtcClientConsolePeerWindow.hpp"
#elif defined(MACOSX)  
// MacOSX 
#include "XosMacWebRtcClientConsolePeerWindow.hh"
#else // defined(WINDOWS)  
// Unix 
#endif // defined(WINDOWS)  

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

#if defined(WINDOWS)  
// Windows 
typedef XosWinWebRtcClientConsolePeerWindow XosWebRtcClientConsolePeerWindowExtend;
#elif defined(MACOSX)  
// MacOSX 
typedef XosMacWebRtcClientConsolePeerWindow XosWebRtcClientConsolePeerWindowExtend;
#else // defined(WINDOWS)  
// Unix 
typedef XosWebRtcClientConsoleBaseWindow XosWebRtcClientConsolePeerWindowExtend;
#endif // defined(WINDOWS)  

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePeerWindow
///
/// Author: $author$
///   Date: 1/22/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePeerWindow
: public XosWebRtcClientConsolePeerWindowExtend
{
public:
    typedef XosWebRtcClientConsolePeerWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePeerWindow
    ///
    ///       Author: $author$
    ///         Date: 1/22/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePeerWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents)
    {
    }
    virtual ~XosWebRtcClientConsolePeerWindow()
    {
    }
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPEERWINDOW_HPP 
