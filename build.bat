set files=src\*.c
set libs=w:\lib\SDL2main.lib w:\lib\SDL2.lib

cl /Zi /I .\include /I w:\include %files% /link %libs% /out:rider.exe
