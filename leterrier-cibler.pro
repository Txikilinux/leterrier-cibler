######################################################################
# Automatically generated by qmake (2.01a) lun. nov. 15 07:44:54 2010
######################################################################

QT += script xml network
system(ccache -V):QMAKE_CXX = ccache g++

TEMPLATE = app

TARGET = leterrier-cibler

DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += abuleduaproposv0.h mainwindow.h tete.h \
    abuleduexercicev0.h version.h

FORMS += mainwindow.ui \
    abuleduaproposv0.ui

SOURCES += abuleduaproposv0.cpp main.cpp mainwindow.cpp tete.cpp \
    abuleduexercicev0.cpp

RESOURCES += NombreCible.qrc

RC_FILE = windows/icon.rc
include(lib/abuleduapplicationv1/abuleduapplicationv1.pri)
include(lib/abuleduconstantesv1/abuleduconstantesv1.pri)
include(lib/abuledunetworkaccessmanagerv1/abuledunetworkaccessmanagerv1.pri)
include(lib/abuledumessageboxv1/abuledumessageboxv1.pri)
include(lib/abuleduidentitesv1/abuleduidentitesv1.pri)
include(lib/abuleduflatboutonv1/abuleduflatboutonv1.pri)
include(lib/maia/maia.pri)
include(lib/abuledufilev1/abuledufilev1.pri)
include(lib/abuledustackedwidgetv1/abuledustackedwidgetv1.pri)
include(lib/abuledulangv1/abuledulangv1.pri)
include(lib/abuledumenufeuillev1/abuledumenufeuillev1.pri)
