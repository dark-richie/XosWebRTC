///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
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
///   File: XosXWebRtcClientMain.hpp
///
/// Author: $author$
///   Date: 2/9/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTMAIN_HPP
#define _XOSXWEBRTCCLIENTMAIN_HPP

#include "XosXWebRtcClientMainWindow.hpp"
#include "XosXWindowMain.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosXWindowMainImplement XosXWebRtcClientMainImplement;
typedef XosXWindowMain XosXWebRtcClientMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXWebRtcClientMain
///
/// Author: $author$
///   Date: 2/9/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXWebRtcClientMain
: virtual public XosXWebRtcClientMainImplement,
  public XosXWebRtcClientMainExtend
{
public:
    typedef XosXWebRtcClientMainImplement Implements;
    typedef XosXWebRtcClientMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosXWebRtcClientMain
    ///
    ///       Author: $author$
    ///         Date: 2/9/2013
    ///////////////////////////////////////////////////////////////////////
    XosXWebRtcClientMain()
    : m_mainWindow(*this)
    {
    }
    virtual ~XosXWebRtcClientMain()
    {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Create/Destroy MainWindow
    ///////////////////////////////////////////////////////////////////////
    virtual XosXWindowInterface* CreateMainWindow
    (Display& xDisplay, Window xWindow, 
     int argc, char** argv, char** env)
    {
        XosXWindowInterface* mainWindow = 0;
        XosError error;
        XOS_DBI(("() ...\n"));
        if (!(error = m_mainWindow.CreateSimple
            (xDisplay, xWindow, 
             m_mainWindowX,m_mainWindowY, m_mainWindowWidth,m_mainWindowHeight, 
             m_mainWindowBorderWidth, m_mainWindowBorderColor, m_mainWindowBackgroundColor))) 
        {
            mainWindow = &m_mainWindow;
            m_mainWindow.OnWindowOpen();
        }
        return mainWindow;
    }
    virtual int DestroyMainWindow
    (XosXWindowInterface* mainWindow,
     int argc, char** argv, char** env)
    {
        int err = 1;
        XosError error;
        XOS_DBI(("() ...\n"));
        if ((mainWindow == &m_mainWindow))
        {
            m_mainWindow.OnWindowClose();
            if (!(error = m_defaultMainWindow.Destroy()))
                err = 0;
        }
        return err;
    }
    virtual Pixel GetMainWindowBackgroundColor() const {
        XOS_DBI(("() ...\n"));
        return WhiteColor();
    }

protected:
    XosXWebRtcClientMainWindow m_mainWindow;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTMAIN_HPP 
