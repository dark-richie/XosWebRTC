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
///   File: XosWebRtcClientLibJingleTrace.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTLIBJINGLETRACE_HPP
#define _XOSWEBRTCCLIENTLIBJINGLETRACE_HPP

#include "XosWebRtcClientLibJingleOStream.hpp"
#include "XosWebRtcClientTrace.hpp"

#define XOSWEBRTCCLIENTLIBJINGLETRACE_DEFAULT_FILE_EXTENSION "LibJingle"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientLibJingleTraceImplement
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef XosInterfaceBase
XosWebRtcClientLibJingleTraceImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientLibJingleTraceExtend
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef XosInstanceBase
XosWebRtcClientLibJingleTraceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientLibJingleTrace
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class c_INSTANCE_CLASS XosWebRtcClientLibJingleTrace
: virtual public XosWebRtcClientLibJingleTraceImplement,
  public XosWebRtcClientLibJingleTraceExtend
{
public:
    typedef XosWebRtcClientLibJingleTraceImplement Implements;
    typedef XosWebRtcClientLibJingleTraceExtend Extends;

    typedef talk_base::LoggingSeverity LoggingSeverity;
    typedef talk_base::FileStream FileStream;
    typedef talk_base::StreamState StreamState;

    XosWebRtcClientLibJingleOStream m_stream;
    FileStream m_fileStream;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientLibJingleTrace
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientLibJingleTrace
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    {
        XosError error;
        if ((error = Init(xosOStream, traceLevelsFilter)))
            throw(error);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientLibJingleTrace
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientLibJingleTrace
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    {
        XosError error;
        if ((error = Init(traceFileName, traceLevelsFilter)))
            throw(error);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientLibJingleTrace
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientLibJingleTrace()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientLibJingleTrace
    ///
    ///      Author: $author$
    ///        Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientLibJingleTrace()
    {
        XosError error;
        if ((error = Finish()))
            throw(error);
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Init
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    {
        XosError error = XOS_ERROR_FAILED;
        LoggingSeverity loggingSeverity = ToLoggingSeverity(traceLevelsFilter);
        if ((m_stream.Open(&xosOStream)))
        {
            talk_base::LogMessage::AddLogToStream(&m_stream, loggingSeverity);
            error = XOS_ERROR_NONE;
        }
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Init
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    {
        XosError error = XOS_ERROR_FAILED;
        LoggingSeverity loggingSeverity = ToLoggingSeverity(traceLevelsFilter);
        int err;
        if ((m_fileStream.Open(traceFileName, "w", &err)))
        if ((m_fileStream.DisableBuffering()))
        {
            talk_base::LogMessage::AddLogToStream(&m_fileStream, loggingSeverity);
            error = XOS_ERROR_NONE;
        }
        else
        m_fileStream.Close();
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Finish()
    {
        XosError error = XOS_ERROR_NONE;
        StreamState streamState;

        if (talk_base::SS_CLOSED != (streamState = m_stream.GetState()))
        {
            talk_base::LogMessage::RemoveLogToStream(&m_stream);
            m_stream.Close();
        }

        if (talk_base::SS_CLOSED != (streamState = m_fileStream.GetState()))
        {
            talk_base::LogMessage::RemoveLogToStream(&m_fileStream);
            m_fileStream.Close();
        }
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: ToLoggingSeverity
    ///
    ///    Author: $author$
    ///      Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual LoggingSeverity ToLoggingSeverity
    (XosWebRtcClientTraceLevel traceLevelsFilter) const
    {
        LoggingSeverity loggingSeverity = (LoggingSeverity)(talk_base::LS_ERROR+1);
        LoggingSeverity newLoggingSeverity;
        XosWebRtcClientTraceLevel level;

        for (level = 1; 0 < level; level <<= 1)
        {
            switch (level & traceLevelsFilter)
            {
            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_ERROR:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_ERROR))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_WARNING:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_WARNING))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_INFO:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_INFO))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_FUNC:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_INFO))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_DEBUG:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_VERBOSE))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_TRACE:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_SENSITIVE))
                    loggingSeverity = newLoggingSeverity;
                break;
            }
        }
        return loggingSeverity;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTLIBJINGLETRACE_HPP 
        

