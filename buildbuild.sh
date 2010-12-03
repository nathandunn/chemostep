#!/bin/sh
# FILE: "/Users/nathandunn/cvs/WORKSPACE/arraymulttest/buildbuild.sh"
# LAST MODIFICATION: "Thu, 10 Jul 2003 17:44:44 -0700 (nathandunn)"
# (C) 2003 by Nathan Dunn, <ndunn@mac.com>
# $Id: buildbuild.sh,v 1.1 2003/10/24 20:35:57 ndunn Exp $
aclocal
autoconf
automake --add-missing
