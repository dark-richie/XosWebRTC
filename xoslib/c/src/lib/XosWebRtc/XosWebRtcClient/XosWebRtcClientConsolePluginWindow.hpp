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
///   File: XosWebRtcClientConsolePluginWindow.hpp
///
/// Author: $author$
///   Date: 1/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOW_HPP
#define _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOW_HPP

#include "XosWebRtcClientConsoleWindow.hpp"
#include "XosWebRtcClientImageInterface.hpp"
#include "XosWebRtcClientEventInterface.hpp"
#include "XosWebRtcClientConsolePluginVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientConsoleWindowImplement 
XosWebRtcClientConsolePluginWindowImplementImplement;

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePluginWindowImplement
///
/// Author: $author$
///   Date: 1/2/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePluginWindowImplement
: virtual public XosWebRtcClientConsolePluginWindowImplementImplement,
  virtual public XosWebRtcClientImageInterface,
  virtual public XosWebRtcClientEventInterface
{
public:
    typedef XosWebRtcClientConsolePluginWindowImplementImplement Implements;
};

typedef XosWebRtcClientConsoleWindow
XosWebRtcClientConsolePluginWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientConsolePluginWindow
///
/// Author: $author$
///   Date: 1/2/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientConsolePluginWindow
: virtual public XosWebRtcClientConsolePluginWindowImplement,
  public XosWebRtcClientConsolePluginWindowExtend
{
public:
    typedef XosWebRtcClientConsolePluginWindowImplement Implements;
    typedef XosWebRtcClientConsolePluginWindowExtend Extends;

    XosWebRtcClientImageObserverInterface* m_imageObserver;
    XosWebRtcClientEventObserverInterface* m_eventObserver;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientConsolePluginWindow
    ///
    ///       Author: $author$
    ///         Date: 1/2/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientConsolePluginWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_imageObserver(0), m_eventObserver(0)
    {
        m_postInvalidateWindowUIMessages = true;
    }
    virtual ~XosWebRtcClientConsolePluginWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToConnectToServer();
        else
        Extends::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers() {
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToListPeers();
        else
        Extends::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming() { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToStreaming();
        else
        Extends::OnChangeStateToStreaming();
    }
    virtual void OnChangeState(const std::string& toStateName) { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeState(toStateName);
        else
        Extends::OnChangeState(toStateName);
    }

    virtual void OnFailedToConnectToServer(const std::string& server) {
        if ((m_eventObserver))
            m_eventObserver->OnFailedToConnectToServer(server);
        else
        Extends::OnFailedToConnectToServer(server);
    }
    ///////////////////////////////////////////////////////////////////////
    // Event Interface
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        Extends::OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        Extends::OnRButtonUp();
    }

    virtual void RegisterEventObserver
    (XosWebRtcClientEventObserverInterface* observer) {
        if ((observer))
            m_eventObserver = observer;
    }
    virtual void UnregisterEventObserver
    (XosWebRtcClientEventObserverInterface* observer) {
        if ((observer == m_eventObserver))
            m_eventObserver = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow
    (bool eraseBackground = true) 
    { 
        if ((m_imageObserver))
            m_imageObserver->InvalidateWindow(eraseBackground);
        return true; 
    }
    ///////////////////////////////////////////////////////////////////////
    // Image Interface
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        //XOS_DBI(("() in.."));
        if ((imageObserver))
            m_imageObserver = imageObserver;
    }
    virtual void UnregisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        //XOS_DBI(("() in.."));
        if (imageObserver == m_imageObserver)
            m_imageObserver = 0;
    }

    virtual uint8_t* AcquireRemoteImage
    (int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        XosWebRtcClientVideoRenderer* video;
        //XOS_DBI(("() in.."));
        if ((video = remote_video_.get())) {
            video->Lock();
            if (!(image = video->d_image())) {
                video->Unlock();
            } else {
                width = video->image_width();
                height = video->image_height();
                switch(video->RenderImageFormat()) 
                {
                case cricket::FOURCC_ARGB:
                    format = FORMAT_GL_BGRA;
                default:
                    format = FORMAT_NONE;
                }
            }
        }
        return image;
    }
    virtual bool ReleaseRemoteImage
    (uint8_t* image)
    {
        bool success = false;
        XosWebRtcClientVideoRenderer* video;
        //XOS_DBI(("() in.."));
        if ((video = remote_video_.get())) {
            if (!(image != video->d_image())) {
                video->Unlock();
                success = true;
            }
        }
        return success;
    }

    virtual uint8_t* AcquireLocalImage
    (int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        XosWebRtcClientVideoRenderer* video;
        //XOS_DBI(("() in.."));
        if ((video = local_video_.get())) {
            video->Lock();
            if (!(image = video->d_image())) {
                video->Unlock();
            } else {
                width = video->image_width();
                height = video->image_height();
                switch(video->RenderImageFormat()) 
                {
                case cricket::FOURCC_ARGB:
                    format = FORMAT_GL_BGRA;
                default:
                    format = FORMAT_NONE;
                }
            }
        }
        return image;
    }
    virtual bool ReleaseLocalImage
    (uint8_t* image)
    {
        bool success = false;
        XosWebRtcClientVideoRenderer* video;
        //XOS_DBI(("() in.."));
        if ((video = local_video_.get())) {
            if (!(image != video->d_image())) {
                video->Unlock();
                success = true;
            }
        }
        return success;
    }

    virtual uint8_t* GetRemoteImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        XosWebRtcClientVideoRenderer* video;
        if ((video = remote_video_.get()))
            image = video->d_image();
        return image;
    }
    virtual uint8_t* GetLocalImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        XosWebRtcClientVideoRenderer* video;
        if ((video = local_video_.get()))
            image = video->d_image();
        return image;
    }

    ///////////////////////////////////////////////////////////////////////
    // Renderer
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XosWebRtcClientVideoRenderer* renderer = 0;
        renderer = new XosWebRtcClientConsolePluginVideoRenderer
        (*this, width, height, isRemote);
        return renderer; 
    }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) 
    { 
        if ((renderer))
        {
            delete renderer;
            return true;
        }
        return false; 
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTCONSOLEPLUGINWINDOW_HPP 
