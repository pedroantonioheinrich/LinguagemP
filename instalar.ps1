# Script de Instalação - Linguagem P (Windows)
$ErrorActionPreference = "Stop"

Write-Host "🚀 Iniciando instalação da Linguagem P no Windows..." -ForegroundColor Cyan

# 1. Verificar se o GCC está instalado
Write-Host -NoNewline "🔍 Verificando dependências: gcc... "
$gccCheck = Get-Command gcc -ErrorAction SilentlyContinue
if (!$gccCheck) {
    Write-Host "ERRO" -ForegroundColor Red
    Write-Host "--------------------------------------------------------" -ForegroundColor Yellow
    Write-Host "❌ O compilador 'gcc' não foi encontrado."
    Write-Host "A Linguagem P precisa do MinGW ou GCC instalado no Windows."
    Write-Host "Como instalar:"
    Write-Host "  1. Baixe o MSYS2 (https://www.msys2.org/)"
    Write-Host "  2. Ou use o Chocolatey: choco install mingw"
    Write-Host "--------------------------------------------------------"
    exit
}
Write-Host "OK!" -ForegroundColor Green

# 2. Criar pastas de build
if (!(Test-Path "obj")) { New-Item -ItemType Directory -Path "obj" | Out-Null }
if (!(Test-Path "bin")) { New-Item -ItemType Directory -Path "bin" | Out-Null }

# 3. Compilar os módulos
Write-Host "📦 Compilando módulos do sistema..." -ForegroundColor Cyan
gcc -Wall -Wextra -g -Iinclude -c src/*.c
Move-Item *.o obj/

# 4. Gerar o executável lp.exe
Write-Host "🔧 Gerando binário lp.exe..." -ForegroundColor Cyan
gcc -o bin/lp.exe obj/*.o

# 5. Configurar o PATH (Comando Global)
$installDir = "$env:USERPROFILE\.linguagemp"
if (!(Test-Path $installDir)) { New-Item -ItemType Directory -Path $installDir | Out-Null }

Write-Host "📂 Movendo binário para $installDir..." -ForegroundColor Cyan
Copy-Item "bin/lp.exe" "$installDir\lp.exe" -Force

# Adicionar ao PATH do usuário se não estiver lá
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -notlike "*$installDir*") {
    Write-Host "🌐 Adicionando Linguagem P ao seu PATH..." -ForegroundColor Cyan
    [Environment]::SetEnvironmentVariable("Path", "$currentPath;$installDir", "User")
    $env:Path += ";$installDir"
}

# 6. Limpeza
Remove-Item -Recurse -Force obj, bin

Write-Host "--------------------------------------------------------"
Write-Host "✅ Instalação concluída com sucesso!" -ForegroundColor Green
Write-Host "Reinicie seu terminal para começar a usar o comando 'lp'."
Write-Host "Exemplo: lp -r seu_arquivo.lp" -ForegroundColor White
Write-Host "--------------------------------------------------------"