# $Id$
#
# Resource location for standalone documents. A document is standalone if its
# installation directory contains all neccessary for viewing it; this should be
# the case for documents installed under $PREFIX on user's systems.

RESOURCES = $(THEME)/css/docs $(THEME)/css/common
CSSFILE = docs/docs.css

# To output documentation inside each project's doc/ directory.
DOCSINSTALLDIR = doc/install

include common.mk

