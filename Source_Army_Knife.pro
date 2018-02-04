TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
  sak \
  tf2mb \
  testing

tf2mb.depends = sak
testing.depends = sak

DISTFILES += \
    README.md \
    project_layout.txt
