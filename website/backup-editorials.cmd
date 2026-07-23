@echo off
setlocal
cd /d "%~dp0editor-gateway"
if not exist backups mkdir backups
call npm run db:export
