import unreal

# MCP 서버 자동 시작
unreal.SystemLibrary.execute_console_command(None, "MCP.StartServer")
unreal.log("MCP Server auto-started")