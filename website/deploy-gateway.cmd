@echo off
setlocal
cd /d "%~dp0editor-gateway"
call npm install || exit /b 1
call npm run check || exit /b 1
call npm run db:migrate:remote || exit /b 1
call npm run deploy
