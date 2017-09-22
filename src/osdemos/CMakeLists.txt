include_directories (
	${CMAKE_SOURCE_DIR}/src/util
	${OSMESA_INCLUDE_DIRS}
	${OPENGL_INCLUDE_PATH}
)

link_directories (
	${CMAKE_SOURCE_DIR}/src/util
	${OSMESA_LIBRARY_DIRS}
)

link_libraries (
	util
	${OSMESA_LIBRARIES}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
)

set (subdir osdemos)

set (targets
	osdemo
	osdemo16
	osdemo32
)

foreach (target ${targets})
	add_executable (${subdir}_${target} ${target}.c)
	set_target_properties (${subdir}_${target} PROPERTIES OUTPUT_NAME ${target})
	install (TARGETS ${subdir}_${target} DESTINATION ${subdir})
endforeach (target)
