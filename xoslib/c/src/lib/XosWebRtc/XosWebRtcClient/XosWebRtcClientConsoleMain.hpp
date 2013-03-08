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
///   File: XosWebRtcClientConsoleMain.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEMAIN_HPP
#define _XOSWEBRTCCLIENTCONSOLEMAIN_HPP

#include "XosPlatform_build.hpp"

#if defined(MACOSX) 
// Mac OSX 
#include <Cocoa/Cocoa.h>
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

#include "XosWebRtcClientConsoleWindow.hpp"
#include "XosWebRtcClientConsoleWindowPeerImplement.hpp"
#include "XosOptMain.hpp"

#if defined(WINDOWS) 
// Windows 
#include "XosWinWebRtcClientSocketServer.hpp"
typedef XosWinWebRtcClientSocketServer
XosWebRtcClientConsoleMainSocketServer;
#else // defined(WINDOWS) 
// Unix 
#if defined(MACOSX) 
// Mac OSX 
#include "XosMacWebRtcClientSocketServer.hh"
typedef XosMacWebRtcClientSocketServer 
XosWebRtcClientConsoleMainSocketServer;
#else // defined(MACOSX) 
// Otherwise 
#include "XosWebRtcClientSocketServer.hpp"
typedef XosWebRtcClientSocketServer 
XosWebRtcClientConsoleMainSocketServer;
#endif // defined(MACOSX) 
#endif // defined(WINDOWS) 


#define XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_NAME "localhost"
#define XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_PORT 8888

#define XOSWEBRTCCLIENTMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES false
#define XOSWEBRTCCLIENTMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES true

#define XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE

#define XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE \
    XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientConsoleMainImplement
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef XosOptMainImplement
XosWebRtcClientConsoleMainImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientConsoleMainExtend
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef XosOptMain
XosWebRtcClientConsoleMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsoleMain
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsoleMain
: virtual public XosWebRtcClientConsoleMainImplement,
  public XosWebRtcClientConsoleMainExtend
{
public:
    typedef XosWebRtcClientConsoleMainImplement Implements;
    typedef XosWebRtcClientConsoleMainExtend Extends;

    std::string m_serverName;
    int m_serverPort;

    XosWebRtcClientVideoCodecMode m_webrtcVideoVideoCodecMode;
    XosWebRtcClientTraceLevel m_webrtcClientTraceLevels;
    std::string m_webrtcClientTraceFileName;
    std::string m_webrtcClientTraceFileDir;
    std::string m_webrtcClientTraceFileEnv;

    XosWebRtcClientConsoleMain()
    : m_serverName(XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWEBRTCCLIENTMAIN_DEFAULT_SERVER_PORT),
    
      m_webrtcVideoVideoCodecMode
      (XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE),

      m_webrtcClientTraceLevels
      (XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS),

      m_webrtcClientTraceFileName
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcClientTraceFileDir
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcClientTraceFileEnv
      (XOSWEBRTCCLIENTTRACE_DEFAULT_TRACE_FILEENV)
    {
    }
    virtual ~XosWebRtcClientConsoleMain()
    {
    }
    virtual int Run
    (int argc, char**argv, char**env)
    {
        XOS_DBT(("() in...\n"));

        int err = 0;

#if defined(MACOSX) 
// Mac OSX 
        NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
        XOS_DBT(("() NSAutoreleasePool* pool = %p\n", pool));
        [NSRunLoop currentRunLoop];
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

        XosWebRtcClientConsoleWindow peerWindow
        (m_serverName.c_str(), m_serverPort, true, true);
        XosWebRtcClientBaseWindowPeerImplement windowPeer(peerWindow);

        XosWebRtcClientConsoleMainSocketServer socketServer(peerWindow);

        std::string webrtcClientTraceFileName
        (peerWindow.GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));

        //XosWebRtcClientTraceLevel webrtcClientTraceLevels
        //= XOSWEBRTCCLIENTMAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS;

        if ((windowPeer.Open()))
        {
            XosWebRtcClientVideoCodec webrtcVideoVideoCodec(m_webrtcVideoVideoCodecMode);
            XosWebRtcClientTrace webrtcClientTrace
            (webrtcClientTraceFileName, m_webrtcClientTraceLevels);
            XosWebRtcClientConnection client;
            XosWebRtcClientConductor conductor
            (webrtcVideoVideoCodec, webrtcClientTrace, 
             &client, &peerWindow, 
             XOSWEBRTCCLIENTMAIN_DEFAULT_USE_ALTERNATE_SERVER_ADDRESSES,
             XOSWEBRTCCLIENTMAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);

            peerWindow.ConnectToServer(m_serverName, m_serverPort);
            //XosWebRtcClientConsoleMainSocketServer socketServer(peerWindow);
            socketServer.Run();
            windowPeer.Close();
        }

#if defined(MACOSX) 
// Mac OSX 
        [pool release];
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

        XOS_DBT(("() ...out\n"));
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: SetServerName
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual const char* SetServerName
    (const char* toChars)
    {
        const char* chars = 0;
        m_serverName.assign(toChars);
        chars = m_serverName.c_str();
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetServerName
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual const char* GetServerName() const
    {
        const char* chars = m_serverName.c_str();
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: SetServerPort
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int SetServerPort
    (const char* toChars)
    {
        XosString serverPort;
        serverPort.assign(toChars);
        serverPort >> m_serverPort;
        return m_serverPort;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetServerPort
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int GetServerPort() const
    {
        return m_serverPort;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: OnOption
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case 's':
            if ((optarg))
            if ((optarg[0]))
                SetServerName(optarg);
            break;
        case 'p':
            if ((optarg))
            if ((optarg[0]))
                SetServerPort(optarg);
            break;
            
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: OptionUsage
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case 's':
            optarg = "hostname";
            chars = "Server Name or IP";
            break;
        case 'p':
            optarg = "port";
            chars = "Server Port";
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Options
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = "s:p:d:h";
        static struct option optstruct[]= {
            {"server-name", e_MAIN_OPT_ARGUMENT_REQUIRED, 0, 's'},
            {"server-port", e_MAIN_OPT_ARGUMENT_REQUIRED, 0, 'p'},
            {"debug-levels", e_MAIN_OPT_ARGUMENT_REQUIRED, 0, 'd'},
            {"help", e_MAIN_OPT_ARGUMENT_NONE, 0, 'h'},
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEMAIN_HPP 
