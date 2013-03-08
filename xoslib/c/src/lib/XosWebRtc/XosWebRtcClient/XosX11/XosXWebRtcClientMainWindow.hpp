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
///   File: XosXWebRtcClientMainWindow.hpp
///
/// Author: $author$
///   Date: 2/8/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTMAINWINDOW_HPP
#define _XOSXWEBRTCCLIENTMAINWINDOW_HPP

#include "XosWebRtcClientConsolePlugoutMainWindow.hpp"
#include "XosXWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosXWindowMain.hpp"
#include "XosXWindow.hpp"
#include "XosXEvent.hpp"
#include "XosXColor.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientConsolePlugoutMainWindowImplement
<XosXWindowImplement> 
XosXWebRtcClientMainWindowImplement;

typedef XosWebRtcClientConsolePlugoutMainWindow
<XosXWebRtcClientMainWindowImplement, XosXWindow> 
XosXWebRtcClientMainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXWebRtcClientMainWindow
///
/// Author: $author$
///   Date: 2/8/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXWebRtcClientMainWindow
: virtual public XosXWebRtcClientMainWindowImplement,
  public XosXWebRtcClientMainWindowExtend
{
public:
    typedef XosXWebRtcClientMainWindowImplement Implements;
    typedef XosXWebRtcClientMainWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosXWebRtcClientMainWindow
    ///
    ///       Author: $author$
    ///         Date: 2/8/2013
    ///////////////////////////////////////////////////////////////////////
    XosXWebRtcClientMainWindow(XosXWindowMain& windowMain)
    : m_windowMain(windowMain),
      m_useGLRenderer(false)
    {
    }
    virtual ~XosXWebRtcClientMainWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // On Window Open/Close
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpen()
    {
        bool success = false;
        if ((m_useGLRenderer = m_glRenderer.init(m_xDisplay, m_xWindow)))
            m_glRenderer.prepareOpenGL();
        if ((success = AllocateColors())) {
            if ((success = Extends::OnWindowOpen()))
                return success;
            FreeColors();
        }
        return success;
    }
    virtual bool OnWindowClose()
    {
        bool success = Extends::OnWindowClose();
        if (!(FreeColors())) 
            success = false;
        if ((m_useGLRenderer))
            m_glRenderer.finish();
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        //Invalidate();
        return true; 
    }
    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        XOS_DBI(("()...\n"));
        //m_bgColor.Attach(m_bgColorUnconnected.Attached());
        //InvalidateWindow();
        //EventImplements::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers() { 
        XOS_DBI(("()...\n"));
        //m_bgColor.Attach(m_bgColorConnected.Attached());
        //InvalidateWindow();
        //EventImplements::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming() {
        XOS_DBI(("()...\n"));
        //m_bgColor.Attach(m_bgColorStreaming.Attached());
        //InvalidateWindow();
        //EventImplements::OnChangeStateToStreaming();
    }
    virtual void OnFailedToConnectToServer(const std::string& server) {
        XOS_DBI(("(\"%s\")...\n", server.c_str()));
    }

    ///////////////////////////////////////////////////////////////////////
    // X11 events
    ///////////////////////////////////////////////////////////////////////
    virtual XosError OnButtonReleaseXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        XOS_DBI(("()...\n"));
        if ((xEvent.xbutton.button != Button1)) {
            if ((xEvent.xbutton.button != Button2)) {
            } else {
                OnRButtonUp();
            }
        } else {
            OnLButtonUp();
        }
        return error;
    }
    virtual XosError OnConfigureNotifyXEvent(const XEvent& xEvent) 
    {
        const XConfigureEvent& xConfigureEvent = (const XConfigureEvent&)(xEvent);
        XosError error = XOS_ERROR_NONE;
        XOS_DBI(("() width=%d height=%d ...\n", xConfigureEvent.width, xConfigureEvent.height));
        return error;
    }
    virtual XosError OnExposeXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    // Allocate/Free colors
    ///////////////////////////////////////////////////////////////////////
    virtual bool AllocateColors()
    {
        XosError error;
        Colormap xColormap;
        if ((xColormap = m_windowMain.GetColorMap()))
        if (!(error = m_bgColorUnconnected.AllocateRGB8
            (m_xDisplay, xColormap, 
             XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED,
             XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN,
             XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE))) {
            if (!(error = m_bgColorConnected.AllocateRGB8
                (m_xDisplay, xColormap, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED,
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN,
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE))) {
                 if (!(error = m_bgColorStreaming.AllocateRGB8
                     (m_xDisplay, xColormap, 
                      XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED,
                      XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN,
                      XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE)))
                     return true;
                 m_bgColorConnected.Free();
            }
            m_bgColorUnconnected.Free();
        }
        return false;
    }
    virtual bool FreeColors()
    {
        bool isSuccess = true;
        XosError error;
        if ((error = m_bgColorStreaming.Free())) 
            isSuccess = false;
        if ((error = m_bgColorConnected.Free())) 
            isSuccess = false;
        if ((error = m_bgColorUnconnected.Free())) 
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // Invalidate window
    ///////////////////////////////////////////////////////////////////////
    virtual void Invalidate() {
        XWindowAttributes xWindowAttributes;
        XosError error;
        if (!(error = GetWindowAttributes(xWindowAttributes))) {
            Invalidate(0,0, xWindowAttributes.width,xWindowAttributes.height);
        }
    }
    virtual void Invalidate(int x,int y, int width,int height) {
        XosXExposeEvent xExposeEvent(m_xDisplay, m_xWindow, x,y, width,height);
        xExposeEvent.Send();
    }

protected:
    XosXWindowMain& m_windowMain;
    bool m_useGLRenderer;
    XosXWebRtcClientOpenGLVideoRenderer m_glRenderer;
    XosXColor m_bgColorUnconnected;
    XosXColor m_bgColorConnected;
    XosXColor m_bgColorStreaming;
    XosXColor m_bgColor;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTMAINWINDOW_HPP 
