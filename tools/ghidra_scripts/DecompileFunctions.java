// DecompileFunctions.java — headless postScript: batch-decompile a list of functions
// (one hex address per line in arg[0]) and write each function's C to arg[1]/<name>.c.
// Built for the Phase-17 harvest Ghidra pre-pass: dump whole-program Ghidra-C for the
// tractable residuals so harvest agents get local/global/callee disambiguation m2c lacks,
// WITHOUT live-MCP contention (agents read the cached files).
// Usage: -postScript DecompileFunctions.java <addr-list-file> <out-dir>
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class DecompileFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        if (a.length < 2) {
            println("USAGE: DecompileFunctions.java <addr-list-file> <out-dir>");
            return;
        }
        String addrFile = a[0];
        String outDir = a[1];
        new File(outDir).mkdirs();
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        List<String> lines = Files.readAllLines(Paths.get(addrFile));
        int ok = 0, fail = 0, nofunc = 0;
        for (String raw : lines) {
            String line = raw.trim();
            if (line.isEmpty()) continue;
            Address addr = toAddr(line);
            Function f = getFunctionAt(addr);
            if (f == null) f = getFunctionContaining(addr);
            if (f == null) { nofunc++; println("NOFUNC " + line); continue; }
            DecompileResults res = di.decompileFunction(f, 60, monitor);
            String out;
            if (res != null && res.decompileCompleted()) {
                out = res.getDecompiledFunction().getC();
                ok++;
            } else {
                out = "// DECOMPILE FAILED: " + (res != null ? res.getErrorMessage() : "null result");
                fail++;
            }
            Files.write(Paths.get(outDir, f.getName() + ".c"), out.getBytes());
        }
        di.dispose();
        println("DecompileFunctions: " + ok + " ok, " + fail + " decompile-fail, " + nofunc
                + " no-func -> " + outDir);
    }
}
