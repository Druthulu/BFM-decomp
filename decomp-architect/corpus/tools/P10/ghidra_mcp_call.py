"""tools/ghidra_mcp_call.py — call the Ghidra MCP server (:8080, SSE JSON-RPC) from a context without mcp__ghidra__* tools (P3.41 T8, C0554).

    ghidra_mcp_call.py list                              tool names, descriptions, argument names
    ghidra_mcp_call.py call <tool> '<json args>'          e.g. call types '{"action":"get","name":"COORD2_8001EFE0","program_name":"SLUS_007.26"}'
Read-only by use, not by design: a write tool called here edits the live DB. Needs tools/ghidra_mcp_start.sh serving."""
import json, sys, threading, queue, urllib.request
BASE = "http://127.0.0.1:8080"
q = queue.Queue()
def reader():
    r = urllib.request.urlopen(BASE + "/sse", timeout=120)
    ev = None
    for raw in r:
        ln = raw.decode("utf-8", "replace").rstrip("\r\n")
        if ln.startswith("event:"): ev = ln[6:].strip()
        elif ln.startswith("data:"): q.put((ev, ln[5:].strip()))
threading.Thread(target=reader, daemon=True).start()
ev, ep = q.get(timeout=30)
url = ep if ep.startswith("http") else BASE + ep
def rpc(i, method, params=None, notify=False):
    m = {"jsonrpc": "2.0", "method": method}
    if params is not None: m["params"] = params
    if not notify: m["id"] = i
    req = urllib.request.Request(url, json.dumps(m).encode(), {"Content-Type": "application/json"})
    urllib.request.urlopen(req, timeout=120).read()
    if notify: return None
    while True:
        ev, d = q.get(timeout=120)
        try: o = json.loads(d)
        except ValueError: continue
        if o.get("id") == i: return o
rpc(1, "initialize", {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "ghidra_mcp_call", "version": "1"}})
rpc(0, "notifications/initialized", notify=True)
if sys.argv[1] == "list":
    for t in rpc(2, "tools/list")["result"]["tools"]: print(t["name"], "|", (t.get("description") or "")[:90], "|", list(t.get("inputSchema", {}).get("properties", {})))
else:
    o = rpc(3, "tools/call", {"name": sys.argv[2], "arguments": json.loads(sys.argv[3] if len(sys.argv) > 3 else "{}")})
    for c in o.get("result", {}).get("content", []): print(c.get("text", c))
    if "error" in o: print("ERROR", o["error"])
