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
///   File: XosXWebRtcClientOpenGLVideoRenderer.hpp
///
/// Author: $author$
///   Date: 1/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTOPENGLVIDEORENDERER_HPP
#define _XOSXWEBRTCCLIENTOPENGLVIDEORENDERER_HPP

#include "XosWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosXOpenGLContext.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosWebRtcClientOpenGLVideoRendererImplement
XosXWebRtcClientOpenGLVideoRendererImplement;

typedef XosWebRtcClientOpenGLVideoRenderer
XosXWebRtcClientOpenGLVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 1/3/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXWebRtcClientOpenGLVideoRenderer
: virtual public XosXWebRtcClientOpenGLVideoRendererImplement,
  public XosXWebRtcClientOpenGLVideoRendererExtend
{
public:
    typedef XosXWebRtcClientOpenGLVideoRendererImplement Implements;
    typedef XosXWebRtcClientOpenGLVideoRendererExtend Extends;

    XosXWebRtcClientOpenGLVideoRenderer
    (Display* xDisplay=0, Window xWindow=None)
    : m_xDisplay(xDisplay),
      m_xWindow(xWindow) {
    }
    virtual ~XosXWebRtcClientOpenGLVideoRenderer() {
    }

    virtual bool init(Display* xDisplay, Window xWindow)
    {
        bool isSuccess = false;
        XOS_DBT(("() in...\n"));
        if ((isSuccess = m_context.Init(xDisplay, xWindow)))
        {
            m_xDisplay = xDisplay;
            m_xWindow = xWindow;
        }
        XOS_DBT(("() ...out\n"));
        return isSuccess;
    }
    virtual bool init()
    {
        XOS_DBT(("()...\n"));
        return m_context.Init(m_xDisplay, m_xWindow);
    }
    virtual bool finish()
    {
        XOS_DBT(("()...\n"));
        m_xDisplay = 0;
        m_xWindow = None;
        return m_context.Finish();
    }

    virtual bool swapBuffers()
    {
        bool isSuccess = false;
        XOS_DBT(("()...\n"));
        if ((isSuccess = ((m_xDisplay) && (None != (m_xWindow)))))
            glXSwapBuffers(m_xDisplay, m_xWindow);
        return isSuccess;
    }
    virtual bool reshape() 
    {
        bool isSuccess = false;
        XOS_DBT(("()...\n"));
        if ((m_xDisplay) && (None != (m_xWindow))) {
            Status success;
            XWindowAttributes xWindowAttributes;
            if (!(success = XGetWindowAttributes
                (m_xDisplay, m_xWindow, &xWindowAttributes))) {
                XOS_DBE(("() failed on XGetWindowAttributes()\n"));
            } else {
                reshape(xWindowAttributes.width, xWindowAttributes.height);
                isSuccess = true;
            }
        }
        return isSuccess;
    }
    using Extends::reshape;

protected:
    Display* m_xDisplay;
    Window m_xWindow;
    XosXOpenGLContext m_context;
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTOPENGLVIDEORENDERER_HPP 
