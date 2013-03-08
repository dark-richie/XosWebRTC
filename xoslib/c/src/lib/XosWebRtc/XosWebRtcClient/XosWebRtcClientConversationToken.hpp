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
///   File: XosWebRtcClientConversationToken.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONVERSATIONTOKEN_HPP
#define _XOSWEBRTCCLIENTCONVERSATIONTOKEN_HPP

#include "XosWebRtcClientConversationTokenInterface.hpp"
#include "XosInstanceBase.hpp"

#define XOS_DEFAULT_WEBRTC_CLIENT_CONVERSATION_TOKEN_ALLOW_NON_SEPARATE_FIELDS true

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosInstanceBase XosWebRtcClientConversationTokenExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConversationToken
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
class c_INSTANCE_CLASS XosWebRtcClientConversationToken
: virtual public XosWebRtcClientConversationTokenImplement,
  public XosWebRtcClientConversationTokenExtend
{
public:
    typedef XosWebRtcClientConversationTokenImplement Implements;
    typedef XosWebRtcClientConversationTokenExtend Extends;

    class c_INSTANCE_CLASS Fields;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConversationToken
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConversationToken(const char* peerName)
    :  m_allowNonSeparateFields
       (XOS_DEFAULT_WEBRTC_CLIENT_CONVERSATION_TOKEN_ALLOW_NON_SEPARATE_FIELDS)
    {
        if ((peerName)) m_peerName = peerName;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConversationToken
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConversationToken()
    :  m_allowNonSeparateFields
       (XOS_DEFAULT_WEBRTC_CLIENT_CONVERSATION_TOKEN_ALLOW_NON_SEPARATE_FIELDS)
    {
    }
    virtual ~XosWebRtcClientConversationToken()
    {
    }

    virtual bool Make(std::string& name);
    virtual bool CheckIsValid(const std::string& name);

    virtual void Clear()
    {
        m_peerName.clear();
    }

    virtual void SetPeerName(const char* chars)
    {
        if ((chars))
        {
            Clear();
            m_peerName.assign(chars);
        }
    }
    virtual const char* GetPeerName() const
    {
        const char* chars = 0;
        chars = m_peerName.c_str();
        return chars;
    }

    virtual bool CombineFields
    (std::string& name, const Fields& fields);

    virtual bool SeparateFields
    (Fields& fields, const std::string& name);

    virtual void PrintFields
    (std::string& text, const Fields& fields);

protected:
    bool m_allowNonSeparateFields;
    std::string m_peerName;
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONVERSATIONTOKEN_HPP 
