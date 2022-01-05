Compile c++ code to webassembly

```
cd engine
emcc -I. -o newtonraphson.js -Oz -s MODULARIZE=1 \       1 х  4s  16:16:50
 -s EXPORT_NAME=createModule --bind \
 problem.cpp newtonraphson.cpp board.cpp performance.cpp bindings.cpp
```

To inject webassembly code, insert following line into `visualisation/public/index.html` file

```
<script type="text/javascript" src="./engine/engine.js"></script>
```
