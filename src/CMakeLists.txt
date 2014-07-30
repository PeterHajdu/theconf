
set(SOURCE_FILES
    )

add_library(theconf STATIC ${SOURCE_FILES})
target_link_libraries(theconf ${LIBS})
install(TARGETS theconf DESTINATION lib)

