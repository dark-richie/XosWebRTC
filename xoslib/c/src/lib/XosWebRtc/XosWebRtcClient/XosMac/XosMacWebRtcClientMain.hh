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
///   File: XosMacWebRtcClientMain.hh
///
/// Author: $author$
///   Date: 12/30/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSMACWEBRTCCLIENTMAIN_HH
#define _XOSMACWEBRTCCLIENTMAIN_HH

#include "XosMacWindowMain.hh"
#include "XosMacWebRtcClientPlugoutMain.hh"
#include "XosMacWebRtcClientOpenGLVideoRenderer.hh"

#define DEFAULT_XOSMACWEBRTCCLIENT_OPENGL_VIEW_BG_COLOR blackColor

class XosMacWebRtcClientImageObserver;

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClientMainView
///
///    Author: $author$
///      Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClientMainView: NSOpenGLView {
    bool m_invalid;
    XosMacWebRtcClientImageObserver* m_imageObserver;
    XosWebRtcClientImageInterface* m_image;
    XosMacWebRtcClientOpenGLVideoRenderer m_openglRenderer;
    }
    - (id)init:(NSRect)rect;
    - (void)invalidateWindow:(bool)eraseBackground;
    - (void)prepareOpenGL;
    - (void)reshape;
    - (void)drawRect:(NSRect)rect;
    - (void)setImage:(XosWebRtcClientImageInterface*)image;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClientMainWindow
///
///    Author: $author$
///      Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClientMainWindow: XosMacMainWindow {
    XosWebRtcClientImageInterface* m_image;
    }
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (void)setImage:(XosWebRtcClientImageInterface*)image;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: XosMacWebRtcClientMain
///
///    Author: $author$
///      Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@interface XosMacWebRtcClientMain: XosMacWindowMain {
    XosMacWebRtcClientPlugoutMain m_webrtcMain;
    }
    - (XosMacMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  

#endif // _XOSMACWEBRTCCLIENTMAIN_HH 
        

