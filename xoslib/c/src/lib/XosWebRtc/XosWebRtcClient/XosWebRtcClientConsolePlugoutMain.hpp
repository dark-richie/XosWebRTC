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
///   File: XosWebRtcClientConsolePlugoutMain.hpp
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAIN_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAIN_HPP

#include "XosWebRtcClientConsolePlugoutWindowPeer.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosOptMain.hpp"
#include "XosString.hpp"

#if defined(MACOSX) 
// Mac OSX 
#include <Cocoa/Cocoa.h>
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientImageObserver
///
/// Author: $author$
///   Date: 12/31/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientImageObserver
: virtual public XosWebRtcClientImageObserverInterface
{
public:
    XosWebRtcClientImageInterface& m_image;

    XosWebRtcClientImageObserver
    (XosWebRtcClientImageInterface& image)
    : m_image(image)
    {
    }
    virtual bool InvalidateWindow
    (bool eraseBackground = true) 
    { 
        uint8_t* image;
        int imageWidth, imageHeight, imageFormat;

        if ((image = m_image.GetRemoteImage
            (imageWidth, imageHeight, imageFormat)))
            image = 0;

        if ((image = m_image.GetLocalImage
            (imageWidth, imageHeight, imageFormat)))
            image = 0;
        return true; 
    }
};
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugoutMainImplement
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePlugoutMainImplement
: virtual public XosOptMainImplement,
  virtual public XosWebRtcClientImageInterface
{
public:
};
typedef XosOptMain XosWebRtcClientConsolePlugoutMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePlugoutMain
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePlugoutMain
: virtual public XosWebRtcClientConsolePlugoutMainImplement,
  public XosWebRtcClientConsolePlugoutMainExtend
{
public:
    typedef XosWebRtcClientConsolePlugoutMainExtend Extends;

    std::string m_serverName;
    int m_serverPort;

    XosWebRtcClientConsolePlugoutWindowPeer m_mainWindow;
    XosWebRtcClientImageObserver m_imageObserver;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePlugoutMain
    ///
    ///       Author: $author$
    ///         Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePlugoutMain()
    : m_imageObserver(*this)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientConsolePlugoutMain
    ///
    ///      Author: $author$
    ///        Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientConsolePlugoutMain()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Run
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual int Run
    (int argc, char**argv, char**env)
    {
        int err = 0;

#if defined(MACOSX) 
// Mac OSX 
        NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
        NSApplication* app = [NSApplication sharedApplication];
        XOS_DBT(("() NSAutoreleasePool* pool = %p\n", pool));
        [NSRunLoop currentRunLoop];
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

        RegisterImageObserver(&m_imageObserver);

        if ((m_mainWindow.Open())) {
            m_mainWindow.ConnectToServer(m_serverName, m_serverPort);
#if defined(WINDOWS)
            MSG msg;
            for (bool done=false; !done; ) {
                if (!(done = !(GetMessage(&msg, 0, 0, 0)))) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
#else // defined(WINDOWS)
#if defined(MACOSX) 
// Mac OSX 
            if ((app))
                [app run];
#else // defined(MACOSX) 
// Otherwise 
            for (bool done=false; !done; ) {
                XOS_DBT(("() sleep(1)...\n"));
                sleep(1);
                XOS_DBT(("() ...sleep(1)\n"));
            }
#endif // defined(MACOSX) 
#endif // defined(WINDOWS)
            m_mainWindow.Close();
        }
        UnregisterImageObserver(&m_imageObserver);

#if defined(MACOSX) 
// Mac OSX 
        [pool release];
#else // defined(MACOSX) 
// Otherwise 
#endif // defined(MACOSX) 

        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: ImageInterfaceDelegated
    ///
    ///    Author: $author$
    ///      Date: 12/29/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientImageInterface* ImageInterfaceDelegated() const {
        return (XosWebRtcClientImageInterface*)(&m_mainWindow);
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

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGOUTMAIN_HPP 
        

