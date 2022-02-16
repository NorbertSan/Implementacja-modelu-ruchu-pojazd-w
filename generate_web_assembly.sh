printf "\n[1/3] 👉 Cleanning up old webassembly code \n"

cd visualisation/src || exit
rm engine.mjs

cd ../../engine

printf "\n[2/3] 👉 Compiling c++ code into webassembly and inserting into react application... \n"

emcc -o ../visualisation/src/engine.mjs -Oz -s EXPORT_NAME=createModule \ -s ENVIRONMENT='web'  \ -s SINGLE_FILE=1 \ --bind \ board.cpp cell.cpp globals.cpp bindings.cpp

printf "\n[3/3] 👉 Finished ✅\n"

exit 0