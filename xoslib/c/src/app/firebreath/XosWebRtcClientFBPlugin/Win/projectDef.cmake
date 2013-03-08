########################################################################
# Copyright 2012, Google Inc.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote products
#     derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#   File: projectDef.cmake
#
# Author: $author$
#   Date: 4/3/2012
########################################################################

#
# Windows template platform definition CMake file
# Included from ../CMakeLists.txt
#
set (VCVersion "vc9")

########################################################################
# WebRTC
# ...
########################################################################
set (WEBRTC_GROUP "webrtc/")
set (WEBRTC_NAME "webrtc")
set (WEBRTC_VERSION "-trunk-r-")
set (WEBRTC_REVISION_NUMBER "1125")

set (WEBRTC_ROOT "../../../../${WEBRTC_GROUP}${WEBRTC_NAME}${WEBRTC_VERSION}${WEBRTC_REVISION_NUMBER}")
set (WEBRTC_OUTPUT "../${WEBRTC_ROOT}/build")
set (WEBRTC_BUILD "${WEBRTC_OUTPUT}/$(ConfigurationName)")
set (WEBRTC_LIB "${WEBRTC_BUILD}/lib")

set(WEBRTC_INCLUDE_DIRS 
${WEBRTC_ROOT}
${WEBRTC_ROOT}/src;
${WEBRTC_ROOT}/third_party/wtl/include
${WEBRTC_ROOT}/third_party/libjingle/source
${WEBRTC_ROOT}/third_party_mods/libjingle/source
${WEBRTC_ROOT}/third_party_mods/third_party/platformsdk_win7/files/Include
${WEBRTC_ROOT}/third_party/expat/files/lib
${WEBRTC_ROOT}/third_party/platformsdk_win7/files/Include
${WEBRTC_ROOT}/third_party/directxsdk/files/Include
${VSInstallDir}/VC/atlmfc/include  
)
set(WEBRTC_LIB_DIRS 
${WEBRTC_LIB}
${WEBRTC_ROOT}/third_party/platformsdk_win7/files/Lib
${WEBRTC_ROOT}/third_party/directxsdk/files/Lib/x86
)

set(WEBRTC_EXTERNAL_LIBS 
wininet.lib dnsapi.lib version.lib msimg32.lib ws2_32.lib 
usp10.lib psapi.lib dbghelp.lib winmm.lib shlwapi.lib winmm.lib 
dmoguids.lib wmcodecdspuuid.lib amstrmid.lib msdmo.lib secur32.lib 
crypt32.lib iphlpapi.lib)

set(WEBRTC_1125_INTERNAL_LIBS 
"${WEBRTC_LIB}/aec"
"${WEBRTC_LIB}/aecm"
"${WEBRTC_LIB}/agc"
"${WEBRTC_LIB}/apm_util"
"${WEBRTC_LIB}/audioproc_debug_proto"
"${WEBRTC_LIB}/audio_coding_module"
"${WEBRTC_LIB}/audio_conference_mixer"
"${WEBRTC_LIB}/audio_device"
"${WEBRTC_LIB}/audio_processing"
"${WEBRTC_LIB}/CNG"
"${WEBRTC_LIB}/expat"
"${WEBRTC_LIB}/G711"
"${WEBRTC_LIB}/G722"
"${WEBRTC_LIB}/genperf_libs"
"${WEBRTC_LIB}/iLBC"
"${WEBRTC_LIB}/iSAC"
"${WEBRTC_LIB}/iSACFix"
"${WEBRTC_LIB}/jsoncpp"
"${WEBRTC_LIB}/libjingle"
"${WEBRTC_LIB}/libjingle_app"
"${WEBRTC_LIB}/libjingle_p2p"
"${WEBRTC_LIB}/libjpeg"
"${WEBRTC_LIB}/libvpx"
"${WEBRTC_LIB}/media_file"
"${WEBRTC_LIB}/NetEq"
"${WEBRTC_LIB}/ns"
"${WEBRTC_LIB}/PCM16B"
"${WEBRTC_LIB}/protobuf_full_do_not_use"
"${WEBRTC_LIB}/protobuf_lite"
"${WEBRTC_LIB}/resampler"
"${WEBRTC_LIB}/rtp_rtcp"
"${WEBRTC_LIB}/signal_processing"
"${WEBRTC_LIB}/system_wrappers"
"${WEBRTC_LIB}/udp_transport"
"${WEBRTC_LIB}/vad"
"${WEBRTC_LIB}/video_capture_module"
"${WEBRTC_LIB}/video_engine_core"
"${WEBRTC_LIB}/video_processing"
"${WEBRTC_LIB}/video_render_module"
"${WEBRTC_LIB}/voice_engine_core"
"${WEBRTC_LIB}/webrtc_i420"
"${WEBRTC_LIB}/webrtc_jpeg"
"${WEBRTC_LIB}/webrtc_utility"
"${WEBRTC_LIB}/webrtc_video_coding"
"${WEBRTC_LIB}/webrtc_vp8"
"${WEBRTC_LIB}/webrtc_vplib"
)

set(WEBRTC_LIBS ${WEBRTC_1125_INTERNAL_LIBS} ${WEBRTC_EXTERNAL_LIBS})
########################################################################
# ...
# WebRTC
########################################################################

########################################################################
# XosLib
# ...
########################################################################
set (XOSLIB_ROOT "../../../../xoslib")
set (XOSLIB_OUTPUT "../${XOSLIB_ROOT}/build")
set (XOSLIB_BUILD "${XOSLIB_OUTPUT}/$(PlatformName)/${VCVersion}/$(ConfigurationName)")
set (XOSLIB_SRC "${XOSLIB_ROOT}/c/src")

set (XOSLIB_BUILD_BIN "${XOSLIB_BUILD}/bin")
set (XOSLIB_BUILD_LIB "${XOSLIB_BUILD}/lib")
set (XOSLIB_BUILD_OBJ "${XOSLIB_BUILD}/obj/$(ProjectName)")

set (XOSLIB_INCLUDE_DIRS 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient/XosWin" 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient" 
"${XOSLIB_SRC}/lib/XosGui/XosWin" 
"${XOSLIB_SRC}/lib/XosGui" 
"${XOSLIB_SRC}/lib/XosCore/XosThread/XosWin" 
"${XOSLIB_SRC}/lib/XosCore/XosThread" 
"${XOSLIB_SRC}/lib/XosCore/XosWin" 
"${XOSLIB_SRC}/lib/XosCore" 
"${XOSLIB_SRC}/lib/XosPlatform" 
)

set (XOSLIB_LIB_DIRS 
"${XOSLIB_BUILD_LIB}"
)

set (XOSLIB_DEFINES 
)

set (XOSLIB_LIBS 
"${XOSLIB_BUILD_LIB}/libXosWebRtc"
)
########################################################################
# ...
# XosLib
########################################################################

#
# remember that the current source dir is the project root; this file is in Win/
#
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Win/[^.]*.cpp
    Win/[^.]*.hpp
    Win/[^.]*.cc
    Win/[^.]*.h
    Win/[^.]*.cmake
    )

#
# use this to add preprocessor definitions
#
add_definitions(
    /D "_ATL_STATIC_REGISTRY"
    /D "WEBRTC_REVISION=${WEBRTC_REVISION_NUMBER}"
)

SOURCE_GROUP(Win FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

add_windows_plugin(${PROJECT_NAME} SOURCES)

#
# add incluide directories here
#
include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}/"
${XOSLIB_INCLUDE_DIRS}
${WEBRTC_INCLUDE_DIRS}
)

#
# add library directories here
#
link_directories(
${XOSLIB_LIB_DIRS}
${WEBRTC_LIB_DIRS}
)

#
# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there
# unless you know what you're doing!
#
target_link_libraries(${PROJECT_NAME}
${PLUGIN_INTERNAL_DEPS}
${XOSLIB_LIBS}
${WEBRTC_LIBS}
opengl32.lib
glu32.lib
)

#
# This is an example of how to add a build step to sign the plugin DLL before
# the WiX installer builds.  The first filename (certificate.pfx) should be
# the path to your pfx file.  If it requires a passphrase, the passphrase
# should be located inside the second file. If you don't need a passphrase
# then set the second filename to "".  If you don't want signtool to timestamp
# your DLL then make the last parameter "".
#
# Note that this will not attempt to sign if the certificate isn't there --
# that's so that you can have development machines without the cert and it'll
# still work. Your cert should only be on the build machine and shouldn't be in
# source control!
# -- uncomment lines below this to enable signing --
#firebreath_sign_plugin(${PROJECT_NAME}
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")
#

set(WIX_HEAT_FLAGS
    -gg                 # Generate GUIDs
    -srd                # Suppress Root Dir
    -cg PluginDLLGroup  # Set the Component group name
    -dr INSTALLDIR      # Set the directory ID to put the files in
    )

add_wix_installer( ${PLUGIN_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/${PLUGIN_NAME}Installer.wxs
    PluginDLLGroup
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll
    ${PROJECT_NAME}
    )

#
# This is an example of how to add a build step to sign the WiX installer
# -- uncomment lines below this to enable signing --
#firebreath_sign_file("${PLUGIN_NAME}_WiXInstall"
#    "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PLUGIN_NAME}.msi"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")
#
