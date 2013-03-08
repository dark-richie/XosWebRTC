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
///   File: XosWebRtcClientLibJingleOStream.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTLIBJINGLEOSTREAM_HPP
#define _XOSWEBRTCCLIENTLIBJINGLEOSTREAM_HPP

#include "talk/base/stream.h"
#include "XosOStreamInterface.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientLibJingleOStreamExtend
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef talk_base::StreamInterface
XosWebRtcClientLibJingleOStreamExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientLibJingleOStream
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS XosWebRtcClientLibJingleOStream
: //virtual public XosWebRtcClientLibJingleOStreamImplement,
  public XosWebRtcClientLibJingleOStreamExtend
{
public:
    //typedef XosWebRtcClientLibJingleOStreamImplement Implements;
    typedef XosWebRtcClientLibJingleOStreamExtend Extends;

    typedef talk_base::Thread Thread;
    typedef talk_base::StreamState StreamState;
    typedef talk_base::StreamResult StreamResult;
    typedef talk_base::StreamEvent StreamEvent;

    XosOStreamInterface* m_xosOStream;
    StreamState m_state;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientLibJingleOStream
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientLibJingleOStream
    (XosOStreamInterface* xosOStream=0)
    : m_xosOStream(xosOStream),
      m_state(talk_base::SS_CLOSED)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientLibJingleOStream
    ///
    ///      Author: $author$
    ///        Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientLibJingleOStream()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Read
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual StreamResult Read
    (void* buffer, size_t buffer_len,
     size_t* read, int* error)
    { 
        StreamResult result = talk_base::SR_ERROR; 
        return result; 
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Write
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual StreamResult Write
    (const void* data, size_t data_len,
     size_t* written, int* error)
    { 
        StreamResult result = talk_base::SR_ERROR; 
        ssize_t count;
        if ((m_xosOStream))
        if (data_len == (count = m_xosOStream->Write((const char*)(data), data_len)))
            result = talk_base::SR_SUCCESS;
        return result; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Open
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(XosOStreamInterface* xosOStream)
    {
        if ((m_xosOStream = xosOStream))
        {
            m_state = talk_base::SS_OPEN;
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Close
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void Close()
    {
        m_xosOStream = 0;
        m_state = talk_base::SS_CLOSED;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetState
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual StreamState GetState() const
    { 
        return m_state; 
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTLIBJINGLEOSTREAM_HPP 
        

