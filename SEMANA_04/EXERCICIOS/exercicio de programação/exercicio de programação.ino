#define Led1 4
#define Led2 5
#define Led3 6
#define Led4 7
#define LDR 3
#define buzz 10
#define button 15
#define button2 16
const int leds[4] = {Led1, Led2, Led3, Led4};
int vetor[100] = {};
int cont = 0;
int convertAmostra(int valor, int valmax, int valmin ) {
  float convertido = (valor - valmin) / ((valmax - valmin) / 15);
  Serial.println(convertido);
  return convertido ;
}
int binario(int decimal) {
  int bin = 0;    //função que transforma em binário os valores decimais ajustados na função converte() e retorna esses binários;
  int remainder;
  int product = 1;

  while (decimal != 0) {
    remainder = decimal % 2;
    bin = bin + (remainder * product);
    decimal = decimal / 2;
    product *= 10;
  }
  return bin;
}
void splita(int valor, int* b) {
  b[0] = valor % 10;
  b[1] = valor / 10 % 10;
  b[2] = valor / 100 % 10;
  b[3] = valor / 1000 % 10;
}
void ascenderLed(int* vetor) {
  for (int i = 0; i < 4; i++) {
    if (vetor[i] == 1) {
      digitalWrite(leds[i], HIGH);
      Serial.println("Entrou");
    }
  }
}
void tocarBuzz(int valor) {
  tone(buzz, 200 * valor, 500);
}

void apagarLed(void) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}
int size = (sizeof(vetor)) / (sizeof(int));
void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {

  int valButton = digitalRead(button);
  int valButton2 = digitalRead(button2);
  if (valButton == 0) {
    Serial.println("Pressionado");
    int b[4];
    int valLdr = analogRead(LDR);
    int valor = convertAmostra(valLdr, 8190, 64);
    int valorB = binario(valor);
    splita(valorB,b);
    ascenderLed(b);
    Serial.println(b[0]);
    Serial.println(b[1]);
    Serial.println(b[2]);
    Serial.println(b[3]);
    tocarBuzz(valor);
    delay(1000);
    apagarLed();
    vetor[cont] = valLdr;
    cont += 1;
  }
  if (valButton2 == 0) {
    for (int i = 0; vetor[i] != 0; i++) {
      Serial.println("Pressionado");
      Serial.print("Posiçao: ");
      Serial.print(i);
      int b[4];
      int valLdr = vetor[i];
      int valor = convertAmostra(valLdr, 8190, 64);
      int valorB = binario(valor); 
      splita(valorB,b);
      ascenderLed(b);
      tocarBuzz(valor);
      delay(1000);
      apagarLed();
    }
    for (int i = 0; i < size; i++) {
      vetor[i] = 0;
      cont = 0;

    }
  }
}