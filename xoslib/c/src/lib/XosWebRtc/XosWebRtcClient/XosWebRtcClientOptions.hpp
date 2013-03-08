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
///   File: XosWebRtcClientOptions.hpp
///
/// Author: $author$
///   Date: 5/13/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTOPTIONS_HPP
#define _XOSWEBRTCCLIENTOPTIONS_HPP

#include "XosWebRtcClientPortServerOptionsInterface.hpp"
#include "XosWebRtcClientAudioVideoOptions.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientOptionsInterface
///
/// Author: $author$
///   Date: 5/13/2012
///////////////////////////////////////////////////////////////////////
class _INTERFACE_CLASS XosWebRtcClientOptionsInterface
: virtual public XosWebRtcClientAudioVideoOptionsInterface,
  virtual public XosWebRtcClientPortServerOptionsInterface
{
public:
    typedef XosWebRtcClientAudioVideoOptionsInterface AudioVideoOptionsImplements;
    typedef XosWebRtcClientPortServerOptionsInterface PortServerOptionsImplements;
};
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientOptionsImplement
///
/// Author: $author$
///   Date: 5/13/2012
///////////////////////////////////////////////////////////////////////
class _IMPLEMENT_CLASS XosWebRtcClientOptionsImplement
: virtual public XosWebRtcClientOptionsInterface,
  virtual public XosWebRtcClientAudioVideoOptionsImplement,
  virtual public XosWebRtcClientPortServerOptionsImplement
{
public:
    typedef XosWebRtcClientOptionsInterface Implements;
    typedef XosWebRtcClientAudioVideoOptionsImplement AudioVideoOptionsImplements;
    typedef XosWebRtcClientPortServerOptionsImplement PortServerOptionsImplements;
};
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientOptionsExtend
///
///  Author: $author$
///    Date: 5/13/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientAudioVideoOptions
XosWebRtcClientOptionsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientOptions
///
/// Author: $author$
///   Date: 5/13/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientOptions
: virtual public XosWebRtcClientOptionsImplement,
  public XosWebRtcClientOptionsExtend
{
public:
    typedef XosWebRtcClientOptionsImplement Implements;
    typedef XosWebRtcClientOptionsExtend Extends;

    XosWebRtcClientPortServerOptionsInterface* m_delegatedPortServerOptions;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientOptions
    ///
    ///       Author: $author$
    ///         Date: 5/13/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientOptions
    (XosWebRtcClientOptionsInterface* delegated=0)
    : Extends(delegated),
      m_delegatedPortServerOptions(delegated)
    {
    }

    virtual XosWebRtcClientPortServerOptionsInterface* DelegatePortServerOptions
    (XosWebRtcClientPortServerOptionsInterface* delegateTo)
    {
        m_delegatedPortServerOptions = delegateTo;
        return m_delegatedPortServerOptions;
    }
    virtual XosWebRtcClientPortServerOptionsInterface* DelegatedPortServerOptions() const
    {
        return m_delegatedPortServerOptions;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTOPTIONS_HPP 
        

