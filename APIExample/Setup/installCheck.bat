cd /d %~dp0

powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; ./'installCheck.ps1'}"
