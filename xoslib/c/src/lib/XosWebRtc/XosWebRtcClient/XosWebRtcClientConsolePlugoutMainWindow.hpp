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
///   File: XosWebRtcClientConsolePlugoutMainWindow.hpp
///
/// Author: $author$
///   Date: 2/9/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAINWINDOW_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAINWINDOW_HPP

#include "XosWebRtcClientConsolePluginInterface.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosWebRtcClientEventInterface.hpp"

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME "localhost"
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT 8888

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN 128
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE 128

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

#undef CDB_CLASS
#define CDB_CLASS "XosWebRtcClientConsolePlugoutMainWindowImplement"
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugoutMainWindowImplement
///
/// Author: $author$
///   Date: 2/9/2013
///////////////////////////////////////////////////////////////////////
template <class TImplement>
class _EXPORT_CLASS XosWebRtcClientConsolePlugoutMainWindowImplement
: virtual public TImplement,
  virtual public XosWebRtcClientImageObserverInterface,
  virtual public XosWebRtcClientEventObserverInterface
{
public:
    typedef TImplement Implements;
    typedef XosWebRtcClientImageObserverInterface ImageImplements;
    typedef XosWebRtcClientEventObserverInterface EventImplements;
};
#undef CDB_CLASS

#undef CDB_CLASS
#define CDB_CLASS "XosWebRtcClientConsolePlugoutMainWindow"
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugoutMainWindow
///
/// Author: $author$
///   Date: 2/9/2013
///////////////////////////////////////////////////////////////////////
template <class TImplement, class TExtend>
class _EXPORT_CLASS XosWebRtcClientConsolePlugoutMainWindow
: virtual public TImplement,
  public TExtend
{
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePlugoutMainWindow
    ///
    ///       Author: $author$
    ///         Date: 2/9/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePlugoutMainWindow()
    : m_plugin(0), 
      m_autoConnectToPeerOn(false),
      m_serverName(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT)
    {
    }
    virtual ~XosWebRtcClientConsolePlugoutMainWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // On Window Open/Close
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpen()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if (!(m_plugin))
        if ((success = (0 != (m_plugin = LoadPlugin(error))))) 
        {
            m_plugin->SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
            m_plugin->SetServerName(m_serverName);
            m_plugin->SetServerPort(m_serverPort);
            m_plugin->RegisterImageObserver(this);
            m_plugin->RegisterEventObserver(this);
            m_plugin->OnWindowAttached(this);
        }
        return success;
    }
    virtual bool OnWindowClose()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if ((m_plugin))
        {
            m_plugin->OnWindowDetached(this);
            m_plugin->UnregisterEventObserver(this);
            m_plugin->UnregisterImageObserver(this);
            success = !(error = UnloadPlugin(m_plugin));
            m_plugin = 0;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    // Connect/Disconnect Server
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
    virtual bool DisconnectFromServer()
    {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->DisconnectFromServer();
        return success;
    }
    virtual void SetServerName(const std::string& serverName) { 
        if ((m_plugin))
            m_plugin->SetServerName(serverName);
    }
    virtual void SetServerPort(int serverPort) {
        if ((m_plugin))
            m_plugin->SetServerPort(serverPort);
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

protected:
    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_plugin))
            m_plugin->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_plugin))
            m_plugin->OnRButtonUp();
    }

    ///////////////////////////////////////////////////////////////////////
    // Load/Unload Plugin
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientConsolePluginInterface* 
    LoadPlugin(XosError& error)
    {
        XosWebRtcClientConsolePluginInterface* plugin = 0;
        plugin = XosWebRtcClientConsolePluginInterface::AcquireInstance(error);
        return plugin;
    }
    virtual XosError UnloadPlugin
    (XosWebRtcClientConsolePluginInterface* plugin)
    {
        XosError error = 0;
        error = XosWebRtcClientConsolePluginInterface::ReleaseInstance(plugin);
        return error;
    }

protected:
    XosWebRtcClientConsolePluginInterface* m_plugin;
    XosString m_serverName;
    int m_serverPort;
    bool m_autoConnectToPeerOn;
};
#undef CDB_CLASS

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAINWINDOW_HPP 
