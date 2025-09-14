# 标题
cmake_minimum_required(VERSION 3.10.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)

# 添加可执行文件
set(SOURCES
    src/core/game.cpp
    src/core/actor.cpp
    src/core/asset_store.cpp
    src/core/object_world.cpp
    src/core/scene.cpp
    src/core/object.cpp
    src/core/object_affiliate.cpp
    src/affiliate/sprite.cpp
    src/affiliate/sprite_animation.cpp
    src/affiliate/collider.cpp
    src/affiliate/affiliate_bar.cpp
    src/affiliate/text_label.cpp
    src/raw/stats.cpp
    src/raw/weapon.cpp
    src/raw/timer.cpp
    src/raw/bg_star.cpp
    src/world/spell.cpp
    src/world/effect.cpp
    src/screen/ui_mouse.cpp
    src/screen/hud_stats.cpp
    src/screen/hud_skill.cpp
    src/screen/hud_text.cpp
    src/screen/hud_button.cpp
    src/main.cpp
    src/scene_title.cpp
    src/scene_main.cpp
    src/player.cpp
    src/enemy.cpp
    src/spawner.cpp
    src/weapon_thunder.cpp
)

if(WIN32)
    list(APPEND SOURCES resources.rc)
endif()

# 添加可执行文件
add_executable(${TARGET} ${SOURCES})

# 链接库
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf
                        glm::glm
)

# 控制不弹出控制台窗口
if(MSVC)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()


# clang-uml + PlantUML 设置
set(CLANG_UML_CMD clang-uml)                                # clang-uml 可执行路径
set(CLANG_UML_CONFIG ${CMAKE_SOURCE_DIR}/.clang-uml.yaml)    # clang-uml 配置
set(UML_SRC_DIR ${CMAKE_SOURCE_DIR}/docs/uml)               # .puml 输出目录
set(UML_IMG_DIR ${CMAKE_SOURCE_DIR}/docs/images)            # PNG/SVG 输出目录
set(PLANTUML_JAR ${CMAKE_SOURCE_DIR}/tools/plantuml.jar)    # PlantUML jar 路径

# 确保输出目录存在
file(MAKE_DIRECTORY ${UML_SRC_DIR})
file(MAKE_DIRECTORY ${UML_IMG_DIR})

# 自定义目标：生成 .puml 文件
add_custom_target(generate_puml
    COMMAND ${CLANG_UML_CMD} -c ${CLANG_UML_CONFIG} -o ${UML_SRC_DIR}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating PlantUML .puml files with clang-uml"
)

# 自定义命令：生成 PNG/SVG
file(GLOB PUML_FILES "${UML_SRC_DIR}/*.puml")
set(UML_OUTPUTS)

foreach(puml ${PUML_FILES})
    get_filename_component(fname ${puml} NAME_WE)

    # 生成 SVG
    add_custom_command(
        OUTPUT ${UML_IMG_DIR}/${fname}.svg
        COMMAND java -Djava.awt.headless=true -Dfile.encoding=UTF-8 -jar ${PLANTUML_JAR} -tsvg -o ${UML_IMG_DIR} ${puml}
        DEPENDS ${puml}
        COMMENT "Generating SVG for ${fname}.puml"
    )

    # 生成 PNG
    add_custom_command(
        OUTPUT ${UML_IMG_DIR}/${fname}.png
        COMMAND java -Djava.awt.headless=true -Dfile.encoding=UTF-8 -jar ${PLANTUML_JAR} -tpng -o ${UML_IMG_DIR} ${puml}
        DEPENDS ${puml}
        COMMENT "Generating PNG for ${fname}.puml"
    )

    list(APPEND UML_OUTPUTS 
        ${UML_IMG_DIR}/${fname}.svg
        ${UML_IMG_DIR}/${fname}.png
    )
endforeach()

# 自定义目标：生成 UML 图片
add_custom_target(generate_uml ALL
    DEPENDS generate_puml ${UML_OUTPUTS}
    COMMENT "Generating all UML diagrams (.puml -> .png/.svg)"
)

# 可选：拷贝 compile_commands.json 到源目录
# add_custom_target(copy_compile_commands ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_BINARY_DIR}/compile_commands.json
#         ${CMAKE_SOURCE_DIR}/compile_commands.json
#     COMMENT "Copy compile_commands.json to source root"
# )
