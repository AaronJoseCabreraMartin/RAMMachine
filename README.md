# RAM MAchine Simulator
## *Autor*: _Aarón José Cabrera Martín_

### Uso

1. Compilar con `make`.
2. Ejecutar con `./bin/RAMMachine [falta]`

### Argumentos permitidos en el ejecutable

ram_sim recibe al menos 4 parámetros, puede recibir un quinto opcionalmente
Los parámetros que puede recibir se encuentran detallados en la siguiente lista:
  1. Programa formato RAM. Almacenado en un fichero con extensión ".ram" 
  2. Contenido de la cinta de entrada. Almacenado en un fichero con extensión ".in" .
  3. Fichero en el que se volcará el contenido de la cinta de salida.
  4. Se almacenará en un fichero con extensión ".out" .
  5. _Opcional_ Activar el modo depuración. (Con un 1)

Ejemplo de ejecución:
  ``./bin/ram_sim ejemplosRAM/test1.ram entrada.in salida.out 1``

### Modos de ejecución

 1. **Modo normal**

  La máquina ejecuta el programa, con la entrada de la cinta y arrojando el resultado en el fichero de salida que le hayamos pasado. Sólo mostrará en pantalla el número de instrucciones ejecutadas.

 2. **Modo debug**
 
  La máquina no ejecutará directamente sino que nos mostrará el siguiente menú:
  ```
    >h
      r: ver los registros      
      t: traza
      e: ejecutar
      s: desensamblador
      i: ver cinta entrada      
      o: ver cinta salida       
      h: ayuda
      x: salir
      p: ver programa almacenado
    >
  ```
  - **r**: muestra el contenido de los registros. El número de registros se modifica dinámicamente según se vaya necesitando durante la ejecución.

  - **t**: ejecuta el programa introducido paso a paso y mostrando los valores de los registros, del contador de programa etc.

  - **e**: ejecuta el programa introducido como lo haría normalmente.

  - **i**: muestra el contenido actual de la cinta de entrada.

  - **o**: muestra el contenido actual de la cinta de salida.

  - **h**: muestra la ayuda.

  - **x**: termina la ejecución y cierra el programa.

  - **p**: muestra el programa de entrada tal y como lo interpreta el simulador. Si hay algún fallo en la sintaxis, etiquetas duplicadas, se salta a una etiqueta no definida o se intenta dividir por 0 (mediante la carga inmediata, es decir, DIV =0 o DIV =-0). Se mostrará un mensaje de error en la consola y el programa aparecerá como vacío.

### Sintaxis de los programas RAM

- Sintaxis de las intrucciones

La sintaxis de los programas RAM debe ser la siguiente:

_[etiqueta]_ **(instrucción)** **(operando)**

A no ser que la instrucción sea **HALT**, en cuyo caso la sintaxis cambia a:

_[etiqueta]_ **HALT**

Nótese que se ha escrito entre corchetes y en cursiva la parte opcional de la sentencia (es decir, la etiqueta) y con paréntesis y en negrita la parte obligatoria (es decir, la instrucción y el operando, excepto HALT que no recibe operando)

- Operandos

Los operandos pueden ser de 3 tipos **directo**, **indirecto** o **inmediato**.

  - _Directo_

_Si no se trata de una instrucción de salto_

Los operandos en modo directo hacen referencia a que el número que contenga el operando se tratará como el registro al que hay que acceder. Los números de los registros deben ser enteros positivo, si no se cumple esta restricción se parará la ejecución de la máquina.

Ejemplo: ADD 2 sumará al contenido del acumulador el contenido del registro 2 y lo almacenará en el acumulador.

_Si se trata de una instrucción de salto_

El operando se tratará como una etiqueta, la cual puede contener números, letras... Cualquier carácter excepto el de los comentarios ";" y mientras la etiqueta se defina en algún punto del programa.

Ejemplo:

bucle: SUB =1
      JGTZ bucle
      HALT

Este fragmento de código resta uno al acumulador, luego comprueba si es mayor que 0, si lo es salta a la etiqueta bucle, con lo que se vuelve a ejecutar la resta. Si no se cumple la condición de que el acumulador es mayor que 0 se ejecutaría la siguiente instrucción, es decir HALT terminando la ejecución del programa.

  - _Indirecto_

Las sentencias que permiten el modo indirecto en los operandos son STORE y READ. Este modo se activa colocando un "*" delante del número que representará un registro, es decir, lo que realizará la instrucción será: acceder al registro indicado detrás del *, el valor que contenga ese registro se tratará como la dirección de un registro así que finalmente la instrucción se ejecutará con ese otro registro.

El número detrás del * debe cumplir las restricciones propias de un registro, un número entero positivo.

Ejemplo: STORE *2 se miraría el contenido del registro 2, pero, supongamos que contiene un 1, en ese caso, la instrucción sería equivalente a STORE 1.

  - _Inmediato_

Este modo se activa colocando un símbolo "=" delante de un número. El número detrás del = se tratará como un literal, por lo tanto puede ser negativo. La interpretación de este modo es la siquiente: por ejemplo con ADD =1, sería; acumulador = acumulador + 1.

Las instrucciones STORE y READ no permiten direccionamiento inmediato por el propio significado de las instrucciones.
