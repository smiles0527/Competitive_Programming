$ErrorActionPreference = "Stop"
$gateway = Join-Path $PSScriptRoot "editor-gateway"
Set-Location $gateway

if (-not (Test-Path -LiteralPath "node_modules")) {
    Write-Host "Installing gateway tools..."
    npm install
}

Write-Host "Preparing consolidated editorial snapshot..."
npm run seed:build

Write-Host "Applying local D1 migrations..."
npm run db:migrate

$marker = Join-Path $gateway ".wrangler\editorials-seeded"
if (-not (Test-Path -LiteralPath $marker)) {
    Write-Host "Importing the initial 399 editorials..."
    npm run db:seed | Out-Null
    if ($LASTEXITCODE -ne 0) {
        throw "The initial editorial import failed."
    }
    New-Item -ItemType File -Force -Path $marker | Out-Null
}

Write-Host "Local editorial database is ready."
