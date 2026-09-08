// BfmMcpServer.java — headless GhidrAssistMCP server with clean save-on-shutdown.
//
// PERSISTENCE MODEL (verified 2026-06-13):
//   * GhidrAssistMCP write tools apply changes immediately, but under headless
//     (-Djava.awt.headless=true) they leave the change in an OPEN transaction:
//     program.isChanged() reads false and program.save() throws
//     "Unable to lock due to active transaction" — so there is NO mid-session save.
//   * On a CLEAN shutdown, analyzeHeadless's normal end-of-run save COMMITS that
//     pending transaction and writes the program DB (verified: a rename survived a
//     full stop + reopen, db.3.gbf -> db.4.gbf, "Save succeeded for processed file").
//
//   => To persist MCP work: request a clean stop (touch the stopreq sentinel, e.g.
//      via tools/ghidra_mcp_stop.sh). This script stops the MCP server and RETURNS,
//      letting analyzeHeadless save+close the project. Resume by restarting (the
//      saved db reopens). Checkpoint == stop + restart at task boundaries.
//
// Run as a -preScript (no package decl). Imports the extension server class, which
// resolves because GhidrAssistMCP.jar is on the headless JVM classpath.
//
// Args (key=value): host=  port=  stopreq=

import ghidra.app.script.GhidraScript;
import ghidra.util.Msg;
import ghidrassistmcp.GhidrAssistMCPHeadlessServer;
import java.io.File;

public class BfmMcpServer extends GhidraScript {

    @Override
    protected void run() throws Exception {
        if (currentProgram == null) {
            Msg.warn(this, "BfmMcpServer: no program loaded — aborting");
            return;
        }

        String host = "127.0.0.1";
        int port = 8080;
        String stopReqPath = System.getProperty("user.home") + "/bfm-decomp/.run/mcp-stop.req"; // project-local default (overridden by stopreq= arg)
        String[] scriptArgs = getScriptArgs();
        if (scriptArgs != null) {
            for (String a : scriptArgs) {
                if (a.startsWith("host=")) host = a.substring(5);
                else if (a.startsWith("port=")) port = parseIntOr(a.substring(5), port);
                else if (a.startsWith("stopreq=")) stopReqPath = a.substring(8);
            }
        }

        File stopReq = new File(stopReqPath);
        stopReq.delete(); // clear any stale sentinel so we don't stop immediately

        GhidrAssistMCPHeadlessServer srv = GhidrAssistMCPHeadlessServer.getInstance();
        if (srv.isRunning()) {
            srv.setProgram(currentProgram);
            Msg.info(this, "BfmMcpServer: server already running; program reference updated");
        } else {
            srv.start(currentProgram, host, port);
            Msg.info(this, "BfmMcpServer: MCP server started on " + host + ":" + port);
        }

        Msg.info(this, "BfmMcpServer: serving (stopreq=" + stopReqPath + "). "
                 + "MCP writes persist on CLEAN SHUTDOWN only — analyzeHeadless commits+saves on close; "
                 + "no mid-session save (GhidrAssist holds an open transaction while serving).");

        while (!monitor.isCancelled() && srv.isRunning()) {
            if (stopReq.exists()) {
                stopReq.delete();
                Msg.info(this, "BfmMcpServer: stop requested via sentinel");
                break;
            }
            Thread.sleep(1000);
        }

        srv.stop();
        Msg.info(this, "BfmMcpServer: server stopped; returning so analyzeHeadless saves+closes the project.");
    }

    private static int parseIntOr(String s, int dflt) {
        try { return Integer.parseInt(s.trim()); } catch (Exception e) { return dflt; }
    }
}
