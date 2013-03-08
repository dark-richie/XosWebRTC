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
///   File: XosWebRtcClientConsolePlugoutWindowPeer.hpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGOUTWINDOWPEER_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGOUTWINDOWPEER_HPP

#include "XosWebRtcClientConsolePluginInterface.hpp"
#include "XosExportBase.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientImageInterface 
XosWebRtcClientConsolePlugoutWindowPeerImplement;

typedef XosExportBase 
XosWebRtcClientConsolePlugoutWindowPeerExtend;

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugoutWindowPeer
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePlugoutWindowPeer
: virtual public XosWebRtcClientConsolePlugoutWindowPeerImplement,
  public XosWebRtcClientConsolePlugoutWindowPeerExtend
{
public:
    typedef XosWebRtcClientConsolePlugoutWindowPeerImplement Implements;
    typedef XosWebRtcClientConsolePlugoutWindowPeerExtend Extends;

    XosWebRtcClientConsolePluginInterface* m_plugin;
    XosWebRtcClientImageObserverInterface* m_imageObserver;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePlugoutWindowPeer
    ///
    ///       Author: $author$
    ///         Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePlugoutWindowPeer()
    : m_plugin(0), m_imageObserver(0) 
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientConsolePlugoutWindowPeer
    ///
    ///      Author: $author$
    ///        Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientConsolePlugoutWindowPeer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Open
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if (!(m_plugin))
        if ((success = (0 != (m_plugin = LoadPlugin(error)))))
            m_plugin->OnWindowAttached(this);
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Close
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool Close()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if ((m_plugin))
        {
            m_plugin->OnWindowDetached(this);
            success = !(error = UnloadPlugin(m_plugin));
            m_plugin = 0;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: ConnectToServer
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort)
    {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ConnectToServer(serverName, serverPort);
        return success;
    }
    virtual bool ConnectToServer()
    {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ConnectToServer();
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: DisconnectFromServer
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool DisconnectFromServer()
    {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->DisconnectFromServer();
        return success;
    }

    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
        if ((m_plugin)) {
            m_plugin->SetAutoConnectToPeerOn(isTrue);
            m_plugin->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
        if ((m_plugin)) {
            m_plugin->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }

    virtual void RegisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        if ((m_plugin)) {
            m_plugin->RegisterImageObserver(imageObserver);
        } else {
            m_imageObserver = imageObserver;
        }
    }
    virtual void UnregisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        if ((m_plugin)) {
            m_plugin->UnregisterImageObserver(imageObserver);
        } else {
            m_imageObserver = 0;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: ImageInterfaceDelegated
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientImageInterface* ImageInterfaceDelegated() const {
        if ((m_plugin))
            return (XosWebRtcClientImageInterface*)(m_plugin);
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: LoadPlugin
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientConsolePluginInterface* 
    LoadPlugin(XosError& error)
    {
        XosWebRtcClientConsolePluginInterface* plugin = 0;
        if ((plugin = XosWebRtcClientConsolePluginInterface::AcquireInstance(error))) {
            if ((m_imageObserver))
                plugin->RegisterImageObserver(m_imageObserver);
        }
        return plugin;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: UnloadPlugin
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError UnloadPlugin
    (XosWebRtcClientConsolePluginInterface* plugin)
    {
        XosError error = 0;
        if ((m_imageObserver))
            plugin->UnregisterImageObserver(m_imageObserver);
        error = XosWebRtcClientConsolePluginInterface::ReleaseInstance(plugin);
        return error;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGOUTWINDOWPEER_HPP 
        

