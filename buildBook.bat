@echo off

set BAT_FILE_DIR=%~dp0

rem Create directory for output files
mkdir "%BAT_FILE_DIR%\pdf

rem Build the book
pdflatex -aux-directory=%BAT_FILE_DIR%\pdf -include-directory=%BAT_FILE_DIR%\book -output-directory=%BAT_FILE_DIR%\pdf %BAT_FILE_DIR%\book\cppDesignBook.tex

set BAT_FILE_DIR=