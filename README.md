## Descripción del Programa

Este programa permite a los usuarios cargar datos de películas desde un archivo y de esta manera poder organizarlas y buscarlas según un código identificador, director, década de estreno, genero/s de la película, rango de calificaciones, y finalmente una busqueda que permite filtrar por década y género al mismo tiempo.

Esta herramienta tiene la intención de darle a los usuarios una experiencia dinámica a la hora de buscar películas y lograr encontrar la que más se ajuste a sus gustos personales.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. 

Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/JoaquinGarridoRiquelme/Tarea-2`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", pegar el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -lm -o main" y presionar "done".
7. Presione el boton "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Cargar datos de las películas desde un archivo
- Buscar las películas según su código identificador
- Buscar las películas según su director
- Buscar las películas según su genero
- Buscar las películas según su década de estreno
- Buscar las películas según su calificación
- Buscar las películas según su década de estreno y género al mismo tiempo
- Salir del programa

### Problemas conocidos:

- Para el funcionamiento correcto de la aplicación, el usuario debe ingresar los datos a la hora de
  buscar de la misma manera que se ingresa la carga de películas, en este caso el archivo. Un ejemplo
  para esto es que si en el archivo la película tiene genero "Romance", el usuario a la hora de buscar
  según ese criterio debe ingresar la palabra "Romance" de la misma forma, con la primera letra mayúscula
  y las siguientes en minúscula, o en caso de contener un tilde también debería ingresarse.


### A mejorar:

- Con el fin de evitar resultados inesperados, el usuario deberá ingresar respuestas lógicas y que estén dentro de las opciones disponibles en la búsqueda. Un ejemplo de esto, es que el si el usuario desea buscar según la calificación de una película, no debe ingresar la palabra "choclo", ya que aunque el programa seguirá funcionando sin fallos, no le pedirá nuevamente ingresar la opción.

## Ejemplo de uso

**Paso 1: Cargar datos de películas**

Nuestro usuario quiere buscar películas de su interés, por lo que primero cargará datos desde el archivo para comenzar el uso del programa.
````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción: 1
````


(Para este caso, por la naturaleza extensa del archivo, no ingresaremos la lista completa de películas y solo dejaremos claro que se cargó correctamente).

**Paso 2: Buscar película por código identificador**
````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción: 2
````

Nuestro usuario ha ingresado a la opción 2 del menú, por lo que procedemos a pedirle que escriba el código al que quiere acceder, para así saber que película debemos mostrar.

````
|| BUSCAR POR ID ||

Ingrese el id de la película: tt0084602
Título: Rocky III, Año: 1982
Presione enter para continuar...
````

**Paso 3: Buscar película por director**

````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción: 3
````
Nuestro usuario ha ingresado a la opción 3 del menú, por lo que procedemos a pedirle que escriba el nombre del director del cual desea mostrar la lista de películas.

````
|| BUSCAR POR DIRECTOR ||

Ingrese su opción: 3
Ingrese el director de las películas buscadas: Sylvester Stallone
Título: Rocky IV, Año: 1985
Título: Rocky II, Año: 1979
Título: Rocky III, Año: 1982
Presione enter para continuar...
````

**Paso 4: Buscar película según década y género**

````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción: 7
````

Nuestro usuario ha ingresado a la opción 7 del menú, por lo que desea hacer una busqueda de películas que pertenezcan a una misma década y a un mismo género.

````
|| BUSCAR POR DECADA Y GENERO ||

Ingrese el genero de películas buscado: Thriller
Ingrese la decada de las peliculas buscadas
1930
Título: The 39 Steps, Año: 1935
Título: Fury, Año: 1936
Título: M - Eine Stadt sucht einen Mörder, Año: 1931
Título: Frankenstein, Año: 1931
Título: Scarface, Año: 1932
Título: The Lady Vanishes, Año: 1938
Título: Angels with Dirty Faces, Año: 1938
Título: The Man Who Knew Too Much, Año: 1934
Título: The Princess Comes Across, Año: 1936
Título: Young and Innocent, Año: 1937
Título: Marked Woman, Año: 1937
Título: Number Seventeen, Año: 1932
Título: Sabotage, Año: 1936
Título: The Petrified Forest, Año: 1936
Presione enter para continuar...
````

**Paso 5: Salir del programa**

````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción: 8
````

Nuestro usuario ha ingresado la opción 8 del menú, por lo que entendemos que ya no desea seguir utilizando el programa y debemos salir del mismo.

````
Saliendo de la base de datos...
````

## Contribuciones individuales

### Nicolas Reed:
- Rol asumido: Conductor
- Implementación y modularización del código
- Documentación y comentarios en el código
- Auto-evaluación : 3 (Aporte excelente)

### Joaquín Garrido:
- Rol asumido : Navegador
- Revisión y corrección de errores
- Sugerencia de cambios y enfoque en las respuestas
- Diseño y redacción del README.
- Auto-evaluación : 3 (Aporte excelente)
