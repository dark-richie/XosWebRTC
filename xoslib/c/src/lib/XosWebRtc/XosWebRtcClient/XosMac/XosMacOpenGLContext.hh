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
///   File: XosMacOpenGLContext.hh
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACOPENGLCONTEXT_HH
#define _XOSMACOPENGLCONTEXT_HH

#include "XosInterfaceBase.hpp"
#include "XosExportBase.hpp"
#include "XosPlatform_cocoa.hh"
#include "XosPlatform_opengl.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosMacOpenGLContextImplement
///
///  Author: $author$
///    Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
typedef XosInterfaceBase
XosMacOpenGLContextImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosMacOpenGLContextExtend
///
///  Author: $author$
///    Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosMacOpenGLContextExtend;

///////////////////////////////////////////////////////////////////////
///  Class: XosMacOpenGLContext
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosMacOpenGLContext
: virtual public XosMacOpenGLContextImplement,
  public XosMacOpenGLContextExtend
{
public:
    typedef XosMacOpenGLContextImplement Implements;
    typedef XosMacOpenGLContextExtend Extends;

    XosMacOpenGLContext() {}
    virtual ~XosMacOpenGLContext() {}

    virtual bool Init(NSOpenGLView* view) {
        bool isSuccess = false;
        NSOpenGLPixelFormatAttribute* pixelFormatAttributes;
        NSOpenGLPixelFormat* pixelFormat;
        if ((m_view = view)) {
            if ((pixelFormatAttributes = GetPixelFormatAttributes())) {
                if ((m_pixelFormat = GetPixelFormat())) {
                    if ((pixelFormat = AcquirePixelFormat(pixelFormatAttributes))) {
                        isSuccess = !(pixelFormat != SetPixelFormat(pixelFormat));
                        ReleasePixelFormat(pixelFormat);
                        return isSuccess;
                    }
                    m_pixelFormat = 0;
                }
            }
            m_view = 0;
        }
        return isSuccess;
    }
    virtual bool Finish() {
        bool isSuccess = false;
        if ((m_pixelFormat)) {
            isSuccess = !(m_pixelFormat != SetPixelFormat(m_pixelFormat));
            m_pixelFormat = 0;
        }
        m_view = 0;
        return isSuccess;
    }

    NSOpenGLPixelFormat* AcquirePixelFormat(NSOpenGLPixelFormatAttribute* attributes) const;
    bool ReleasePixelFormat(NSOpenGLPixelFormat* pixelFormat) const;

    NSOpenGLPixelFormat* SetPixelFormat(NSOpenGLPixelFormat* toPixelFormat);
    NSOpenGLPixelFormat* GetPixelFormat() const;

    NSOpenGLContext* GetContext() const;
    NSOpenGLPixelFormatAttribute* GetPixelFormatAttributes() const;

protected:
    NSOpenGLView* m_view;
    NSOpenGLPixelFormat* m_pixelFormat;
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSMACOPENGLCONTEXT_HH 
        

