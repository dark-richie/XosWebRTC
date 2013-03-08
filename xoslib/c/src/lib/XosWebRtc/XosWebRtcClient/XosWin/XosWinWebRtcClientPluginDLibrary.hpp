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
///   File: XosWinWebRtcClientPluginDLibrary.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGINDLIBRARY_HPP
#define _XOSWINWEBRTCCLIENTPLUGINDLIBRARY_HPP

#include "XosWinWebRtcClientPluginDLibraryInterface.hpp"
#include "XosDLibrary.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginDLibraryImplement
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosDLibraryImplement
XosWinWebRtcClientPluginDLibraryImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginDLibraryExtend
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosDLibrary
XosWinWebRtcClientPluginDLibraryExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginDLibrary
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPluginDLibrary
: virtual public XosWinWebRtcClientPluginDLibraryImplement,
  public XosWinWebRtcClientPluginDLibraryExtend
{
public:
    typedef XosWinWebRtcClientPluginDLibraryImplement Implements;
    typedef XosWinWebRtcClientPluginDLibraryExtend Extends;

    XosString m_dlibraryFileName;

    XosString m_pluginAcquireSymbol;
    XosString m_pluginReleaseSymbol;

    XosWinWebRtcClientPlugin_Acquire_fp m_pluginAcquire;
    XosWinWebRtcClientPlugin_Release_fp m_pluginRelease;

    XosWinWebRtcClientPluginInterface* m_plugin;

    XosDLibrary m_dlibrary;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPluginDLibrary
    ///
    ///       Author: $author$
    ///         Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPluginDLibrary()
    : m_dlibraryFileName(XOSWINWEBRTCCLIENTPLUGINDLIBRARY_FILENAME),
      m_pluginAcquireSymbol(XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE_SYMBOL),
      m_pluginReleaseSymbol(XOSWINWEBRTCCLIENTPLUGIN_RELEASE_SYMBOL),
      m_pluginAcquire(0),
      m_pluginRelease(0),
      m_plugin(0)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPluginDLibrary
    ///
    ///      Author: $author$
    ///        Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPluginDLibrary()
    {
        XosError error;
        if (m_isOpen)
        if ((error = Close()))
            throw(error);
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Open
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Open(const char* dlibraryFileName=0)
    {
        XosError error = XOS_ERROR_FAILED;
        const char* pluginAcquire;
        const char* pluginRelease;

        if ((m_isOpen))
            return XOS_ERROR_NONE;

        if (!dlibraryFileName)
        if (!(dlibraryFileName = m_dlibraryFileName.c_str()))
            return XOS_ERROR_FAILED;

        if ((pluginAcquire = m_pluginAcquireSymbol.c_str()))
        if ((pluginRelease = m_pluginReleaseSymbol.c_str()))
        if (!(error = m_dlibrary.Open(dlibraryFileName)))
        {
            if (!(m_pluginAcquire = (XosWinWebRtcClientPlugin_Acquire_fp)
                (m_dlibrary.GetAddress(pluginAcquire))))
                XOS_DBE(("() failed to get address of \"%s\"\n", pluginAcquire));
            else if (!(m_pluginRelease = (XosWinWebRtcClientPlugin_Release_fp)
                    (m_dlibrary.GetAddress(pluginRelease))))
                    XOS_DBE(("() failed to get address of \"%s\"\n", pluginRelease));
            else
            {
                m_isOpen = true;
                return XOS_ERROR_NONE;
            }
            m_pluginAcquire = 0;
            m_dlibrary.Close();
        }
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Close
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Close()
    {
        XosError error = XOS_ERROR_FAILED;
        XosError error2;

        if ((m_plugin))
        if ((error2 = ReleasePlugin(m_plugin)))
        if (!(error)) error = error2;

        if ((m_isOpen))
        if ((error2 = m_dlibrary.Close()))
        {
            XOS_DBE(("() m_dlibrary.Close() failed"));
            if (!(error)) error = error2;
        }

        m_isOpen = false;
        m_pluginAcquire = 0;
        m_pluginRelease = 0;
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: AcquirePlugin
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWinWebRtcClientPluginInterface* AcquirePlugin
    (XosError& error)
    {
        XosWinWebRtcClientPluginInterface* plugin = 0;
        error = XOS_ERROR_FAILED;
        if (!(m_plugin))
        if ((m_pluginAcquire))
        if ((plugin = m_pluginAcquire(error)))
            m_plugin = plugin;
        return plugin;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: ReleasePlugin
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError ReleasePlugin
    (XosWinWebRtcClientPluginInterface* plugin)
    {
        XosError error = XOS_ERROR_FAILED;
        if ((plugin) && (plugin == m_plugin))
        {
            if ((m_pluginRelease))
                error = m_pluginRelease(plugin);
            m_plugin = 0;
        }
        return error;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGINDLIBRARY_HPP 
