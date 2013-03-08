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
///   File: XosWebRtcClientConnectorPair.hpp
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONNECTORPAIR_HPP
#define _XOSWEBRTCCLIENTCONNECTORPAIR_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWebRtcClientConnection.hpp"
#include "XosWebRtcClientConductor.hpp"
#include "XosWebRtcClientTrace.hpp"
#include "XosWebRtcClientVideoCodec.hpp"
#include "XosWebRtcClientVideoCodecMode.hpp"

#define XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE \
    XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA

#define XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE

#define XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILENAME \
    XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME

#define XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILEDIR \
    XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR

#define XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_FILEENV \
    XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV


#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientConnectorPairImplement
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosInterfaceBase
XosWebRtcClientConnectorPairImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientConnectorPairExtend
///
///  Author: $author$
///    Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosWebRtcClientConnectorPairExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConnectorPair
///
/// Author: $author$
///   Date: 4/4/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConnectorPair
: virtual public XosWebRtcClientConnectorPairImplement,
  public XosWebRtcClientConnectorPairExtend
{
public:
    typedef XosWebRtcClientConnectorPairImplement Implements;
    typedef XosWebRtcClientConnectorPairExtend Extends;

    XosWebRtcClientBaseWindow& m_userInterface;

    XosWebRtcClientConnection m_connection;

    XosWebRtcClientVideoCodecMode m_videoServiceVideoCodecMode;
    XosWebRtcClientVideoCodec m_videoServiceVideoCodec;

    std::string m_webrtcClientTraceFileName;
    XosWebRtcClientTraceLevel m_webrtcClientTraceLevels;
    XosWebRtcClientTrace m_webrtcClientTrace;

    XosWebRtcClientConductor m_conductor;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConnectorPair
    ///
    ///       Author: $author$
    ///         Date: 1/2/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConnectorPair
    (XosWebRtcClientBaseWindow& userInterface,
     const std::string& webrtcClientTraceFileName,
     XosWebRtcClientTraceLevel webrtcClientTraceLevels,
     XosWebRtcClientVideoCodecMode videoServiceVideoCodecMode 
     = XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE,
     bool useAlternateServerAddresses 
     = XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES)
    : m_userInterface(userInterface),

      m_videoServiceVideoCodecMode(videoServiceVideoCodecMode),
      m_videoServiceVideoCodec(videoServiceVideoCodecMode),

      m_webrtcClientTraceFileName(webrtcClientTraceFileName),
      m_webrtcClientTraceLevels(webrtcClientTraceLevels),
      m_webrtcClientTrace(m_webrtcClientTraceFileName, webrtcClientTraceLevels),

      m_conductor
      (m_videoServiceVideoCodec, m_webrtcClientTrace, 
       &m_connection, &m_userInterface, useAlternateServerAddresses)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConnectorPair
    ///
    ///       Author: $author$
    ///         Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConnectorPair
    (XosWebRtcClientBaseWindow& userInterface,
     const std::string& webrtcClientTraceFileName,
     XosWebRtcClientVideoCodecMode videoServiceVideoCodecMode 
     = XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE,
     bool useAlternateServerAddresses 
     = XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
     XosWebRtcClientTraceLevel webrtcClientTraceLevels
     = XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS)
    : m_userInterface(userInterface),

      m_videoServiceVideoCodecMode(videoServiceVideoCodecMode),
      m_videoServiceVideoCodec(videoServiceVideoCodecMode),

      m_webrtcClientTraceFileName(webrtcClientTraceFileName),
      m_webrtcClientTraceLevels(webrtcClientTraceLevels),
      m_webrtcClientTrace(m_webrtcClientTraceFileName, webrtcClientTraceLevels),

      m_conductor
      (m_videoServiceVideoCodec, m_webrtcClientTrace, 
       &m_connection, &m_userInterface, useAlternateServerAddresses)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConnectorPair
    ///
    ///       Author: $author$
    ///         Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConnectorPair
    (XosWebRtcClientBaseWindow& userInterface,
     XosWebRtcClientVideoCodecMode videoServiceVideoCodecMode 
     = XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE,
     const char* webrtcClientTraceFileName
     = XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME,
     bool useAlternateServerAddresses 
     = XOSPEERCONNECTIONCONDUCTOR_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
     XosWebRtcClientTraceLevel webrtcClientTraceLevels
     = XOSWEBRTCCLIENT_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS)
    : m_userInterface(userInterface),

      m_videoServiceVideoCodecMode(videoServiceVideoCodecMode),
      m_videoServiceVideoCodec(videoServiceVideoCodecMode),

      m_webrtcClientTraceFileName(webrtcClientTraceFileName),
      m_webrtcClientTraceLevels(webrtcClientTraceLevels),
      m_webrtcClientTrace(m_webrtcClientTraceFileName, webrtcClientTraceLevels),

      m_conductor
      (m_videoServiceVideoCodec, m_webrtcClientTrace, 
       &m_connection, &m_userInterface, useAlternateServerAddresses)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientConnectorPair
    ///
    ///      Author: $author$
    ///        Date: 4/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientConnectorPair()
    {
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONNECTORPAIR_HPP 
        

