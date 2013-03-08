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
///   File: XosMacWebRtcClient.hh
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENT_HH
#define _XOSMACWEBRTCCLIENT_HH

#include "XosMacWindowMain.hh"
#include "XosMacWebRtcClientOpenGLVideoRenderer.hh"
#include "XosMacOpenGLContext.hh"

#define XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_RED   0
#define XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_GREEN 0
#define XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_BLUE  128
#define XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_ALPHA 255

#define XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_RED 0
#define XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_GREEN 128
#define XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_BLUE 0
#define XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_ALPHA 255

#if defined(OBJC)
///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClientMainView
///
///    Author: $author$
///      Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClientMainView: NSOpenGLView {
    void *m_remoteImage, *m_localImage;
    unsigned m_remoteImageWidth, m_remoteImageHeight, m_remoteImageDepth, m_remoteImageSize;
    unsigned m_localImageWidth, m_localImageHeight, m_localImageDepth, m_localImageSize;
    char m_remoteImagePixel[4];
    char m_localImagePixel[4];
    XosMacWebRtcClientOpenGLVideoRenderer m_openglRenderer;
    }
    - (id)init:(NSRect)rect;
    - (void)prepareOpenGL;
    - (void)reshape;
    - (void)drawRect:(NSRect)rect;
@end
///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClientMainWindow
///
///    Author: $author$
///      Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClientMainWindow: XosMacMainWindow {
    }
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env;
@end
///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClient
///
///    Author: $author$
///      Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClient: XosMacWindowMain {
    }
    - (XosMacMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
@end
#endif // defined(OBJC)

#endif // _XOSMACWEBRTCCLIENT_HH 
        

