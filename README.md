# Reporte:
Nuestro proyecto constó de organizar un listado de 100,000 palabras usando los algoritmos de quicksort y heapsort, y con la estructura de arbol binario avl.
## Algoritmos de ordenamiento:
### quicksort:
El primer algoridmo usado, el quicksort, consiste en primero encontrar un "pivote" dentro de la lista,
calculando la media entre el valor maximo y minimo de la lista(metodo "median of three"), para luego agrupar todos los valores mayores y menores al pivote juntos; 
luego, dentro de cada grupo de datos, se encuentran pivotes en cada uno y se repite el proceso; esto eventualmente organizaría los datos.
### funciones:
Para este proceso se hizo una funcion que se encarge de encontrar el pivote con median of three, sumando al dato menor la mitad de la diferencia entre el dato mayor y menor(low + (high - low) / 2); para despues cambiar de lugar cambiar el dato mayor, menor y mediana para que queden ordenados de menor a mayor dentro del arreglo. Y finalmente intercambiando el dato mayor con el pivote, para facilitar el ordenamiento.
Otra funcion se encarga de la particion entre datos mayores y menores que el pivote, encontrando la media y apilando todos los datos menores a esta al principio del vector, para despues ubicar el dato del pivote en la posicion posterior al ultimo dato menor apilado.
Y finalmente, una función principal que lleve a cabo la partición de forma recursiva en los conjuntos a cada lado del pivote, para así llevar a cabo el quicksort.


### Heapsort:
El segúndo algoritmo usado es el heapsort, basado en la estructura del "heap", que es un arbol binarío organizado, 
lo que en este caso significa que los nodos hijos deben ser menores que sus padres(max heap). El algoritmo organiza los datos como si se tratara de un heap, 
luego, mueve el primer elemento(que en este caso es el nodo superior del arbol), y lo cambia por el ultimo elemento; 
luego de esto, se vuelve a ordenar un max heap con todos los datos exepto por el ultimo elemento(que sería el dato mayor), esto se repite hasta que los datos esten organizados
### funciones:
Nuestro algoritmo contiene una función que primero organiza el heap tree, analizando si cierto dato y sus nodos hijos(encontrados con las formulas 2i + 1 y 2i+2 para los hijos izquierdos y derechos, respectivamente), e intercambiandolo de lugar con alguno de ellos si estos son mayores que su padre, para despues revisar recursivamente si también es mayor que los demas nodos de su linea de desendencia, para también intercambiarlos dado el caso.
Y otra función que primero organiza los datos iniciales en un heap, y despues llama a la anterior de forma recursiva omitiendo el ultimo elemento, 
consiguiendo así el heapsort.
