#include <Adafruit_Sensor.h>//Auxiliar al DTH11
#include <DHT.h>//Sensor de humedad temperatura
#define DHTTYPE DHT11 //Se define el tipo de sensor

int sensor_humedad_pin = A0;//Sensor humedad tierra planta

int pinDHT11 = 2;//Sensor humedad y temperatura
DHT dht(pinDHT11, DHTTYPE); //Se asigna el pin y el tipo de la libreria

int fotorresistor_value = 0; //Se declara el valor de la fotoresistencia
int agua_pin = 3; //Se declara el pin de la valvula de agua
int agua_speed = 255; //Se declara la velocidad en la que trabaja la valvula de agua

int valorLDR = 0; //Se declara el valor de la fotorresistencia
void setup() {
  pinMode(A0, INPUT); //Se declara que el pin A0 es de entrada donde se conecta el sensor de humedad
  pinMode(4, OUTPUT); //Se captura la salida digital de la fotoresistencia 
  pinMode(agua_pin, OUTPUT); //Salida de la bomba de agua por el pin 3
  dht.begin(); //Se inicializa el DHT
  Serial.begin(9600); //Monitor seriall
}

void loop() {
  Fotorresistor(); //inicializa el metodo de la fotoresistencia
  Sensor_humedad(); //inicializa el metodo del sensor de la humedad
}



void Fotorresistor() {
  valorLDR = analogRead(A5); //Captura los datos que llegan de la entrada analoga
  int fotorresistor_value = map(analogRead(valorLDR), 1023, 0, 100, 0); //Con esto se mapea para que de un valor 
                                                                        //exacto entre 0 y 100 de la fotoresistencia 
  if ( valorLDR <= 100 )//Valida la data de la fotoresistencia
  {
    digitalWrite(4, HIGH);
    Serial.print("Nivel Luz Alto: "); //Entre mas capacidad de luz imprime
    Serial.println(fotorresistor_value);
    delay(2000);
  }

  else
  {
    digitalWrite(4, LOW);
    Serial.println("Nivel De luz Bajo: ");//Entre menor capacidad de luz imprime
    Serial.println(fotorresistor_value);
    delay(2000);
  }
}

void Sensor_humedad() {
  float h = dht.readHumidity(); //leemos la humedad relativa
  float t = dht.readTemperature(); //Leemos la temperatura(°C) //Con TRUE se toma la temperatura en F°

  
  int valor_humedad_tierra = map(analogRead(sensor_humedad_pin),1023, 0, 100, 0); //Mapea los rangos del sensor de humedad de la tierra
  
  Serial.print("Humedad :"); //Imprime valor humedad
  Serial.println(h);
  Serial.println(" %\t");

  Serial.print("Temperaruta: ");
  Serial.println(t);
  Serial.println("°C");

  Serial.print("Humedad Suelo: ");
  Serial.println(valor_humedad_tierra);
  Serial.println("%");

  if (valor_humedad_tierra <= 50) { //Se hace la validacion para encender el actuador de la bomba de agua
    digitalWrite(agua_pin, HIGH);
  } else {
    digitalWrite(agua_pin, LOW);
  }
  delay(2000);
}
