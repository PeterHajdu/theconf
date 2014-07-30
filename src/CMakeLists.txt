
set(SOURCE_FILES
  configuration.cpp
    )

add_library(theconf STATIC ${SOURCE_FILES})
target_link_libraries(theconf ${LIBS})
install(TARGETS theconf DESTINATION lib)

