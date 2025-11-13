# 🧠 Monitor Inteligente de Postura e Ambiente – IoT com ESP32 e MQTT

## 📌 Descrição Geral
O projeto **Monitor Inteligente de Postura e Ambiente** tem como objetivo **promover saúde e bem-estar no ambiente de trabalho** por meio do uso da **Internet das Coisas (IoT)**.

Com o aumento do trabalho remoto e do tempo em frente às telas, surgem problemas como má postura, cansaço visual e sedentarismo.  
A proposta é desenvolver um **sistema que monitora em tempo real a postura, o tempo sentado e as condições do ambiente**, emitindo alertas automáticos quando algo foge dos padrões saudáveis.

O sistema utiliza um **ESP32**, sensores físicos e comunicação via **MQTT** com um broker público.

---

## 🧩 Problema Identificado
Com o avanço da automação e das rotinas digitais, profissionais passam horas em frente ao computador, resultando em:
- Postura incorreta;
- Longos períodos sentados;
- Exposição excessiva à tela;
- Ambientes desconfortáveis.

Esses fatores reduzem produtividade e impactam a saúde física e mental.

---

## 💡 Solução Desenvolvida
O **Monitor Inteligente de Postura e Ambiente**:
- Detecta **tempo sentado** e envia alertas de pausa (Pomodoro automatizado);
- Mede **ângulo da postura** para corrigir más posições;
- Verifica **distância da tela** para evitar fadiga ocular;
- Monitora **temperatura e umidade** para conforto térmico;
- Envia tudo via **MQTT**, integrando-se a dashboards e automações.

---

## 🛠️ Componentes Utilizados
| Componente | Função | Pino |
|-------------|--------|------|
| ESP32 | Microcontrolador principal | - |
| DHT22 | Temperatura e umidade | GPIO 4 |
| MPU6050 | Sensor de aceleração (postura) | I2C |
| HC-SR04 | Distância da tela | TRIG: 5 / ECHO: 18 |
| Botão | Detecta presença na cadeira | GPIO 33 |
| LED | Alerta visual | GPIO 2 |

---

## 🌐 Comunicação MQTT
**Broker:** `test.mosquitto.org`  
**Porta:** `1883`

| Tópico | Função |
|--------|--------|
| `office/led` | Recebe comandos para LED |
| `office/alerta` | Envia mensagens de alerta (postura, pausa, distância) |
| `office/ar` | Publica alertas sobre temperatura ambiente |
| `office/dados` | Publica dados gerais em JSON |

**Exemplo de payload JSON:**
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
Acesse o simulador Wokwi:
👉 [Link do Projeto no Wokwi](https://wokwi.com/projects/447398308648781825)

Execute o código no ESP32.

Abra o Monitor Serial (115200) para visualizar leituras.

Acompanhe mensagens MQTT em HiveMQ Web Client:

Broker: test.mosquitto.org

Porta: 8000

Tópicos:

bash
Copiar código
office/dados
office/alerta
office/ar
📈 Resultados Esperados
Redução de problemas posturais e fadiga ocular.

Incentivo a pausas regulares.

Aumento da produtividade e conforto.

Aplicação em home offices, empresas e escolas.

🔮 Futuras Implementações
Dashboard web em tempo real.

Aplicativo móvel com notificações.

Controle automático de dispositivos inteligentes via MQTT.

👥 Autores
Nome	RM
João Lucas	562608
Samuel de Oliveira	566244
Rafael Felix	565855

🧾 Licença
Projeto desenvolvido para a Global Solution – FIAP 2025.2, tema “O Futuro do Trabalho”.
