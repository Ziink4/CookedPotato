# Set target name
set(POTATO_TARGET cookbook)
message("Configuring ${POTATO_TARGET}")

find_package(Doxygen REQUIRED)

set(DOXYGEN_MULTILINE_CPP_IS_BRIEF YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT    YES)
set(DOXYGEN_WARN_NO_PARAMDOC       YES)
set(DOXYGEN_GENERATE_TREEVIEW      YES)

doxygen_add_docs(${POTATO_TARGET}
    "../src"
    "../include"
    ALL
    COMMENT "Generating documentation"
)