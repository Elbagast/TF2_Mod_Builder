
# Flamingo
#==============================
FLAMINGO_INCLUDE_DIR = "D:/Programming/Qt Projects/flamingo/"
FLAMINGO_LIBRARY_DIR = "D:/Programming/Qt Projects/flamingo/lib/"

CONFIG(release, debug|release): FLAMINGO_LIBRARY_DIR = $${FLAMINGO_LIBRARY_DIR}release/
CONFIG(debug, debug|release): FLAMINGO_LIBRARY_DIR = $${FLAMINGO_LIBRARY_DIR}debug/

LIBS += -L$${FLAMINGO_LIBRARY_DIR}
LIBS += -lflamingo

INCLUDEPATH += $${FLAMINGO_INCLUDE_DIR}
DEPENDPATH += $${FLAMINGO_LIBRARY_DIR}
