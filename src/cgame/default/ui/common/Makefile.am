cguicommondir = @PKGLIBDIR@/default/ui/common
cguicommon_DATA = \
	common.css

noinst_HEADERS = \
	BindTextView.h \
	CvarCheckbox.h \
	CvarSelect.h \
	CvarSlider.h \
	CvarTextView.h

noinst_LTLIBRARIES = \
	libcguicommon.la

libcguicommon_la_SOURCES = \
	BindTextView.c \
	CvarCheckbox.c \
	CvarSelect.c \
	CvarSlider.c \
	CvarTextView.c

libcguicommon_la_CFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/cgame \
	-I$(top_srcdir)/src/cgame/default \
	-I$(top_srcdir)/src/cgame/default/ui \
	@BASE_CFLAGS@ \
	@GLIB_CFLAGS@ \
	@OBJECTIVELYMVC_CFLAGS@ \
	@OPENGL_CFLAGS@

libcguicommon_la_LDFLAGS = \
	-shared

libcguicommon_la_LIBADD = \
	@OBJECTIVELYMVC_LIBS@ \
	@OPENGL_LIBS@
