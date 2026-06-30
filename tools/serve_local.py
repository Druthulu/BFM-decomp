#!/usr/bin/env python3
"""serve_local.py — minimal OpenAI-compatible server for the fine-tuned BFM matcher, on the GPU.

Loads the base Qwen2.5-Coder-7B (4-bit) + a LoRA adapter via Unsloth — the SAME .venv-train stack
that trained it, so no llama.cpp build and no SIGILL-prone prebuilt wheel (this host's CPU has no
AVX-512, which crashes the generic llama-cpp-python CUDA wheels). Serves /v1/chat/completions +
/v1/models so tools/api_draft.py + tools/lora_grind.py hit it UNCHANGED.

  .venv-train/bin/python tools/serve_local.py --adapter models/bfm-match-7b --name bfm-match-7b-v2 --port 1234
  API_BASE=http://127.0.0.1:1234/v1 MODEL=bfm-match-7b-v2 ... tools/lora_grind.py ...

On-demand only (no daemon); SIGTERM/Ctrl-C to stop. One GPU generation at a time (a lock serializes
— lora_grind drafts sequentially anyway). The requested `model` field is ignored; the loaded adapter
is served (so MODEL can be any non-empty string).
"""
import argparse, json, threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--adapter", default="models/bfm-match-7b")
    ap.add_argument("--name", default="bfm-match-local")
    ap.add_argument("--port", type=int, default=1234)
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--max-seq", type=int, default=4096)
    a = ap.parse_args()

    from unsloth import FastLanguageModel
    import torch
    print(f"[serve] loading {a.adapter} (base+adapter, 4-bit, GPU)...", flush=True)
    model, tok = FastLanguageModel.from_pretrained(a.adapter, max_seq_length=a.max_seq, load_in_4bit=True)
    FastLanguageModel.for_inference(model)
    lock = threading.Lock()
    print(f"[serve] model ready: {a.name}", flush=True)

    def generate(messages, max_tokens, temperature):
        prompt = tok.apply_chat_template(messages, tokenize=False, add_generation_prompt=True)
        inputs = tok(prompt, return_tensors="pt").to("cuda")
        do_sample = bool(temperature and temperature > 0)
        with lock, torch.no_grad():
            out = model.generate(**inputs, max_new_tokens=max_tokens, do_sample=do_sample,
                                 temperature=(temperature or 1.0), pad_token_id=tok.eos_token_id)
        return tok.decode(out[0][inputs["input_ids"].shape[1]:], skip_special_tokens=True)

    class H(BaseHTTPRequestHandler):
        def log_message(self, *args):
            pass

        def _json(self, code, obj):
            b = json.dumps(obj).encode()
            self.send_response(code)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(b)))
            self.end_headers()
            self.wfile.write(b)

        def do_GET(self):
            if self.path.rstrip("/").endswith("/models"):
                self._json(200, {"object": "list", "data": [{"id": a.name, "object": "model"}]})
            else:
                self._json(404, {"error": "not found"})

        def do_POST(self):
            if not self.path.endswith("/chat/completions"):
                self._json(404, {"error": "not found"})
                return
            n = int(self.headers.get("Content-Length", 0))
            req = json.loads(self.rfile.read(n) or b"{}")
            try:
                txt = generate(req.get("messages", []), int(req.get("max_tokens", 1024)),
                               float(req.get("temperature", 0.2)))
                self._json(200, {"id": "cmpl", "object": "chat.completion", "model": a.name,
                                 "choices": [{"index": 0, "finish_reason": "stop",
                                              "message": {"role": "assistant", "content": txt}}]})
            except Exception as e:
                self._json(500, {"error": str(e)})

    srv = ThreadingHTTPServer((a.host, a.port), H)
    print(f"[serve] {a.name} serving on http://{a.host}:{a.port}/v1", flush=True)
    srv.serve_forever()


if __name__ == "__main__":
    main()
