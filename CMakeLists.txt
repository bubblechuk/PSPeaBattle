cmake_minimum_required(VERSION 3.11)

project(pspeabattle)

add_executable(${PROJECT_NAME}
    main.cpp

    CCell.cpp
    CField.cpp
    CGame.cpp
    CGameInput.cpp
    CGameLogic.cpp
    CGameRenderer.cpp
    CShip.cpp
    CStrategyAI.cpp
    CTextureManager.cpp
)
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FEATURE)
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

if (PSP)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH "./build/icon.png"
        BACKGROUND_PATH "./build/bg.png"
        PREVIEW_PATH NULL
        TITLE "PSPeaBattle"
        VERSION 01.00
    )
endif()