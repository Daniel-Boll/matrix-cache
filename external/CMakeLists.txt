include(../cmake/CPM.cmake)

# Utility
# ----------------------- FMT ------------------------#
CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 8.1.1
)
