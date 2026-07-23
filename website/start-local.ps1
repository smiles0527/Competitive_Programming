param(
    [int]$Port = 8766,
    [int]$ApiPort = 8787,
    [switch]$Open,
    [switch]$SkipSetup
)

$ErrorActionPreference = "Stop"
$repository = Split-Path -Parent $PSScriptRoot
$gateway = Join-Path $PSScriptRoot "editor-gateway"
Set-Location $repository

if (-not (Get-Command node -ErrorAction SilentlyContinue)) {
    throw "Node.js was not found. Install Node.js 20 or newer."
}
if (-not (Get-Command npm.cmd -ErrorAction SilentlyContinue)) {
    throw "npm was not found."
}
$python = Get-Command python -ErrorAction SilentlyContinue
if (-not $python) {
    throw "Python 3 was not found."
}

if (-not $SkipSetup) {
    & (Join-Path $PSScriptRoot "setup-local.ps1")
}

$wranglerState = Join-Path $gateway ".wrangler"
New-Item -ItemType Directory -Force -Path $wranglerState | Out-Null
$apiOut = Join-Path $wranglerState "api.out.log"
$apiError = Join-Path $wranglerState "api.error.log"
$api = Start-Process -FilePath "npm.cmd" `
    -ArgumentList @("run", "dev", "--", "--port", "$ApiPort") `
    -WorkingDirectory $gateway `
    -RedirectStandardOutput $apiOut `
    -RedirectStandardError $apiError `
    -WindowStyle Hidden `
    -PassThru

$url = "http://127.0.0.1:$Port/website/index.html"
Write-Host ""
Write-Host "Editorial site: $url"
Write-Host "Editorial API:  http://127.0.0.1:$ApiPort"
Write-Host "Press Ctrl+C to stop both services."
Write-Host ""

if ($Open) {
    Start-Process $url
}

try {
    & $python.Source -m http.server $Port --bind 127.0.0.1 --directory $repository
}
finally {
    if ($api -and -not $api.HasExited) {
        taskkill /PID $api.Id /T /F 2>$null | Out-Null
    }
}
