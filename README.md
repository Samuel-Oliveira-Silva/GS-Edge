# 🧠 Monitor Inteligente de Postura e Ambiente – IoT com ESP32 e MQTT

## 📌 Descrição Geral
O projeto **Monitor Inteligente de Postura e Ambiente** busca promover **saúde e bem-estar no ambiente de trabalho**, utilizando **Internet das Coisas (IoT)** e **automação inteligente**.

Com o aumento do trabalho remoto, a má postura, a fadiga ocular e o sedentarismo se tornaram problemas comuns.  
A proposta deste sistema é **monitorar em tempo real** a postura, o tempo sentado e as condições do ambiente, emitindo **alertas automáticos** para incentivar pausas e corrigir comportamentos prejudiciais.

---

## 🧩 Problema Identificado
O cenário atual do trabalho digital trouxe novos desafios à saúde e produtividade:

- Permanência excessiva sentado;
- Postura inadequada e dores musculares;
- Exposição prolongada à tela;
- Ambientes com temperatura desconfortável.

Esses fatores prejudicam a qualidade de vida e o desempenho profissional.  
O projeto se propõe a mitigar esses efeitos através de **monitoramento inteligente e feedback imediato**.

---

## 💡 Solução Desenvolvida
O **Monitor Inteligente de Postura e Ambiente** é um sistema IoT baseado em **ESP32**, que integra sensores físicos e comunicação via **protocolo MQTT**.

### Principais Funcionalidades:
- Detecção do **tempo de permanência sentado** (alerta Pomodoro);
- Identificação de **postura incorreta** através do sensor MPU6050;
- Cálculo da **distância entre o usuário e a tela**;
- Medição da **temperatura e umidade** (sensor DHT22);
- Emissão de **alertas visuais (LED)** e notificações via MQTT;
- Envio de dados contínuos para o broker em formato **JSON**.

---

## 🛠️ Componentes Utilizados
| Componente | Função | Pino |
|-------------|--------|------|
| ESP32 | Microcontrolador principal | - |
| DHT22 | Sensor de temperatura e umidade | GPIO 4 |
| MPU6050 | Sensor de movimento/postura | I2C |
| HC-SR04 | Sensor ultrassônico (distância) | TRIG: 5 / ECHO: 18 |
| Botão (Chair Sensor) | Detecta presença na cadeira | GPIO 33 |
| LED | Alerta visual | GPIO 2 |

---

## 🌐 Conectividade e Comunicação MQTT

**Broker MQTT:** `test.mosquitto.org`  
**Porta:** `1883`

### 📡 Tópicos Utilizados
| Tópico | Função |
|--------|--------|
| `office/led` | Recebe comandos externos para o LED |
| `office/alerta` | Publica mensagens de alerta (postura, tempo, distância) |
| `office/ar` | Envia alertas de temperatura ambiente |
| `office/dados` | Publica todos os dados em JSON |

**Exemplo de Payload JSON:**
```json
{
  "temp": 26.4,
  "umidade": 52,
  "distancia": 55.7,
  "angulo": 8.4,
  "ocupado": 1,
  "pomodoro": 28
}



⚙️ Instruções de Uso
Acesse o projeto no Wokwi:
👉 https://wokwi.com/projects/447533375028775937

Execute o código no ESP32 (ou simulador Wokwi).

No Serial Monitor (115200 baud), acompanhe as leituras e alertas.

Acesse um cliente MQTT, como:

HiveMQ Web Client

MQTT Explorer

Conecte-se ao broker e assine os tópicos:

bash
Copiar código
office/dados
office/alerta
office/ar
Observe os alertas e as medições em tempo real.
<img width="1278" height="690" alt="Captura de tela 2025-11-13 155538" src="https://github.com/user-attachments/assets/a8d7660e-c096-45d7-b685-a08104b16aa4" />
<img width="1910" height="916" alt="Captura de tela 2025-11-13 155510" src="https://github.com/user-attachments/assets/0bcaab9e-b941-4cc5-92cd-e6a8ab4787b2" />


📈 Resultados Esperados
Redução de problemas posturais e fadiga visual;

Incentivo a pausas e alongamentos regulares;

Melhoria do bem-estar e produtividade;

Aplicação prática em home offices e empresas.

🔮 Possibilidades Futuras
Dashboard web com gráficos em tempo real;

Integração com apps móveis e assistentes de voz;

Automação de dispositivos inteligentes (ex: ligar o ar-condicionado via MQTT);

Expansão para ambientes corporativos e educacionais.

👥 Autores
Nome	RM
João Lucas	562608
Samuel de Oliveira	566244
Rafael Felix	565855

📜 Licença
Este projeto foi desenvolvido para a disciplina Edge Computing & IoT no contexto da Global Solution FIAP 2025.2 – O Futuro do Trabalho.
