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
///   File: XosXWebRtcClientWindowPeerImplement.hpp
///
/// Author: $author$
///   Date: 2/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTWINDOWPEERIMPLEMENT_HPP
#define _XOSXWEBRTCCLIENTWINDOWPEERIMPLEMENT_HPP

#include "XosXWebRtcClientBaseWindowPeerImplement.hpp"
#include "XosXWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosWebRtcClientEventInterface.hpp"
#include "XosXWindowMain.hpp"
#include "XosXWindow.hpp"
#include "XosXEvent.hpp"
#include "XosXColor.hpp"
#include "XosXGC.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosXWindowImplement XosWebRtcClientWindowPeerImplementImplement;
typedef XosXWindow XosWebRtcClientWindowPeerImplementExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientWindowPeerImplement
///
/// Author: $author$
///   Date: 2/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientWindowPeerImplement
: virtual public XosWebRtcClientWindowPeerImplementImplement,
  virtual public XosWebRtcClientImageObserverInterface,
  virtual public XosWebRtcClientEventObserverInterface,
  public XosWebRtcClientWindowPeerImplementExtend
{
public:
    typedef XosWebRtcClientWindowPeerImplementImplement Implements;
    typedef XosWebRtcClientImageObserverInterface ImageImplements;
    typedef XosWebRtcClientEventObserverInterface EventImplements;
    typedef XosWebRtcClientWindowPeerImplementExtend Extends;
    typedef XosWebRtcClientWindowPeerImplement Derives;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientWindowPeerImplement
    ///
    ///       Author: $author$
    ///         Date: 2/10/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientWindowPeerImplement(XosXWindowMain& windowMain)
    : m_windowMain(windowMain),
      m_uiWindow(0),
      m_window(0),
      m_autoConnectToPeerOn(false),
      m_serverName(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT),
      m_onExposeXEvent(0),
      m_useGLRenderer(false)
    {
    }
    virtual ~XosWebRtcClientWindowPeerImplement()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // Open/Close X11 window
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpen() {
        if ((m_useGLRenderer = m_glRenderer.init(m_xDisplay, m_xWindow)))
            m_glRenderer.prepareOpenGL();
        if ((AllocateColors()))
            return true;
        return false;
    }
    virtual bool OnWindowClose() {
        if ((FreeColors()))
            return true;
        if ((m_useGLRenderer))
            m_glRenderer.finish();
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    // Open/Close UI window and peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (XosWebRtcClientBasePeerWindowImplement* uiWindow,
     XosWebRtcClientBaseWindowPeerImplement* window)
    {
        if ((m_uiWindow = uiWindow)) {
            if ((m_window = window)) {
                m_uiWindow->SetServerName(m_serverName);
                m_uiWindow->SetServerPort(m_serverPort);
                m_uiWindow->SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
                m_uiWindow->RegisterImageObserver(this);
                m_uiWindow->RegisterEventObserver(this);
                if ((m_window->Open(this))) {
                    return true;
                }
                m_window = 0;
            }
            m_uiWindow = 0;
        }
        return false;
    }
    virtual bool Close
    (XosWebRtcClientBasePeerWindowImplement* uiWindow,
     XosWebRtcClientBaseWindowPeerImplement* window)
    {
        bool isSuccess = false;
        ChangeBackground(m_windowMain.GetMainWindowBackgroundColor());
        if ((m_uiWindow) && (uiWindow == m_uiWindow)) {
            if ((m_window) && (window == m_window)) {
                isSuccess = m_window->Close(this);
                m_uiWindow->UnregisterEventObserver(this);
                m_uiWindow->UnregisterImageObserver(this);
                m_window = 0;
            }
            m_uiWindow = 0;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // Connect/Disconnect Server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort)
    {
        bool success = false;
        if ((m_uiWindow))
            success = m_uiWindow->ConnectToServer(serverName, serverPort);
        return success;
    }
    virtual bool ConnectToServer()
    {
        bool success = false;
        if ((m_uiWindow))
            success = m_uiWindow->ConnectToServer();
        return success;
    }
    virtual bool DisconnectFromServer()
    {
        bool success = false;
        if ((m_uiWindow))
            success = m_uiWindow->DisconnectFromServer();
        return success;
    }
    virtual void SetServerName(const std::string& serverName) { 
        if ((m_uiWindow))
            m_uiWindow->SetServerName(serverName);
    }
    virtual void SetServerPort(int serverPort) {
        if ((m_uiWindow))
            m_uiWindow->SetServerPort(serverPort);
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
        if ((m_uiWindow)) {
            m_uiWindow->SetAutoConnectToPeerOn(isTrue);
            m_uiWindow->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
        if ((m_uiWindow)) {
            m_uiWindow->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }

protected:
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
        if ((m_useGLRenderer))
            m_glRenderer.reshape(xConfigureEvent.width, xConfigureEvent.height);
        return error;
    }
    virtual XosError OnExposeXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        if ((m_onExposeXEvent))
            (this->*m_onExposeXEvent)(xEvent);
        return error;
    }
    virtual XosError OnBlankExposeXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        int x = xEvent.xexpose.x;
        int y = xEvent.xexpose.y;
        int width = xEvent.xexpose.width;
        int height = xEvent.xexpose.height;
        XosError error2;
        XosXGC gc;
        if (!(error2 = gc.Create(m_xDisplay, m_xWindow))) {
            gc.FillRectangle(m_bgColor.Attached(), x,y, width,height);
            gc.Destroy();
        }
        return error;
    }
    virtual XosError OnImageExposeXEvent(const XEvent& xEvent) 
    {
        XosError error = XOS_ERROR_NONE;
        if ((m_uiWindow) && (m_useGLRenderer)) {
            uint8 *remoteImage, *localImage;
            int remoteImageFormat, localImageFormat;
            int remoteImageWidth, remoteImageHeight;
            int localImageWidth, localImageHeight;

            if ((remoteImage = m_uiWindow->AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = m_uiWindow->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_glRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_uiWindow->ReleaseLocalImage(localImage);
                } else {
                    m_glRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_uiWindow->ReleaseRemoteImage(remoteImage);
                m_glRenderer.swapBuffers();
            } else {
                if ((localImage = m_uiWindow->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_glRenderer.render
                    (localImage, localImageWidth, localImageHeight);
                    m_uiWindow->ReleaseLocalImage(localImage);
                    m_glRenderer.swapBuffers();
                } else {
                }
            }
        }
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_uiWindow))
            m_uiWindow->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_uiWindow))
            m_uiWindow->OnRButtonUp();
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        XOS_DBI(("()...\n"));
        m_onExposeXEvent = &Derives::OnBlankExposeXEvent;
        ChangeBGColor(m_bgColorUnconnected.Attached());
    }
    virtual void OnChangeStateToListPeers() { 
        XOS_DBI(("()...\n"));
        m_onExposeXEvent = &Derives::OnBlankExposeXEvent;
        ChangeBGColor(m_bgColorConnected.Attached());
    }
    virtual void OnChangeStateToStreaming() {
        XOS_DBI(("()...\n"));
        m_onExposeXEvent = &Derives::OnImageExposeXEvent;
        ChangeBGColor(m_bgColorStreaming.Attached());
    }
    virtual void OnFailedToConnectToServer(const std::string& server) {
        XOS_DBI(("(\"%s\")...\n", server.c_str()));
    }
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        Invalidate();
        return true; 
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
    virtual void ChangeBGColor(Pixel bgColor) {
        ChangeBackground(m_bgColor.Attach(bgColor));
        //Invalidate();
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
    typedef XosError (Derives::*MOnExposeXEvent)(const XEvent& xEvent);

    XosXWindowMain& m_windowMain;
    XosWebRtcClientBasePeerWindowImplement* m_uiWindow;
    XosWebRtcClientBaseWindowPeerImplement* m_window;
    XosXColor m_bgColorUnconnected;
    XosXColor m_bgColorConnected;
    XosXColor m_bgColorStreaming;
    XosXColor m_bgColor;
    XosString m_serverName;
    int m_serverPort;
    bool m_autoConnectToPeerOn;
    MOnExposeXEvent m_onExposeXEvent;
    bool m_useGLRenderer;
    XosXWebRtcClientOpenGLVideoRenderer m_glRenderer;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTWINDOWPEERIMPLEMENT_HPP 
