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
///   File: XosWebRtcClientConsolePlugin.hpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGIN_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGIN_HPP

#include "XosWebRtcClientConsolePluginWindow.hpp"
#include "XosWebRtcClientConsolePluginWindowPeer.hpp"
#include "XosWebRtcClientConsolePluginInterface.hpp"
#include "XosExportBase.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientConsolePluginInterface XosWebRtcClientConsolePluginImplement;
typedef XosExportBase XosWebRtcClientConsolePluginExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugin
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePlugin
: virtual public XosWebRtcClientConsolePluginImplement,
  public XosWebRtcClientConsolePluginExtend
{
public:
    typedef XosWebRtcClientConsolePluginImplement Implements;
    typedef XosWebRtcClientConsolePluginExtend Extends;

    XosWebRtcClientConsolePluginWindow m_window;
    XosWebRtcClientConsolePluginWindowPeer m_windowPeer;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePlugin
    ///
    ///       Author: $author$
    ///         Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePlugin
    (const char* serverName=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : m_window(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_windowPeer(m_window)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientConsolePlugin
    ///
    ///      Author: $author$
    ///        Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientConsolePlugin()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        return m_window.ConnectToServer(serverName, serverPort); 
    }
    virtual bool ConnectToServer() {
        return m_window.ConnectToServer(); 
    }
    virtual bool DisconnectFromServer() { 
        return m_window.DisconnectFromServer(); 
    }
    virtual void SetServerName(const std::string& serverName) { 
         m_window.SetServerName(serverName);
    }
    virtual void SetServerPort(int serverPort) {
         m_window.SetServerPort(serverPort);
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        return m_window.ConnectToPeer(peerName); 
    }
    virtual bool ConnectToPeer(int peerId) {
        return m_window.ConnectToPeer(peerId); 
    }
    virtual bool ConnectToPeer() {
        return m_window.ConnectToPeer(); 
    }
    virtual bool DisconnectFromPeer() { 
        return m_window.DisconnectFromPeer(); 
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
         m_window.SetAutoConnectToPeerOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerOn() const {
        return  m_window.GetAutoConnectToPeerOn(); 
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
         m_window.SetAutoConnectToPeerAfterOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerAfterOn() const {
        return  m_window.GetAutoConnectToPeerAfterOn(); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowAttached
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(void* attached=0) {
        //m_window.OnWindowAttached(attached);
        m_windowPeer.Attach();
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowDetached
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowDetached(void* attached=0) {
        //m_window.OnWindowDetached(attached);
        m_windowPeer.Detach();
    }

    ///////////////////////////////////////////////////////////////////////
    // Interface Delegated
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientImageInterface* ImageInterfaceDelegated() const {
        return (XosWebRtcClientImageInterface*)(&m_window);
    }
    virtual XosWebRtcClientEventInterface* EventInterfaceDelegated() const {
        return (XosWebRtcClientEventInterface*)(&m_window);
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGIN_HPP 
        

