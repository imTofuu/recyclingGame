file(GLOB_RECURSE ASSET_FILES RELATIVE ${CMAKE_SOURCE_DIR}/assets *.*)

add_custom_command(
        OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        DEPENDS ${ASSET_FILES}
        COMMENT "Copying assets to output directory"
        VERBATIM
)

add_custom_target(copy_assets ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)