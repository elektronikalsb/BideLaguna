#define LED 10          // Se indica que el led se conectará al pin 10 del Atmega.
#define SENSOR A0       // Pin de entrada analógica al Atmega (en las pruebas se utiliza un Fin de Carrera).
                        // En caso de utilizar un sensor analógico habría que hacer un mapeo-equivalencia (0 = 0 v = 0 bits ; 1 = 5v = 1023 bits).
#define BUZZER 11       // Pin del Atmega al que se conecta el buzzer.

int contador = 0;       // Variable que contará los ciclos. Empieza en cero.
float estado_sensor;    // Variable que indica el dato que registra el sensor, que como es analógico tiene distintos "infinitos" valores.
int intermitencia = 1;  // Variable llamada así que es "1", necesaria para que el programa sepa en qué situación se encuentra.

                     
void setup()
{
  Serial.begin(9600);                 // Abre el puerto serie
                                      // Sirve para mandar la letra "código" vía Bluettoth.           
                                      // Conexión serie entre ordenador y Atmega para visualización de la progresión del programa.
  pinMode (SENSOR, INPUT);            // Indica que el sensor (fin de carrera) es un pin de entrada al ATMEGA.
  pinMode (LED, OUTPUT);              // Indica que el led es un pin de salida del Atmega.
  pinMode (BUZZER, OUTPUT);           // Indica que el buzzer es un pin de salida del Atmega.
}

void loop()
{
  do                                          // (1º)La instrucción principal en la que se basa este programa es "do while". Para que se de una progresión del
                                              // programa indicada en un "while" lo indicado entre este y su"do" tiene que suceder por lo menos una vez. 
  {                                           // Pequeño bloque de instrucciones que se ejecutan nada más alimentar el Atmega. Sucederá sí o sí.    
    digitalWrite (LED, HIGH);                 // Al encenderse el dispositivo, cuando le llega corriente, se enciende una luz contínua que lo indica.
    //Serial.println("Encendido");            // En el visualiador del ordenador se leería ...
    estado_sensor = digitalRead (SENSOR);     // Se ordena que el Atmega empiece a leer el sensor o detecte si el FC está presionado.
    //Serial.print("estado_sensor = "); 
    //Serial.println(estado_sensor);
    digitalWrite (BUZZER, LOW);               // El buzzer no suena.
  } while (estado_sensor == LOW);             // (1º). Cuando se presiona el FC (Hasta ahora "encendido", a partir de aquí "trabajando".
  do                                          // (2º). Cuando suceda lo siguiente en su "while" se entrará en estado de "alarma".
  {
    do                                        // (3º). Cuando suceda lo siguiente,tras su "while" se entra en estado de "prealarma".
    {
      if (intermitencia == 1)                 // Si el estado de intermitencia es "1"
      {
        digitalWrite (BUZZER, LOW);           // el buzzer no suena
      } 
      else                                    // si no
      {
        digitalWrite (LED, HIGH);             // se enciende la luz y no suena el buzzer.
        digitalWrite (BUZZER, LOW);
      }
      //Serial.println("Trabajando");       
      estado_sensor = digitalRead (SENSOR);   // Lee el sensor (o F.C.)
      //Serial.print("estado_sensor = ");
      //Serial.println(estado_sensor);
      if (estado_sensor == 1)                 // Si el estado del sensor es "1"; detecta señal
      {
        contador = 0;                         // el contador está a cero y
        intermitencia = 1;                    // el estado "intermitencia" es "1" 
      }
    } while (estado_sensor == HIGH);          // (3º). Cuando el FC no está presionado. (Se entra en “prealarma”).
    intermitencia = 0;                        // El estado de "intermitencia" se pone a cero
    digitalWrite (LED, HIGH);                 // se enciende el led y
    analogWrite(BUZZER, 120);                 // el buzzer emite un sonido bajo (120 del tope de salida que es 255; salida PWM)
    delay (500);                              // durante medio segundo.
    digitalWrite (BUZZER, LOW);               // Se apaga el led y
    digitalWrite (LED, LOW);                  // el buzzer
    delay (500);                              // otro medio segundo.
    contador++;                               // El contador empieza a contar o sumar. Cada ciclo será de un segundo.
    //Serial.print("contador = ");            //
    //Serial.println(contador);               //
  }  while (contador < 10);                   // (2º). Hace lo anterior hasta que el contador es mayor que "10", entonces ("alarma")
  analogWrite(BUZZER, 255);                   // el buzzer suena fuerte.
  //Serial.println("Alarma");                 //
  while (1);                                  // Se "fuerza" al programa a quedarse en este bucle.
  {                                           // Estado en el que se encuentra el programa al empezar.
    digitalWrite (LED, HIGH);                 // Led encendido
    delay (200);                              // durante un cuarto de segundo
    digitalWrite (LED, LOW);                  // led apagado
    delay (200);                              // durante un cuarto de segundo
  }
}
