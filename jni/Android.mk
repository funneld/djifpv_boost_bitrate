LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99
LOCAL_LDFLAGS += -fPIC 
LOCAL_LDLIBS := -llog

LOCAL_MODULE    := boost_bitrate 
LOCAL_SRC_FILES := boost_bitrate.c

include $(BUILD_SHARED_LIBRARY)
