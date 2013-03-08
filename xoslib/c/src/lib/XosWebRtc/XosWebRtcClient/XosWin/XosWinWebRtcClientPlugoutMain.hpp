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
///   File: XosWinWebRtcClientPlugoutMain.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGOUTMAIN_HPP
#define _XOSWINWEBRTCCLIENTPLUGOUTMAIN_HPP

#include "XosWinWebRtcClientPlugoutMainWindow.hpp"
#include "XosWinMain.hpp"

#define XOSWINWEBRTCCLIENTPLUGOUTMAIN_DEFAULT_SERVER_NAME "localhost"
#define XOSWINWEBRTCCLIENTPLUGOUTMAIN_DEFAULT_SERVER_PORT 8888

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPlugoutMainImplement
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinMainImplement
XosWinWebRtcClientPlugoutMainImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPlugoutMainExtend
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinMain
XosWinWebRtcClientPlugoutMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPlugoutMain
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPlugoutMain
: virtual public XosWinWebRtcClientPlugoutMainImplement,
  public XosWinWebRtcClientPlugoutMainExtend
{
public:
    typedef XosWinWebRtcClientPlugoutMainImplement Implements;
    typedef XosWinWebRtcClientPlugoutMainExtend Extends;

    XosString m_serverName;
    int m_serverPort;
    XosWinWebRtcClientPlugoutMainWindow m_mainWindow;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPlugoutMain
    ///
    ///       Author: $author$
    ///         Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPlugoutMain()
    : m_serverName(XOSWINWEBRTCCLIENTPLUGOUTMAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWINWEBRTCCLIENTPLUGOUTMAIN_DEFAULT_SERVER_PORT)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPlugoutMain
    ///
    ///      Author: $author$
    ///        Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPlugoutMain()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWinMain
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int OnWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance,
     LPSTR cmdLine, int cmdShow)
    {
        int result = 0;
        XosError error;
        MSG msg;
        if (!(error = m_mainWindow.RegisterWindowClass(hInstance)))
        {
            if (!(error = m_mainWindow.Create(hInstance)))
            {
                m_mainWindow.SetServerName(m_serverName);
                m_mainWindow.SetServerPort(m_serverPort);
                if (!(error = m_mainWindow.Show()))
                while((GetMessage(&msg, 0, 0, 0)))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                m_mainWindow.Destroy();
            }
            m_mainWindow.UnregisterWindowClass(hInstance);
        }
        return result;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGOUTMAIN_HPP 
        

