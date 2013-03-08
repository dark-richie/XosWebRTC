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
///   File: XosWebRtcClientWebRtcTrace.cpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientWebRtcTrace.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientWebRtcTrace
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace
(XosOStreamInterface& xosOStream,
 XosWebRtcClientTraceLevel traceLevelsFilter)
: m_isInitialized(false),
  m_xosOStream(0)
{
    XosError error;
    if ((error = Init(xosOStream, traceLevelsFilter)))
        throw(error);
}
///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace
(const std::string& traceFileName,
 XosWebRtcClientTraceLevel traceLevelsFilter)
 : m_isInitialized(false),
   m_xosOStream(0)
{
    XosError error;
    if ((error = Init(traceFileName, traceLevelsFilter)))
        throw(error);
}
///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientWebRtcTrace::XosWebRtcClientWebRtcTrace()
: m_isInitialized(false),
  m_xosOStream(0)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientWebRtcTrace::~XosWebRtcClientWebRtcTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientWebRtcTrace::~XosWebRtcClientWebRtcTrace()
{
    XosError error;
    if ((m_isInitialized))
    if ((error = Finish()))
        throw (error);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientWebRtcTrace::Init
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientWebRtcTrace::Init
(XosOStreamInterface& xosOStream,
 XosWebRtcClientTraceLevel traceLevelsFilter)
{
    WebRtc_UWord32 webrtcTraceLevelFilter = ToWebrtcTraceLevelFilter(traceLevelsFilter);
    XosError error = XOS_ERROR_FAILED;

    if ((m_isInitialized))
    if ((Finish()))
        return error;

    webrtc::Trace::CreateTrace();
    webrtc::Trace::SetTraceCallback(this);
    webrtc::Trace::SetLevelFilter(webrtcTraceLevelFilter);
    m_xosOStream = &xosOStream;
    m_isInitialized = true;
    error = XOS_ERROR_NONE;
    return error;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientWebRtcTrace::Init
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientWebRtcTrace::Init
(const std::string& traceFileName,
 XosWebRtcClientTraceLevel traceLevelsFilter)
{
    WebRtc_UWord32 webrtcTraceLevelFilter = ToWebrtcTraceLevelFilter(traceLevelsFilter);
    XosError error = XOS_ERROR_FAILED;

    if ((m_isInitialized))
    if ((Finish()))
        return error;

    webrtc::Trace::CreateTrace();
    webrtc::Trace::SetTraceFile(traceFileName.c_str());
    webrtc::Trace::SetLevelFilter(webrtcTraceLevelFilter);
    m_xosOStream = 0;
    m_isInitialized = true;
    error = XOS_ERROR_NONE;
    return error;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientWebRtcTrace::Finish
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientWebRtcTrace::Finish()
{
    XosError error = XOS_ERROR_FAILED;

    if ((m_isInitialized))
    {
        webrtc::Trace::ReturnTrace();
        m_isInitialized = false;
        m_xosOStream = 0;
        error = XOS_ERROR_NONE;
    }
    return error;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientWebRtcTrace::ToWebrtcTraceLevelFilter
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
WebRtc_UWord32 XosWebRtcClientWebRtcTrace::ToWebrtcTraceLevelFilter
(XosWebRtcClientTraceLevel traceLevelsFilter)
{
    WebRtc_UWord32 webrtcTraceLevelFilter = webrtc::kTraceNone;
    XosWebRtcClientTraceLevel level;

    if (0 > (traceLevelsFilter))
        webrtcTraceLevelFilter = webrtc::kTraceDefault;
    else
    {
        for (level = 1; 0 < level; level <<= 1)
        {
            switch (level & traceLevelsFilter)
            {
            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_ERROR:
                webrtcTraceLevelFilter |= (webrtc::kTraceError | webrtc::kTraceCritical);
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_WARNING:
                webrtcTraceLevelFilter |= (webrtc::kTraceWarning);
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_INFO:
                webrtcTraceLevelFilter |= (webrtc::kTraceStateInfo);
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_FUNC:
                webrtcTraceLevelFilter |= (webrtc::kTraceApiCall | webrtc::kTraceModuleCall);
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_DEBUG:
                webrtcTraceLevelFilter |= (webrtc::kTraceDebug | webrtc::kTraceInfo | webrtc::kTraceStateInfo);
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_TRACE:
                webrtcTraceLevelFilter |= (webrtc::kTraceAll);
                break;
            }
        }
    }
    return webrtcTraceLevelFilter;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientWebRtcTrace::Print
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientWebRtcTrace::Print
(const webrtc::TraceLevel level,
 const char *traceString, const int length)
{
    if ((m_xosOStream) && (traceString))
        m_xosOStream->Write(traceString, length);
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

        

