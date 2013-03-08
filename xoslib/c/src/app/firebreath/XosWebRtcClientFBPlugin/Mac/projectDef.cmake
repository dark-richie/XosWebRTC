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
#   Date: 4/11/2012
########################################################################

#
# Mac template platform definition CMake file
# Included from ../CMakeLists.txt
#

set (SOURCE_ROOT "$ENV{HOME}/source/frameworks")
set (BUILD_CONFIGURATION "$(CONFIGURATION)")

########################################################################
# WebRTC
# ...
########################################################################
if(NOT DEFINED WEBRTC_REVISION_NUMBER)
set (WEBRTC_REVISION_NUMBER "1080")
endif()

set (WEBRTC_GROUP "webrtc/")
set (WEBRTC_NAME "webrtc")
set (WEBRTC_VERSION "-trunk-r-")

set (WEBRTC_ROOT "${SOURCE_ROOT}/${WEBRTC_GROUP}${WEBRTC_NAME}${WEBRTC_VERSION}${WEBRTC_REVISION_NUMBER}")
set (WEBRTC_OUTPUT "${WEBRTC_ROOT}/xcodebuild")
set (WEBRTC_BUILD "${WEBRTC_OUTPUT}/${BUILD_CONFIGURATION}")
set (WEBRTC_LIB "${WEBRTC_BUILD}")

set(WEBRTC_INCLUDE_DIRS 
${WEBRTC_ROOT}
${WEBRTC_ROOT}/src;
${WEBRTC_ROOT}/third_party/libjingle/source
${WEBRTC_ROOT}/third_party_mods/libjingle/source
${WEBRTC_ROOT}/third_party/expat/files/lib
${WEBRTC_ROOT}/../../gocast/webrtc_plugin/third_party_mods/webrtc/trunk/third_party/libjingle/source
)
set(WEBRTC_LIB_DIRS 
${WEBRTC_LIB}
)

set (WEBRTC_DEFINES 
-DOSX
-DPOSIX
-DWEBRTC_FBPLUGIN
-DWEBRTC_REVISION=${WEBRTC_REVISION_NUMBER}
)

set(WEBRTC_EXTERNAL_LIBS 
)

set(WEBRTC_810_INTERNAL_LIBS_A 
"${WEBRTC_LIB}/libaec.a"
"${WEBRTC_LIB}/libaecm.a"
"${WEBRTC_LIB}/libagc.a"
"${WEBRTC_LIB}/libapm_util.a"
"${WEBRTC_LIB}/libaudio_coding_module.a"
"${WEBRTC_LIB}/libaudio_conference_mixer.a"
"${WEBRTC_LIB}/libaudio_device.a"
"${WEBRTC_LIB}/libaudio_processing.a"
"${WEBRTC_LIB}/libCNG.a"
"${WEBRTC_LIB}/libexpat.a"
"${WEBRTC_LIB}/libG711.a"
"${WEBRTC_LIB}/libG722.a"
"${WEBRTC_LIB}/libgenperf_libs.a"
"${WEBRTC_LIB}/libgtest.a"
"${WEBRTC_LIB}/libgtest_main.a"
"${WEBRTC_LIB}/libiLBC.a"
"${WEBRTC_LIB}/libiSAC.a"
"${WEBRTC_LIB}/libiSACFix.a"
"${WEBRTC_LIB}/libjingle.a"
"${WEBRTC_LIB}/libjingle_app.a"
"${WEBRTC_LIB}/libjingle_p2p.a"
"${WEBRTC_LIB}/libjpeg_turbo.a"
"${WEBRTC_LIB}/libjsoncpp.a"
"${WEBRTC_LIB}/libmedia_file.a"
"${WEBRTC_LIB}/libNetEq.a"
"${WEBRTC_LIB}/libns.a"
"${WEBRTC_LIB}/libPCM16B.a"
"${WEBRTC_LIB}/libprotobuf_full_do_not_use.a"
"${WEBRTC_LIB}/libprotobuf_lite.a"
"${WEBRTC_LIB}/libresampler.a"
"${WEBRTC_LIB}/librtp_rtcp.a"
"${WEBRTC_LIB}/libspl.a"
"${WEBRTC_LIB}/libsystem_wrappers.a"
"${WEBRTC_LIB}/libudp_transport.a"
"${WEBRTC_LIB}/libvad.a"
"${WEBRTC_LIB}/libvideo_capture_module.a"
"${WEBRTC_LIB}/libvideo_engine_core.a"
"${WEBRTC_LIB}/libvideo_processing.a"
"${WEBRTC_LIB}/libvideo_render_module.a"
"${WEBRTC_LIB}/libvoice_engine_core.a"
"${WEBRTC_LIB}/libvpx.a"
"${WEBRTC_LIB}/libwebrtc_i420.a"
"${WEBRTC_LIB}/libwebrtc_jpeg.a"
"${WEBRTC_LIB}/libwebrtc_utility.a"
"${WEBRTC_LIB}/libwebrtc_video_coding.a"
"${WEBRTC_LIB}/libwebrtc_vp8.a"
"${WEBRTC_LIB}/libwebrtc_vplib.a"
)

set(WEBRTC_810_INTERNAL_LIBS 
${WEBRTC_810_INTERNAL_LIBS_A}
)

set(WEBRTC_1080_INTERNAL_LIBS_A 
"${WEBRTC_LIB}/libaec.a"
"${WEBRTC_LIB}/libaecm.a"
"${WEBRTC_LIB}/libagc.a"
"${WEBRTC_LIB}/libapm_util.a"
"${WEBRTC_LIB}/libaudio_coding_module.a"
"${WEBRTC_LIB}/libaudio_conference_mixer.a"
"${WEBRTC_LIB}/libaudio_device.a"
"${WEBRTC_LIB}/libaudio_processing.a"
"${WEBRTC_LIB}/libaudioproc_debug_proto.a"
"${WEBRTC_LIB}/libaudioproc_unittest_proto.a"
"${WEBRTC_LIB}/libCNG.a"
"${WEBRTC_LIB}/libG711.a"
"${WEBRTC_LIB}/libG722.a"
"${WEBRTC_LIB}/libgenperf_libs.a"
"${WEBRTC_LIB}/libgmock.a"
"${WEBRTC_LIB}/libgoogle-gflags.a"
"${WEBRTC_LIB}/libgtest.a"
"${WEBRTC_LIB}/libiLBC.a"
"${WEBRTC_LIB}/libiSAC.a"
"${WEBRTC_LIB}/libiSACFix.a"
"${WEBRTC_LIB}/libjpeg_turbo.a"
"${WEBRTC_LIB}/libmedia_file.a"
"${WEBRTC_LIB}/libNetEq.a"
"${WEBRTC_LIB}/libNetEqTestTools.a"
"${WEBRTC_LIB}/libns.a"
"${WEBRTC_LIB}/libns_fix.a"
"${WEBRTC_LIB}/libPCM16B.a"
"${WEBRTC_LIB}/libprotobuf_full_do_not_use.a"
"${WEBRTC_LIB}/libprotobuf_lite.a"
"${WEBRTC_LIB}/libresampler.a"
"${WEBRTC_LIB}/librtp_rtcp.a"
"${WEBRTC_LIB}/libsignal_processing.a"
"${WEBRTC_LIB}/libsystem_wrappers.a"
"${WEBRTC_LIB}/libtest_framework.a"
"${WEBRTC_LIB}/libtest_support.a"
"${WEBRTC_LIB}/libtest_support_main.a"
"${WEBRTC_LIB}/libudp_transport.a"
"${WEBRTC_LIB}/libvad.a"
"${WEBRTC_LIB}/libvideo_capture_module.a"
"${WEBRTC_LIB}/libvideo_codecs_test_framework.a"
"${WEBRTC_LIB}/libvideo_engine_core.a"
"${WEBRTC_LIB}/libvideo_processing.a"
"${WEBRTC_LIB}/libvideo_render_module.a"
"${WEBRTC_LIB}/libvoice_engine_core.a"
"${WEBRTC_LIB}/libvpx.a"
"${WEBRTC_LIB}/libwebrtc_i420.a"
"${WEBRTC_LIB}/libwebrtc_jpeg.a"
"${WEBRTC_LIB}/libwebrtc_utility.a"
"${WEBRTC_LIB}/libwebrtc_video_coding.a"
"${WEBRTC_LIB}/libwebrtc_vp8.a"
"${WEBRTC_LIB}/libwebrtc_vplib.a"
"${WEBRTC_LIB}/../../third_party/libsrtp/libsrtp.a"
)

set(WEBRTC_1080_INTERNAL_LIBS 
"${WEBRTC_LIB}/libwebrtc_${BUILD_CONFIGURATION}.a"
"${WEBRTC_LIB}/../../third_party/libsrtp/libsrtp.a"
)

set(WEBRTC_LIBS 
${WEBRTC_${WEBRTC_REVISION_NUMBER}_INTERNAL_LIBS} 
${WEBRTC_EXTERNAL_LIBS}
)
########################################################################
# ...
# WebRTC
########################################################################

########################################################################
# XosLib
# ...
########################################################################
set (XOSLIB_ROOT "${SOURCE_ROOT}/xoslib")
set (XOSLIB_OUTPUT "${XOSLIB_ROOT}/build/macosx")
set (XOSLIB_BUILD "${XOSLIB_OUTPUT}/${BUILD_CONFIGURATION}")
set (XOSLIB_SRC "${XOSLIB_ROOT}/c/src")

set (XOSLIB_BUILD_BIN "${XOSLIB_BUILD}/bin")
set (XOSLIB_BUILD_LIB "${XOSLIB_BUILD}/lib")

set (XOSLIB_INCLUDE_DIRS 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient/XosMac" 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient" 
"${XOSLIB_SRC}/lib/XosWebRtcVideo/XosMac" 
"${XOSLIB_SRC}/lib/XosWebRtcVideo" 
"${XOSLIB_SRC}/lib/XosGui/XosMac" 
"${XOSLIB_SRC}/lib/XosGui" 
"${XOSLIB_SRC}/lib/XosNetwork/XosMac" 
"${XOSLIB_SRC}/lib/XosNetwork" 
"${XOSLIB_SRC}/lib/XosCore/XosThread/XosMac" 
"${XOSLIB_SRC}/lib/XosCore/XosThread/XosUnix" 
"${XOSLIB_SRC}/lib/XosCore/XosThread" 
"${XOSLIB_SRC}/lib/XosCore" 
"${XOSLIB_SRC}/lib/XosPlatform" 
)

set (XOSLIB_LIB_DIRS 
"${XOSLIB_BUILD_LIB}"
)

set (XOSLIB_DEFINES 
)

set (XOSLIB_LIBS 
"${XOSLIB_BUILD_LIB}/libXosWebRtcCore.a"
"${XOSLIB_BUILD_LIB}/libXosWebRtcClient.a"
)
########################################################################
# ...
# XosLib
########################################################################

#
# remember that the current source dir is the project root; this file is in Mac/
#
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Mac/[^.]*.cpp
    Mac/[^.]*.hpp
    Mac/[^.]*.mm
    Mac/[^.]*.hh
    Mac/[^.]*.m
    Mac/[^.]*.h
    Mac/[^.]*.cmake
    )

#
# use this to add preprocessor definitions
#
add_definitions(
${WEBRTC_DEFINES}
${XOSLIB_DEFINES}
)

SOURCE_GROUP(Mac FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

set(PLIST "Mac/bundle_template/Info.plist")
set(STRINGS "Mac/bundle_template/InfoPlist.strings")
set(LOCALIZED "Mac/bundle_template/Localized.r")

add_mac_plugin(${PROJECT_NAME} ${PLIST} ${STRINGS} ${LOCALIZED} SOURCES)

#
# add incluide directories here
#
include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}/"
${XOSLIB_INCLUDE_DIRS}
${WEBRTC_INCLUDE_DIRS}
)

find_library(QTKIT_FRAMEWORK QTKit)
find_library(QUARTZ_CORE_FRAMEWORK QuartzCore)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
find_library(CORE_AUDIO_FRAMEWORK CoreAudio)
find_library(AUDIO_TOOLBOX_FRAMEWORK AudioToolbox)
find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(CARBON_FRAMEWORK Carbon) 
find_library(OPENGL_FRAMEWORK OpenGL)

#
# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there
# unless you know what you're doing!
#
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    ${QTKIT_FRAMEWORK}
    ${QUARTZ_CORE_FRAMEWORK}
    ${CORE_FOUNDATION_FRAMEWORK}
    ${CORE_VIDEO_FRAMEWORK}
    ${CORE_AUDIO_FRAMEWORK}
    ${AUDIO_TOOLBOX_FRAMEWORK}
    ${APPLICATION_SERVICES_FRAMEWORK}
    ${COCOA_FRAMEWORK}
    ${CARBON_FRAMEWORK}
    ${OPENGL_FRAMEWORK}
    ${XOSLIB_LIBS}
    ${WEBRTC_LIBS}
    )
