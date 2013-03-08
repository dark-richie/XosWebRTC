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
///   File: XosWebRtcClientTraceImplemented.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTTRACEIMPLEMENTED_HPP
#define _XOSWEBRTCCLIENTTRACEIMPLEMENTED_HPP

#include "XosWebRtcClientLibJingleTrace.hpp"
#include "XosWebRtcClientWebRtcTrace.hpp"
#include "XosWebRtcClientTrace.hpp"
#include "XosInstanceBase.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientTraceImplementedExtend
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef XosInstanceBase
XosWebRtcClientTraceImplementedExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientTraceImplemented
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class _INSTANCE_CLASS XosWebRtcClientTraceImplemented
: public XosWebRtcClientTraceImplementedExtend
{
public:
    typedef XosWebRtcClientTraceImplementedExtend Extends;

    bool m_traceIsCritical;

    std::string m_webRtcTraceFileExtension;
    std::string m_libJingleTraceFileExtension;

    XosWebRtcClientWebRtcTrace m_webRtcTrace;
    XosWebRtcClientLibJingleTrace m_libJingleTrace;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientTraceImplemented
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientTraceImplemented
    (XosOStreamInterface& xosOStream,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    : m_traceIsCritical
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_IS_CRITICAL),
      
      m_webRtcTraceFileExtension
      (XOSWEBRTCCLIENTWEBRTCTRACE_DEFAULT_FILE_EXTENSION),
     
      m_libJingleTraceFileExtension
      (XOSWEBRTCCLIENTLIBJINGLETRACE_DEFAULT_FILE_EXTENSION)
    {
        XosError error;
        if ((error = Init(xosOStream, traceLevelsFilter)))
            throw(error);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientTraceImplemented
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientTraceImplemented
    (const std::string& traceFileName,
     XosWebRtcClientTraceLevel traceLevelsFilter=XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_LEVELS)
    : m_traceIsCritical
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_IS_CRITICAL),
      
      m_webRtcTraceFileExtension
      (XOSWEBRTCCLIENTWEBRTCTRACE_DEFAULT_FILE_EXTENSION),

      m_libJingleTraceFileExtension
      (XOSWEBRTCCLIENTLIBJINGLETRACE_DEFAULT_FILE_EXTENSION)
    {
        XosError error;
        if ((error = Init(traceFileName, traceLevelsFilter)))
            throw(error);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientTraceImplemented
    ///
    ///      Author: $author$
    ///        Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientTraceImplemented()
    {
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
        XosError error = XOS_ERROR_NONE;
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
        XosError error = XOS_ERROR_NONE;
        const char* pathSeparator = 0;
        const char* traceFileNameChars = 0;
        std::string traceFileNameBase(traceFileName);
        std::string traceFileNameExt;
        std::string traceFileNamePath;

        if ((traceFileNameChars = traceFileName.c_str()))
            pathSeparator = strrchr(traceFileNameChars, '.');

        if ((pathSeparator))
        {
            traceFileNameBase.assign(traceFileNameChars, (pathSeparator-traceFileNameChars+1));
            traceFileNameExt.assign(pathSeparator);
        }
        else
        traceFileNameBase.append(".");

        traceFileNamePath = traceFileNameBase;
        traceFileNamePath += m_webRtcTraceFileExtension;
        traceFileNamePath += traceFileNameExt;

        if ((error = m_webRtcTrace.Init(traceFileNamePath, traceLevelsFilter)))
        {
            XOS_DBE(("() failed on m_webRtcTrace.Init(\"%s\",...)\n", traceFileNamePath.c_str()));
            if ((m_traceIsCritical))
                return error;
            error = XOS_ERROR_NONE;
        }

        traceFileNamePath = traceFileNameBase;
        traceFileNamePath += m_libJingleTraceFileExtension;
        traceFileNamePath += traceFileNameExt;

        if ((error = m_libJingleTrace.Init(traceFileNamePath, traceLevelsFilter)))
        {
            XOS_DBE(("() failed on m_libJingleTrace.Init(\"%s\",...)\n", traceFileNamePath.c_str()));
            if ((m_traceIsCritical))
                return error;
            error = XOS_ERROR_NONE;
        }

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
        return error;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTTRACEIMPLEMENTED_HPP 
        

