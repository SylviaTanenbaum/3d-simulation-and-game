
ifndef USE_FREETYPE
USE_FREETYPE := 2.4.2
endif

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := PX2Unity

LOCAL_SRC_FILES := \
PX2InputPushTransformController.cpp \
PX2CSVParser.cpp \
PX2CSVParser1.cpp \
ZLib/adler32.c \
ZLib/compress.c \
ZLib/crc32.c \
ZLib/deflate.c \
ZLib/gzclose.c \
ZLib/gzlib.c \
ZLib/gzread.c \
ZLib/gzwrite.c \
ZLib/infback.c \
ZLib/inffast.c \
ZLib/inflate.c \
ZLib/inftrees.c \
ZLib/trees.c \
ZLib/uncompr.c \
ZLib/zutil.c \
ZLib/minzip/ioapi.c \
ZLib/minzip/unzip.c \
DevIL/PNG/png.c \
DevIL/PNG/pngerror.c \
DevIL/PNG/pngget.c \
DevIL/PNG/pngmem.c \
DevIL/PNG/pngpread.c \
DevIL/PNG/pngread.c \
DevIL/PNG/pngrio.c \
DevIL/PNG/pngrtran.c \
DevIL/PNG/pngrutil.c \
DevIL/PNG/pngset.c \
DevIL/PNG/pngtrans.c \
DevIL/PNG/pngwio.c \
DevIL/PNG/pngwrite.c \
DevIL/PNG/pngwtran.c \
DevIL/PNG/pngwutil.c \
DevIL/altivec_common.c \
DevIL/altivec_typeconversion.c \
DevIL/il_alloc.c \
DevIL/il_bits.c \
DevIL/il_convbuff.c \
DevIL/il_convert.c \
DevIL/il_devil.c \
DevIL/il_error.c \
DevIL/il_files.c \
DevIL/il_fastconv.c \
DevIL/il_internal.c \
DevIL/il_io.c \
DevIL/il_manip.c \
DevIL/il_neuquant.c \
DevIL/il_pal.c \
DevIL/il_quantizer.c \
DevIL/il_register.c \
DevIL/il_rawdata.c \
DevIL/il_size.c \
DevIL/il_stack.c \
DevIL/il_states.c \
DevIL/il_utility.c \
DevIL/il_bmp.c \
DevIL/il_wbmp.c \
DevIL/il_png.c \
DevIL/il_dds-save.c \
DevIL/il_dds.c \
PX2JNI.cpp \
FreeType/src/base/ftbbox.c \
FreeType/src/base/ftbitmap.c \
FreeType/src/base/ftfstype.c \
FreeType/src/base/ftglyph.c \
FreeType/src/base/ftlcdfil.c \
FreeType/src/base/ftstroke.c \
FreeType/src/base/fttype1.c \
FreeType/src/base/ftxf86.c \
FreeType/src/base/ftbase.c \
FreeType/src/base/ftsystem.c \
FreeType/src/base/ftinit.c \
FreeType/src/base/ftgasp.c \
FreeType/src/raster/raster.c \
FreeType/src/sfnt/sfnt.c \
FreeType/src/smooth/smooth.c \
FreeType/src/autofit/autofit.c \
FreeType/src/truetype/truetype.c \
FreeType/src/cff/cff.c \
FreeType/src/psnames/psnames.c \
FreeType/src/pshinter/pshinter.c \
PX2CharCodingGBK.cpp \
PX2CharCodingUTF8.cpp \
PX2FontGlyphMapFreeType.cpp \
PX2FontGlyphMapTrueType.cpp \
PX2Font.cpp \
PX2FontBitmapImpl.cpp \
PX2FontCommonImpl.cpp \
PX2FontManager.cpp \
PX2IMEDelegate.cpp \
PX2IMEDispatcher.cpp \
PX2InputEvent.cpp \
PX2InputEventAdapter.cpp \
PX2InputEventHandler.cpp \
PX2InputEventListener.cpp \
PX2InputRanges.cpp \
PX2LanguageManager.cpp \
PX2ResourceUpdate.cpp \
PX2ResourceManager.cpp \
Lua/lapi.c \
Lua/lauxlib.c \
Lua/lbaselib.c \
Lua/lcode.c \
Lua/ldblib.c \
Lua/ldebug.c \
Lua/ldo.c \
Lua/ldump.c \
Lua/lfunc.c \
Lua/lgc.c \
Lua/linit.c \
Lua/liolib.c \
Lua/llex.c \
Lua/lmathlib.c \
Lua/lmem.c \
Lua/loadlib.c \
Lua/lobject.c \
Lua/lopcodes.c \
Lua/loslib.c \
Lua/lparser.c \
Lua/lstate.c \
Lua/lstring.c \
Lua/lstrlib.c \
Lua/ltable.c \
Lua/ltablib.c \
Lua/ltm.c \
Lua/lundump.c \
Lua/lvm.c \
Lua/lzio.c \
Lua/print.c \
CURL/src/file.c \
CURL/src/timeval.c \
CURL/src/base64.c \
CURL/src/hostip.c \
CURL/src/progress.c \
CURL/src/formdata.c \
CURL/src/cookie.c \
CURL/src/http.c \
CURL/src/sendf.c \
CURL/src/ftp.c \
CURL/src/url.c \
CURL/src/dict.c \
CURL/src/speedcheck.c \
CURL/src/ssluse.c \
CURL/src/version.c \
CURL/src/getenv.c \
CURL/src/escape.c \
CURL/src/mprintf.c \
CURL/src/telnet.c \
CURL/src/netrc.c \
CURL/src/getinfo.c \
CURL/src/transfer.c \
CURL/src/strequal.c \
CURL/src/easy.c \
CURL/src/security.c \
CURL/src/curl_fnmatch.c \
CURL/src/fileinfo.c \
CURL/src/ftplistparser.c \
CURL/src/wildcard.c \
CURL/src/krb5.c \
CURL/src/memdebug.c \
CURL/src/http_chunks.c \
CURL/src/strtok.c \
CURL/src/connect.c \
CURL/src/llist.c \
CURL/src/hash.c \
CURL/src/multi.c \
CURL/src/content_encoding.c \
CURL/src/share.c \
CURL/src/http_digest.c \
CURL/src/md4.c \
CURL/src/md5.c \
CURL/src/http_negotiate.c \
CURL/src/inet_pton.c \
CURL/src/strtoofft.c \
CURL/src/strerror.c \
CURL/src/amigaos.c \
CURL/src/hostasyn.c \
CURL/src/hostip4.c \
CURL/src/hostip6.c \
CURL/src/hostsyn.c \
CURL/src/inet_ntop.c \
CURL/src/parsedate.c \
CURL/src/select.c \
CURL/src/gtls.c \
CURL/src/sslgen.c \
CURL/src/tftp.c \
CURL/src/splay.c \
CURL/src/strdup.c \
CURL/src/socks.c \
CURL/src/ssh.c \
CURL/src/nss.c \
CURL/src/qssl.c \
CURL/src/rawstr.c \
CURL/src/curl_addrinfo.c \
CURL/src/socks_gssapi.c \
CURL/src/socks_sspi.c \
CURL/src/curl_sspi.c \
CURL/src/slist.c \
CURL/src/nonblock.c \
CURL/src/curl_memrchr.c \
CURL/src/imap.c \
CURL/src/pop3.c \
CURL/src/smtp.c \
CURL/src/pingpong.c \
CURL/src/rtsp.c \
CURL/src/curl_threads.c \
CURL/src/warnless.c \
CURL/src/hmac.c \
CURL/src/polarssl.c \
CURL/src/polarssl_threadlock.c \
CURL/src/curl_rtmp.c \
CURL/src/curl_gethostname.c \
CURL/src/gopher.c \
CURL/src/axtls.c \
CURL/src/idn_win32.c \
CURL/src/http_negotiate_sspi.c \
CURL/src/cyassl.c \
CURL/src/http_proxy.c \
CURL/src/non-ascii.c \
CURL/src/asyn-ares.c \
CURL/src/asyn-thread.c \
CURL/src/curl_gssapi.c \
CURL/src/curl_ntlm.c \
CURL/src/curl_ntlm_wb.c \
CURL/src/curl_ntlm_core.c \
CURL/src/curl_ntlm_msgs.c \
CURL/src/curl_sasl.c \
CURL/src/curl_schannel.c \
CURL/src/curl_multibyte.c \
CURL/src/curl_darwinssl.c \
CURL/src/hostcheck.c \
CURL/src/bundles.c \
CURL/src/conncache.c \
CURL/src/pipeline.c \
CURL/src/dotdot.c \
CURL/src/x509asn1.c \
CURL/src/gskit.c \
CURL/src/http2.c \
PX2CURLDownload.cpp \
ToLua/tolua_event.c \
ToLua/tolua_is.c \
ToLua/tolua_map.c \
ToLua/tolua_push.c \
ToLua/tolua_to.c \
PX2LuaManager.cpp \
PX2ScriptManager.cpp \
PX2TexPackData.cpp \
PX2XMLData.cpp \
PX2XMLNode.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/DevIL/IL/ \
$(LOCAL_PATH)/DevIL/PNG/ \
$(LOCAL_PATH)/ZLib/ \
$(LOCAL_PATH)/ZLib/minzip/ \
$(LOCAL_PATH)/DevIL/ \
$(LOCAL_PATH)/FreeType/builds/ \
$(LOCAL_PATH)/FreeType/include/ \
$(LOCAL_PATH)/RapidXML/ \
$(LOCAL_PATH)/Lua/ \
$(LOCAL_PATH)/ToLua/ \
$(LOCAL_PATH)/CURL/config/android \
$(LOCAL_PATH)/CURL/src \
$(LOCAL_PATH)/CURL/ \
$(PX2_ROOT)/PX2SDK/Include/ \

# define the macros          
LOCAL_CFLAGS := -D__ANDROID__
LOCAL_CFLAGS += -DIL_STATIC_LIB
LOCAL_CFLAGS += -DIOAPI_NO_64
LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += "-DFT2_BUILD_LIBRARY"
LOCAL_CFLAGS += -O2
LOCAL_CFLAGS += -DRAPIDXML_NO_EXCEPTIONS

include $(BUILD_STATIC_LIBRARY)
