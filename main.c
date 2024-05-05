#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct { // Struct para los datos de cada película.
  char id[100];
  char title[100];
  List *genres;
  List *directors;
  float rating;
  int year;
  int decade;
} Film;

typedef struct{ // Struct para cada mapa necesitado.
  Map *pelis_byId;
  Map *pelis_byDirector;
  Map *pelis_byGenre;
  Map *pelis_byDecade;
  Map *pelis_byRating;
} TypeMapsList;

// Menú principal.
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Películas");
  puts("========================================");

  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente.
}

/**
 * Compara dos claves de tipo flotante para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo flotante.
 *
 * @param key1 Primer puntero a la clave flotante.
 * @param key2 Segundo puntero a la clave flotante.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_float(void *key1, void *key2) {
  return *(float *)key1 == *(float *)key2; // Compara valores flotantes directamente.
}

// Función para inicializar los mapas a utilizar.
void inicializarMapas(TypeMapsList *mapasPeliculas){
  // Utilizamos la función map_create para inicializar cada uno de los mapas
  // con su tipo de key correspondiente.
  mapasPeliculas->pelis_byId = map_create(is_equal_str);
  mapasPeliculas->pelis_byDirector = map_create(is_equal_str);
  mapasPeliculas->pelis_byGenre = map_create(is_equal_str);
  mapasPeliculas->pelis_byDecade = map_create(is_equal_int);
  mapasPeliculas->pelis_byRating = map_create(is_equal_float);
}

// Función que rellena una lista recibiendo un string.
void asignar_listas(List *lista, char *string){
  // Utiliza la función strtok para separar el string
  // si es que se encuentra el separador indicado.
  char *aux = strtok(string, ",");
  // Ciclo para recorrer la cadena completa.
  while(aux != NULL){
    // Si el primer carácter de nuestra cadena aux es un espacio, 
    // se avanza de posición para no considerar el espacio.
    if(isspace(*aux)) aux++;
    // Si el final de nuestra cadena aux son unas comillas, lo modificamos
    // para que ese sea el final de nuestra cadena auxiliar.
    if(aux[strlen(aux)-1] == '"') aux[strlen(aux)-1] = '\0';

    // Se ingresa la cadena auxiliar a la lista.
    list_pushBack(lista, strdup(aux));
    // Se continua recorriendo el string.
    aux = strtok(NULL, ",");
  }
}

// Función para guardar los pares dentro de un mapa.
void guardarPair(Map *mapa, MapPair *pair, Film *peli, void *key){
  if(pair != NULL){
    // Si el par es encontrado en el mapa, se ingresa en la lista de 
    // la key correspondiente.
    list_pushBack(pair->value, peli);
  } else{
    // Si el par no es encontrado en el mapa, creamos manualmente la lista.
    List *lista = list_create();
    // Ingresamos la pelicula a la lista.
    list_pushBack(lista, peli);
    // Insertamos la lista con su key correspondiente en el mapa.
    map_insert(mapa, key, lista);
  }
}

// Función para rellenar el mapa con key directores
void insertarMapaDirectores(Map *mapaDirectores, Film *peli){

  // Declaramos nuestro director auxiliar como el primero de la lista
  // de directores, ya que una película puede tener más de uno.
  char *directorAux = list_first(peli->directors);

  // Ciclo para recorrer la lista de directores de la película.
  while(directorAux != NULL){
    // Buscamos el par con el nombre del director auxiliar.
    MapPair *pair = map_search(mapaDirectores, directorAux);
    // Guardamos el par dentro del mapa.
    guardarPair(mapaDirectores, pair, peli, directorAux);
    // Continuamos recorriendo la lista de directores de la película.
    directorAux = list_next(peli->directors);
  }
}

// Función para rellenar el mapa con key generos.
void insertarMapaGeneros(Map *mapaGeneros, Film *peli){

  // Declaramos nuestro genero auxiliar como el primero de la lista
  // de generos, ya que una película puede tener más de uno.
  char *genreAux = list_first(peli->genres);

  // Ciclo para recorrer la lista de generos de la pelicula.
  while(genreAux != NULL){
    // Buscamos el par con el genero auxiliar.
    MapPair *pair = map_search(mapaGeneros, genreAux);
    // Guardamos el par dentro del mapa.
    guardarPair(mapaGeneros, pair, peli, genreAux);
    // Continuamos recorriendo la lista de generos de la película.
    genreAux = list_next(peli->genres);
  }
}

// Función para rellenar el mapa con key decadas.
void insertarMapaDecadas(Map *mapaDecadas, Film *peli){
  // Buscamos el par con la decada de la película.
  MapPair *pair = map_search(mapaDecadas, &peli->decade);
  // Guardamos el par dentro del mapa.
  guardarPair(mapaDecadas, pair, peli, &peli->decade);
}

// Función para rellenar el mapa con key ratings.
// En este caso, debido a que se busca por rango de calificaciones,
// las keys de los mapas iran de 0.5 en 0.5, ya que los rangos definidos
// son [0.0 - 0.4] - [0.5 - 0.9] - ... La forma de trabajarlos sera con el
// primer valor de cada rango, es decir, las peliculas dentro 
// del rango [7.0 - 7.4] se guardaran con key 7.0 para fines practicos.
void insertarMapaRatings(Map *mapaRatings, Film *peli){
  // Reservamos memoria para la key.
  float *key = (float *) malloc(sizeof(float));
  // Creamos un auxiliar que correspondera al rating redondeado.
  float aux = round(peli->rating);

  // Si la resta entre el rating y su valor redondeado es negativo,
  // quiere decir que el rating corresponderá al intervalo superior
  // por lo que key será su valor redondeado restado a 0.5, para que
  // corresponda al primer valor del intervalo.
  if(peli->rating - aux < 0) *key = aux - 0.5;
  // En caso contrario, el rating se habrá redondeado hacia abajo,
  // por lo que key conservará su valor redondeado.
  else *key = aux;

  // Buscamos el par con la key.
  MapPair *pair = map_search(mapaRatings, key);
  // Guardamos el par dentro del mapa.
  guardarPair(mapaRatings, pair, peli, key);
}

// Función para insertar las películas en todos los mapas a utilizar.
void insertar_en_mapas(TypeMapsList *mapasPeliculas, Film *peli){
  map_insert(mapasPeliculas->pelis_byId, peli->id, peli);
  insertarMapaDirectores(mapasPeliculas->pelis_byDirector, peli);
  insertarMapaGeneros(mapasPeliculas->pelis_byGenre, peli);
  insertarMapaDecadas(mapasPeliculas->pelis_byDecade, peli);
  insertarMapaRatings(mapasPeliculas->pelis_byRating, peli);
}

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
void cargar_peliculas(TypeMapsList *mapasPeliculas) {
  // Intenta abrir el archivo CSV que contiene datos de películas.
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse.
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV.

  // Lee cada línea del archivo CSV hasta el final.
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película.
    Film *peli = (Film *)malloc(sizeof(Film));    
    strcpy(peli->id, campos[1]);        // Asigna ID.
    strcpy(peli->title, campos[5]);     // Asigna título.
    peli->directors = list_create(); // Crea la lista de directores.
    asignar_listas(peli->directors, campos[14]); // Rellena la lista.
    peli->genres = list_create();   // Crea la lista de generos.
    asignar_listas(peli->genres, campos[11]); // Rellena la lista.
    peli->rating = 
      atof(campos[8]); // Asigna rating, convirtiendo de cadena a flotante.
    peli->year =
      atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero.
    peli->decade = (peli->year / 10) * 10; // Asigna decada de la película
    // Inserta las películas en los mapas correspondientes.
    insertar_en_mapas(mapasPeliculas, peli);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas.

  // Itera sobre el mapa para mostrar las películas cargadas.
  MapPair *pair = map_first(mapasPeliculas->pelis_byId);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title,
          peli->year);
    pair = map_next(mapasPeliculas->pelis_byId); // Avanza al siguiente par en el mapa.
  }
}

/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */
void buscar_por_id(Map *pelis_byId) {
  char id[100]; // Buffer para almacenar el ID de la película.

  printf("\n|| BUSCAR POR ID ||\n\n");
  // Solicita al usuario el ID de la película.
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado.

  // Busca el par clave-valor en el mapa usando el ID proporcionado.
  MapPair *pair = map_search(pelis_byId, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película.
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película.
    // Muestra el título y el año de la película.
    printf("Título: %s, Año: %d\n", peli->title, peli->year);
  } else {
    // Si no se encuentra la película, informa al usuario.
    printf("La película con id %s no existe\n", id);
  }
}

/**
 * Busca y muestra la información de una película por su director en un mapa.
 */
void buscar_por_director(Map *pelis_byDirector) {
  char director[300]; // Buffer para almacenar el director buscado.

  printf("\n|| BUSCAR POR DIRECTOR ||\n\n");
  // Solicita al usuario el director buscado.
  printf("Ingrese el director buscado: ");
  scanf(" %299[^\n]s", director); // Lee el director.

  // Busca el par utilizando el director proporcionado.
  MapPair *pair = map_search(pelis_byDirector, director);

  // Si se encontro el par, recorre la lista de películas con aquel
  // director y muestra la información.
  if (pair != NULL) {
    Film *peli = list_first(pair->value); // Obtiene el primer dato de la lista.
    while(peli != NULL){
      printf("Título: %s, Año: %d\n", peli->title, peli->year);
      peli = list_next(pair->value); // Continua recorriendo la lista.
    }
  } else {
    // Si no se encuentran películas, informa al usuario.
    printf("No existen películas con el director %s\n", director);
  }
}

/**
 * Busca y muestra la información de una película por su genero en un mapa.
 */
void buscar_por_genero(Map *pelis_byGenre) {
  char genero[100]; // Buffer para almacenar el género buscado.

  printf("\n|| BUSCAR POR GÉNERO ||\n\n");
  // Solicita al usuario el género buscado.
  printf("Ingrese el género de películas buscado: ");
  scanf(" %99[^\n]s", genero); // Lee el género.

  // Busca el par utilizando el género proporcionado.
  MapPair *pair = map_search(pelis_byGenre, genero);

  // Si se encontro el par, recorre la lista de películas con aquel
  // género y muestra la información.
  if (pair != NULL) {
    Film *peli = list_first(pair->value); // Obtiene el primer dato de la lista.
    while(peli != NULL){
      printf("Título: %s, Año: %d\n", peli->title, peli->year);
      peli = list_next(pair->value); // Continua recorriendo la lista.
    }
  } else {
    // Si no se encuentran películas, informa al usuario.
    printf("No existen películas del genero %s\n", genero);
  }
}

/**
 * Busca y muestra la información de una película por su decada en un mapa.
 */
void buscar_por_decada(Map *pelis_byDecade){
  int decada; // Buffer para almacenar la decada buscada.

  printf("\n|| BUSCAR POR DECADA ||\n\n");
  // Solicita al usuario la decada buscada.
  printf("Ingrese la decada de las películas buscadas: ");
  scanf(" %d", &decada); // Lee la decada.

  // Busca el par utilizando la decada proporcionada.
  MapPair *pair = map_search(pelis_byDecade, &decada);

  // Si se encontro el par, recorre la lista de películas con aquella
  // decada y muestra la información.
  if (pair != NULL) {
    Film *peli = list_first(pair->value); // Obtiene el primer dato de la lista.
      while(peli != NULL){
        printf("Título: %s, Año: %d\n", peli->title, peli->year);
        peli = list_next(pair->value); // Continua recorriendo la lista.
      }
    } else {
      // Si no se encuentran películas, informa al usuario.
      printf("No existen películas de la decada de %d\n", decada);
    } 
}

/**
 * Busca y muestra la información de una película por su rango de rating en un mapa.
 */
void buscar_por_rating(Map *pelis_byRating){
    float rating; // Variable para guardar el rating ingresado por el usuario.
    float aux; // Variable auxiliar para el rating redondeado.

    printf("\n|| BUSCAR POR RANGO DE CALIFICACIONES ||\n\n");
    // Se enseñan los intervalos de los rangos de calificaciones.
    printf(" [0.0-0.4]  [0.5-0.9]  [1.0-1.4]  [1.5-1.9]\n");
    printf(" [2.0-2.4]  [2.5-2.9]  [3.0-3.4]  [3.5-3.9]\n");
    printf(" [4.0-4.4]  [4.5-4.9]  [5.0-5.4]  [5.5-5.9]\n");
    printf(" [6.0-6.4]  [6.5-6.9]  [7.0-7.4]  [7.5-7.9]\n");
    printf(" [8.0-8.4]  [8.5-8.9]  [9.0-9.4]  [9.5-9.9]\n");
    printf(" [10.0]\n");
    // Se solicita al usuario que ingrese un rating dentro del rango
    // que desea observar.
    printf("\nIngrese un rating dentro del rango deseado: \n");
    scanf(" %f", &rating); // Se lee el rango.

    //Se redondea el rating ingresado y se guarda en aux.
    aux = round(rating);
  
    // Si la resta entre el rating y su valor redondeado es negativo,
    // quiere decir que el rating corresponderá al intervalo superior
    // por lo que su valor será el aux redondeado restado a 0.5, para que
    // corresponda al primer valor del intervalo.
    if(rating - aux < 0) rating = aux - 0.5;
    // En caso contrario, el rating se habrá redondeado hacia abajo,
    // por lo que rating conservará su valor redondeado.
    else rating = aux;

    // Se busca el par con el rating obtenido.
    MapPair *pair = map_search(pelis_byRating, &rating);

    // Si se encontro el par, recorre la lista del rango de califaciones
    // y muestra la información.
    if (pair != NULL) {
      Film *peli = list_first(pair->value); // Obtiene el primer dato de la lista.
        while(peli != NULL){
          printf("Título: %s, Año: %d, Rating: %.1f\n", 
            peli->title, peli->year, peli->rating);
          peli = list_next(pair->value); // Continua recorriendo la lista.
        }
      } else {
        // Si no se encuentran películas, informa al usuario.
        printf("No existen películas dentro de ese rango\n");
      } 
}

/**
 * Busca y muestra la información de una película por su decada y género en un mapa.
 */
void buscar_por_decada_y_genero(Map *pelis_byGenre){
  char genero[100]; // Buffer para almacenar el género buscado.
  int decada; // Buffer para almacenar la decada buscada.
  int aux = 0; // Variable para verificar si se encontró una
               // película con la decada buscada.

  printf("\n|| BUSCAR POR DECADA Y GENERO ||\n\n");
  // Se solicita al usuario el género buscado.
  printf("Ingrese el genero de películas buscado: ");
  scanf(" %99[^\n]s", genero); // Lee el género.
  // Se solicita al usuario la decada buscada.
  printf("Ingrese la decada de las peliculas buscadas\n");
  scanf(" %d", &decada); // Lee la decada.

  // Se busca un par con el GÉNERO proporcionado.
  MapPair *pair = map_search(pelis_byGenre, genero);

  // Si se encuentra un par con el GÉNERO buscado, recorre la lista
  // correspondiente a ese par.
  if (pair != NULL) {
    Film *peli = list_first(pair->value); // Obtiene el primer dato de la lista.
    while(peli != NULL){
      // Si la decada de la película corresponde a la decada buscada,
      // se enseña su información.
      if(peli->decade == decada){
        printf("Título: %s, Año: %d\n", peli->title, peli->year);
        aux = 1; // Se actualiza la variable auxiliar para corroborar que
                 // se encontro una película con los parametros proporcionados.
      }
      peli = list_next(pair->value); // Se continua recorriendo la lista.
    }
    // Si aux es 0, signficia que no se encontraron películas, por lo 
    // que se informa al usuario.
    if(aux == 0) 
      printf("No existen películas con aquellas especificaciones\n");
  } else {
    // En otro caso, se informa al usuario que no se encontraron películas.
    printf("No existen películas con aquellas especificaciones\n");
  }
}

// Función para liberar la memoria de los mapas.
void limpiarMapas(TypeMapsList *mapasPeliculas){
  // Utilizamos la función map_clean para liberar la memoria.
  map_clean(mapasPeliculas->pelis_byId);
  map_clean(mapasPeliculas->pelis_byDirector);
  map_clean(mapasPeliculas->pelis_byGenre);
  map_clean(mapasPeliculas->pelis_byDecade);
  map_clean(mapasPeliculas->pelis_byRating);
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario.
  TypeMapsList mapasPeliculas; // Creamos nuestra variable con todos los mapas.

  // Inicializamos los mapas.
  inicializarMapas(&mapasPeliculas);

  // Ciclo para el menú.
  do {
    // Mostramos el menú principal.
    mostrarMenuPrincipal();
    // Solicitamos al usuario la opción deseada.
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Lee la opción.

    // Se utiliza un switch para cada caso.
    switch (opcion) {
    case '1':
      cargar_peliculas(&mapasPeliculas);
      break;
    case '2':
      buscar_por_id(mapasPeliculas.pelis_byId);
      break;
    case '3':
      buscar_por_director(mapasPeliculas.pelis_byDirector);
      break;
    case '4':
      buscar_por_genero(mapasPeliculas.pelis_byGenre);
      break;
    case '5':
      buscar_por_decada(mapasPeliculas.pelis_byDecade);
      break;
    case '6':
      buscar_por_rating(mapasPeliculas.pelis_byRating);
      break;
    case '7':
      buscar_por_decada_y_genero(mapasPeliculas.pelis_byGenre);
      break;
    case '8':
      printf("Saliendo de la base de datos...\n");
      limpiarMapas(&mapasPeliculas);
      return 0;
    default:
      printf("\nLa opción ingresada no es válida\n");
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
