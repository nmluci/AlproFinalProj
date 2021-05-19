Write-Host "Kissaten Simulator AutoCompiler" -ForegroundColor "cyan"
Write-Host "By. nmluci (github.com/nmluci)" -ForegroundColor "darkcyan"

if (Get-Command "gcc.exe" -ErrorAction SilentlyContinue) {
    Write-Host "Compiling..." -ForegroundColor "darkcyan"
    $cxCFile = Get-ChildItem *.c -Recurse | Resolve-Path -Relative | Join-String -Separator " "
    $cxHFile = Get-ChildItem *.h -Recurse | Resolve-Path -Relative | Join-String -Separator " "
    Invoke-Expression("gcc {0} {1} -o app.exe" -f ($cxCFile, $cxHFile))
    Write-Host "Program Compiled as app.exe" -ForegroundColor "darkcyan"
} else {
    Write-Host "Install GCC first!" -ForegroundColor "red"
}