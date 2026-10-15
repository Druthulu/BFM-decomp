#!/usr/bin/env python
"""job.py -- a long command run detached, so the agent hands back while it runs (3.28.1 T11).

    job.py start -- <cmd> [args...]   start it under .run/jobs/<id>/; prints the id and returns at once
    job.py status <id>                running | done <exit> | dead (then the log's last lines)

`.run/jobs/<id>/`: `pid` (the waiting wrapper's), `log` (the command's stdout and stderr) and, when it exits, `done`
(`<exit code> <UTC time>`). The agent then hands back `WAITING: job <id>`; the mod tells it `job <id> finished: exit
<n>` when `done` appears, or that it died. The command is an argv, run in the project root; a pipeline is `bash -c`.
Stdlib only; Windows and POSIX (WSL).
"""

import datetime
import json
import os
import secrets
import subprocess
import sys

try:                          # UTF-8 output even when not started with -X utf8
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
except Exception:
    pass

TAIL = 10


def find_root(start=None):
    env = os.environ.get("PA_PROJECT_ROOT")
    if env:
        return os.path.abspath(env)
    cur = os.path.abspath(start or os.getcwd())
    while True:
        if os.path.isfile(os.path.join(cur, ".claude", "pa.json")):
            return cur
        parent = os.path.dirname(cur)
        if parent == cur:
            return os.path.abspath(start or os.getcwd())
        cur = parent


def job_dir(root, jid):
    return os.path.join(root, ".run", "jobs", jid)


def alive(pid):
    """Whether process `pid` runs (Windows: OpenProcess and its exit code; os.kill there would terminate it)."""
    if pid <= 0:
        return False
    if os.name == "nt":
        import ctypes
        k = ctypes.windll.kernel32
        h = k.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
        if not h:
            return False
        code = ctypes.c_ulong()
        ok = k.GetExitCodeProcess(h, ctypes.byref(code))
        k.CloseHandle(h)
        return bool(ok) and code.value == 259  # STILL_ACTIVE
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except PermissionError:
        return True
    return True


def start(argv):
    if not argv:
        print("job.py start -- <cmd> [args...]: no command", file=sys.stderr)
        return 2
    root = find_root()
    jid = "%s-%s" % (datetime.datetime.now().strftime("%Y%m%d-%H%M%S"), secrets.token_hex(2))
    d = job_dir(root, jid)
    os.makedirs(d)
    with open(os.path.join(d, "cmd.json"), "w", encoding="utf-8", newline="\n") as fh:
        json.dump({"argv": argv, "cwd": root}, fh)
    kw = {"stdin": subprocess.DEVNULL, "stdout": subprocess.DEVNULL, "stderr": subprocess.DEVNULL,
          "cwd": root, "close_fds": True}
    run = [sys.executable, os.path.abspath(__file__), "_run", d]
    if os.name == "nt":
        flags = subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP
        try:   # outside the caller's job object, so the shell's end does not take it along
            subprocess.Popen(run, creationflags=flags | subprocess.CREATE_BREAKAWAY_FROM_JOB, **kw)
        except OSError:
            subprocess.Popen(run, creationflags=flags, **kw)
    else:
        subprocess.Popen(run, start_new_session=True, **kw)
    print(jid)
    return 0


def run_job(d):
    """The detached wrapper: runs the command, then writes `done`."""
    with open(os.path.join(d, "pid"), "w", encoding="utf-8", newline="\n") as fh:
        fh.write("%d\n" % os.getpid())
    with open(os.path.join(d, "cmd.json"), encoding="utf-8") as fh:
        spec = json.load(fh)
    with open(os.path.join(d, "log"), "ab") as log:
        try:
            code = subprocess.call(spec["argv"], cwd=spec["cwd"], stdin=subprocess.DEVNULL, stdout=log,
                                   stderr=subprocess.STDOUT)
        except OSError as err:
            log.write(("job.py: %s\n" % err).encode("utf-8"))
            code = 127
    at = datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    tmp = os.path.join(d, "done.tmp")
    with open(tmp, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("%d %s\n" % (code, at))
    os.replace(tmp, os.path.join(d, "done"))
    return 0


def tail(path, n=TAIL):
    try:
        with open(path, "rb") as fh:
            fh.seek(0, os.SEEK_END)
            fh.seek(max(0, fh.tell() - 16384))
            lines = fh.read().decode("utf-8", "replace").splitlines()
    except OSError:
        return []
    return lines[-n:]


def status(jid):
    d = job_dir(find_root(), jid)
    if not os.path.isdir(d):
        print("no job %s" % jid, file=sys.stderr)
        return 2
    def done():
        try:
            with open(os.path.join(d, "done"), encoding="utf-8") as fh:
                return fh.read().split()[0]
        except (OSError, IndexError):
            return None
    try:
        with open(os.path.join(d, "pid"), encoding="utf-8") as fh:
            pid = int(fh.read().strip() or 0)
    except (OSError, ValueError):
        pid = -1   # not written yet: the wrapper is starting
    running = pid == -1 or alive(pid)
    code = done()   # read after the liveness check: a wrapper that exited meanwhile has written it
    if code is not None:
        print("done %s" % code)
        return 0
    if running:
        print("running")
        return 0
    print("dead")
    for line in tail(os.path.join(d, "log")):
        print(line)
    return 0


def main(argv):
    if len(argv) >= 2 and argv[0] == "_run":
        return run_job(argv[1])
    if len(argv) >= 1 and argv[0] == "start":
        rest = argv[1:]
        return start(rest[1:] if rest[:1] == ["--"] else rest)
    if len(argv) == 2 and argv[0] == "status":
        return status(argv[1])
    print(__doc__.strip().splitlines()[2] + "\n" + __doc__.strip().splitlines()[3])
    return 0 if argv[:1] in (["-h"], ["--help"]) else 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
