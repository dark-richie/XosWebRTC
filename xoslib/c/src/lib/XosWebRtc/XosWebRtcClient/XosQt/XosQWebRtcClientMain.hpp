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
///   File: XosQWebRtcClientMain.hpp
///
/// Author: $author$
///   Date: 2/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSQWEBRTCCLIENTMAIN_HPP
#define _XOSQWEBRTCCLIENTMAIN_HPP

#include "XosQWebRtcClientMainWindow.hpp"
#include "XosQWindowMain.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosOptMainImplement XosQWebRtcClientMainImplement;
typedef XosQWindowMain XosQWebRtcClientMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosQWebRtcClientMain
///
/// Author: $author$
///   Date: 2/3/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosQWebRtcClientMain
: virtual public XosQWebRtcClientMainImplement,
  public XosQWebRtcClientMainExtend
{
public:
    typedef XosQWebRtcClientMainImplement Implements;
    typedef XosQWebRtcClientMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosQWebRtcClientMain
    ///
    ///       Author: $author$
    ///         Date: 2/3/2013
    ///////////////////////////////////////////////////////////////////////
    XosQWebRtcClientMain()
    : m_mainWindow(0)
    {
    }
    virtual ~XosQWebRtcClientMain()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // main window
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* CreateMainWindow
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        if ((m_mainWindow = new XosQWebRtcClientMainWindow())) {
            if (!(m_mainWindow->OnWindowOpen())) {
                delete m_mainWindow;
                m_mainWindow = 0;
            }
        }
        return m_mainWindow;
    }
    virtual bool DestroyMainWindow
    (QMainWindow* mainWindow, QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        bool isSuccess = false;
        if ((mainWindow) && (mainWindow == m_mainWindow)) {
            m_mainWindow->OnWindowClose();
            delete m_mainWindow;
            m_mainWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }

protected:
    XosQWebRtcClientMainWindow* m_mainWindow;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSQWEBRTCCLIENTMAIN_HPP 
