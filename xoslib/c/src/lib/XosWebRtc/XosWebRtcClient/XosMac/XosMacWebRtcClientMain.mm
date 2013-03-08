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
///   File: XosMacWebRtcClientMain.mm
///
/// Author: $author$
///   Date: 12/30/2012
///////////////////////////////////////////////////////////////////////
#include "XosMacWebRtcClientMain.hh"
#include "XosWebRtcClientImageInterface.hpp"

#if !defined(OBJC)
struct XosMacWebRtcClientMainView;
#endif // !defined(OBJC)

class XosMacWebRtcClientImageObserver
: virtual public XosWebRtcClientImageObserverInterface
{
public:
    XosMacWebRtcClientMainView* m_view;
    XosWebRtcClientImageInterface* m_image;

    XosMacWebRtcClientImageObserver()
    : m_view(0), m_image(0) {
    }
    virtual ~XosMacWebRtcClientImageObserver() {
    }

    void Register
    (XosWebRtcClientImageInterface* image, 
     XosMacWebRtcClientMainView* view)
    {
        if ((image) && (view)) {
            image->RegisterImageObserver(this);
            m_image = m_image;
            m_view = view;
        }
    }
    void Unregister()
    {
        if ((m_image)) {
            m_image->UnregisterImageObserver(this);
            m_image = 0;
        }
        m_view = 0;
    }
    virtual bool InvalidateWindow
    (bool eraseBackground = true) 
    { 
#if defined(OBJC)
        if ((m_view))
            [m_view invalidateWindow:eraseBackground];
#endif // defined(OBJC)
        return true; 
    }
};

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClientMainView
///
///       Author: $author$
///         Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClientMainView
    - (id)init:(NSRect)rect {
        [super initWithFrame:rect pixelFormat:[NSOpenGLView defaultPixelFormat]];
        m_invalid = false;
        m_imageObserver = 0;
        m_image = 0;
        return self;
    }
    - (void)invalidateWindow:(bool)eraseBackground {
        m_invalid = true;
        [self setNeedsDisplay:YES];
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
        if ((m_image) && (m_invalid)) {
            uint8 *remoteImage, *localImage;
            int remoteImageFormat, localImageFormat;
            int remoteImageWidth, remoteImageHeight;
            int localImageWidth, localImageHeight;

            if ((remoteImage = m_image->AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = m_image->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_image->ReleaseLocalImage(localImage);
                } else {
                    m_openglRenderer.render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_invalid = false;
                m_image->ReleaseRemoteImage(remoteImage);
            } else {
                if ((localImage = m_image->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.render
                    (localImage, localImageWidth, localImageHeight);
                    m_invalid = false;
                    m_image->ReleaseLocalImage(localImage);
                } else {
                    [[NSColor DEFAULT_XOSMACWEBRTCCLIENT_OPENGL_VIEW_BG_COLOR] set];
                    NSRectFill([self bounds]);
                    m_invalid = false;
                }
            }
        } else {
            [[NSColor DEFAULT_XOSMACWEBRTCCLIENT_OPENGL_VIEW_BG_COLOR] set];
            NSRectFill([self bounds]);
        }
    }
    - (void)setImage:(XosWebRtcClientImageInterface*)image {
        if ((image)) {
            if ((m_imageObserver = new XosMacWebRtcClientImageObserver())) {
                m_imageObserver->Register(m_image = image, self);
            }
        } else {
            if ((m_image)) {
                if ((m_imageObserver)) {
                    m_imageObserver->Unregister();
                    delete m_imageObserver;
                    m_imageObserver = 0;
                }
                m_image = 0;
            }
        }
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClientMainWindow
///
///       Author: $author$
///         Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClientMainWindow
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env {
        XosMacWebRtcClientMainView* view = 0;
        if ((view = [[XosMacWebRtcClientMainView alloc] init:[self frame]])) {
            [view setImage:m_image];
        }
        return view;
    }
    - (void)setImage:(XosWebRtcClientImageInterface*)image {
        m_image = image;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacWebRtcClientMain
///
///       Author: $author$
///         Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacWebRtcClientMain
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
            [window setImage:&m_webrtcMain];
            if ((view = [window CreateMainView:argc argv:argv env:env])) {
                [window setContentView:view];
            }
        }
        return window;
    }
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if (!(err = [super BeforeRun:argc argv:argv env:env])) {
            err = m_webrtcMain.BeforeRun(argc, argv, env);
        }
        return err;
    }
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        int err2 = 0;
        err = m_webrtcMain.AfterRun(argc, argv, env);
        if ((err2 = [super AfterRun:argc argv:argv env:env])) {
            err = (!err)?(err2):(err);
        }
        return err;
    }
@end
///////////////////////////////////////////////////////////////////////
/// Implentation: XosMacMain
///
///       Author: $author$
///         Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@implementation XosMacMain
+ (id<XosMacMain>)Allocate {
    return [[XosMacWebRtcClientMain alloc] init];
    //return [[XosMacBaseMain alloc] init];
}
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  
