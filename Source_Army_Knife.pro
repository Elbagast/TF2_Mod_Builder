TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
  sak \
  tf2mb \
  sak_test \
  tf2mb_test

tf2mb.depends = sak
sak_test.depends = sak
tf2mb_test.depends = tf2mb

DISTFILES += \
    README.md \
    project_layout.txt
