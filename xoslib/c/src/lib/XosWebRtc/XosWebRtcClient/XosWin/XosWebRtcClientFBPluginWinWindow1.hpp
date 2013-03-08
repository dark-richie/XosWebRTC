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
///   File: XosWebRtcClientFBPluginWinWindow.hpp
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP
#define _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP

#include "XosWinWebRtcClientBaseWindow.hpp"
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#include "XosWebRtcClientFBPluginInterface.hpp"
#include "XosWebRtcClientConnectorPair.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowImplement
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginJavaScriptAPI
XosWebRtcClientFBPluginWinWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginWinWindowExtend
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWinWebRtcClientBaseWindow
XosWebRtcClientFBPluginWinWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginWinWindow
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginWinWindow
: virtual public XosWebRtcClientFBPluginWinWindowImplement,
  public XosWebRtcClientFBPluginWinWindowExtend
{
public:
    typedef XosWebRtcClientFBPluginWinWindowImplement Implements;
    typedef XosWebRtcClientFBPluginWinWindowExtend Extends;
    typedef XosWebRtcClientConnectorPair ClientPair;

    XosWebRtcClientFBPluginInterface& m_plugin;

    ClientPair* m_clientPair;
    EventsInterface* m_jsapiEvents;

    std::string m_webrtcClientTraceFileName;
    std::string m_webrtcClientTraceFileDir;
    std::string m_webrtcClientTraceFileEnv;

    Peers m_peers;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginWinWindow
    ///
    ///       Author: $author$
    ///         Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginWinWindow
    (XosWebRtcClientFBPluginInterface& plugin,
     const char* serverName=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_plugin(plugin),

      m_clientPair(0),
      m_jsapiEvents(0),

      m_webrtcClientTraceFileName
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcClientTraceFileDir
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcClientTraceFileEnv
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginWinWindow
    ///
    ///      Author: $author$
    ///        Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginWinWindow()
    {
        if ((m_clientPair))
            delete m_clientPair;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowAttached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(HWND hWnd)
    {
        std::string webrtcClientTraceFileName
        (GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));
        HWND attached = 0;
        if ((attached = Attached()))
            OnWindowDetached(attached);
        m_clientPair = new ClientPair
        (*this, webrtcClientTraceFileName);
        hWnd = Attach(hWnd);
        CreateUIMessageThread();
        OnOpen();
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnWindowDetached
    ///
    ///    Author: $author$
    ///      Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowDetached(HWND hWnd)
    {
        HWND attached = 0;
        if ((attached = Attached()) 
            && (hWnd == attached))
        {
            OnClose();
            DestroyUIMessageThread();
            hWnd = Detach();
            if ((m_clientPair))
            {
                delete m_clientPair;
                m_clientPair = 0;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual void Signin
    (const std::string& userName, 
     const std::string& serverIP, int serverPort)
    {
        SetThisPeerName(userName);
        ConnectToServer(serverIP, serverPort);
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual void Signout()
    {
        DisconnectFromServer();
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual void OnFailedToConnectToServer(const std::string& server)
    {
        if ((m_jsapiEvents))
            m_jsapiEvents->onFailedToConnectToServer(server);
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnSignedIn(const Peers& peers)
    {
        Peers::const_iterator i;
        std::string eventData;
        std::string peerName;
        int peerId;

        for (i = peers.begin(); i != peers.end(); ++i)
        {
            peerName = i->second;
            peerId = i->first;
            if (0 < (peerName.length()))
            {
                eventData.append(peerName);
                eventData.append(":", 1);
            }
        }

        if ((m_jsapiEvents))
            m_jsapiEvents->onSignedIn(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual void Call(const std::string& peerName)
    {
        ConnectToPeer(peerName);
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual void Hangup(const std::string& peerName)
    {
        DisconnectFromPeer();
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnPeerConnected(int id, const std::string& name)
    {
        std::string eventData = name;
        m_peers[id] = name;
        if ((m_jsapiEvents))
            m_jsapiEvents->onPeerOnline(eventData);
        return false;
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnPeerDisconnected(int id)
    {
        std::string eventData = m_peers[id];
        if ((m_jsapiEvents))
            m_jsapiEvents->onPeerOffline(eventData);
        m_peers.erase(id);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnSignalingMessageFromUnconnectedPeer(int peer_id, const std::string& message)
    {
        std::string eventData = m_peers[peer_id];
        if ((0 > (m_peerId)) && (0 < (eventData.length())))
        if ((m_jsapiEvents))
            m_jsapiEvents->onRemotePeerCall(eventData);
        return false;
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnSignalingMessageToPeer(int peer_id, const std::string& message)
    {
        std::string eventData = m_peerName;
        if ((0 < (m_peerId)) && (peer_id == m_peerId) && (0 < (eventData.length())))
        if ((m_jsapiEvents))
            m_jsapiEvents->onRemotePeerCall(eventData);
        return false;
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnPeerConnectionClosed(int id)
    {
        std::string eventData = m_peers[id];
        if ((m_jsapiEvents))
            m_jsapiEvents->onRemotePeerHangup(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnAddStream(const std::string& stream_id, bool video)
    {
        int codecWidth = 0;
        int codecHeight = 0;
        int frameRate = 0;
        int minBitrate = 0;
        XosString eventData = "640:480";
        if ((video))
        {
            GetVideoCodecOptions
            (codecWidth, codecHeight, frameRate, minBitrate);
            if ((0 < codecWidth) && (0 < codecHeight))
            {
                eventData.clear();
                eventData << codecWidth;
                eventData << ":";
                eventData << codecHeight;
            }
            if ((m_jsapiEvents))
                m_jsapiEvents->onRendererAdd(eventData);
        }
        return false;
    }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: 
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnRemoveStream(const std::string& stream_id, bool video)
    {
        std::string eventData;
        if ((m_jsapiEvents))
            m_jsapiEvents->onRendererRemove(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    ///  Function: Delegate
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ////////////////////////////////////////////////////////////////////////
    virtual Implements* Delegate(EventsInterface* events=0)
    { 
        m_jsapiEvents = events;
        return ((Implements*)(this)); 
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINWINWINDOW_HPP 
