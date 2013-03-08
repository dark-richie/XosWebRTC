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
///   File: XosWebRtcClientFBPluginMac.mm
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientFBPluginMac.hh"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPlugin
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticInitialize
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticInitialize()
{
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPlugin::StaticDeinitialize
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientFBPlugin::StaticDeinitialize()
{
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientFBPluginMac
///
/// Author: $author$
///   Date: 4/12/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientFBPluginMac::XosWebRtcClientFBPluginMac
///
///       Author: $author$
///         Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginMac::XosWebRtcClientFBPluginMac
(const std::string& mimeType)
: Extends(mimeType),
  m_window(*this),
  m_windowPeer(m_window)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientFBPluginMac::~XosWebRtcClientFBPluginMac
///
///       Author: $author$
///         Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientFBPluginMac::~XosWebRtcClientFBPluginMac()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onWindowAttached
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onWindowAttached
(FB::AttachedEvent* evt, FB::PluginWindowMac* wnd)
{
    bool handled = false;
    bool isCA = (FB::PluginWindowMac::DrawingModelCoreAnimation == wnd->getDrawingModel());
    bool isInvalidatingCA = (FB::PluginWindowMac::DrawingModelInvalidatingCoreAnimation == wnd->getDrawingModel());
    m_wnd.m_wnd = wnd;
    m_windowPeer.OnWindowAttached(&m_wnd);
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onWindowDetached
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onWindowDetached
(FB::DetachedEvent* evt, FB::PluginWindowMac* wnd)
{
    bool handled = false;
    m_windowPeer.OnWindowDetached(&m_wnd);
    m_wnd.m_wnd = 0;
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onWindowResized
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onWindowResized
(FB::ResizedEvent *evt, FB::PluginWindowMac* wnd)
{
    bool handled = false;
    if ((wnd))
    {
        FB::Rect rect = wnd->getWindowPosition();
        m_windowPeer.OnWindowResized
        (rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top,
         (XosMacWindowResizedEventImplemented*)(evt));
    }
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onWindowRefresh
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onWindowRefresh
(FB::RefreshEvent *evt, FB::PluginWindowMac* wnd)
{
    bool handled = false;
    if ((evt))
    {
        FB::Rect rect = evt->bounds;
        m_windowPeer.OnWindowRefresh
        (rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top,
         (XosMacWindowRefreshEventImplemented*)(evt));
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onDrawCG
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onDrawCG
(FB::CoreGraphicsDraw* evt, FB::PluginWindowMacCG* cg)
{
    bool handled = false;
    if ((evt))
    {
        FB::Rect clip(evt->clip);
        FB::Rect rect(evt->bounds);
        CGContextRef cgContextRef(evt->context);
        XosMacWindowCGImplemented cgContext
        (cgContextRef, rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top,
         clip.left,clip.top, clip.right-clip.left,clip.bottom-clip.top);

        handled = m_windowPeer.OnWindowDrawCG
        (rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top,
         &cgContext, (XosMacWindowDrawCGEventImplemented*)(evt));
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientFBPluginMac::onMouseUp
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientFBPluginMac::onMouseUp
(FB::MouseUpEvent* evt, FB::PluginWindowMac* wnd)
{
    bool handled = false;
    if ((evt))
    switch(evt->m_Btn)
    {
    case FB::MouseUpEvent::MouseButton_Left:
        m_windowPeer.OnLMouseUp((XosMacWindowMouseUpEventImplemented*)(evt));
        break;
    case FB::MouseUpEvent::MouseButton_Right:
        m_windowPeer.OnRMouseUp((XosMacWindowMouseUpEventImplemented*)(evt));
        break;
    }
    return handled;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
