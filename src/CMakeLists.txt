
set(SOURCE_FILES
    )

add_library(theopt STATIC ${SOURCE_FILES})
target_link_libraries(theopt ${LIBS})
install(TARGETS theopt DESTINATION lib)

