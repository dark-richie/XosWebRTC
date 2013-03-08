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
///   File: XosMacWebRtcClientOpenGLVideoRenderer.hh
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTOPENGLVIDEORENDERER_HH
#define _XOSMACWEBRTCCLIENTOPENGLVIDEORENDERER_HH

#include "XosWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosMacOpenGLContext.hh"
#include "XosPlatform_cocoa.hh"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosMacWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacWebRtcClientOpenGLVideoRenderer
: public XosWebRtcClientOpenGLVideoRenderer
{
public:
    typedef XosWebRtcClientOpenGLVideoRenderer Extends;

    XosMacOpenGLContext m_context;

    XosMacWebRtcClientOpenGLVideoRenderer(NSOpenGLView* view=0): m_view(view) {}
    virtual ~XosMacWebRtcClientOpenGLVideoRenderer() {}

    virtual bool init(NSOpenGLView* view) { 
        m_view = view;
        return m_context.Init(m_view); 
    }
    virtual bool init() { 
        return m_context.Init(m_view); 
    }
    virtual bool finish() { 
        return m_context.Finish(); 
    }

    virtual bool swapBuffers() {
#if defined(OBJC) 
        NSOpenGLContext* glContext;
        if ((glContext = m_context.GetContext())) {
            [glContext flushBuffer];
            return true;
        }
#else // defined(OBJC) 
#endif // defined(OBJC) 
        return false;
    }
    virtual bool reshape() {
#if defined(OBJC)  
#else // defined(OBJC)  
#endif // defined(OBJC)  
        return false;
    }
    using Extends::reshape;

protected:
    NSOpenGLView* m_view;
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSMACWEBRTCCLIENTOPENGLVIDEORENDERER_HH 
        

