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
///   File: XosQWebRtcClientMainWindow.hpp
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSQWEBRTCCLIENTMAINWINDOW_HPP
#define _XOSQWEBRTCCLIENTMAINWINDOW_HPP

#include "XosWebRtcClientConsolePluginInterface.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosWebRtcClientEventInterface.hpp"
#include "XosQWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosQMainWindow.hpp"
#include "XosString.hpp"

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME "localhost"
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT 8888

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN 128
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE 128

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef QGLWidget XosQWebRtcClientOpenGLWidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosQWebRtcClientOpenGLWidget
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosQWebRtcClientOpenGLWidget
: public XosQWebRtcClientOpenGLWidgetExtend {
public:
    typedef XosQWebRtcClientOpenGLWidgetExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosQWebRtcClientOpenGLWidget
    ///
    ///       Author: $author$
    ///         Date: 2/4/2013
    ///////////////////////////////////////////////////////////////////////
    XosQWebRtcClientOpenGLWidget
    (QWidget* parent, 
     XosWebRtcClientConsolePluginInterface* plugin, 
     const QColor& bgColor)
    : Extends(parent), 
      m_plugin(plugin),
      m_bgColor(bgColor)
    {
    }
    virtual void Invalidate() {
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
    }
    virtual void Resize() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        update(0,0, width,height);
    }
    virtual void Show() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        show();
    }

protected:
    virtual void initializeGL() {
        m_openglRenderer.init();
    }
    virtual void resizeGL(int w, int h) {
        m_openglRenderer.reshape(w, h);
    }
    virtual void paintGL() {
        uint8_t *remoteImage, *localImage;
        int remoteImageFormat, localImageFormat;
        int remoteImageWidth, remoteImageHeight;
        int localImageWidth, localImageHeight;

        if ((m_plugin)) {
            if ((remoteImage = m_plugin->AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = m_plugin->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                } else {
                    m_openglRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_plugin->ReleaseRemoteImage(remoteImage);
                m_openglRenderer.swapBuffers();
            } else {
                if ((localImage = m_plugin->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.render
                    (localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                    m_openglRenderer.swapBuffers();
                } else {
                    PaintBackground();
                }
            }
        } else {
            PaintBackground();
        }
    }
    virtual void PaintBackground() {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }

protected:
    XosWebRtcClientConsolePluginInterface* m_plugin;
    QColor m_bgColor;
    XosWebRtcClientOpenGLVideoRenderer m_openglRenderer;
};
typedef XosQMainWindowImplement XosQWebRtcClientMainWindowImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: XosQWebRtcClientMainWindowImplement
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosQWebRtcClientMainWindowImplement
: virtual public XosQWebRtcClientMainWindowImplementImplement,
  virtual public XosWebRtcClientImageObserverInterface,
  virtual public XosWebRtcClientEventObserverInterface
{
public:
    typedef XosQWebRtcClientMainWindowImplementImplement Implements;
    typedef XosWebRtcClientImageObserverInterface ImageImplements;
    typedef XosWebRtcClientEventObserverInterface EventImplements;
};
typedef XosQMainWindow XosQWebRtcClientMainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosQWebRtcClientMainWindow
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosQWebRtcClientMainWindow
: virtual public XosQWebRtcClientMainWindowImplement,
  public XosQWebRtcClientMainWindowExtend
{
public:
    typedef XosQWebRtcClientMainWindowImplement Implements;
    typedef XosQWebRtcClientMainWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosQWebRtcClientMainWindow
    ///
    ///       Author: $author$
    ///         Date: 2/4/2013
    ///////////////////////////////////////////////////////////////////////
    XosQWebRtcClientMainWindow()
    : m_plugin(0), 
      m_openglWidget(0),
      m_autoConnectToPeerOn(false),
      m_serverName(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME),
      m_serverPort(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT),
      m_bgColorUnconnected
      (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE),
      m_bgColorConnected
      (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE),
      m_bgColorStreaming
      (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN,
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE),
      m_bgColor(m_bgColorUnconnected),
      m_errorMessage(0)
    {
    }
    virtual ~XosQWebRtcClientMainWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // On Window Open/Close
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpen()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if (!(m_plugin))
        if ((success = (0 != (m_plugin = LoadPlugin(error))))) 
        {
            if ((m_openglWidget = new XosQWebRtcClientOpenGLWidget
                (this, m_plugin, m_bgColorStreaming))) {
                setCentralWidget(m_openglWidget);
            }
            m_plugin->SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
            m_plugin->SetServerName(m_serverName);
            m_plugin->SetServerPort(m_serverPort);
            m_plugin->RegisterImageObserver(this);
            m_plugin->RegisterEventObserver(this);
            m_plugin->OnWindowAttached(this);
        }
        return success;
    }
    virtual bool OnWindowClose()
    {
        bool success = false;
        XosError error = XOS_ERROR_NONE;
        if ((m_plugin))
        {
            m_plugin->OnWindowDetached(this);
            m_plugin->UnregisterEventObserver(this);
            m_plugin->UnregisterImageObserver(this);
            if ((m_openglWidget)) {
                setCentralWidget(0);
                m_openglWidget = 0;
            }
            success = !(error = UnloadPlugin(m_plugin));
            m_plugin = 0;
        }
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        QApplication::postEvent(this, new InvalidateQEvent());
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        QApplication::postEvent(this, new ChangeStateQEvent(ConnectServer));
    }
    virtual void OnChangeStateToListPeers() { 
        QApplication::postEvent(this, new ChangeStateQEvent(ListPeers));
    }
    virtual void OnChangeStateToStreaming() {
        QApplication::postEvent(this, new ChangeStateQEvent(Streaming));
    }
    virtual void OnFailedToConnectToServer(const std::string& server) {
        QApplication::postEvent(this, new FailedConnectServerQEvent(server));
    }

    ///////////////////////////////////////////////////////////////////////
    // Message Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnResize() 
    { 
        int width = this->width();
        int height = this->height();
        if ((m_openglWidget))
            m_openglWidget->Resize();
        update(0,0, width,height);
    }
    virtual void OnInvalidate() 
    { 
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
        if ((m_openglWidget) && (m_openglWidget == centralWidget()))
            m_openglWidget->Invalidate();
    }
    virtual void OnConnectServer() { 
        if ((m_openglWidget))
            m_openglWidget->hide();
        m_bgColor = m_bgColorUnconnected;
        OnResize();
        EventImplements::OnChangeStateToConnectToServer();
    }
    virtual void OnListPeers() { 
        if ((m_openglWidget))
            m_openglWidget->hide();
        m_bgColor = m_bgColorConnected;
        OnResize();
        EventImplements::OnChangeStateToListPeers();
    }
    virtual void OnStreaming() {
        if ((m_openglWidget) && (m_openglWidget == centralWidget()))
            m_openglWidget->Show();
        m_bgColor = m_bgColorStreaming;
        OnResize();
        EventImplements::OnChangeStateToStreaming();
    }
    virtual void OnFailedConnectServer(const std::string& server) {
        if ((m_errorMessage)) {
            delete m_errorMessage;
            m_errorMessage = 0;
        }
        if ((m_errorMessage = new QErrorMessage(this))) {
            QString message("Failed to connect to server \"");
            message.append(server.c_str());
            message.append("\"");
            m_errorMessage->showMessage(message);
        }
        EventImplements::OnFailedToConnectToServer(server);
    }

    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_plugin))
            m_plugin->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_plugin))
            m_plugin->OnRButtonUp();
    }

    ///////////////////////////////////////////////////////////////////////
    // Qt events
    ///////////////////////////////////////////////////////////////////////
    virtual void customEvent(QEvent* event) 
    {
        switch((event->type()))
        {
        case FailedConnectServer:
            OnFailedConnectServer(((FailedConnectServerQEvent*)(event))->server());
            break;
        case ConnectServer:
            OnConnectServer();
            break;
        case ListPeers:
            OnListPeers();
            break;
        case Streaming:
            OnStreaming();
            break;
        case Invalidate:
            OnInvalidate();
            break;
        }
    }
    virtual void mouseReleaseEvent(QMouseEvent *event)
    {
        switch((event->button()))
        {
        case Qt::MouseButton::LeftButton:
            OnLButtonUp();
            break;
        case Qt::MouseButton::RightButton:
            OnRButtonUp();
            break;
        }
        Extends::mouseReleaseEvent(event);
    }
    virtual void paintEvent(QPaintEvent *event) 
    {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }

    ///////////////////////////////////////////////////////////////////////
    // Load/Unload Plugin
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientConsolePluginInterface* 
    LoadPlugin(XosError& error)
    {
        XosWebRtcClientConsolePluginInterface* plugin = 0;
        plugin = XosWebRtcClientConsolePluginInterface::AcquireInstance(error);
        return plugin;
    }
    virtual XosError UnloadPlugin
    (XosWebRtcClientConsolePluginInterface* plugin)
    {
        XosError error = 0;
        error = XosWebRtcClientConsolePluginInterface::ReleaseInstance(plugin);
        return error;
    }

protected:
    enum  { 
        FailedConnectServer = QEvent::User+1,
        ConnectServer,
        ListPeers,
        Streaming,
        Invalidate
    };
    class FailedConnectServerQEvent: public QEvent {
    public:
        FailedConnectServerQEvent(const std::string& server)
        : QEvent((Type)(FailedConnectServer)), m_server(server) {}
        const std::string& server() const { return m_server; }
    protected:
        std::string m_server;
    };
    class ChangeStateQEvent: public QEvent {
    public:
        ChangeStateQEvent(int type): QEvent((Type)(type)) {}
    };
    class InvalidateQEvent: public QEvent {
    public:
        InvalidateQEvent(): QEvent((Type)(Invalidate)) {}
    };

protected:
    XosWebRtcClientConsolePluginInterface* m_plugin;
    XosQWebRtcClientOpenGLWidget* m_openglWidget;
    XosString m_serverName;
    int m_serverPort;
    bool m_autoConnectToPeerOn;
    QColor m_bgColorUnconnected;
    QColor m_bgColorConnected;
    QColor m_bgColorStreaming;
    QColor m_bgColor;
    QErrorMessage* m_errorMessage;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSQWEBRTCCLIENTMAINWINDOW_HPP 
