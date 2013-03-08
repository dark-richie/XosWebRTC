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
///   File: XosWebRtcClientPluginInterface.hpp
///
/// Author: $author$
///   Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTPLUGININTERFACE_HPP
#define _XOSWEBRTCCLIENTPLUGININTERFACE_HPP

#include "XosWebRtcClientFBPluginInterface.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientPluginInterfaceImplement
///
///  Author: $author$
///    Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginInterface
XosWebRtcClientPluginInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientPluginInterface
///
/// Author: $author$
///   Date: 12/9/2012
///////////////////////////////////////////////////////////////////////
class _INTERFACE_CLASS XosWebRtcClientPluginInterface
: virtual public XosWebRtcClientPluginInterfaceImplement
{
public:
    typedef XosWebRtcClientPluginInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        return false;
    }
    virtual bool ConnectToServer() {
        return false;
    }
    virtual bool DisconnectFromServer() { 
        return false; 
    }
    virtual void SetServerName(const std::string& serverName) { 
    }
    virtual void SetServerPort(int serverPort) {
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        return false;
    }
    virtual bool ConnectToPeer(int peerId) {
        return false;
    }
    virtual bool ConnectToPeer() {
        return false;
    }
    virtual bool DisconnectFromPeer() { 
        return false; 
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
    }
    virtual bool GetAutoConnectToPeerOn() const {
        return false; 
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
    }
    virtual bool GetAutoConnectToPeerAfterOn() const {
        return false; 
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTPLUGININTERFACE_HPP 
