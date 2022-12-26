#!/bin/bash

DoxyfilePath="$1/docs/Doxyfile"
cd "docs"
doxygen $DoxyfilePath

