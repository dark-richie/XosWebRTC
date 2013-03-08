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
///   File: XosMacWebRtcClientPlugoutMain.hh
///
/// Author: $author$
///   Date: 12/30/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTPLUGOUTMAIN_HH
#define _XOSMACWEBRTCCLIENTPLUGOUTMAIN_HH

#include "XosWebRtcClientConsolePlugoutWindowPeer.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosOptMain.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosMacWebRtcClientPlugoutMainImplement
: virtual public XosOptMainImplement,
  virtual public XosWebRtcClientImageInterface
{
public:
};

typedef XosOptMain
XosMacWebRtcClientPlugoutMainExtend;

///////////////////////////////////////////////////////////////////////
///  Class: XosMacWebRtcClientPlugoutMain
///
/// Author: $author$
///   Date: 12/30/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacWebRtcClientPlugoutMain
: virtual public XosMacWebRtcClientPlugoutMainImplement,
  public XosMacWebRtcClientPlugoutMainExtend
{
public:
    typedef XosMacWebRtcClientPlugoutMainImplement Implements;
    typedef XosMacWebRtcClientPlugoutMainExtend Extends;

    XosWebRtcClientConsolePlugoutWindowPeer m_mainWindow;
    bool m_autoConnectToPeerOn;
    bool m_connectedToServer;

    XosMacWebRtcClientPlugoutMain()
    : m_autoConnectToPeerOn(false),
      m_connectedToServer(false)
    {
    }
    virtual ~XosMacWebRtcClientPlugoutMain()
    {
    }

    virtual int BeforeRun(int argc, char**argv, char**env)
    {
        int err = 1;
        if ((m_mainWindow.Open())) {
            XOS_DBT(("() ConnectToServer()...\n"));
            m_mainWindow.SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
            m_mainWindow.SetAutoConnectToPeerAfterOn(m_autoConnectToPeerOn);
            m_connectedToServer = m_mainWindow.ConnectToServer();
            err = 0;
        }
        return err;
    }
    virtual int AfterRun(int argc, char**argv, char**env)
    {
        int err = 1;
        if ((m_connectedToServer)) {
            XOS_DBT(("() DisconnectFromServer()..\n"));
            m_mainWindow.DisconnectFromServer();
             m_connectedToServer = false;
        }
        if ((m_mainWindow.Close())) {
            err = 0;
        }
        return err;
    }

    virtual XosWebRtcClientImageInterface* ImageInterfaceDelegated() const {
        return (XosWebRtcClientImageInterface*)(&m_mainWindow);
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSMACWEBRTCCLIENTPLUGOUTMAIN_HH 
