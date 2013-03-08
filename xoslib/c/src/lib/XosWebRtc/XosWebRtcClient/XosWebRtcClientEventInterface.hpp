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
///   File: XosWebRtcClientEventInterface.hpp
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTEVENTINTERFACE_HPP
#define _XOSWEBRTCCLIENTEVENTINTERFACE_HPP

#include "XosInterfaceBase.hpp"
#include "XosString.hpp"
#include "XosDebug.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientEventObserverInterface
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientEventObserverInterface
{
public:
    ///////////////////////////////////////////////////////////////////////
    // Change State
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToConnectToServer();
        else
        OnChangeState("ConnectToServer"); 
    }
    virtual void OnChangeStateToListPeers() { 
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToListPeers();
        else
        OnChangeState("ListPeers"); 
    }
    virtual void OnChangeStateToStreaming() { 
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToStreaming();
        else
        OnChangeState("Streaming"); 
    }
    virtual void OnChangeState(const std::string& toStateName) { 
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeState(toStateName);
        else {
        std::string eventName = "ChangeState to ";
        eventName += toStateName;
        OnEvent(eventName); 
        }
    }
    ///////////////////////////////////////////////////////////////////////
    // Server Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnFailedToConnectToServer(const std::string& server) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnFailedToConnectToServer(server);
        else
        OnEvent("FailedToConnectToServer"); 
    }
    virtual void OnConnectedToServer(int id, const std::string& name) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnConnectedToServer(id, name);
        else
        OnEvent("ConnectedToServer"); 
    }
    virtual void OnDisconnectedFromServer() {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnDisconnectedFromServer();
        else
        OnEvent("DisconnectedFromServer"); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Peer Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnPeerConnectedToServer(int id, const std::string& name) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnPeerConnectedToServer(id, name);
        else
        OnEvent("PeerConnectedToServer"); 
    }
    virtual void OnPeerDisconnectedFromServer(int id) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnPeerDisconnectedFromServer(id);
        else
        OnEvent("PeerDisconnectedFromServer"); 
    }
    virtual void OnDisconnectedFromPeer(int id) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnDisconnectedFromPeer(id);
        else
        OnEvent("DisconnectedFromPeer"); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Event
    ///////////////////////////////////////////////////////////////////////
    virtual void OnEvent(const std::string& eventName) {
        XosWebRtcClientEventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnEvent(eventName);
    }
    ///////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientEventObserverInterface* 
    EventObserverInterfaceDelegated() const {
        return 0;
    }
};
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientEventInterface
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientEventInterface
{
public:
    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        XosWebRtcClientEventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        XosWebRtcClientEventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->OnRButtonUp();
    }
    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterEventObserver
    (XosWebRtcClientEventObserverInterface* observer) {
        XosWebRtcClientEventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->RegisterEventObserver(observer);
    }
    virtual void UnregisterEventObserver
    (XosWebRtcClientEventObserverInterface* observer) {
        XosWebRtcClientEventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->UnregisterEventObserver(observer);
    }
    virtual XosWebRtcClientEventInterface* EventInterfaceDelegated() const {
        return 0;
    }
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTEVENTINTERFACE_HPP 
