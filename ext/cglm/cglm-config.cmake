set(CGLM_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/cglm")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(CGLM_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/win/x64/Debug/cglm.lib")
else ()
  set(CGLM_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/win/Debug/cglm.lib")
endif ()
