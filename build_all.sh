#!/bin/bash
#
# Convenience script to build all versions of Tao Presentations.
# When done, packages are copied into .. (parent directory).
#
# Usage: ./build_all.sh
#
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2012 Jerome Forissier <jerome@taodyne.com>
# (C) 2012 Taodyne SAS

doo() {
  echo "$@" >&4
  "$@"
}

cp_kit() {
  case `uname` in
    Darwin)
      doo cp packaging/macosx/*.dmg ..
      ;;
    MINGW*)
      doo cp packaging/win/*.exe ..
      ;;
    Linux)
      doo cp packaging/linux/*.deb ..
      ;;
  esac
}

die() {
  echo $1 >&2
  exit 1
}

git diff-index --quiet HEAD -- || die "Error: Git work area is dirty."

LOG=/tmp/taobuild.log
echo Log file: $LOG >&2

exec 4>&2
{ time {
for v in discovery creativity impress ; do
  doo make distclean
  doo ./configure $v && doo make -j3 install && doo make kit && cp_kit
done ;
} >$LOG 2>&1; }
exec 4>&-
