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
///   File: XosWebRtcClientConversationInterface.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONVERSATIONINTERFACE_HPP
#define _XOSWEBRTCCLIENTCONVERSATIONINTERFACE_HPP

#include "XosInterfaceBase.hpp"
#include <string>

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConversationInterface
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class c_INTERFACE_CLASS XosWebRtcClientConversationInterface
{
public:
    ///////////////////////////////////////////////////////////////////////
    // connection
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer()
    { return false; }
    virtual bool DisconnectFromServer()
    { return false; }
    virtual bool ConnectToPeer()
    { return false; }
    virtual bool DisconnectFromPeer()
    { return false; }

    ///////////////////////////////////////////////////////////////////////
    // server
    ///////////////////////////////////////////////////////////////////////
    virtual void SetServerName(const char* toChars)
    { }
    virtual const char* GetServerName() const
    { const char* val=0; return val; }
    virtual void SetServerPort(int serverPort)
    { }
    virtual int GetServerPort() const
    { int val = -1; return val; }

    ///////////////////////////////////////////////////////////////////////
    // options
    ///////////////////////////////////////////////////////////////////////
    virtual void SetAutoConnectToPeerOn(bool isTrue=true)
    { }
    virtual bool GetAutoConnectToPeerOn() const
    { bool val=false; return val; }

    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true)
    { }
    virtual bool GetAutoConnectToPeerAfterOn() const
    { bool val=false; return val; }

    virtual void SetUseOpenGLRendererOn(bool isTrue=true)
    { }
    virtual bool GetUseOpenGLRendererOn() const
    { bool val=false; return val; }

    virtual void UseOpenGLRenderer()
    { SetUseOpenGLRendererOn(); }
    virtual void DontUseOpenGLRenderer()
    { SetUseOpenGLRendererOn(false); }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONVERSATIONINTERFACE_HPP 
