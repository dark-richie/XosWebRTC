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
///   File: XosWebRtcClientFBPluginX11WindowImplemented.hpp
///
/// Author: $author$
///   Date: 4/22/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTFBPLUGINX11WINDOWIMPLEMENTED_HPP
#define _XOSWEBRTCCLIENTFBPLUGINX11WINDOWIMPLEMENTED_HPP

#include "XosGtkWidget.hpp"
#include "XosGtk.hpp"
#include "XosGdk.hpp"
#include "XosXlib.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosX11WindowImplemented
///
/// Author: $author$
///   Date: 4/22/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosX11WindowImplemented
: public XosGtkWidget
{
public:
    typedef XosGtkWidget Extends;

    GtkWidget* m_gtkWidget;
    GdkWindow* m_gdkWindow;
    Window m_xWindow;
    Window m_xTopWindow;
    Screen* m_xScreen;
    Display* m_xDisplay;
    int m_x,m_y, m_width,m_height;
    bool m_dontUseOpenGL;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosX11WindowImplemented
    ///
    ///       Author: $author$
    ///         Date: 4/22/2012
    ///////////////////////////////////////////////////////////////////////
    XosX11WindowImplemented
    (GtkWidget* gtkWidget=0,
     GdkWindow* gdkWindow=0,
     Window xWindow=None,
     Window xTopWindow=None,
     Screen* xScreen=0,
     Display* xDisplay=0,
     int x=0, int y=0,
     int width=0, int height=0,
     bool dontUseOpenGL=false)
    : Extends(gtkWidget),
      m_gtkWidget(gtkWidget),
      m_gdkWindow(gdkWindow),
      m_xWindow(xWindow), 
      m_xTopWindow(xTopWindow),
      m_xScreen(xScreen),
      m_xDisplay(xDisplay),
      m_x(x), m_y(y),
      m_width(width), m_height(height),
      m_dontUseOpenGL(dontUseOpenGL)
    {
    }
    virtual ~XosX11WindowImplemented()
    {
    }

    virtual GtkWidget* Attach
    (GtkWidget* gtkWidget,
     GdkWindow* gdkWindow,
     Window xWindow,
     Window xTopWindow,
     Screen* xScreen,
     Display* xDisplay,
     int x=0, int y=0,
     int width=0, int height=0,
      bool dontUseOpenGL=false)
    {
        XOS_DBT(("(...,dontUseOpenGL=%s)...\n", (dontUseOpenGL)?("true"):("false")));
        m_gtkWidget = Extends::Attach(gtkWidget);
        m_gdkWindow = gdkWindow;
        m_xWindow = xWindow;
        m_xTopWindow = xTopWindow;
        m_xScreen = xScreen;
        m_xDisplay = xDisplay;
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
        m_dontUseOpenGL = dontUseOpenGL;
        return m_gtkWidget;
    }
    virtual GtkWidget* Detach()
    {
        XOS_DBT(("()...\n"));
        GtkWidget* gtkWidget = Extends::Detach();
        m_gtkWidget = 0;
        m_gdkWindow = 0;
        m_xWindow = None;
        m_xTopWindow = None;
        m_xScreen = 0;
        m_xDisplay = 0;
        m_x = 0;
        m_y = 0;
        m_width = 0;
        m_height = 0;
        m_dontUseOpenGL = false;
        return gtkWidget;
    }

    virtual bool InvalidateWindow
    (bool eraseBackground = true);

    virtual bool FillRectangleRGB8
    (uint8_t red, uint8_t green, uint8_t blue,
     int x,int y, int width,int height);

    virtual bool SetDontUseOpenGL(bool dontUseOpenGL=true)
    { return m_dontUseOpenGL=dontUseOpenGL; }

    virtual bool GetDontUseOpenGL() const
    { return m_dontUseOpenGL; }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTFBPLUGINX11WINDOWIMPLEMENTED_HPP 
