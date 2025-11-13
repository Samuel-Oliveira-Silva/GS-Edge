# 🧠 Monitor Inteligente de Postura e Ambiente – IoT com ESP32 e MQTT  

---

## 📘 Descrição Geral  

O projeto **Monitor Inteligente de Postura e Ambiente** foi desenvolvido para **promover saúde, conforto e eficiência no ambiente de trabalho**.  
Com o avanço do trabalho remoto, surgem desafios como **má postura, sedentarismo e desconforto térmico**.  

Este sistema IoT, baseado em **ESP32 e protocolo MQTT**, monitora a postura do usuário, o tempo sentado e o ambiente, enviando alertas em tempo real para **melhorar hábitos e prevenir problemas físicos**.  

---

## 🚨 Problema Identificado  

Com o aumento do uso de computadores e home offices, milhões de pessoas passam horas sentadas, muitas vezes sem pausas, em más condições ergonômicas.  
Esses fatores resultam em:
- Dores lombares e problemas posturais;
- Cansaço visual;
- Diminuição da produtividade;
- Sedentarismo e falta de pausas regulares.

---

## 💡 Solução Desenvolvida  

A solução proposta utiliza sensores conectados ao **ESP32** para detectar:
- 🪑 Tempo sentado (botão de presença na cadeira);
- 📏 Postura incorreta (sensor MPU6050);
- 👀 Distância da tela (sensor ultrassônico HC-SR04);
- 🌡️ Temperatura e umidade (sensor DHT22).  

Os dados são enviados via **protocolo MQTT** ao broker `broker.emqx.io`, permitindo integração com dashboards e sistemas de automação.

---

## 🛠️ Componentes Utilizados  

| Componente | Função | Pino |
|-------------|--------|------|
| ESP32 | Microcontrolador principal | — |
| DHT22 | Temperatura e umidade | GPIO 4 |
| MPU6050 | Postura corporal (aceleração e ângulo) | I2C |
| HC-SR04 | Distância do usuário até a tela | TRIG: 5 / ECHO: 18 |
| Botão | Detecta ocupação da cadeira | GPIO 33 |
| LED | Alerta visual | GPIO 2 |

<img width="1278" height="690" alt="Captura de tela 2025-11-13 155538" src="https://github.com/user-attachments/assets/dee7d348-b3ca-4a35-8b88-3e65b030a0fa" />

yaml
Copiar código

---

## 🌐 Conectividade MQTT  

| Parâmetro | Valor |
|------------|--------|
| **Broker** | `broker.emqx.io` |
| **Porta (TCP)** | `1883` |
| **Porta (WebSocket)** | `8084` |
| **Protocolo** | MQTT |
| **Tópicos Principais** | `office/dados`, `office/alerta`, `office/ar` |

**Exemplo de Payload JSON publicado:**  
json
  {
    "temp": 26.4,
    "umidade": 52,
    "distancia": 55.7,
    "angulo": 8.4,
    "ocupado": 1,
    "pomodoro": 28
  }

## 🧠 Funcionamento
O ESP32 coleta os dados dos sensores;

Verifica postura, tempo sentado, distância da tela e temperatura;

Envia os dados via MQTT para o broker broker.emqx.io;

Dispara alertas visuais (LED) e mensagens em tópicos MQTT específicos;

Os dados podem ser monitorados em tempo real em painéis como o EMQX Web Client.

📊 <img width="1179" height="2556" alt="IMG_0724" src="https://github.com/user-attachments/assets/1ebe8f82-9795-48a2-bd8c-e96cc654f866" />


scss
Copiar código
⚙️ Instruções de Uso
🧩 Simulador Wokwi
Acesse o projeto completo:
👉 [Monitor de Postura no Wokwi](https://wokwi.com/projects/447533375028775937)

Abra o link acima.

Execute a simulação.

No console do Wokwi, observe as leituras de sensores e alertas.

## 🌐 Teste MQTT via Web
Acesse o cliente online:
👉 EMQX Online MQTT Client

Configuração:

Host: broker.emqx.io

Port: 8084

Subscribe to topic:

bash
Copiar código
office/#
Observe as mensagens chegando em tempo real 🚀

📸 [Espaço reservado para print do MQTT Web Client]

scss
Copiar código
<img width="1910" height="916" alt="Captura de tela 2025-11-13 155510" src="https://github.com/user-attachments/assets/62bd6d1a-a3b6-4261-8980-6087e3ccd19c" />

📈 Resultados Esperados
✅ Redução de problemas posturais e fadiga visual
✅ Incentivo a pausas e alongamentos regulares
✅ Melhoria no bem-estar e produtividade
✅ Aplicação prática em home offices e empresas

🔮 Possibilidades Futuras
🌐 Dashboard web com gráficos em tempo real
📱 Integração com aplicativos móveis e assistentes de voz
🏠 Automação de dispositivos inteligentes (ex: ligar o ar-condicionado via MQTT)
🏫 Expansão para ambientes corporativos e educacionais

📸 [Espaço reservado para print do dashboard futuro]

scss
Copiar código
![Dashboard Web](./imagens/dashboard_futuro.png)
## 👥 Autores
Nome	RM
João Lucas	562608
Samuel de Oliveira	566244
Rafael Felix	565855

## 🧾 Licença
Este projeto foi desenvolvido para a disciplina Edge Computing & IoT, dentro do contexto da
Global Solution FIAP 2025.2 – O Futuro do Trabalho.
