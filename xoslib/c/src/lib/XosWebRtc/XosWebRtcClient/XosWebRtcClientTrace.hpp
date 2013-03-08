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
///   File: XosWebRtcClientTrace.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTTRACE_HPP
#define _XOSWEBRTCCLIENTTRACE_HPP

#include "XosInstanceBase.hpp"
#include "XosOStreamInterface.hpp"
#include <string>


#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV \
    "APPDATA"

#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEPATH \
    "XosDevelopment/"

#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR \
    XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEPATH \
    "XosWebRtcClientTrace/logs"

#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME \
    "XosWebRtcClientTrace.log"

#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_WARNING

#define XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_IS_CRITICAL false

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///    Enum: XosWebRtcClientTraceLevel
///
///  Author: $author$
///    Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
typedef int XosWebRtcClientTraceLevel;
enum 
{
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_NONE = 0,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_ERROR = 0x1,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_WARNING = 0x2,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_INFO = 0x4,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_FUNC = 0x8,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_DEBUG = 0x10,
    XOS_WEBRTC_CLIENT_TRACE_LEVEL_TRACE = 0x20
};
enum 
{
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_NONE = 0,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_ERROR = 0x1,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_WARNING = 0x3,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_INFO = 0x7,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_FUNC = 0xF,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_DEBUG = 0x1F,
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE = 0x3F
};

class c_INSTANCE_CLASS XosWebRtcClientTraceImplemented;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientTraceExtend
///
///  Author: $author$
///    Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
typedef XosInstanceBase
XosWebRtcClientTraceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientTrace
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
class c_INSTANCE_CLASS XosWebRtcClientTrace
: //virtual public XosWebRtcClientTraceImplement,
  public XosWebRtcClientTraceExtend
{
public:
    //typedef XosWebRtcClientTraceImplement Implements;
    typedef XosWebRtcClientTraceExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientTrace
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientTrace
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientTrace
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientTrace();
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientTrace
    ///
    ///      Author: $author$
    ///        Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientTrace();
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Init
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Init
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Finish();

protected:
    XosWebRtcClientTraceImplemented* m_implemented;
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTTRACE_HPP 
