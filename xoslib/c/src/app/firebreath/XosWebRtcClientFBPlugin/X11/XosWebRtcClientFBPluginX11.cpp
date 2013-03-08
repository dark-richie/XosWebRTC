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
///   File: XosWebRtcClientFBPluginX11.cpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientFBPluginX11.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Function: MakeRect
///
///    Author: $author$
///      Date: 4/28/2012
///////////////////////////////////////////////////////////////////////
FB::Rect MakeRect(int left, int top, int right, int bottom)
{
    FB::Rect normalizedRect;
    normalizedRect.left = left;
    normalizedRect.top = top;
    normalizedRect.right = right;
    normalizedRect.bottom = bottom;
    return normalizedRect;
}

///////////////////////////////////////////////////////////////////////
///  Function: NormalizeRect
///
///    Author: $author$
///      Date: 4/28/2012
///////////////////////////////////////////////////////////////////////
FB::Rect NormalizeRect(const FB::Rect& rect)
{
    FB::Rect normalizedRect;
    normalizedRect.left = 0;
    normalizedRect.top = 0;
    normalizedRect.right -= rect.left;
    normalizedRect.bottom -= rect.top;
    return normalizedRect;
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPlugin
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticInitialize
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticInitialize()
{
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticDeinitialize
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticDeinitialize()
{
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginX11
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientFBPluginX11::XosWebRtcClientFBPluginX11
///
///       Author: $author$
///         Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginX11::XosWebRtcClientFBPluginX11
(const std::string& mimeType)
: Extends(mimeType),
  m_window(*this),
  m_windowPeer(m_window)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientFBPluginX11::~XosWebRtcClientFBPluginX11
///
///       Author: $author$
///         Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginX11::~XosWebRtcClientFBPluginX11()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onWindowAttached
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onWindowAttached
(FB::AttachedEvent* evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;
    m_wnd.Attach(wnd);
    m_windowPeer.OnWindowAttached(&m_wnd);
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onWindowDetached
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onWindowDetached
(FB::DetachedEvent* evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;
    m_windowPeer.OnWindowDetached(&m_wnd);
    m_wnd.Detach();
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onWindowResized
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onWindowResized
(FB::ResizedEvent *evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;

    XOS_DBT(("()...\n"));

    if ((evt) && (wnd))
    {
        FB::Rect rect = wnd->getWindowPosition();
        FB::Rect crect = wnd->getWindowClipping();
        m_wnd.Resize
        (0,0, rect.right-rect.left,rect.bottom-rect.top);
        m_windowPeer.OnWindowResized
        (0,0, rect.right-rect.left,rect.bottom-rect.top,
         (XosX11WindowResizedEventImplemented*)(evt));
    }
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onWindowRefresh
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onWindowRefresh
(FB::RefreshEvent *evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;

    XOS_DBT(("()...\n"));

    if ((evt))
    {
        FB::Rect rect = wnd->getWindowPosition();
        FB::Rect crect = wnd->getWindowClipping();
        handled = m_windowPeer.OnWindowRefresh
        (0,0, rect.right-rect.left,rect.bottom-rect.top,
         (XosX11WindowRefreshEventImplemented*)(evt));
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onX11Event
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onX11Event
(FB::X11Event* evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;
    GdkEvent* gdkEvent;

    //XOS_DBT(("()...\n"));

    if ((evt) && (wnd))
    if ((gdkEvent = evt->m_event))
    {
        GdkEventType type = gdkEvent->type;
        switch(type)
        {
        case GDK_EXPOSE:
            XOS_DBT(("() GDK_EXPOSE...\n"));

            if (!(handled = m_windowPeer.OnX11Event
            ((XosX11WindowX11EventImplemented*)(evt))))
            //if (0)
            {
                FB::Rect rect = wnd->getWindowPosition();
                FB::Rect crect = wnd->getWindowClipping();
                FB::RefreshEvent refreshEvent(NormalizeRect(rect));
                //handled = onWindowRefresh(&refreshEvent, wnd);
                handled = m_windowPeer.OnWindowRefresh
                (0,0, rect.right-rect.left,rect.bottom-rect.top,
                 (XosX11WindowRefreshEventImplemented*)(&refreshEvent));
            }
            break;

        case GDK_CONFIGURE:
            XOS_DBT(("() GDK_CONFIGURE...\n"));

            if (!(handled = m_windowPeer.OnX11Event
            ((XosX11WindowX11EventImplemented*)(evt))))
            if (0)
            {
                int x = gdkEvent->configure.x;
                int y = gdkEvent->configure.y;
                int width = gdkEvent->configure.width;
                int height = gdkEvent->configure.height;
                FB::Rect rect = MakeRect(x,y, x+width,y+height);
                FB::ResizedEvent resizedEvent;
                //handled = onWindowResized(&resizedEvent, wnd);
                m_wnd.Resize
                (0,0, rect.right-rect.left,rect.bottom-rect.top);
                handled = m_windowPeer.OnWindowResized
                (0,0, rect.right-rect.left,rect.bottom-rect.top,
                 (XosX11WindowResizedEventImplemented*)(&resizedEvent));
            }
            break;

        default:
            handled = m_windowPeer.OnX11Event
            ((XosX11WindowX11EventImplemented*)(evt));
        }
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginX11::onMouseUp
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginX11::onMouseUp
(FB::MouseUpEvent* evt, FB::PluginWindowX11* wnd)
{
    bool handled = false;
    if ((evt))
    switch(evt->m_Btn)
    {
    case FB::MouseUpEvent::MouseButton_Left:
        m_windowPeer.OnLMouseUp((XosX11WindowMouseUpEventImplemented*)(evt));
        break;
    case FB::MouseUpEvent::MouseButton_Right:
        m_windowPeer.OnRMouseUp((XosX11WindowMouseUpEventImplemented*)(evt));
        break;
    }
    return handled;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
