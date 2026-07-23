$ErrorActionPreference = "Stop"
$repository = Split-Path -Parent $PSScriptRoot
$gateway = Join-Path $PSScriptRoot "editor-gateway"
Set-Location $repository

foreach ($script in @(
    "website\api.js",
    "website\shortcut.js",
    "website\site-config.js",
    "website\editor-gateway\src\worker.js",
    "website\editor-gateway\scripts\build-seed.mjs",
    "website\editor-gateway\scripts\check-snapshot.mjs"
)) {
    node --check $script
    if ($LASTEXITCODE -ne 0) { throw "JavaScript validation failed: $script" }
}

Push-Location $gateway
try {
    node scripts/check-snapshot.mjs
    if ($LASTEXITCODE -ne 0) { throw "Editorial snapshot validation failed." }
    node --test tests/*.test.mjs
    if ($LASTEXITCODE -ne 0) { throw "Gateway tests failed." }
}
finally {
    Pop-Location
}

$legacyMarkdown = Get-ChildItem -LiteralPath (Join-Path $repository "CSES") -Recurse -Filter *.md
if ($legacyMarkdown.Count) {
    throw "Legacy Markdown remains in CSES solution folders: $($legacyMarkdown.Count) files"
}

Write-Host "Website checks passed: D1 schema, Worker, UI scripts, and 399-editorial snapshot."
