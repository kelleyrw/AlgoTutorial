@ECHO OFF

CALL python gen_proj.py --ignore-environment --format=msvs -G msvs_version=2013 --generator-output=build\msvs-12.0

PAUSE
