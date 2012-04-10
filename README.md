
By any means, this is not completely ready yet.

Pre-req (Setup and configure Informix)
======================================
Download and install informix (supported version 11.5).
Download and install CSDK.
It is assumed that informix is installed at `/opt/informix`, adjust approriately.
(by default IBM installs informix at `/opt/IBM/informix`)


```bash
INFORMIXDIR='/opt/informix'
INFORMIXSERVER='__MyInformixServer__'
ONCONFIG="onconfig.${INFORMIXSERVER}"
INFORMIXSQLHOSTS="${INFORMIXDIR}/etc/sqlhosts.${INFORMIXSERVER}"

INFORMIXLIBDIR="${INFORMIXDIR}/lib"
INFORMIXLIBS=${INFORMIXLIBDIR}

for d in c++ cli client client/csm csm dmi esql ; do
    if [[ -d "${INFORMIXLIBDIR}/${d}" ]]; then
        INFORMIXLIBS=${INFORMIXLIBS}:${INFORMIXLIBDIR}/${d}
    fi
done

LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${INFORMIXLIBS}

PATH=${INFORMIXDIR}/bin:${PATH}
IFMX_HISTORY_SIZE=10000

export INFORMIXSERVER INFORMIXDIR ONCONFIG INFORMIXSQLHOSTS LD_LIBRARY_PATH PATH IFMX_HISTORY_SIZE
```
Make sure Informix is running. Test that its accepting connections.

```bash
$ dbaccess sysmaster -
```

Install
=======
$ npm install nodejs-db-informix

NOTE: install with `sudo npm install nodejs-db-informix -g` fails at present.
It complains about finding esql. This can be fixed by adding above paths in
Pre-req for root user.

Build
=====
$ node-waf distclean configure build


Debug
-----
$ node-waf --debug distclean configure build


Test
====
$ node-waf test
-or-
$ nodejs tests/tests.js


License
=======
This module is released under the [MIT License] [license].

[license]: http://www.opensource.org/licenses/mit-license.php
