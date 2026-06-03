add_subdirectory(glfw)
add_subdirectory(glad)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)

# Assimp config
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

# Нам потрібен тільки імпорт моделей, експорт не потрібен
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)

# Для дедлайну краще збирати не всі імпортери, а тільки OBJ
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)

add_subdirectory(assimp)

# Fix for Apple Clang: do not fail Assimp build on unsafe-buffer-usage warnings
if (TARGET assimp)
    target_compile_options(assimp PRIVATE
            $<$<CXX_COMPILER_ID:AppleClang,Clang>:-Wno-error=unsafe-buffer-usage>
            $<$<CXX_COMPILER_ID:AppleClang,Clang>:-Wno-unsafe-buffer-usage>
    )

endif ()