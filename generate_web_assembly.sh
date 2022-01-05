printf "\n[1/2] 👉 Cleanning up old webassembly code \n"

cd visualisation/src || exit
rm engine.mjs

cd ../../engine

printf "\n[2/2] 👉 Compiling c++ code into webassembly and inserting into react application... \n"
emcc -I. -o ../visualisation/src/engine.mjs -Oz -s EXPORT_NAME=createModule \ -s ENVIRONMENT='web'  \ -s SINGLE_FILE=1  \ -s USE_ES6_IMPORT_META=0  \ --bind \ board.cpp cell.cpp main.cpp globals.cpp bindings.cpp

