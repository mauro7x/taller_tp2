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

<hr>

# Detalles de implementación <a name="detalles"></a>

<hr>

# Conclusiones <a name="conclusiones"></a>