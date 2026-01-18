@ECHO OFF

IF EXIST ".\build\" (
    ECHO Removing build folder...
    RD /S /Q ".\build\"
    ECHO Done.
) ELSE (
    ECHO build folder not found, skip.
)
