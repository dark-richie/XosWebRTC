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
///   File: XosX11WebRtcClientOpenGLVideoRenderer.hpp
///
/// Author: $author$
///   Date: 1/22/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSX11WEBRTCCLIENTOPENGLVIDEORENDERER_HPP
#define _XOSX11WEBRTCCLIENTOPENGLVIDEORENDERER_HPP

#include "XosPlatform_winsock2api.hpp"
#include "XosPlatform_X11_Xlib.hpp"
#include "XosPlatform_GL_gl.hpp"
#include "XosPlatform_GL_glu.hpp"
#include "XosPlatform_GL_glx.hpp"
#include "XosWebRtcClientOpenGLVideoRenderer.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientOpenGLVideoRenderer 
XosX11WebRtcClientOpenGLVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosX11WebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 1/22/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosX11WebRtcClientOpenGLVideoRenderer
: public XosX11WebRtcClientOpenGLVideoRendererExtend
{
public:
    typedef XosX11WebRtcClientOpenGLVideoRendererExtend Extends;

    Display* m_dpy;
    Window m_win;
    GLXContext m_glc;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosX11WebRtcClientOpenGLVideoRenderer
    ///
    ///       Author: $author$
    ///         Date: 1/22/2013
    ///////////////////////////////////////////////////////////////////////
    XosX11WebRtcClientOpenGLVideoRenderer()
    : m_dpy(0),
      m_win(None),
      m_glc(0)
    {
    }
    virtual ~XosX11WebRtcClientOpenGLVideoRenderer()
    {
        finish();
    }

    virtual bool init(Display* dpy, Window win)
    {
        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        bool isSuccess = false;
        int screen = 0;
        XVisualInfo* vi;
        Status err;
        XWindowAttributes watt;

        XOS_DBT(("()...\n"));

        if ((dpy) && (None != (win)))
        {
            if ((Success != (err = XGetWindowAttributes(dpy, win, &watt))))
            {   XOS_DBE(("() returned %d on XGetWindowAttributes()\n", err)); }
            //else
            screen = XScreenNumberOfScreen(watt.screen);

            if (!(vi = glXChooseVisual(dpy, screen, att)))
            {   XOS_DBE(("() failed on glXChooseVisual()\n")); }
            else
            if (None != (m_glc = glXCreateContext(dpy, vi, NULL, GL_TRUE)))
            {
                if (!(glXMakeCurrent(dpy, win, m_glc)))
                {   XOS_DBE(("() failed on glXMakeCurrent()\n")); }
                else
                {
                    m_dpy = dpy;
                    m_win = win;
                    return true;
                }
                glXDestroyContext(m_dpy, m_glc);
                m_glc = 0;
            }
            else
            {   XOS_DBE(("() failed on glXCreateContext()\n")); }
        }
        return isSuccess;
    }
    virtual bool finish()
    {
        bool isSuccess = false;

        XOS_DBT(("()...\n"));

        if ((m_dpy) && (m_glc))
        {
            if (!(glXMakeCurrent(m_dpy, None, 0)))
            {   XOS_DBE(("() failed on glXMakeCurrent()\n")); }
            else
            isSuccess = true;
            glXDestroyContext(m_dpy, m_glc);
        }
        m_glc = 0;
        m_win = None;
        m_dpy = 0;
        return isSuccess;
    }
    virtual bool swapBuffers()
    {
        bool isSuccess = false;

        XOS_DBT(("()...\n"));

        if ((m_dpy) && (None != (m_win)))
        {
            glXSwapBuffers(m_dpy, m_win);
            isSuccess = true;
        }
        return isSuccess;
    }

    virtual GLenum textureImageFormat() const 
    { return GL_RGBA; }
};


#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSX11WEBRTCCLIENTOPENGLVIDEORENDERER_HPP 
