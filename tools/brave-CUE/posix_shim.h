/* POSIX build shim for CUE's brave.c + common.inc on glibc/gcc.
 *
 * The GPL upstream sources (brave.c, common.inc) are compiled UNMODIFIED via
 *   gcc -include tools/brave-CUE/posix_shim.h ...
 * keeping the re-vendored upstream byte-for-byte clean. common.inc uses two
 * Watcom/MSVC-isms that glibc lacks, and omits the headers they need:
 *
 *   - filelength(int fd)  -> provided here via fstat().
 *   - mkdir(path)         -> one-arg call; POSIX mkdir needs (path, mode), so a
 *                            function-like macro supplies a default mode. The
 *                            real prototype is pulled in (below) BEFORE the macro
 *                            is defined, so the declaration is unaffected; only
 *                            common.inc's later 1-arg call sites expand.
 */
#ifndef BRAVE_POSIX_SHIM_H
#define BRAVE_POSIX_SHIM_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static long filelength(int fd) {
    struct stat s;
    return fstat(fd, &s) ? -1L : (long)s.st_size;
}

/* common.inc calls mkdir(path) with one argument; redirect to 2-arg POSIX
 * mkdir. The name inside the expansion is not re-expanded (self-reference is
 * "painted blue"), so this resolves to the real mkdir(path, 0777). */
#define mkdir(p) mkdir((p), 0777)

#endif /* BRAVE_POSIX_SHIM_H */
