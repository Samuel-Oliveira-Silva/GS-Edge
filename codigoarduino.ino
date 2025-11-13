/*
  =====================================================
  🧠 MONITOR INTELIGENTE DE POSTURA E AMBIENTE (IoT)
  -----------------------------------------------------
  Projeto da Global Solution - FIAP 2025.2
  Tema: O Futuro do Trabalho
  Autores:
    - João Lucas (RM: 562608)
    - Samuel de Oliveira (RM: 566244)
    - Rafael Felix (RM: 565855)

  Descrição:
  Este código implementa um sistema IoT para monitorar
  postura, tempo sentado, distância da tela e temperatura
  ambiente, utilizando o ESP32, sensores e comunicação MQTT.
  =====================================================
*/

// ---------------- BIBLIOTECAS ----------------
#include <WiFi.h>            // Conexão Wi-Fi
#include <PubSubClient.h>    // Comunicação MQTT
#include "DHT.h"             // Sensor de temperatura/umidade
#include <Wire.h>            // Comunicação I2C
#include <MPU6050.h>         // Sensor de movimento/postura

// ---------------- DEFINIÇÃO DE PINOS ----------------
#define DHTPIN 4             // Pino do sensor DHT22
#define DHTTYPE DHT22        // Tipo do sensor DHT
#define LEDPIN 2             // LED de alerta
#define BUTTON_PIN 33        // Botão para detectar ocupação da cadeira
#define TRIG_PIN 5           // Pino TRIG do sensor ultrassônico
#define ECHO_PIN 18          // Pino ECHO do sensor ultrassônico

// ---------------- OBJETOS ----------------
DHT dht(DHTPIN, DHTTYPE);    // Instância do sensor DHT22
MPU6050 mpu;                 // Instância do sensor de movimento
WiFiClient espClient;        // Cliente WiFi
PubSubClient client(espClient); // Cliente MQTT

// ---------------- REDE E MQTT ----------------
const char* ssid = "Wokwi-GUEST";             // Nome da rede Wi-Fi (no simulador)
const char* password = "";                    // Senha da rede Wi-Fi
const char* mqtt_server = "broker.emqx.io";   // Servidor MQTT público

// ---------------- VARIÁVEIS GLOBAIS ----------------
unsigned long lastMsg = 0;    // Controle do tempo de envio das mensagens
unsigned long chairStart = 0; // Tempo de início na cadeira
float temp, hum;              // Leituras de temperatura e umidade
bool chairOccupied = false;   // Estado da cadeira
bool pomodoroRunning = false; // Controle do temporizador (Pomodoro)
int pomodoroTime = 0;         // Tempo acumulado sentado
bool alertaAtivo = false;     // Controle do LED de alerta

// ======================================================
// 🧩 FUNÇÕES AUXILIARES
// ======================================================

// ---- Conecta ao Wi-Fi ----
void setup_wifi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ---- Conecta ao servidor MQTT ----
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("esp32-office-monitor")) {
      Serial.println(" ✅ Conectado!");
      client.subscribe("office/led");  // Assina o tópico para controle do LED
    } else {
      Serial.print(" Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando em 5s...");
      delay(5000);
    }
  }
}

// ---- Callback para mensagens MQTT recebidas ----
void callback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)message[i];
  if (msg == "1") digitalWrite(LEDPIN, HIGH);
  else digitalWrite(LEDPIN, LOW);
}

// ---- Mede a distância do sensor ultrassônico ----
float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  float duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Conversão para centímetros
}

// ---- Calcula o ângulo de inclinação (postura) ----
float lerAngulo() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  return atan2(ay, az) * 57.3; // Retorna o ângulo em graus
}

// ---- Função para emitir alertas ----
void dispararAlerta(String mensagem, const char* topico) {
  alertaAtivo = true;
  digitalWrite(LEDPIN, HIGH);  // Acende o LED
  client.publish(topico, mensagem.c_str()); // Envia o alerta via MQTT
  Serial.println(mensagem);
}

// ======================================================
// ⚙️ CONFIGURAÇÃO INICIAL (SETUP)
// ======================================================
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Wire.begin();   // Inicializa o barramento I2C
  mpu.initialize();
  dht.begin();

  setup_wifi();   // Conecta ao Wi-Fi
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println("🪑 Sistema de Monitoramento de Postura Iniciado!");
}

// ======================================================
// 🔄 LOOP PRINCIPAL
// ======================================================
void loop() {
  if (!client.connected()) reconnect(); // Reestabelece conexão MQTT
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg >= 5000) { // Leitura e envio a cada 5 segundos
    lastMsg = now;
    alertaAtivo = false; // Reseta o LED

    // ---- Leitura dos sensores ----
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    float distance = medirDistancia();
    float angle = lerAngulo();
    bool chair = (digitalRead(BUTTON_PIN) == LOW);

    // ---- Verifica se a cadeira está ocupada ----
    if (chair) {
      if (!pomodoroRunning) {
        pomodoroRunning = true;
        chairStart = now;
      }

      chairOccupied = true;
      pomodoroTime = (now - chairStart) / 1000; // Tempo em segundos

      // Simulação: alerta a cada 30s (equivalente a 25min reais)
      if (pomodoroTime >= 30) {
        dispararAlerta("🚨 Levante-se, alongue e beba água!", "office/alerta");
        pomodoroRunning = false;
      }
    } else {
      chairOccupied = false;
      pomodoroRunning = false;
      pomodoroTime = 0;
    }

    // ---- Verifica postura ----
    if (abs(angle) > 20) {
      dispararAlerta("⚠️ Postura incorreta detectada!", "office/alerta");
    }

    // ---- Verifica distância da tela ----
    if (distance < 40) {
      dispararAlerta("👀 Muito perto da tela!", "office/alerta");
    } else if (distance > 80) {
      dispararAlerta("👀 Muito longe da tela!", "office/alerta");
    }

    // ---- Verifica temperatura ambiente ----
    if (temp > 28) {
      dispararAlerta("🌡️ Ambiente quente: ativando resfriamento!", "office/ar");
    } else if (temp < 20) {
      dispararAlerta("❄️ Ambiente frio: ativando aquecimento!", "office/ar");
    }

    // ---- Desliga o LED se não houver alerta ativo ----
    if (!alertaAtivo) digitalWrite(LEDPIN, LOW);

    // ---- Envia dados gerais via MQTT ----
    String payload = "{\"temp\":" + String(temp) +
                     ",\"umidade\":" + String(hum) +
                     ",\"distancia\":" + String(distance) +
                     ",\"angulo\":" + String(angle) +
                     ",\"ocupado\":" + String(chairOccupied ? "1" : "0") +
                     ",\"pomodoro\":" + String(pomodoroTime) + "}";
    client.publish("office/dados", payload.c_str());
    Serial.println(payload);
  }
}
