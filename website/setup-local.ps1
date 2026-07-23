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

$countJson = npx wrangler d1 execute DB --local `
    --command "SELECT COUNT(*) AS count FROM editorials WHERE status = 'published';" `
    --json
if ($LASTEXITCODE -ne 0) {
    throw "Could not inspect the local editorial database."
}
$countResult = $countJson | ConvertFrom-Json
$publishedCount = [int]$countResult[0].results[0].count

if ($publishedCount -eq 0) {
    Write-Host "Importing the initial 399 editorials..."
    npm run db:seed | Out-Null
    if ($LASTEXITCODE -ne 0) {
        throw "The initial editorial import failed."
    }
}
else {
    Write-Host "Local database already contains $publishedCount published editorials."
}

Write-Host "Local editorial database is ready."
