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
///   File: XosWebRtcClientFBPluginX11.hpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINX11_HPP
#define _XOSWEBRTCCLIENTFBPLUGINX11_HPP

#include "X11/PluginWindowX11.h"
#include "PluginEvents/DrawingEvents.h"
#include "PluginEvents/X11Event.h"
#include "PluginEvents/X11XEvent.h"
#include "PluginEvents/X11GdkEvent.h"

#include "XosWebRtcClientFBPlugin.hpp"
#include "XosWebRtcClientFBPluginJavaScriptAPI.hpp"
#include "XosWebRtcClientFBPluginX11Window.hpp"
#include "XosWebRtcClientFBPluginX11WindowPeer.hpp"
#include "XosWebRtcClientFBPluginX11WindowImplemented.hpp"
#include "XosDebug.hpp"

#include <gdk/gdkx.h>

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosX11WindowX11EventImplemented
: public FB::X11Event {};

class _EXPORT_CLASS XosX11WindowMouseUpEventImplemented
: public FB::MouseUpEvent {};

class _EXPORT_CLASS XosX11WindowResizedEventImplemented
: public FB::ResizedEvent {};

class _EXPORT_CLASS XosX11WindowRefreshEventImplemented
: public FB::RefreshEvent {};

///////////////////////////////////////////////////////////////////////
///  Class: XosFBPluginX11WindowImplemented
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosFBPluginX11WindowImplemented
: public XosX11WindowImplemented 
{
public:
    typedef XosX11WindowImplemented Extends;

    FB::PluginWindowX11* m_wnd;

    XosFBPluginX11WindowImplemented
    (FB::PluginWindowX11* wnd=0)
    : m_wnd(wnd) {}

    virtual bool InvalidateWindow
    (bool eraseBackground = true)
    {
        bool handled = false;
        GdkRegion* gdkRegion = 0;

        XOS_DBT(("()...\n"));

        if ((handled = ((m_wnd) && (m_gtkWidget) && (m_gdkWindow))))
        {
            FB::Rect rect = m_wnd->getWindowPosition();
            FB::Rect crect = m_wnd->getWindowClipping();

            FB::X11GdkEventExpose exposeEvent
            (m_gdkWindow, gdkRegion, 
             0,0, rect.right-rect.left,rect.bottom-rect.top);

            // send a native X11 event
            exposeEvent.SendEvent();

            // tell gdk to invalidate
            //gdk_window_invalidate_rect(m_gdkWindow, NULL, true);

            // tell fb to invalidate
            //m_wnd->InvalidateWindow();
        }
        return handled;
    }
    bool xFillRectangleRGB8
    (uint8_t red, uint8_t green, uint8_t blue,
     int x,int y, int width,int height)
    {
        bool handled = true;
        return handled;
    }

    virtual void Attach
    (FB::PluginWindowX11* wnd)
    {
        GtkWidget* widget;

        if ((m_wnd = wnd))
        if ((widget = wnd->getWidget()))
        {
            FB::Rect rect = wnd->getWindowPosition();
            FB::Rect crect = wnd->getWindowClipping();

            GTK_WIDGET_UNSET_FLAGS(widget, GTK_DOUBLE_BUFFERED);
            GTK_WIDGET_SET_FLAGS(widget, GTK_APP_PAINTABLE);

            Extends::Attach
            (widget, gtk_widget_get_window(widget), 
             wnd->getWindow(), wnd->getTopLevelWindow(),
             GDK_SCREEN_XSCREEN(gtk_widget_get_screen(widget)),
             GDK_DISPLAY_XDISPLAY(gtk_widget_get_display(widget)),
             0,0, rect.right-rect.left,rect.bottom-rect.top);
        }
    }
    virtual GtkWidget* Detach()
    {
        GtkWidget* detached = Extends::Detach();
        m_wnd = 0;
        return detached;
    }
    virtual void Resize
    (int x, int y, int width, int height)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }
};

FB_FORWARD_PTR(XosWebRtcClientFBPluginX11)
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginX11Implement
///
///  Author: $author$
///    Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPluginImplement
XosWebRtcClientFBPluginX11Implement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientFBPluginX11
///
///  Author: $author$
///    Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientFBPlugin
XosWebRtcClientFBPluginX11Extend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginX11
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class XosWebRtcClientFBPluginX11
: virtual public XosWebRtcClientFBPluginX11Implement,
  public XosWebRtcClientFBPluginX11Extend
{
public:
    typedef XosWebRtcClientFBPluginX11Implement Implements;
    typedef XosWebRtcClientFBPluginX11Extend Extends;

    XosWebRtcClientFBPluginX11Window m_window;
    XosWebRtcClientFBPluginX11WindowPeer m_windowPeer;
    XosFBPluginX11WindowImplemented m_wnd;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientFBPluginX11
    ///
    ///       Author: $author$
    ///         Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientFBPluginX11(const std::string& mimeType);
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientFBPluginX11
    ///
    ///      Author: $author$
    ///        Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientFBPluginX11();

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::X11Event, onX11Event, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::ResizedEvent, onWindowResized, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::RefreshEvent, onWindowRefresh, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowX11)
        PLUGIN_EVENT_MAP_CASCADE(XosWebRtcClientFBPlugin)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent* evt, FB::PluginWindowX11* wnd);
    virtual bool onWindowDetached(FB::DetachedEvent* evt, FB::PluginWindowX11* wnd);
    virtual bool onWindowResized(FB::ResizedEvent *evt, FB::PluginWindowX11* wnd);
    virtual bool onWindowRefresh(FB::RefreshEvent *evt, FB::PluginWindowX11* wnd);
    virtual bool onMouseUp(FB::MouseUpEvent* evt, FB::PluginWindowX11* wnd);
    virtual bool onX11Event(FB::X11Event* evt, FB::PluginWindowX11* wnd);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

    ////////////////////////////////////////////////////////////////////////
    ///  Function: Delegate
    ///
    ///    Author: $author$
    ///      Date: 4/20/2012
    ////////////////////////////////////////////////////////////////////////
    virtual Implements::Implements* Delegate(EventsInterface* events=0)
    { return m_window.Delegate(events); }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINX11_HPP 
