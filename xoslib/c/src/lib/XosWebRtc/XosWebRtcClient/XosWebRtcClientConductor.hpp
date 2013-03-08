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
///   File: XosWebRtcClientConductor.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONDUCTOR_HPP
#define _XOSWEBRTCCLIENTCONDUCTOR_HPP

#include <deque>
#include <set>
#include <string>

#include "talk/base/scoped_ptr.h"
#include "talk/app/webrtc/peerconnection.h"
#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/session/phone/mediaengine.h"

#include "XosWebRtcClientConductorInterface.hpp"
#include "XosWebRtcClientConnectionObserverInterface.hpp"
#include "XosWebRtcClientUserInterface.hpp"
#include "XosWebRtcClientConnection.hpp"
#include "XosWebRtcClientVideoCodec.hpp"
#include "XosWebRtcClientAudioDeviceOptions.hpp"
#include "XosWebRtcClientTrace.hpp"
#include "XosExportBase.hpp"

#define WEBRTC_GEN_2_REVISION 1200

#define XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER
#define XOSPEERCONNECTIONCONDUCTOR_USE_RELAY_SERVER_1
#define XOSPEERCONNECTIONCONDUCTOR_NO_USE_ALTERNATE_SERVER_ADDRESSES
#define XOSPEERCONNECTIONCONDUCTOR_NO_USE_NUMERIC_SERVER_ADDRESSES

#if !defined(XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES)
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES false
#endif // !defined(XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES)

#if !defined(XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES) 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES false
#endif // !defined(XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES) 

//
// Google address
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_NAME "stun.l.google.com"
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_ADDRESS "72.215.255.9"
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_PORT 19302

#if defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_ADDRESS
#else // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_NAME
#endif // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// Relay address
//
#if !defined(XOSPEERCONNECTIONCONDUCTOR_USE_RELAY_SERVER_2)
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_NAME "Indri"
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_ADDRESS "192.168.3.103"
#else // !defined(XOSPEERCONNECTIONCONDUCTOR_USE_RELAY_SERVER_2)
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_NAME "BushBaby"
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_ADDRESS "192.168.3.107"
#endif // !defined(XOSPEERCONNECTIONCONDUCTOR_USE_RELAY_SERVER_2)

#if defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_ADDRESS
#else // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST_NAME
#endif // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// local address
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_NAME "localhost"
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_ADDRESS "127.0.0.1"

#if defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_ADDRESS
#else // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST \
    XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_NAME
#endif // defined(XOSPEERCONNECTIONCONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// XOS default server addresses
//
#if defined(XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER)
//
// Use Google stun server
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_STUN_SERVER_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_STUN_SERVER_PORT XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_PORT

#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_UDP_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_UDP_PORT -1

#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_TCP_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_TCP_PORT -1

#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT -1
#else // XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER
//
// Use relay stun server
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_STUN_SERVER_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_STUN_SERVER_PORT 7000

#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_UDP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_UDP_PORT 5000

#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_TCP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_TCP_PORT 5000

//#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
//#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT 5000
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT -1
#endif // XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER

//
// Alternate (WebRTC) default server addresses
//
#if defined(XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_USE_GOOGLE_STUN_SERVER)
//
// Use Google stun server
//
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_PORT XOSPEERCONNECTIONCONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_PORT

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_PORT -1

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_PORT -1

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_PORT -1
#else // XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_USE_GOOGLE_STUN_SERVER
#if defined(XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER)
//
// Use relay stun server
//
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_PORT 7000

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_PORT 5000

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_PORT 5000

//#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_RELAY_SERVER_HOST
//#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_PORT 5000
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_HOST ""
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_PORT -1
#else // defined(XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER)
//
// Use local stun server (for testing)
//
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_STUN_SERVER_PORT 7000

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_UDP_PORT 5000

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_TCP_PORT 5000

#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_HOST XOSPEERCONNECTIONCONDUCTOR_DEFAULT_LOCAL_SERVER_HOST
#define XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_RELAY_SERVER_SSL_PORT 5000
#endif // defined(XOSPEERCONNECTIONCONDUCTOR_USE_GOOGLE_STUN_SERVER)
#endif // XOSPEERCONNECTIONCONDUCTOR_ALTERNATE_USE_GOOGLE_STUN_SERVER

//
// Default video device
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_VIDEO_CAPTURE_DEVICE ""

//
// Default audio device options
//
#define XOSPEERCONNECTIONCONDUCTOR_DEFAULT_AUDIO_DEVICE_OPTIONS \
    cricket::MediaEngineInterface::ECHO_CANCELLATION \
    | cricket::MediaEngineInterface::NOISE_SUPPRESSION \
    | cricket::MediaEngineInterface::AUTO_GAIN_CONTROL

#define XOSPEERCONNECTIONCONDUCTOR_VIDEO_LABEL "video_label"
#define XOSPEERCONNECTIONCONDUCTOR_AUDIO_LABEL "audio_label"

namespace cricket {
class VideoRenderer;
#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
class PortAllocator;
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
}  // namespace cricket

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientPeerConnectionObserverInterface
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef webrtc::PeerConnectionObserver
XosWebRtcClientPeerConnectionObserverInterface;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConductorImplement
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _IMPLEMENT_CLASS XosWebRtcClientConductorImplement
: virtual public XosWebRtcClientConductorInterface,
  virtual public XosWebRtcClientConnectionObserverInterface,
  virtual public XosWebRtcClientPeerConnectionObserverInterface
{
public:
    typedef XosWebRtcClientConductorInterface Implements;
};

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientConductorExtend
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosWebRtcClientConductorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConductor
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConductor
: virtual public XosWebRtcClientConductorImplement,
  public XosWebRtcClientConductorExtend
{
public:
    typedef XosWebRtcClientConductorImplement Implements;
    typedef XosWebRtcClientConductorExtend Extends;

    enum CallbackID 
    {
        MEDIA_CHANNELS_INITIALIZED = 1,
        PEER_CONNECTION_CLOSED,
        SEND_MESSAGE_TO_PEER,
        PEER_CONNECTION_ADDSTREAMS,
        PEER_CONNECTION_ERROR,
        NEW_STREAM_ADDED,
        STREAM_REMOVED,
    };
    class ServerAddress
    {
    public:
        std::string host_;
        int port_;
        ServerAddress(const std::string& host, int port)
        : host_(host), port_(port){}
        bool isNil() const 
        {return ((0 >= host_.length())||(0 > port_));};
    };
    class ServerSocketAddress;

    XosWebRtcClientConductor
    (XosWebRtcClientVideoCodec& videoCodec,
     XosWebRtcClientTrace& clientTrace,
     XosWebRtcClientConnection* client, 
     XosWebRtcClientUserInterface* main_wnd,
     bool useAlternateServerAddresses=XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
     bool useNumericServerAddresses=XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);
    virtual ~XosWebRtcClientConductor();

    bool connection_active() const;
    virtual void Close();

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight,
     int frameRate, int minBitrate);
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight,
     int& frameRate, int& minBitrate) const;

    virtual XosWebRtcClientVideoCodecMode SetVideoCodecModeByName
    (const std::string& toModeName);
    virtual void SetVideoCodecModeName
    (const std::string& toModeName);
    virtual std::string GetVideoCodecModeName() const;

    virtual XosWebRtcClientVideoCodecMode SetVideoCodecMode
    (XosWebRtcClientVideoCodecMode toMode);
    virtual XosWebRtcClientVideoCodecMode GetVideoCodecMode() const;

    virtual void SetAudioDeviceOptions
    (bool echoCancelation, bool noiseSupression, bool autoGainControl);
    virtual void GetAudioDeviceOptions
    (bool& echoCancelation, bool& noiseSupression, bool& autoGainControl) const;

    virtual XosWebRtcClientAudioDeviceOptions SetAudioDeviceOptions
    (XosWebRtcClientAudioDeviceOptions toOptions);
    virtual XosWebRtcClientAudioDeviceOptions GetAudioDeviceOptions() const;

protected:

    bool InitializePeerConnection();
    void DeletePeerConnection();
    void SwitchToStreamingUi();
    bool AddStream(const std::string& id, bool video);
    void AddStreams();

    //
    // PeerConnectionObserver implementation.
    //
    virtual void OnError();
    virtual void OnSignalingMessage(const std::string& msg);
    // Called when a remote stream is added
    virtual void OnAddStream(const std::string& stream_id, bool video);
    virtual void OnRemoveStream(const std::string& stream_id,
                                bool video);

    //
    // WebRtcClientObserver implementation.
    //
    virtual void OnSignedIn();
    virtual void OnDisconnected();
    virtual void OnFailedToConnect();
    virtual void OnPeerConnected(int id, const std::string& name);
    virtual void OnPeerDisconnected(int id);
    virtual void OnMessageFromPeer(int peer_id, const std::string& message);
    virtual void OnMessageSent(int err);

    //
    // MainWndCallback implementation.
    //
    virtual std::string GetPeerName();
    virtual bool StartLogin(const std::string& server, int port);
    virtual void DisconnectFromServer(bool doClose=false);
    virtual void ConnectToPeer(int peer_id);
    virtual void DisconnectFromCurrentPeer();
    virtual void UIThreadCallback(int msg_id, void* data);
    virtual bool SendMessageToPeer(const std::string& messageEnvelope);

protected:
    XosWebRtcClientVideoCodec& videoCodec_;
    XosWebRtcClientTrace& clientTrace_;

    ServerAddress stun_server_;
    ServerAddress relay_server_udp_;
    ServerAddress relay_server_tcp_;
    ServerAddress relay_server_ssl_;
    ServerAddress alternate_stun_server_;
    ServerAddress alternate_relay_server_udp_;
    ServerAddress alternate_relay_server_tcp_;
    ServerAddress alternate_relay_server_ssl_;
    bool useAlternateServerAddresses_;
    bool useNumericServerAddresses_;
    int audioDeviceOptions_;
    std::string videoCaptureDevice_;
    std::string videoLabel_;
    std::string audioLabel_;
    int peer_id_;
    talk_base::scoped_ptr<webrtc::PeerConnection> peer_connection_;
    talk_base::scoped_ptr<webrtc::PeerConnectionFactory> peer_connection_factory_;
    talk_base::scoped_ptr<talk_base::Thread> worker_thread_;
    XosWebRtcClientConnection* client_;
    XosWebRtcClientUserInterface* main_wnd_;
    std::deque<std::string*> pending_messages_;
    std::set<std::string> active_streams_;
#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
  talk_base::scoped_ptr<cricket::PortAllocator> port_allocator_;
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
    std::string connecting_to_server_;

public:

    virtual void SetPortServerHost(const std::string& val)
    { stun_server_.host_ = val;
      relay_server_udp_.host_ = val; 
      relay_server_tcp_.host_ = val; 
      relay_server_ssl_.host_ = val; }
    virtual std::string GetPortServerHost() const
    { return stun_server_.host_;}

    virtual void SetStunServerHost(const std::string& val)
    { stun_server_.host_ = val; }
    virtual std::string GetStunServerHost() const
    { return stun_server_.host_;}

    virtual void SetStunServerPort(int val)
    { stun_server_.port_ = val; }
    virtual int GetStunServerPort() const
    { return stun_server_.port_;}

    virtual void SetRelayServerHost(const std::string& val)
    { relay_server_udp_.host_ = val; 
      relay_server_tcp_.host_ = val; 
      relay_server_ssl_.host_ = val; }
    virtual std::string GetRelayServerHost() const
    { return relay_server_udp_.host_;}

    virtual void SetRelayServerPort(int val)
    { relay_server_udp_.port_ = val; 
      relay_server_tcp_.port_ = val; 
      relay_server_ssl_.port_ = val; }
    virtual int GetRelayServerPort() const
    { return relay_server_udp_.port_;}

    virtual void SetRelayUDPServerHost(const std::string& val)
    { relay_server_udp_.host_ = val; }
    virtual std::string GetRelayUDPServerHost() const
    { return relay_server_udp_.host_;}

    virtual void SetRelayUDPServerPort(int val)
    { relay_server_udp_.port_ = val; }
    virtual int GetRelayUDPServerPort() const
    { return relay_server_udp_.port_;}

    virtual void SetRelayTCPServerHost(const std::string& val)
    { relay_server_tcp_.host_ = val; }
    virtual std::string GetRelayTCPServerHost() const
    { return relay_server_tcp_.host_;}

    virtual void SetRelayTCPServerPort(int val)
    { relay_server_tcp_.port_ = val; }
    virtual int GetRelayTCPServerPort() const
    { return relay_server_tcp_.port_;}

    virtual void SetRelaySSLServerHost(const std::string& val)
    { relay_server_ssl_.host_ = val; }
    virtual std::string GetRelaySSLServerHost() const
    { return relay_server_ssl_.host_;}

    virtual void SetRelaySSLServerPort(int val)
    { relay_server_ssl_.port_ = val; }
    virtual int GetRelaySSLServerPort() const
    { return relay_server_ssl_.port_;}

    virtual void SetUseAlternateServerAddresses(bool val = true)
    { useAlternateServerAddresses_ = val; }
    virtual bool GetUseAlternateServerAddresses() const
    { return useAlternateServerAddresses_; }

    virtual void SetUseNumericServerAddresses(bool val = true)
    { useNumericServerAddresses_ = val; }
    virtual bool GetUseNumericServerAddresses() const
    { return useNumericServerAddresses_; }

    virtual void SetUseRelayServer(bool val = true);
    virtual bool GetUseRelayServer() const;

    virtual void SetVideoCaptureDevice(const std::string& val)
    { videoCaptureDevice_ = val; }
    virtual std::string GetVideoCaptureDevice() const
    { return videoCaptureDevice_; }

protected:
    static std::string GetEnvVarOrDefault
    (const char* env_var_name, const char* default_value);
    static std::string GetWebRtcVideoString();
    static std::string GetDefaultServerName();
    static std::string GetDefaultPeerName();
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONDUCTOR_HPP 
