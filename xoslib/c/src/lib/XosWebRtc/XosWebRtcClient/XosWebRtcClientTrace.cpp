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
///   File: XosWebRtcClientTrace.cpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientTraceImplemented.hpp"
#include "XosWebRtcClientTrace.hpp"
#include <sstream>
#include <string.h>
#include <time.h>

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientTrace
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientTrace::XosWebRtcClientTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientTrace::XosWebRtcClientTrace
(XosOStreamInterface& xosOStream,
 XosWebRtcClientTraceLevel traceLevelsFilter)
: m_implemented(0)
{
    XosError error;
    if ((error = Init(xosOStream, traceLevelsFilter)))
        throw (error);
}
///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientTrace::XosWebRtcClientTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientTrace::XosWebRtcClientTrace
(const std::string& traceFileName,
 XosWebRtcClientTraceLevel traceLevelsFilter)
: m_implemented(0)
{
    XosError error;
    if ((error = Init(traceFileName, traceLevelsFilter)))
        throw (error);
}
///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientTrace::XosWebRtcClientTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientTrace::XosWebRtcClientTrace()
: m_implemented(0)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientTrace::~XosWebRtcClientTrace
///
///       Author: $author$
///         Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientTrace::~XosWebRtcClientTrace()
{
    XosError error;
    if ((m_implemented))
    if ((error  = Finish()))
        throw (error);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientTrace::Init
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientTrace::Init
(XosOStreamInterface& xosOStream,
 XosWebRtcClientTraceLevel traceLevelsFilter)
{
    XosError error = XOS_ERROR_FAILED;
    try {
    if ((m_implemented = new XosWebRtcClientTraceImplemented
        (xosOStream, traceLevelsFilter)))
        error = XOS_ERROR_NONE;
    } catch(XosError caught) {
        error = caught;
    }
    return error;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientTrace::Init
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientTrace::Init
(const std::string& traceFileName,
 XosWebRtcClientTraceLevel traceLevelsFilter)
{
    XosError error = XOS_ERROR_FAILED;
    const char* pathSeparator = 0;
    const char* traceFileNameChars = 0;
    std::string traceFileNameBase(traceFileName);
    std::string traceFileNameTime;
    std::string traceFileNameExt;
    std::string traceFileNamePath;
    std::stringstream s;
    struct tm* tm;
    time_t t;

    //
    // Separate file name and extension
    //
    if ((traceFileNameChars = traceFileName.c_str()))
        pathSeparator = strrchr(traceFileNameChars, '.');

    if ((pathSeparator))
    {
        // name before '.'
        traceFileNameBase.assign(traceFileNameChars, (pathSeparator-traceFileNameChars));
        // extension including '.'
        traceFileNameExt.assign(pathSeparator);
    }

    //
    // Generate time string to make file name unique to second
    //
    time(&t);
    if ((tm = localtime(&t)))
    {
        s << '-';
        s << (tm->tm_year+1900);
        if (10 > (tm->tm_mon+1)) s << 0;
        s << (tm->tm_mon+1);
        if (10 > (tm->tm_mday)) s << 0;
        s << (tm->tm_mday);
        s << '-';
        if (10 > (tm->tm_hour)) s << 0;
        s << (tm->tm_hour);
        if (10 > (tm->tm_min)) s << 0;
        s << (tm->tm_min);
        if (10 > (tm->tm_sec)) s << 0;
        s << (tm->tm_sec);

        traceFileNameTime = s.str();
    }

    //
    // Generate unique filename
    //
    traceFileNamePath = traceFileNameBase;
    traceFileNamePath += traceFileNameTime;
    traceFileNamePath += traceFileNameExt;

    try {
    if ((m_implemented = new XosWebRtcClientTraceImplemented
        (traceFileNamePath, traceLevelsFilter)))
        error = XOS_ERROR_NONE;
    } catch(XosError caught) {
        error = caught;
    }
    return error;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientTrace::Finish
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosError XosWebRtcClientTrace::Finish()
{
    XosError error = XOS_ERROR_NONE;

    if ((m_implemented))
    {
        try {
            delete m_implemented;
        } catch (XosError caught) {
            error = caught;
        }
        m_implemented = 0;
    }
    return error;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
