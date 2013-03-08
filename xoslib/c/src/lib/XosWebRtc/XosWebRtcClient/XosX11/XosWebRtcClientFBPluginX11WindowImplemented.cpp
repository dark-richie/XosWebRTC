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
///   File: XosWebRtcClientFBPluginX11WindowImplemented.cpp
///
/// Author: $author$
///   Date: 4/22/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientFBPluginX11WindowImplemented.hpp"
#include "XosXColormap.hpp"
#include "XosXColor.hpp"
#include "XosXGC.hpp"
#include "XosGdkEvent.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosX11WindowImplemented
///
/// Author: $author$
///   Date: 4/22/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosX11WindowImplemented::InvalidateWindow
///
///    Author: $author$
///      Date: 4/27/2012
///////////////////////////////////////////////////////////////////////
bool XosX11WindowImplemented::InvalidateWindow
(bool eraseBackground)
{
    bool handled = false;
    GdkRegion* gdkRegion = 0;

    XOS_DBT(("()...\n"));

    if ((handled = ((m_gtkWidget) && (m_gdkWindow))))
    {
        XosGdkEventExpose exposeEvent
        (m_gdkWindow, gdkRegion, m_x,m_y, m_width,m_height);

        gdk_threads_enter();
        exposeEvent.Put();
        gdk_threads_leave();
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosX11WindowImplemented::
///
///    Author: $author$
///      Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
bool XosX11WindowImplemented::FillRectangleRGB8
(uint8_t red, uint8_t green, uint8_t blue,
 int x,int y, int width,int height)
{
    bool handled = false;
    XosXColormap xcm;
    XosXColor xc;
    XosXGC xgc;
    XosError error;

    XOS_DBT(("()...\n"));

    if ((error = m_window.FillRectangleRGB8
        (red, green, blue, x,y, width,height)))

    if ((m_xDisplay) && (m_xWindow != None))
    {
        XOS_DBT(("() xcm.AttachDefault()...\n"));
        if (!(error = xcm.AttachDefault(m_xDisplay)))
        {
            XOS_DBT(("() xc.AllocateRGB8()...\n"));
            if (!(error = xc.AllocateRGB8(m_xDisplay, xcm.Attached(), red, green, blue)))
            {
                XOS_DBT(("() xgc.Create()...\n"));
                if (!(error = xgc.Create(m_xDisplay, m_xWindow)))
                {
                    XOS_DBT(("() xgc.FillRectangle()...\n"));
                    xgc.FillRectangle(xc.Attached(), x,y, width,height);
                    xgc.Destroy();
                }
                xc.Free();
            }
        }
    }
    return handled;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
