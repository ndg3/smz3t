#!/usr/bin/env sh

cd ${0%/*}

glib-compile-resources --target ../src/items.c --generate-source items.gresource.xml

cd - > /dev/null
