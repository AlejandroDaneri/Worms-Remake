# tp-final-taller

## cmake    uso:
mkdir build

cd build

cmake -DROOT=/home/mati/Desktop/worms .. && make install  

elegir la ruta (para instalar en otra carpeta, con el otro cmakelists.txt) 


### Lista de tareas
https://trello.com/b/77GBgtcb/worms

### Pagina parar rotar imagenes
http://pinetools.com/rotate-image


### archivos Yaml parser
https://github.com/jbeder/yaml-cpp

### Lista de clases gtk
https://www.gtk.org/tutorial1.2/gtk_tut.html#toc10

https://developer.gnome.org/gnome-devel-demos/stable/c.html.es

### Instalar Sdl:

sudo apt-get install libsdl2-mixer-dev (para el sonido)

Si no funciona con esto probar con lo que dice esta pagina:
https://gist.github.com/BoredBored/3187339a99f7786c25075d4d9c80fad5

(No estoy seguro cual de todos fue el que me funciono)

Ejemplos: http://lazyfoo.net/tutorials/SDL/index.php

### valgrind  (es incorrible igual)

valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=gtk_valgrind.sup ./client

### Animations
http://www.gsarchives.net/index2.php?category=sprites&system=computer&game=worms_armageddon&type=sprites&level0=

### Sound effects
https://www.sounds-resource.com/pc_computer/wormsarmageddon/
