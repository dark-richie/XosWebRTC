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
///   File: XosWebRtcClientUserInterfaceImplement.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTUSERINTERFACEIMPLEMENT_HPP
#define _XOSWEBRTCCLIENTUSERINTERFACEIMPLEMENT_HPP

#include "XosWebRtcClientUserInterface.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientUserInterfaceImplement
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _IMPLEMENT_CLASS XosWebRtcClientUserInterfaceImplement
: virtual public XosWebRtcClientUserInterface
{
public:
    typedef XosWebRtcClientUserInterface Implements;

    virtual void RegisterObserver
    (XosWebRtcClientConductorInterface* callback) {}
    virtual void UnRegisterObserver() {}

    virtual bool IsWindow() { return false; }
    virtual void MessageBox
    (const char* caption, const char* text, bool is_error) {}

    virtual UI current_ui() = 0;

    virtual void SwitchToConnectUI() {}
    virtual void SwitchToPeerList(const Peers& peers) {}
    virtual void SwitchToStreamingUI() {}

    virtual cricket::VideoRenderer* local_renderer() { return 0; }
    virtual cricket::VideoRenderer* remote_renderer() { return 0; }

    virtual void QueueUIThreadCallback(int msg_id, void* data) {}

    virtual const std::string GetThisPeerName() { std::string name; return name; }
    virtual void SetThisPeerName(const std::string& name) { }

    virtual bool OnMessageFromPeer
    (int peer_id, const std::string& messageEnvelope) { OnEvent("MessageFromPeer"); return false; }
    virtual bool OnReceiveMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("ReceiveMessageFromPeer"); return false; }
    virtual void OnFailedToConnectToServer(const std::string& server) {OnEvent("FailedToConnectToServer"); }

    virtual void OnChangeStateToConnectToServer() { OnEvent("ChangeState to ConnectToServer"); }
    virtual void OnChangeStateToListPeers() { OnEvent("ChangeState to ListPeers"); }
    virtual void OnChangeStateToStreaming() { OnEvent("ChangeState to Streaming"); }
    virtual void OnChangeState(const std::string& toStateName) { 
        std::string eventName = "ChangeState to ";
        eventName += toStateName;
        OnEvent(eventName); }
    virtual void OnEvent(const std::string& eventName) {}

    virtual bool OnSignedIn(const Peers& peers) { OnEvent("SignedIn"); return false; }
    virtual bool OnDisconnected() { OnEvent("Disconnected"); return false; }

    virtual bool OnPeerConnected(int id, const std::string& name) { OnEvent("PeerConnected"); return false; }
    virtual bool OnPeerDisconnected(int id) { OnEvent("PeerDisconnected"); return false; }
    virtual bool OnPeerConnectionClosed(int id) { OnEvent("PeerConnectionClosed"); return false; }

    virtual bool OnUnexpectedMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("UnexpectedMessageFromPeer"); return false; }
    virtual bool OnEmptyMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("EmptyMessageFromPeer"); return false; }
    virtual bool OnSignalingMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessageFromPeer"); return false; }
    virtual bool OnSignalingMessageFromUnconnectedPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessageFromUnconnectedPeer"); return false; }
    virtual bool OnSignalingMessageToPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessage"); return false; }
    virtual bool OnMessageSentToPeer(int err) { OnEvent("MessageSentToPeer"); return false; }

    virtual bool OnAddStream(const std::string& stream_id, bool video) { OnEvent("AddStream"); return false; }
    virtual bool OnRemoveStream(const std::string& stream_id, bool video) { OnEvent("RemoveStream"); return false; }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTUSERINTERFACEIMPLEMENT_HPP 
        

