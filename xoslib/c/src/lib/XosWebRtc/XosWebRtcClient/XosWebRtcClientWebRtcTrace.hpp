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
///   File: XosWebRtcClientWebRtcTrace.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTWEBRTCTRACE_HPP
#define _XOSWEBRTCCLIENTWEBRTCTRACE_HPP

#include "XosWebRtcClientTrace.hpp"
#include "system_wrappers/source/trace_impl.h"

#define XOSWEBRTCCLIENTWEBRTCTRACE_DEFAULT_FILE_EXTENSION "WebRtc"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientWebRtcTraceImplement
///
///  Author: $author$
///    Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
typedef webrtc::TraceCallback
XosWebRtcClientWebRtcTraceImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientWebRtcTraceExtend
///
///  Author: $author$
///    Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
typedef XosInstanceBase
XosWebRtcClientWebRtcTraceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientWebRtcTrace
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
class c_INSTANCE_CLASS XosWebRtcClientWebRtcTrace
: virtual public XosWebRtcClientWebRtcTraceImplement,
  public XosWebRtcClientWebRtcTraceExtend
{
public:
    typedef XosWebRtcClientWebRtcTraceImplement Implements;
    typedef XosWebRtcClientWebRtcTraceExtend Extends;

    bool m_isInitialized;
    XosOStreamInterface* m_xosOStream;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientWebRtcTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientWebRtcTrace
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientWebRtcTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientWebRtcTrace
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientWebRtcTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientWebRtcTrace();
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientWebRtcTrace
    ///
    ///      Author: $author$
    ///        Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientWebRtcTrace();

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosError Init
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosError Init
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosError Finish();

    ///////////////////////////////////////////////////////////////////////
    ///  Function: ToWebRtcTraceLevelFilter
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual WebRtc_UWord32 ToWebrtcTraceLevelFilter
    (XosWebRtcClientTraceLevel traceLevelsFilter);

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Print
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void Print
    (const webrtc::TraceLevel level, 
     const char *traceString, const int length);
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTWEBRTCTRACE_HPP 
