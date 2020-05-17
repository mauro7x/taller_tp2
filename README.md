# Informe TP2

## Detalles administrativos

* **Materia:** Taller de Programación I
* **Año y cuatrimestre:** 1°C 2020
* **Alumno:** PARAFATI, Mauro
* **Padrón:** 102749
* [**Link al repositorio**](https://github.com/mauro7x/taller_tp2)

<!-- ##################################################################### -->

# Tabla de contenidos

1. [Presentación del trabajo](#presentacion)
    * [Introducción](#introduccion)
    * [Descripción](#descripcion)
    * [Modelo propuesto por la cátedra](#modelo_catedra)
2. [Especificaciones provistas](#especificaciones)
    * [Recolectores](#recolectores)
    * [Productores](#productores)
    * [Archivos de entrada](#archivos)
        * [Configuración de los trabajadores](#workers)
        * [Mapa](#mapa)
    * [Códigos de retorno](#retorno)
    * [Entrada y salida estándar](#stdio)
    * [Restricciones](#restricciones)
3. [Resolución](#resolucion)
    * [Primera etapa: conceptos necesarios](#uno)
    * [Segunda etapa: abstracciones útiles](#dos)
    * [Tercera etapa: análisis del problema y detección de instancias](#tres)
    * [Cuarta etapa: diseño del modelo](#cuatro)
    * [Quinta etapa: manejo de errores](#cinco)
    * [Sexta etapa: desarrollar el modelo](#seis)
    * [Séptima etapa: testeo y debugging](#siete)
    * [Octava y última etapa: refactorizar](#ocho)
4. [Detalles de implementación](#detalles)
5. [Conclusiones](#conclusiones)


<!-- ##################################################################### -->

<hr>

# Presentación del trabajo <a name="presentacion"></a>

## Introducción <a name="introduccion"></a>

> Inspirados en la infinidad de juegos de estrategia que jugamos durante una reciente cuarentena, vamos a simular el comportamiento de un pequeño poblado ubicado en cualquiera de los universos pertenecientes a estos juegos.

## Descripción <a name="descripcion"></a>

> Nuestro poblado va a contar con un conjunto de **trabajadores**, que serán:
> - **Recolectores** (de materias primas),
> - **Productores** (que convierten materias primas en puntos de beneficio).
>
> Ambos tipos de trabajadores los vamos a modelar como **threads**. Existirán distintos tipos de recolectores, y tipos de productores.
>
> Cada conjunto de **recolectores** del mismo tipo recibirá los recursos desde una **cola bloqueante**, que deberemos implementar utilizando **condition variables**. Una vez que recibe el recurso, duerme durante **50 ms** (para simular trabajo), y
los deposita en un **inventario de materias primas compartido**.
> *(HINT: para disminuir la complejidad, se recomienda usar una cola bloqueante por cada tipo de recolector (no por tipo de recurso, aunque está permitido), y un solo inventario general).*
>
> Todos los **productores** van a consumir los recursos depositados en el inventario general tan pronto como estén disponibles *(HINT: entender claramente el significado de esto, relacionarlo con condition variables, y describir en el informe la solución)*, luego dormirán durante **60 ms**, y depositarán los puntos en un **contador de puntos general** (que también deberá ser uno solo para todo el escenario).
>
> El **hilo principal** será el encargado de ​ **spawnear** el resto de los hilos, **leer** tanto el archivo de configuración de los **trabajadores** como un segundo archivo con el **contenido del mapa**, y **repartir los recursos** en las colas bloqueantes, que son las entradas de los recolectores. Luego, este hilo se encargará de orquestar la **finalización ordenada del proceso** e imprimirá las **estadísticas finales**.

## Modelo propuesto por la cátedra <a name="modelo_catedra"></a>

> Si bien hay **numerosas maneras de implementar esto**, es **obligatorio** seguir estos **lineamientos** con el propósito de poner en práctica el uso de todas las **herramientas** de **concurrencia** que se ven en clase **(threads, mutex, y condition variables)**.
> 
> También es muy recomendable **incluir explicaciones breves** de cómo implementaron estas partes claves en sus soluciones.

| ![catedra](img/catedra.png) | 
|:--:| 
| *Modelo propuesto por la cátedra* |

> ​ En la imagen se puede ver un diagrama indicando los **hilos participantes** y los **recursos compartidos**. Notar que el sentido de las flechas indica una dependencia y no flujo de datos.
>
> El **hilo main** lee los **datos del mapa** y los **reparte** en las *colas bloqueantes*; cada **recolector** pasa las materias primas al
inventario *(la tabla del centro)*; y cada **productor** saca esos recursos del inventario y genera *puntos de beneficio*, que sumará al contador que está más a la derecha.
>
> *(HINT: Notar que para **sincronizar los accesos** al inventario se debe esperar por la condición de que “estén disponibles todos los recursos que necesito”: esto se puede resolver con una condition variable (para simplificar, usar una sola y no una por cada tipo de productor). También hay que contemplar que no todos los productores necesitan las mismas materias primas, por lo que será importante tener en cuenta la diferencia entre **notify** y **notify_all**).*

<hr>

# Especificaciones provistas <a name="especificaciones"></a>

## Recolectores <a name="recolectores"></a>

> Habrá **tres tipos de recolectores**:
> 1. **Agricultores:** son recolectores de *trigo​*.
> 2. **Leñadores:** son recolectores de *madera​*.
> 3. **Mineros:** recolectan *hierro* y *carbón​*. *(HINT: tener en mente que este tipo de trabajador puede recolectar dos tipos distintos de materia prima).*
>
> Tiempo de sleep para simular trabajo: **50ms**.
>
> La cantidad de cada recolector viene definida en un **archivo de configuración** de los trabajadores, que se describe más adelante.

## Productores <a name="productores"></a>

> Habrá **tres tipos de productores**:
> 1. **Cocineros:** convierten *2 unidades de trigo​ más 1 de carbón*, en **5 puntos de beneficio**.
> 2. **Carpinteros:** convierten *3 unidades de madera​ más 1 de hierro* en **2 puntos de beneficio**.
> 3. **Armeros:** convierten *2 unidades de carbón​ más 2 de hierro​* en **3 puntos de beneficio**.
>
> Tiempo de sleep para simular trabajo: **60ms**.
>
> La cantidad de cada productor viene definida en un **archivo de configuración** de los trabajadores, que se describe más adelante.

## Archivos de entrada <a name="archivos"></a>

> Nuestro programa cuenta con **dos archivos de entrada**, uno para la configuración de los trabajadores y otro para el contenido del mapa. El **uso del programa** debería ser el siguiente:
>
> `./tp trabajadores.txt mapa.txt`
>
> Se describe el formato de los dos archivos a continuación.

### Configuración de los trabajadores <a name="workers"></a>

> Consiste en un **archivo de texto** que indica las **cantidades de cada tipo de trabajador**. Se muestra un ejemplo con números arbitrarios a continuación:
> ```
> Agricultores=2
> Leniadores=1
> Mineros=3
> Cocineros=1
> Carpinteros=3
> Armeros=1
> ```

### Mapa de materias primas<a name="mapa"></a>

> Las **materias primas** también serán entrada de nuestro programa, y consistirán en una **matriz de caracteres en mayúsculas**. Dichas mayúsculas son las **iniciales de cada tipo de materia prima**: cada ‘T’ se interpreta como una unidad de Trigo, y los demás casos son análogos. Ejemplo arbitrario:
> ```
> TTTMCHHHC
> TTTMMCCCM
> MMMMMMMMM
> ```

## Códigos de retorno <a name="retorno"></a>

> El programa retornará:
> - **0:** si todo se ejecutó correctamente,
> - **1:** en caso de algún error al abrir, leer, o parsear alguno de los parámetros o archivos.
> 
> En caso de que el alumno encuentre otros tipos de errores, **se permite terminar con cualquier valor de retorno**, y se garantiza que no habrá casos de prueba que los validen.

## Entrada y salida estándar <a name="stdio"></a>

> La **entrada estándar** no será utilizada.
> La **salida estándar de errores** es **libre**, y el alumno puede utilizarla para imprimir mensajes útiles de error, a fin de corroborar alguna teoría al subir la implementación a SERCOM en caso de tener problemas que solamente se reproduzcan en ese entorno.
> La **salida estándar** se utilizará al final de cada ejecución para **mostrar cuántos recursos quedaron** en el inventario, y **cuántos puntos de beneficio** se lograron sumar. El formato será el siguiente:
> ```
> Recursos restantes:\n
>   - Trigo: <unidades-de-trigo-restantes>\n
>   - Madera: <unidades-de-madera-restantes>\n
>   - Carbon: <unidades-de-carbon-restantes>\n
>   - Hierro: <unidades-de-hierro-restantes>\n
> \n
> Puntos de Beneficio acumulados: <cantidad-de-puntos-final>\n
> ```
> Notar que antes de cada guión hay dos espacios.

## Restricciones <a name="restricciones"></a>

> La siguiente es una **lista de restricciones técnicas** exigidas por el cliente:
> 1. El sistema debe desarrollarse en **ISO C++11**.
> 2. Está **prohibido** el uso de variables globales.
> 3. Leer atentamente los lineamientos y recomendaciones.
> 4. El único uso permitido de funciones que sirvan para gastar tiempo (usleep) es para simular trabajo como se especificó. **NO está permitido** usarlas como mecanismo de sincronización.

<hr>

# Resolución <a name="resolucion"></a>

Para la resolución del ejercicio, decidí organizar el mismo en distintas **etapas**, con el objetivo de modularizar el trabajo y obtener código con responsabilidades claras desde un principio, para evitar terminar el trabajo con un código extenso y poco legible y luego tener que pasar mucho tiempo *refactorizando* el mismo.

## Primera etapa: conceptos necesarios <a name="uno"></a>

Mucho antes de empezar a codear, y de hecho antes de siquiera pensar en el ejercicio, me predispuse a **familiarizarme** con los conceptos necesarios para su realización y a investigar sobre los mismos para poder aplicarlos de la forma esperada y correcta.

Como se describe en el enunciado, este trabajo práctico hace énfasis en la programación **multi-hilo** *(multi-threading)*, en la que justamente se dividen las tareas del programa en no uno sino **varios hilos independientes** de ejecución, cada uno con responsabilidades claras, con el fin de *paralelizar* la ejecución y lograr mayor eficiencia.

Para su implementación en C++, utilizamos la librería `<thread>`, y luego distintas extensiones útiles para la **sincronización** de los mismos y para evitar problemas que en breve explicaremos, como por ejemplo los **dead-locks** o las **race-condition**. Estas extensiones son principalmente `<mutex>` y `<condition_variable>`:

- Los ***mutex*** son un mecanismo de protección de acceso a **recursos compartidos** entre hilos. Permiten evitar el problema conocido como **race-condition** *(en el que dos hilos intentan acceder al mismo recurso compartido y el resultado no es el esperado debido a que las operaciones no son atómicas, es decir, no son operaciones formadas por una instrucción assembly, estas se llaman CRITICAL SECTIONS)* mediante una idea muy simple: cuando un hilo quiere acceder a un recurso compartido, **se "toma" el mutex**, evitando que cualquier otro hilo que quiera acceder al recurso en ese momento pueda hacerlo. Cuando el hilo solicitante termina su tarea, **"libera"** el mutex para que un nuevo hilo lo pueda tomar.

- Las ***condition variables*** permiten evitar loops ineficientes de espera. Se utilizan cuando un hilo necesita que se cumpla una determinada condición para accionar, pero la misma no se cumple en un determinado momento. Una solución *naive* sería hacer un loop `while(/*no se cumpla la condición*/)`, pero esto resultaría muy ineficiente puesto que se chequearía la condición constantemente. Las **condition variables** solucionan este problema de la siguiente forma: cuando un hilo chequea si una condición se cumple y el resultado es que aun no, se pone a **"dormir"** al hilo (*wait*) hasta que se lo notifique de que *algo cambió*. En el momento en que otro hilo notifque a la condition variable, se **"despertará"** al hilo dormido, que nuevamente chequeará si ahora se cumple efectivamente la condición.

Estos dos mecanismos son **esenciales** en el desarrollo de la programación **multi-hilo** y se hará uso extensivo de ellos para llegar al resultado buscado.

## Segunda etapa: abstracciones útiles <a name="dos"></a>

Entendidos los conceptos, me predispuse a extraer **abstracciones** útiles de los mismos, aprovechando ejemplos que habíamos visto en clase o en internet. 

### Objetos activos (`Thread`)

La primer abstracción extraída y que será importante es la de **objetos activos**. Los objetos activos son aquellos que **corren en su propio hilo de ejecución**. Esto se logra haciendo que su clase lanze un `thread`, con un método al que llamaremos `run()` que se ejecutará en el hilo.

Para lograr encapsulamiento y mayor legibilidad, generamos nuestra clase `Thread` que se encarga de lanzar el método `run()` en un hilo, y de proporcionar la interfaz necesaria para la interacción con el hilo (poder hacerle *start* al hilo, así como poder *joinearlo*). Diremos entonces que todas las clases que hereden de `Thread` serán **objetos activos**.

### Recursos compartidos (`Monitor`)

Como se explicó anteriormente, cuando se programa con varios hilos de ejecución hay que tener especial cuidado con los **recursos compartidos** ya que estos deben tener un mecanismo de evitar que dos hilos lo quieran modificar simultáneamente.

Una idea muy útil es la de encapsular, en un mismo "paquete", tanto al **recurso a proteger** como al **mecanismo de protección**. Esta idea se llama "Monitor" *(ya que se encarga de monitorear el acceso al recurso)*. En nuestra implementación, vamos a proteger a los distintos recursos utilizando el mecanismo previamente explicado, `<mutex>`. Nuestra abstracción será entonces **RecursoProtegido** y será la clase que tenga al recurso y un mutex para protegerlo. Es **muy importante** que la API pública que se le ofrece al usuario de la clase tenga todos sus métodos **protegidos**. Para esto será clave reconocer las secciones de código que queremos **atomizar**, llamadas **critical sections**. Una vez que reconocemos estas secciones, simplemente generamos un método para cada una de ellas y lo ofrecemos en nuestra API.

Para ejemplificar, supongamos que tenemos un contador y una necesidad de incrementarlo **sólamente** si el contador está en `0`. Una primer idea podría ser tener dos métodos en nuestra interfaz: `isZero()` y `increment(int value)`, para luego hacer:

```
if (isZero()) { increment(...) }
```

Pero esto sería un ERROR, pues **esta operación no sería atómica**, y entre que chequeamos que el valor era cero y que efectivamente lo incrementamos, **otro hilo pudo haber modificado su valor**. Por lo tanto, lo correcto sería ofrecer el siguiente método en nuestra interfaz: `incrementIfZero(int value)` para atomizar la operación.

## Tercer etapa: análisis del problema y detección de instancias <a name="tres"></a>

Una vez que ya tengo las herramientas listas, procedo a encarar el enunciado del ejercicio con el objetivo de, en una primer leída entenderlo, y en una segunda leída poder **identificar** los entes que deberemos diseñar para resolverlo. 

Detallando el razonamiento seguido, vemos que tenemos:

- Un **mapa** y un **archivo de configuración** que parsear,
- **Trabajadores** que se dividen en **recolectores** y **productores**,
- Distintas **colas de recursos**, de donde los recolectores los tomarán para luego transferirlos al inventario,
- Un **inventario** general compartido,
- Un **contador de puntos de beneficio** compartido.

Procedo luego a utilizar las abstracciones que describí en la sección anterior:

- Podemos modelar a los **trabajadores** como **objetos activos**, que corran en su propio hilo de ejecución y realicen su tarea independientemente del resto del programa.
- Para implementar las **colas de recursos**, como en el enunciado se pide que sean bloqueantes, deberemos usar **condition variables** para notificar a los recolectores que los recursos que necesitan ya están listos para ser recolectados.
- Para modelar el **inventario** podemos utilizar una mezcla de conceptos: por un lado, necesitaremos un mecanismo de protección ya que se trata de un recurso compartido. Por otro lado, necesitaremos una forma de avisarle a los productores que esperan por recursos que los mismos están disponibles. Para esto último, utilizaremos **condition variables**.
- Podemos modelar al **contador de puntos de beneficio** con un **monitor**, puesto que se trata de un recurso compartido que proteger.
- Para el parseo del archivo de configuración y del mapa no necesitamos ningún hilo extra o mecanismo de protección, basta con modularizarlo en dos objetos **parsers** que se encarguen de darnos la información que necesitamos de los mismos, y eso se puede hacer en el **hilo principal**.

## Cuarta etapa: diseño del modelo <a name="cuatro"></a>

Ahora que ya sé qué debo diseñar y que objetos debo crear, me propongo armar un **plan de ejecución** en **pseudo-código** para luego ponerme a desarrollar sus distintas componentes. Es vital este paso, ya que establecer los lineamientos antes de empezar a escribir código tiene como beneficio la obtención de código muy **prolijo**, **legible** y sobre todo, **modularizado**.

Propongo entonces el siguiente *plan de ejecución*:

1) Lo primero que el hilo principal debe hacer es **parsear** el archivo de configuración de los trabajadores. Para esto, utilizará una clase `WorkersConfig` que tendrá este fin específico y le proporcionará al hilo principal la información necesaria para el *spawn* inicial.

2) El hilo principal hace *spawn* (hacer aparecer, generar, instanciar) a los distintos hilos necesarios: un hilo por cada trabajador. 

3) Se pone a *correr* a los distintos *threads*, para que comiencen su ejecución.

4) Se utiliza una clase `MapParser` para procesar el mapa y obtener sus recursos, y mientras se los obtiene se los distribuye entre las distintas **colas bloqueantes de recursos**.

5) Se **cierran** las colas de recursos para que los recolectores **finalicen su ejecución**, se *joinea* a los mismos.

6) Una vez que los recolectores terminan, se **cierra el inventario**, para indicarle a los productores que **ya no llegarán recursos nuevos**.

7) Cuando los productores terminen de **consumir los recursos del inventario**, terminan su ejecución y se *joinean* sus threads.

8) Se **imprimen los resultados finales** por salida estandar.

## Quinta etapa: manejo de errores <a name="cinco"></a>

Con el modelo listo, lo único que falta decidir es **como manejar los errores** en caso de que la ejecución no logre terminar correctamente. Si bien en el enunciado no lo exige, voy a utilizar el sistema de **excepciones** que provee C++. Me parece muy cómodo de usar, y genera código más legible sin tener tantas verificaciones por todos lados.

En una sección posterior ([Detalles de implementación](#detalles)) se explicará como se utilizó este sistema de manera más específica.

## Sexta etapa: desarrollar el modelo <a name="seis"></a>

Llegado este punto, es momento de **escribir el código** que le de sentido a nuestro diseño. Esto no debería ser una tarea difícil, ya que hemos decidido exactamente qué haremos y cómo lo haremos, y nos hemos tomado el tiempo de **familiarizarnos con las herramientas** que tenemos a nuestra disposición, y cuándo es conveniente utilizarlas.

En la sección [Detalles de implementación](#detalles) explicaré con detalle qué clases diseñe finalmente y la responsabilidad de cada una de ellas, ya que justamente son sólo detalles de implementación y no forman parte del modelo que ya describí.

## Séptima etapa: testeo y debugging <a name="siete"></a>

Con el programa terminado, sólo queda **probarlo** y **debuggearlo** ante la aparición de errores, a fin de solucionarlos. Para esto, utilicé las pruebas que se brindan en el sitio de entregas de la materia ([SERCOM](https://sercom.7542.fi.uba.ar/)) ya que justamente son las pruebas que verifican el comportamiento esperado de nuestro trabajo.

Se comprobó que, después de varias etapas de **debugging** y de **corrección de errores**, efectivamente **las pruebas pasaron**. En este punto ya tenemos un programa que cumple con lo pedido, y que por ende soluciona el ejercicio propuesto.

## Octava y última etapa: refactorizar <a name="ocho"></a>

Finalmente, entré en esta etapa de **refactor** en la que se busca mejorar partes del código que no me convencen, a fin de buscar mayor legibilidad, menos acoplamiento y mayor eficiencia. Por la modalidad seguida, **esta etapa fue muy corta**, ya que considero que plantear el modelo desde un principio ayuda mucho a escribir código limpio en menos intentos.

Para terminar, me aseguré de que cada parte del código este **documentada correctamente** y que sea fácilmente legible, así como de que las responsabilidades sean claras. Una vez logrado esto, **dí por finalizado el trabajo** y me predispuse a escribir el informe del mismo.





<hr>

# Detalles de implementación <a name="detalles"></a>

## Manejo de errores (1/2)

Para mi implementación, decidí vincular los **errores** a distintos **códigos de retorno**, y para esto diseñe una clase `Exception` que hereda de `std::exception` con el objetivo de poder agregarle como atributo el código mencionado a cada excepción. Esta clase me permitirá lanzar mensajes de error y códigos específicos para cada situación que se presente, como podrían ser las siguientes:

- **Errores en alguno de los archivos de entrada:** este caso está contemplado en el enunciado, y nos piden que salgamos con código de error `1`.
- **Errores en el uso del programa:** podemos indicarle al usuario el uso esperado.
- **Errores en la reserva de memoria dinámica:** si `new` falla, podemos devolver un mensaje de error específico y salir con otro código de error que indique este fallo.

Y todos los errores que puedan ir surgiendo a medida que desarrollo las clases, podrán ser agregados a esta lista y devolver un código de error particular.

## Códigos de retorno (2/2)

Siguiendo con el tema descripto en la sección previa, adjunto la tabla que indica los **códigos de retorno utilizados**:

| Código | Nombre | Descripción |
|--------|--------|-------------|
| 1 | INPUT_ERROR | *Ocurrió un error con alguno de los archivos de entrada: no existe(n) / no se pudo (pudieron) abrir / no tiene(n) el formato esperado* |
| 2 | USAGE_ERROR | *No se recibieron los parámetros esperados en la ejecución* |
| 3 | ALLOC_ERROR | *Fallo la reserva de memoria dinámica* |
| 4 | UNEXPECTED_NULL | *Se encontró un valor NULL donde no debía haberlo* |


<hr>

# Conclusiones <a name="conclusiones"></a>