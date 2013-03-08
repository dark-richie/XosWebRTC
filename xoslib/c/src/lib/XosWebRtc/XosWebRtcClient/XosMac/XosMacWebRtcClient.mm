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
///   File: XosMacWebRtcClient.mm
///
/// Author: $author$
///   Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
#include "XosMacWebRtcClient.hh"

#if defined(OBJC)
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClientMainView
///
///       Author: $author$
///         Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClientMainView
    - (id)init:(NSRect)rect {
        [super initWithFrame:rect pixelFormat:[NSOpenGLView defaultPixelFormat]];

        XosMacWebRtcClientOpenGLVideoRenderer::
        ColorIndex color = m_openglRenderer.textureImageColorIndex();

        m_remoteImagePixel[color.Red] = XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_RED;
        m_remoteImagePixel[color.Green] = XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_GREEN;
        m_remoteImagePixel[color.Blue] = XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_BLUE;
        m_remoteImagePixel[color.Alpha] = XOSWEBRTCCLIENT_DEFAULT_REMOTE_IMAGE_COLOR_ALPHA;

        m_remoteImage = m_remoteImagePixel;
        m_remoteImageWidth=1; m_remoteImageHeight=1; m_remoteImageDepth=4; m_remoteImageSize=4;

        m_localImagePixel[color.Red] = XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_RED;
        m_localImagePixel[color.Green] = XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_GREEN;
        m_localImagePixel[color.Blue] = XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_BLUE;
        m_localImagePixel[color.Alpha] = XOSWEBRTCCLIENT_DEFAULT_LOCAL_IMAGE_COLOR_ALPHA;

        m_localImage = m_localImagePixel;
        m_localImageWidth=1; m_localImageHeight=1; m_localImageDepth=4; m_localImageSize=4;
        return self;
    }
    - (void)prepareOpenGL {
        if ((m_openglRenderer.init(self))) {
            m_openglRenderer.prepareOpenGL();
        }
    }
    - (void)reshape {
        NSRect rect = [self bounds];
        m_openglRenderer.reshape(rect.size.width, rect.size.height);
        [super reshape];
    }
    - (void)drawRect:(NSRect)rect {
        m_openglRenderer.render
        (m_remoteImage, m_remoteImageWidth, m_remoteImageHeight,
         m_localImage, m_localImageWidth, m_localImageHeight);
    }
@end
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClientMainWindow
///
///       Author: $author$
///         Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClientMainWindow
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env {
        XosMacWebRtcClientMainView* view = 0;
        if ((view = [[XosMacWebRtcClientMainView alloc] init:[self frame]])) {
        }
        return view;
    }
@end
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClient
///
///       Author: $author$
///         Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClient
    - (XosMacMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env {
        NSRect superRect = [[NSScreen mainScreen] visibleFrame];
        NSRect rect = NSMakeRect(superRect.origin.x, superRect.size.height, DEFAULT_IXOSWINDOWMAIN_WINWOW_WIDTH, DEFAULT_IXOSWINDOWMAIN_WINWOW_HEIGHT);
        NSUInteger style = NSTitledWindowMask| NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
        NSBackingStoreType backing = NSBackingStoreBuffered;
        XosMacWebRtcClientMainWindow* window = 0;
        NSView* view = 0;

        if ((window = [[XosMacWebRtcClientMainWindow alloc] initWithContentRect:rect styleMask:style backing:backing defer:NO])) {
            [window setTitle:@DEFAULT_IXOSWINDOWMAIN_WINWOW_TITLE];
            [window setDelegate:window];
            if ((view = [window CreateMainView:argc argv:argv env:env])) {
                [window setContentView:view];
            }
        }
        return window;
    }
    - (id)init {
        [super init];
        return self;
    }
@end
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacMain
///
///       Author: $author$
///         Date: 12/29/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacMain
+ (id<XosMacMain>)Allocate {
    return [[XosMacWebRtcClient alloc] init];
}
@end
#endif // defined(OBJC)
        

