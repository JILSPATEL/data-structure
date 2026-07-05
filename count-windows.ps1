# Run from repo root: .\count-cpp.ps1

$count = (Get-ChildItem -Recurse -Filter *.cpp -File | Measure-Object).Count
$badge = "![cpp files](https://img.shields.io/badge/.cpp%20files-$count-blue)"

(Get-Content README.md) -replace '!\[cpp files\].*', $badge | Set-Content README.md

Write-Host "Updated: $count .cpp files"
