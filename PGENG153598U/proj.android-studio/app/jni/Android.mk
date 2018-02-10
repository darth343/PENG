LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
    $(LOCAL_PATH)/../../../Classes/AppDelegate.h \
    $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
    $(LOCAL_PATH)/../../../Classes/AnimationManager.h      \
    $(LOCAL_PATH)/../../../Classes/AnimationManager.cpp    \
    $(LOCAL_PATH)/../../../Classes/BaseScene.h             \
    $(LOCAL_PATH)/../../../Classes/BaseScene.cpp           \
    $(LOCAL_PATH)/../../../Classes/BattleScene.h           \
    $(LOCAL_PATH)/../../../Classes/BattleScene.cpp         \
    $(LOCAL_PATH)/../../../Classes/ContactListener.h       \
    $(LOCAL_PATH)/../../../Classes/Entity.h                \
    $(LOCAL_PATH)/../../../Classes/Entity.cpp              \
    $(LOCAL_PATH)/../../../Classes/Grid.h                  \
    $(LOCAL_PATH)/../../../Classes/Grid.cpp                \
    $(LOCAL_PATH)/../../../Classes/GridSystem.h            \
    $(LOCAL_PATH)/../../../Classes/GridSystem.cpp          \
    $(LOCAL_PATH)/../../../Classes/HelloWorldScene.h       \
    $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp     \
    $(LOCAL_PATH)/../../../Classes/Input.h                 \
    $(LOCAL_PATH)/../../../Classes/Input.cpp               \
    $(LOCAL_PATH)/../../../Classes/OverworldScene.h        \
    $(LOCAL_PATH)/../../../Classes/OverworldScene.cpp      \
    $(LOCAL_PATH)/../../../Classes/PlayerEntity.h          \
    $(LOCAL_PATH)/../../../Classes/PlayerEntity.cpp        \
    $(LOCAL_PATH)/../../../Classes/PlayerOverworld.h       \
    $(LOCAL_PATH)/../../../Classes/PlayerOverworld.cpp     \
    $(LOCAL_PATH)/../../../Classes/PostProcessing.h        \
    $(LOCAL_PATH)/../../../Classes/PostProcessing.cpp      \
    $(LOCAL_PATH)/../../../Classes/SceneManager.h          \
    $(LOCAL_PATH)/../../../Classes/SceneManager.cpp        \
    $(LOCAL_PATH)/../../../Classes/SceneSplashScreen.h     \
    $(LOCAL_PATH)/../../../Classes/SceneSplashScreen.cpp   \
    $(LOCAL_PATH)/../../../Classes/SingletonNodeTemplate.h \
    $(LOCAL_PATH)/../../../Classes/SingletonTemplate.h     \
    $(LOCAL_PATH)/../../../Classes/SplashScreen.h          \
    $(LOCAL_PATH)/../../../Classes/SpriteManager.h         \
    $(LOCAL_PATH)/../../../Classes/SpriteManager.cpp       \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
