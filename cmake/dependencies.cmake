# These list variables are going to be sent to caller
set(Dependencies_BINS "")
set(Dependencies_INCLUDE_DIRS "")
set(Dependencies_LIBRARIES "")
set(Dependencies_LIBRARY_DIRS "")
set(Dependencies_DEFINITIONS "")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
# Set up Dependencies variables
find_package(Exiv2 REQUIRED)
list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${EXIV2_INCLUDE_DIR})
list(APPEND Dependencies_LIBRARIES PUBLIC ${EXIV2_LIBRARIES})
list(APPEND Dependencies_DEFINITIONS PUBLIC ${EXIV2_DEFINITIONS})

