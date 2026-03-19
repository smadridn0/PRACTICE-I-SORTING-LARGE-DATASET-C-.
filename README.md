Reporte:
Nuestro proyecto constó de organizar un listado de 100,000 palabras usando los algoritmos de quicksort y heapsort, y con la estructura de arbol binario avl.
El primer algoridmo usado, el quicksort, consiste en primero encontrar un "pivote" dentro de la lista,
calculando la media entre el valor maximo y minimo de la lista(metodo "median of three"), para luego agrupar todos los valores mayores y menores al pivote juntos; 
luego, dentro de cada grupo de datos, se encuentran pivotes en cada uno y se repite el proceso; esto eventualmente organizaría los datos.
Para este proceso se hizo una funcion que se encarge de encontrar el pivote con median of three, 
otra que se encarga de la particion entre datos mayores y menores que el pivote, y otra función principal que lleve a cabo la partición de forma recursiva, 
para así llevar a cabo el quicksort.

El segúndo algoritmo usado es el heapsort, basado en la estructura del "heap", que es un arbol binarío organizado, 
lo que en este caso significa que los nodos hijos deben ser menores que sus padres(max heap). El algoritmo organiza los datos como si se tratara de un heap, 
luego, mueve el primer elemento(que en este caso es el nodo superior del arbol), y lo cambia por el ultimo elemento; 
luego de esto, se vuelve a ordenar un max heap con todos los datos exepto por el ultimo elemento(que sería el dato mayor).
esto se repite hasta que los datos esten organizados.
Nuestro algoritmo contiene una función que primero organiza el heap tree y otra que llama a la anterior de forma recursiva omitiendo el ultimo elemento, 
consiguiendo así el heapsort.
