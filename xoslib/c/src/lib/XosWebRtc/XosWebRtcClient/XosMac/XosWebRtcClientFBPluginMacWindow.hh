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
///   File: XosWebRtcClientFBPluginMacWindow.hh
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINMACWINDOW_HH
#define _XOSWEBRTCCLIENTFBPLUGINMACWINDOW_HH

#include "XosWebRtcClientFBPluginWindow.hpp"
#include "XosWebRtcClientFBPluginMacBaseWindow.hh"
#include "XosMacWebRtcClientBaseWindow.hh"
#include "XosMacWebRtcClientBaseWindowUIMessageThread.hh"
#include "XosMacWebRtcClientVideoRenderer.hh"
#include "XosPlatform_cocoa.hh"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosMacWindowMouseUpEventImplemented;
class _EXPORT_CLASS XosMacWindowResizedEventImplemented;
class _EXPORT_CLASS XosMacWindowRefreshEventImplemented;
class _EXPORT_CLASS XosMacWindowDrawCGEventImplemented;
class _EXPORT_CLASS XosMacWindowCGImplemented;
class _EXPORT_CLASS XosMacWindowImplemented;

///////////////////////////////////////////////////////////////////////
///  Class: XosMacWindowCGImplemented
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacWindowCGImplemented
{
public:
    CGContextRef m_cgContext;
    int m_x,m_y, m_width,m_height;
    int m_cx,m_cy, m_cwidth,m_cheight;

    XosMacWindowCGImplemented
    (CGContextRef cgContext,
     int x, int y, int width, int height,
     int cx, int cy, int cwidth, int cheight)
    : m_cgContext(cgContext),
      m_x(x),m_y(y), m_width(width),m_height(height),
      m_cx(cx),m_cy(cy), m_cwidth(cwidth),m_cheight(cheight)
    {}
};
///////////////////////////////////////////////////////////////////////
///  Class: XosMacWindowImplemented
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacWindowImplemented
{
public:
    virtual bool InvalidateWindow(bool eraseBackground = true) = 0;
};

typedef XosMacWindowImplemented* XosMacWindowAttached;

//typedef XosWebRtcClientFBPluginWindowImplement
typedef XosWebRtcClientFBPluginMacBaseWindowImplement
XosWebRtcClientFBPluginMacWindowImplement;

//typedef XosWebRtcClientFBPluginWindowT<XosMacWebRtcClientBaseWindow>
typedef XosWebRtcClientFBPluginMacBaseWindow
XosWebRtcClientFBPluginMacWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginMacWindow
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginMacWindow
: virtual public XosWebRtcClientFBPluginMacWindowImplement,
  public XosWebRtcClientFBPluginMacWindowExtend
{
public:
    typedef XosWebRtcClientFBPluginMacWindowImplement Implements;
    typedef XosWebRtcClientFBPluginMacWindowExtend Extends;

    XosMacWindowAttached m_attached;
    XosMacWindowCGImplemented* m_cg;
    bool m_onPaintHandled;
    unsigned m_debugLevels;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginMacWindow
    ///
    ///       Author: $author$
    ///         Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginMacWindow
    (XosWebRtcClientFBPluginInterface& plugin,
     const char* serverName=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(plugin, serverName, serverPort, showConnectionState, handleButtonEvents),
      m_attached(0),
      m_cg(0),
      m_onPaintHandled(false),
      m_debugLevels(XOS_GET_DEBUG_LEVELS())
    {
        m_useUIMessageQueue = true;
        m_postButtonEventUIMessages = true;
        //m_autoConnectToPeerOn = true;
        //m_autoConnectToPeerAfterOn = true;
    }
    virtual ~XosWebRtcClientFBPluginMacWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // State change
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        XOS_DBT(("() ...\n"));
        Extends::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        XOS_DBT(("() ...\n"));
        Extends::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming()
    {
        XOS_DBT(("() ...\n"));
        XOS_SET_DEBUG_LEVEL(XOS_DEBUG_LEVELS_NONE);
        Extends::OnChangeStateToStreaming();
    }

    ///////////////////////////////////////////////////////////////////////
    // Attached
    ///////////////////////////////////////////////////////////////////////
    virtual void OnWindowAttached(XosMacWindowAttached attached)
    {
        XOS_DBT(("() ...\n"));
        std::string webrtcClientTraceFileName
        (GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));
        if ((m_attached))
            OnWindowDetached(m_attached);
        if ((m_socketServer = new XosMacWebRtcClientBaseWindowSocketServer(*this)))
            XosWebRtcClientConnection::SetSocketServer(m_socketServer);
        m_clientPair = new ClientPair
        (*this, webrtcClientTraceFileName);
        InitUIMessageThread();
        m_attached = attached;
        OnOpen();
        CreateUIMessageThread();
    }
    virtual void OnWindowDetached(XosMacWindowAttached attached)
    {
        XOS_DBT(("() ...\n"));
        if ((m_attached == attached))
        {
            DestroyUIMessageThread();
            OnClose();
            m_attached = 0;
            FinishUIMessageThread();
            if ((m_clientPair))
            {
                delete m_clientPair;
                m_clientPair = 0;
            }
            if ((m_socketServer))
            {
                XosWebRtcClientConnection::SetSocketServer(0);
                delete m_socketServer;
                m_socketServer = 0;
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // Mouse events
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnLMouseUp
    (XosMacWindowMouseUpEventImplemented* mouseUpEvent)
    {
        XOS_DBT(("() ...\n"));
        bool handled = false;
        OnLButtonUp();
        return handled;
    }
    virtual bool OnRMouseUp
    (XosMacWindowMouseUpEventImplemented* mouseUpEvent)
    {
        XOS_DBT(("() ...\n"));
        bool handled = false;
        OnRButtonUp();
        return handled;
    }

    ///////////////////////////////////////////////////////////////////////
    // Window events
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowResized
    (int x, int y, int width, int height,
     XosMacWindowResizedEventImplemented* resizedEvent)
    {
        bool handled = false;
        return handled;
    }
    virtual bool OnWindowRefresh
    (int x, int y, int width, int height,
     XosMacWindowRefreshEventImplemented* refreshEvent)
    {
        bool handled = false;
        return handled;
    }
    virtual bool OnWindowDrawCG
    (int x, int y, int width, int height,
     XosMacWindowCGImplemented* cg,
     XosMacWindowDrawCGEventImplemented* drawCGEvent)
    {
        bool handled = false;
        if ((m_cg = cg))
        {
            m_onPaintHandled = false;
            OnPaint();
            handled = m_onPaintHandled;
        }
        return handled;
    }

    ///////////////////////////////////////////////////////////////////////
    // Renderer
    ///////////////////////////////////////////////////////////////////////
    /*virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XOS_DBT(("() ...\n"));
        XosWebRtcClientVideoRenderer* renderer = 0;
        renderer = new XosMacWebRtcClientVideoRenderer
        (*this, width, height, isRemote);
        return renderer; 
    }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) 
    { 
        XOS_DBT(("() ...\n"));
        if ((renderer))
        {
            delete renderer;
            return true;
        }
        return false; 
    }*/
    virtual bool ValidateWindow() { return true; }
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        bool handled = false;
        if ((handled = (m_attached != 0)))
            m_attached->InvalidateWindow(eraseBackground);
        return handled;
    }

    ///////////////////////////////////////////////////////////////////////
    // UIMessageThread
    ///////////////////////////////////////////////////////////////////////
    /*virtual bool InitUIMessageThread()
    {
        bool isSuccess = InitUIMessageQueue();
        return isSuccess;
    }
    virtual bool FinishUIMessageThread()
    {
        bool isSuccess = FinishUIMessageQueue();
        return isSuccess;
    }
    virtual bool CreateUIMessageThread()
    {
        bool isSuccess = m_msgThread.CreateMessageThread(this);
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread()
    {
        bool isSuccess = m_msgThread.DestroyMessageThread();
        return isSuccess;
    }
    virtual UIMessageThreadId GetUIMessageThreadId()
    {
        return &m_msgThread;
    }*/

    ///////////////////////////////////////////////////////////////////////
    // Paint events
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnPaintImage
    (const uint8* image, int width, int height, bool is_local)
    {
        bool handled = false;
        if ((handled = (m_onPaintHandled = (m_cg != 0))))
        {
            CGContextRef cgContext = m_cg->m_cgContext;
            CGContextSaveGState(cgContext);
            int winWidth = m_cg->m_width;
            int winHeight = m_cg->m_cheight;

            if ((1 < winWidth) && (1 < winHeight))
            {
                CGContextSetShouldAntialias(cgContext, false);
                CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

                CGImageRef cgImage = CGImageCreate
                 (width, height, 8, 32, 4*width, colorSpace, 
                  kCGImageAlphaNoneSkipLast,
                  CGDataProviderCreateWithData
                  (NULL, image, width*height*4, NULL),
                  NULL, false, kCGRenderingIntentDefault);

                if ((cgImage))
                {
                    CGContextSetInterpolationQuality(cgContext, kCGInterpolationNone);
                    CGContextTranslateCTM(cgContext, 0, winHeight);
                    CGContextScaleCTM(cgContext, 1, -1);
                    CGRect rect = { {0,0}, {width,height}};
                    CGContextDrawImage(cgContext, rect, cgImage);
                    CGImageRelease(cgImage);
                }
                CGColorSpaceRelease(colorSpace);
            }
            CGContextRestoreGState(cgContext);
        }
        return handled;
    }
    virtual bool OnPaintBlank()
    {
        bool handled = false;

        if ((ui_ == STREAMING) && (m_cg != 0))
        if ((remote_video_.get()))
        {
            AutoLock<XosWebRtcClientVideoRenderer> remote_lock(remote_video_.get());
            const uint8* remote_image;

            // if we have a remote stream
            if ((remote_image = remote_video_->image()))
            {
                //Get dimensions
                int remote_width  = remote_video_->image_width();
                int remote_height = remote_video_->image_height();

                if ((handled = OnPaintImage
                    (remote_image, remote_width, remote_height, false)))
                    return handled;
            }
        }

        if ((handled = (m_onPaintHandled = (m_cg != 0))))
        {
            CGContextRef cgContext = m_cg->m_cgContext;
            CGContextSaveGState(cgContext);

            CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
            CGContextSetFillColorSpace(cgContext, colorspace);

            int width = m_cg->m_width;
            int height = m_cg->m_cheight;

            CGRect rect0 = { {0,0}, {width, height} };
            CGContextClearRect(cgContext, rect0);

            if (!(m_showConnectionState))
            {
                //
                // Show blank background before connected to peer.
                //
                /*HBRUSH brush = CreateSolidBrush(RGB
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE));
                FillRect(ps.hdc, &rc, brush);
                DeleteObject(brush);*/

                CGFloat color[] = 
                { (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE)/256, 
                  1.00 };
                CGContextSetFillColor(cgContext, color);
                CGContextFillRect(cgContext, rect0);
            }
            else
            if ((ui_ == LIST_PEERS))
            {
                /*
                HBRUSH brush = CreateSolidBrush(RGB
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE));
                FillRect(ps.hdc, &rc, brush);
                DeleteObject(brush);
                */

                CGFloat color[] = 
                { (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE)/256, 
                  1.00 };
                CGContextSetFillColor(cgContext, color);
                CGContextFillRect(cgContext, rect0);

                std::string text(m_ConnectToPeerBefore.c_str());
                text += m_connectToPeerName;
                text += m_ConnectToPeerAfter.c_str();

                /*DrawWhiteText
                (ps.hdc, rc, text.c_str(),
                 DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/

                text = m_PeerBefore.c_str();
                text += GetThisPeerName().c_str();
                text += m_PeerAfter.c_str();

                /*DrawWhiteText
                (ps.hdc, rc, text.c_str(),
                 DT_CENTER | DT_BOTTOM);*/
            }
            else 
            if ((ui_ == CONNECT_TO_SERVER))
            {
                /*HBRUSH brush = CreateSolidBrush(RGB
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE));
                 FillRect(ps.hdc, &rc, brush);
                 DeleteObject(brush);*/

                CGFloat color[] = 
                { (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE)/256, 
                  1.00 };
                CGContextSetFillColor(cgContext, color);
                CGContextFillRect(cgContext, rect0);

                std::string text(m_ConnectToServerBefore.c_str());
                text += m_serverName;
                text += m_ConnectToServerAfter.c_str();

                /*DrawWhiteText
               (ps.hdc, rc, text.c_str(),
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
            }
            else
            {
                /*HBRUSH brush = CreateSolidBrush(RGB
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE));
                FillRect(ps.hdc, &rc, brush);
                DeleteObject(brush);*/

                CGFloat color[] = 
                { (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN)/256, 
                  (float)(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE)/256, 
                  1.00 };
                CGContextSetFillColor(cgContext, color);
                CGContextFillRect(cgContext, rect0);
            }

            CGColorSpaceRelease(colorspace);
            CGContextRestoreGState(cgContext);
        }
        return handled;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINMACWINDOW_HH 
