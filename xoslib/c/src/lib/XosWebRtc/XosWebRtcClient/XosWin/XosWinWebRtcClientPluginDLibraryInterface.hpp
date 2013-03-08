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
///   File: XosWinWebRtcClientPluginDLibraryInterface.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGINDLIBRARYINTERFACE_HPP
#define _XOSWINWEBRTCCLIENTPLUGINDLIBRARYINTERFACE_HPP

#include "XosWinWebRtcClientPluginInterface.hpp"
#include "XosDLibrary.hpp"

#define XOSWINWEBRTCCLIENTPLUGINDLIBRARY_FILENAME "libXosWinWebRtcClientPlugin.dll"

#define XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE XosWinWebRtcClientPlugin_Acquire
#define XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE_SYMBOL \
    DLIBRARY_SYMBOL(XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE)

#define XOSWINWEBRTCCLIENTPLUGIN_RELEASE XosWinWebRtcClientPlugin_Release
#define XOSWINWEBRTCCLIENTPLUGIN_RELEASE_SYMBOL \
    DLIBRARY_SYMBOL(XOSWINWEBRTCCLIENTPLUGIN_RELEASE)

extern "C"
{
///////////////////////////////////////////////////////////////////////
/// Typedef: 
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef PLATFORM_EXPORT XosWinWebRtcClientPluginInterface*
(*XosWinWebRtcClientPlugin_Acquire_fp)(XosError& error);
///////////////////////////////////////////////////////////////////////
/// Typedef: 
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef PLATFORM_EXPORT XosError
(*XosWinWebRtcClientPlugin_Release_fp)
(XosWinWebRtcClientPluginInterface* plugin);
///////////////////////////////////////////////////////////////////////
/// Function: XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
PLATFORM_EXPORT XosWinWebRtcClientPluginInterface*
XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE(XosError& error);
///////////////////////////////////////////////////////////////////////
/// Function: XOSWINWEBRTCCLIENTPLUGIN_RELEASE
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
PLATFORM_EXPORT XosError
XOSWINWEBRTCCLIENTPLUGIN_RELEASE
(XosWinWebRtcClientPluginInterface* plugin);
}

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGINDLIBRARYINTERFACE_HPP 
