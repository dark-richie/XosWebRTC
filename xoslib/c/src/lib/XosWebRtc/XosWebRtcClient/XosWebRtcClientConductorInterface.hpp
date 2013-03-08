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
///   File: XosWebRtcClientConductorInterface.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONDUCTORINTERFACE_HPP
#define _XOSWEBRTCCLIENTCONDUCTORINTERFACE_HPP

#include "XosWebRtcClientPortServerOptionsInterface.hpp"
#include "XosWebRtcClientAudioVideoOptionsInterface.hpp"
#include "XosWebRtcClientAudioOptionsInterface.hpp"
#include "XosWebRtcClientVideoOptionsInterface.hpp"
#include "XosInterfaceBase.hpp"
#include "XosString.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConductorInterfaceImplement
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class _IMPLEMENT_CLASS XosWebRtcClientConductorInterfaceImplement
: virtual public XosWebRtcClientAudioVideoOptionsInterface,
  virtual public XosWebRtcClientPortServerOptionsInterface
{
public:
    typedef XosWebRtcClientAudioOptionsInterface AudioImplements;
    typedef XosWebRtcClientVideoOptionsInterface VideoImplements;
    typedef XosWebRtcClientAudioVideoOptionsInterface AudioVideoImplements;
    typedef XosWebRtcClientPortServerOptionsInterface Implements;
};
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConductorInterface
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _INTERFACE_CLASS XosWebRtcClientConductorInterface
: virtual public XosWebRtcClientConductorInterfaceImplement
{
public:
    typedef XosWebRtcClientConductorInterfaceImplement Implements;

    virtual bool StartLogin(const std::string& server, int port) = 0;
    virtual void DisconnectFromServer(bool doClose=false) = 0;
    virtual void ConnectToPeer(int peer_id) = 0;
    virtual void DisconnectFromCurrentPeer() = 0;
    virtual void UIThreadCallback(int msg_id, void* data) = 0;
    virtual void Close() = 0;
    virtual bool SendMessageToPeer(const std::string& messageEnvelope) = 0;

    virtual void SetVideoCaptureDevice(const std::string& val) = 0;
    virtual std::string GetVideoCaptureDevice() const = 0;

    virtual void SetVideoCodecModeName(const std::string& toModeName) = 0;
    virtual std::string GetVideoCodecModeName() const = 0;

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight, int frameRate, int minBitrate) = 0;
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const = 0;

    virtual void SetAudioDeviceOptions
    (bool echoCancellation, bool noiseSupression, bool autoGainControl) = 0;
    virtual void GetAudioDeviceOptions
    (bool& echoCancellation, bool& noiseSupression, bool& autoGainControl) const = 0;

    virtual void SetPortServerHost(const std::string& val) = 0;
    virtual std::string GetPortServerHost() const = 0;

    virtual void SetStunServerHost(const std::string& val) = 0;
    virtual std::string GetStunServerHost() const = 0;

    virtual void SetStunServerPort(int val) = 0;
    virtual int GetStunServerPort() const = 0;

    virtual void SetRelayServerHost(const std::string& val) = 0;
    virtual std::string GetRelayServerHost() const = 0;

    virtual void SetRelayServerPort(int val) = 0;
    virtual int GetRelayServerPort() const = 0;

    virtual void SetRelayUDPServerHost(const std::string& val) = 0;
    virtual std::string GetRelayUDPServerHost() const = 0;

    virtual void SetRelayUDPServerPort(int val) = 0;
    virtual int GetRelayUDPServerPort() const = 0;

    virtual void SetRelayTCPServerHost(const std::string& val) = 0;
    virtual std::string GetRelayTCPServerHost() const = 0;

    virtual void SetRelayTCPServerPort(int val) = 0;
    virtual int GetRelayTCPServerPort() const = 0;

    virtual void SetRelaySSLServerHost(const std::string& val) = 0;
    virtual std::string GetRelaySSLServerHost() const = 0;

    virtual void SetRelaySSLServerPort(int val) = 0;
    virtual int GetRelaySSLServerPort() const = 0;

    virtual void SetUseAlternateServerAddresses(bool val = true) = 0;
    virtual bool GetUseAlternateServerAddresses() const = 0;

    virtual void SetUseNumericServerAddresses(bool val = true) = 0;
    virtual bool GetUseNumericServerAddresses() const = 0;

    virtual void SetUseRelayServer(bool val = true) = 0;
    virtual bool GetUseRelayServer() const = 0;
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONDUCTORINTERFACE_HPP 
        

