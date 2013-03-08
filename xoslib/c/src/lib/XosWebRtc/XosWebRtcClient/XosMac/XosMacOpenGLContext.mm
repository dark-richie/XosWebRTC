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
///   File: XosMacOpenGLContext.mm
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////
#include "XosMacOpenGLContext.hh"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosMacOpenGLContext
///
/// Author: $author$
///   Date: 12/27/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::AcquirePixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* XosMacOpenGLContext::AcquirePixelFormat(NSOpenGLPixelFormatAttribute* attributes) const {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute*)attributes];
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::ReleasePixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
bool XosMacOpenGLContext::ReleasePixelFormat(NSOpenGLPixelFormat* pixelFormat) const {
    bool isSuccess = false;
#if defined(OBJC) 
    if ((isSuccess = (0 != pixelFormat))) {
        [pixelFormat release];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::SetPixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* XosMacOpenGLContext::SetPixelFormat(NSOpenGLPixelFormat* toPixelFormat) {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    if (((m_view) && (toPixelFormat))) {
        [m_view setPixelFormat:(pixelFormat = toPixelFormat)];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::GetPixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* XosMacOpenGLContext::GetPixelFormat() const {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    if ((m_view)) {
        pixelFormat = [m_view pixelFormat];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::GetContext
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLContext* XosMacOpenGLContext::GetContext() const {
    NSOpenGLContext* context = 0;
#if defined(OBJC) 
    if ((m_view)) {
        context = [m_view openGLContext];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return context;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosMacOpenGLContext::GetPixelFormatAttributes
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormatAttribute* XosMacOpenGLContext::GetPixelFormatAttributes() const
{
#if defined(OBJC) 
    static NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAWindow,         // window rendered
        NSOpenGLPFAAccelerated,    // hardware accelerated
        NSOpenGLPFADoubleBuffer,   // double buffered
        //NSOpenGLPFAMinimumPolicy,  // meets or exceeds attributes
        0
    };
#else // defined(OBJC) 
    NSOpenGLPixelFormatAttribute* attributes = 0;
#endif // defined(OBJC) 
    return attributes;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
