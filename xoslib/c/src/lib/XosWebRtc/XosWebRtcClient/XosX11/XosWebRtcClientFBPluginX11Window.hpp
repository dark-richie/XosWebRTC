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
///   File: XosWebRtcClientFBPluginX11Window.hpp
///
/// Author: $author$
///   Date: 4/21/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINX11WINDOW_HPP
#define _XOSWEBRTCCLIENTFBPLUGINX11WINDOW_HPP

#include "XosX11WebRtcClientBaseWindow.hpp"
#include "XosX11WebRtcClientOpenGLVideoRenderer.hpp"
#include "XosWebRtcClientFBPluginX11WindowImplemented.hpp"
#include "XosWebRtcClientFBPluginWindow.hpp"
#include "XosDebug.hpp"

#if !defined(XOS_8TO16)
#define XOS_8TO16(n) (n*256)
#endif // !defined(XOS_8TO16)

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosX11WindowMouseUpEventImplemented;
class _EXPORT_CLASS XosX11WindowResizedEventImplemented;
class _EXPORT_CLASS XosX11WindowRefreshEventImplemented;
class _EXPORT_CLASS XosX11WindowX11EventImplemented;
//class _EXPORT_CLASS XosX11WindowImplemented;

typedef XosWebRtcClientFBPluginWindowImplement
XosWebRtcClientFBPluginX11WindowImplement;

typedef XosWebRtcClientFBPluginWindowT
<XosX11WebRtcClientBaseWindow>
XosWebRtcClientFBPluginX11WindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginX11Window
///
/// Author: $author$
///   Date: 4/21/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientFBPluginX11Window
: virtual public XosWebRtcClientFBPluginX11WindowImplement,
  public XosWebRtcClientFBPluginX11WindowExtend
{
public:
    typedef XosWebRtcClientFBPluginX11WindowImplement Implements;
    typedef XosWebRtcClientFBPluginX11WindowExtend Extends;

    XosX11WebRtcClientOpenGLVideoRenderer m_glRenderer;
    XosX11WindowImplemented* m_attached;
    bool m_paintHandled;
    unsigned m_debugLevels;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginX11Window
    ///
    ///       Author: $author$
    ///         Date: 4/21/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginX11Window
    (XosWebRtcClientFBPluginInterface& plugin,
     const char* serverName=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(plugin, serverName, serverPort, showConnectionState, handleButtonEvents),
      m_attached(0),
      m_paintHandled(false),
      m_debugLevels(XOS_GET_DEBUG_LEVELS())
    {
        m_useUIMessageQueue = true;
        m_postButtonEventUIMessages = true;
    }
    virtual ~XosWebRtcClientFBPluginX11Window()
    {
    }

    virtual void OnChangeStateToConnectToServer()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        Extends::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        Extends::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming()
    {
        XOS_SET_DEBUG_LEVEL(XOS_DEBUG_LEVELS_NONE);
        Extends::OnChangeStateToStreaming();
    }

    virtual XosWebRtcClientOpenGLVideoRenderer*
    AcquireOpenGLRenderer() 
    { 
        XosWebRtcClientOpenGLVideoRenderer* renderer = 0;
        Display* xDisplay;
        Window xWindow;

        XOS_DBT(("()... m_attached=%x\n", m_attached));

        if ((m_attached))
        if (!(m_attached->m_dontUseOpenGL))
        if (((xDisplay = m_attached->m_xDisplay) != 0) 
            && ((xWindow =  m_attached->m_xWindow) != None))
        if ((m_glRenderer.init(xDisplay, xWindow))) {
            XOS_DBT(("()... acquired\n"));
            renderer = (XosWebRtcClientOpenGLVideoRenderer*)(&m_glRenderer);
        }
        return renderer; 
    }
    virtual bool ReleaseOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) 
    { 
        bool isTrue = false;
        XOS_DBT(("()...\n"));
        if (((XosWebRtcClientOpenGLVideoRenderer*)(&m_glRenderer) == renderer))
            isTrue = m_glRenderer.finish();
        return isTrue; 
    }
    virtual bool ReshapeOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) 
    { 
        XOS_DBT(("()...\n"));
        if ((renderer))
        if ((m_attached))
        {
            renderer->reshape(m_attached->m_width, m_attached->m_height);
            return true;
        }
        return false; 
    }

    virtual bool ValidateWindow() 
    {
        XOS_DBT(("()...\n"));
        return true; 
    }
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        bool handled = false;
        XOS_DBT(("()...\n"));
        if ((handled = (m_attached != 0)))
            handled = m_attached->InvalidateWindow(eraseBackground);
        return handled;
    }

    virtual void OnWindowAttached
    (XosX11WindowImplemented* attached)
    {
        XOS_DBT(("()...\n"));
        std::string webrtcClientTraceFileName
        (GenerateWebRtcClientTraceFileName
         (m_webrtcClientTraceFileEnv, 
          m_webrtcClientTraceFileDir, 
          m_webrtcClientTraceFileName));
        if ((m_attached))
            OnWindowDetached(m_attached);
        if ((m_socketServer = new XosX11WebRtcClientBaseWindowSocketServer(*this)))
            XosWebRtcClientConnection::SetSocketServer(m_socketServer);
        m_clientPair = new ClientPair
        (*this, webrtcClientTraceFileName);
        InitUIMessageThread();
        m_attached = attached;
        OnOpen();
        CreateUIMessageThread();
    }
    virtual void OnWindowDetached
    (XosX11WindowImplemented* attached)
    {
        XOS_DBT(("()...\n"));
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

    virtual bool OnX11Event
    (XosX11WindowX11EventImplemented* x11Event)
    {
        bool handled = false;
        return handled;
    }

    virtual bool OnLMouseUp
    (XosX11WindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = false;
        OnLButtonUp();
        return handled;
    }
    virtual bool OnRMouseUp
    (XosX11WindowMouseUpEventImplemented* mouseUpEvent)
    {
        bool handled = false;
        OnRButtonUp();
        return handled;
    }

    virtual bool OnWindowResized
    (int x, int y, int width, int height,
     XosX11WindowResizedEventImplemented* resizedEvent)
    {
        m_paintHandled = true;
        XOS_DBT(("()...\n"));
        OnSize();
        return m_paintHandled;
    }
    virtual bool OnWindowRefresh
    (int x, int y, int width, int height,
     XosX11WindowRefreshEventImplemented* refreshEvent)
    {
        m_paintHandled = false;
        XOS_DBT(("()...\n"));
        OnPaint();
        return m_paintHandled;
    }

    virtual bool OnPaintImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height)
    {
        bool handled = false;
        if ((renderer_))
        if (!(renderer_->getDontUse()))
        {
            gdk_threads_enter();
            ValidateWindow();
            renderer_->render
            (remote_image, remote_width, remote_height,
             local_image, local_width, local_height);
            UpdateWindow();
            gdk_threads_leave();
            return true;
        }
        handled = OnPaintImage
        (remote_image, remote_width, remote_height, false);
        return handled;
    }
    virtual bool OnPaintImage
    (const uint8* image, int width, int height, bool is_local)
    {
        bool handled = false;
        GtkWidget* gtkWidget = 0;
        GtkStyle* gtkStyle = 0;
        GdkDisplay* gdkDisplay = 0;
        GdkScreen* gdkScreen = 0;
        GdkWindow* gdkWindow = 0;
        GdkGC* gdkGC = 0;
        GdkColormap* gdkColormap = 0;
        GdkColor gdkColor = 
        {None, 
         XOS_8TO16(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED),
         XOS_8TO16(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN),
         XOS_8TO16(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE)};

        XOS_DBT(("()...\n"));

        if ((renderer_))
        if (!(renderer_->getDontUse()))
        {
            gdk_threads_enter();
            ValidateWindow();
            renderer_->render(image, width, height);
            UpdateWindow();
            gdk_threads_leave();
            return true;
        }

        if ((m_attached != 0))
        if ((gtkWidget = m_attached->m_gtkWidget))
        if ((gdkWindow = gtkWidget->window))
        if ((gtkStyle = gtkWidget->style))
        if ((gdkGC = gtkStyle->fg_gc[GTK_STATE_NORMAL]))
        {
            gdk_threads_enter();

            if (0)
            m_attached->FillRectangleRGB8
            (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
             XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
             XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE,
             m_attached->m_x, m_attached->m_y, 
             m_attached->m_width, m_attached->m_height);
            else
            {
                if ((gdkDisplay = gtk_widget_get_display(gtkWidget)))
                if ((gdkScreen = gtk_widget_get_screen(gtkWidget)))
                if ((gdkColormap = gdk_screen_get_default_colormap(gdkScreen)))
                if ((gdk_colormap_alloc_color
                    (gdkColormap, &gdkColor, TRUE, TRUE)))
                {
                    gdk_gc_set_foreground(gdkGC, &gdkColor);

                    gdk_draw_rectangle
                    (gdkWindow, gdkGC, TRUE,
                     m_attached->m_x, m_attached->m_y, 
                     m_attached->m_width, m_attached->m_height);

                    gdk_colormap_free_colors
                    (gdkColormap, &gdkColor, 1);
                }
            }

            gdk_draw_rgb_32_image
            (gdkWindow, gdkGC, 0,0, width,height, 
             GDK_RGB_DITHER_MAX, image, width*4);

            gdk_threads_leave();
            handled = true;
        }
        return handled;
    }
    virtual bool OnPaintBlank()
    {
        bool handled = false;

        XOS_DBT(("()...\n"));
/*
        if ((ui_ == STREAMING) && (m_attached != 0))
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
*/
        if ((handled = (m_paintHandled = (m_attached != 0))))
        {
            int width = m_attached->m_width;
            int height = m_attached->m_height;

            gdk_threads_enter();
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

                m_attached->FillRectangleRGB8
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE,
                 m_attached->m_x, m_attached->m_y, 
                 m_attached->m_width, m_attached->m_height);
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

                m_attached->FillRectangleRGB8
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE,
                 m_attached->m_x, m_attached->m_y, 
                 m_attached->m_width, m_attached->m_height);

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

                m_attached->FillRectangleRGB8
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE,
                 m_attached->m_x, m_attached->m_y, 
                 m_attached->m_width, m_attached->m_height);

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

                m_attached->FillRectangleRGB8
                (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
                 XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE,
                 m_attached->m_x, m_attached->m_y, 
                 m_attached->m_width, m_attached->m_height);
            }
            gdk_threads_leave();
        }
        return handled;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINX11WINDOW_HPP 
