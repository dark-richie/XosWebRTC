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
///   File: XosQWebRtcClientOpenGLVideoRenderer.hpp
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSQWEBRTCCLIENTOPENGLVIDEORENDERER_HPP
#define _XOSQWEBRTCCLIENTOPENGLVIDEORENDERER_HPP

#include <QtGui>
#include <QtOpenGL>
#include "XosWebRtcClientOpenGLVideoRenderer.hpp"

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

typedef XosWebRtcClientOpenGLVideoRendererImplement 
XosQWebRtcClientOpenGLVideoRendererImplement;

typedef XosWebRtcClientOpenGLVideoRenderer 
XosQWebRtcClientOpenGLVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosQWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 2/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosQWebRtcClientOpenGLVideoRenderer
: virtual public XosQWebRtcClientOpenGLVideoRendererImplement,
  public XosQWebRtcClientOpenGLVideoRendererExtend
{
public:
    typedef XosQWebRtcClientOpenGLVideoRendererImplement Implements;
    typedef XosQWebRtcClientOpenGLVideoRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosQWebRtcClientOpenGLVideoRenderer
    ///
    ///       Author: $author$
    ///         Date: 2/4/2013
    ///////////////////////////////////////////////////////////////////////
    XosQWebRtcClientOpenGLVideoRenderer()
    : m_widget(0), m_glContext(0)
    {
    }
    virtual ~XosQWebRtcClientOpenGLVideoRenderer()
    {
    }

    virtual bool init(QWidget* widget) {
        if ((m_widget = widget)) {
            QGLFormat glFormat
            (QGL::DoubleBuffer | QGL::Rgba | QGL::NoOverlay 
             | QGL::NoAccumBuffer | QGL::NoStencilBuffer 
             | QGL::NoStereoBuffers | QGL::NoSampleBuffers);
            if ((m_glContext = new QGLContext(glFormat, widget))) {
                if ((m_glContext->create())) {
                    m_glContext->makeCurrent();
                    prepareOpenGL();
                    return true;
                }
                delete m_glContext;
                m_glContext = 0;
            }
            m_widget = 0;
        }
        return false;
    }
    virtual bool finish() {
        if ((m_widget)) {
            if ((m_glContext)) {
                m_glContext->doneCurrent();
                delete m_glContext;
                m_glContext = 0;
            }
            m_widget = 0;
        }
        return false;
    }
    virtual bool swapBuffers() {
        if ((m_glContext)) {
            m_glContext->swapBuffers();
            return true;
        }
        return false;
    }
    using Extends::reshape;
    virtual bool reshape() {
        if ((m_widget) && (m_glContext)) {
            int width = m_widget->width();
            int height = m_widget->height();
            reshape(width, height);
            return true;
        }
        return false;
    }
protected:
    QWidget* m_widget;
    QGLContext* m_glContext;
};

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSQWEBRTCCLIENTOPENGLVIDEORENDERER_HPP 
