# Atividade 2: Temporizador de um Disparo (One Shot)

## Descrição
Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando o microcontrolador **Raspberry Pi Pico W** e a função `add_alarm_in_ms()` do SDK Pico. O acionamento dos LEDs ocorre a partir do clique em um **botão (pushbutton)**, seguindo uma sequência de desligamento controlada por temporizadores.

---
## Requisitos

### Hardware
- **Microcontrolador**: Raspberry Pi Pico W.
- **LEDs**:
  - 1 LED vermelho.
  - 1 LED azul.
  - 1 LED verde.
- **Resistores**: 3 resistores de 330Ω.
- **Botão (Pushbutton)**.
- **Simulador**: [Wokwi](https://wokwi.com/)

### Software
- **Ambiente de Desenvolvimento**: VS Code com extensões para Pico SDK.
- **Ferramentas**:
  - Kit de Desenvolvimento de Software (SDK) do Raspberry Pi Pico.

---

## Configuração do Projeto

### 1. Clone o Repositório
Clone este repositório em sua máquina local:

```bash
git clone https://github.com/lipesilvapr/Atv-Disparo.git
```

### 2. Compile o Projeto pela extensão instalada no VS Code

Isso gerará o arquivo binário `temporizador.uf2`.

---

## Simulação no Wokwi

Se você estiver usando o simulador Wokwi:
1. Abra o diagrama JSON fornecido no Wokwi.
2. Carregue o código `disparo.c` no simulador.
---

## Funcionalidades

### 1. Temporização do Acionamento dos LEDs
- Ao pressionar o botão, **todos os LEDs acendem**.
- Após **3 segundos**, o **LED verde apaga**.
- Após mais **3 segundos**, o **LED vermelho apaga**.
- Após mais **3 segundos**, o **LED azul apaga** e o sistema estará pronto para nova ativação.
- Durante esse processo, o botão não pode ser pressionado novamente.

---

## Estrutura do Código

### Arquivos Principais
- `disparo.c`: Código-fonte principal com a lógica do temporizador de um disparo.
- `CMakeLists.txt`: Configuração do projeto para compilação com o SDK Pico.

### Funções Importantes
- `botao_callback()`: Função de callback chamada quando o botão é pressionado.
- `desligar_verde()`, `desligar_vermelho()`, `desligar_azul()`: Funções que controlam o desligamento progressivo dos LEDs.
- `main()`: Rotina principal que inicializa os LEDs e imprime mensagens na porta serial.

