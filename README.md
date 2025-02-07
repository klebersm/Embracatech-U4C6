# Embracatech-U4C6

Este projeto tem o objetivo de exploras interfaces de comunicação do RP2040. Neste exemplo são utilizadas as comunicações serial (para comunicação com um computador via USB) e i2c para comunicação com um display OLED 128 x 64 pixels preto e branco.

Ao interagir com a placa BitgogLab, o usuário pode usar os botões A e B para alternar o status dos leds Verde e Azul respectivamente. Durante o uso, o status atualizado dos leds é exibido tanto no display oled quanto na interface serial. Além disso, o usuário pode, via serial, digitar caracteres maiúsculos ou minúsculos, que também serão exibidos no display e na interface serial. Caso o usuário insira um valor numérico de 0 a 9, este valor será exibido também na matriz de leds WS2812

## Funcionalidades das Teclas 🕹️

| Tecla | Funcionalidade                |
| ----- | ----------------------------- |
| A     | Inverte o status do led verde |
| B     | Inverte o status do led azul  |

## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico).
- Botões tipo Switch.
- Display NeoPixel RGB 5x5.
- Display i2c 128 x 64 pixels
- Comunicação Serial via USB

## Software 💻

- **SDK do Raspberry Pi Pico:** O SDK (Software Development Kit) do Pico, que inclui as bibliotecas e ferramentas necessárias para desenvolver e compilar o código. [Instruções de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
- **CMake:** Um sistema de construção multiplataforma usado para gerar os arquivos de construção do projeto.
- **Compilador C/C++:** Um compilador C/C++ como o GCC (GNU Compiler Collection).
- **Git:** (Opcional) Para clonar o repositório do projeto.

### O código está dividido em vários arquivos para melhor organização:

- **`U4T6.C`**: Código com a função de loop principal: lê a porta serial e os botões e aciona os leds e o display.
- **`display/ssd1306.c/.h`**: Comunica com o display via i2c.
- **`neopixel/neopixel.c/.h`:** Controla o display NeoPixel (inicialização e envio de cores).
- **`CMakeLists.txt`:** Define a estrutura do projeto para o CMake.
- **`diagram.json`:** Diagramas de conexões.
  |

## Como Compilar e Executar ⚙️

1. **Instale o SDK do Raspberry Pi Pico:** Siga as instruções no site oficial do Raspberry Pi.
2. **Clone este repositório:** `git clone git@github.com:klebersm/embarcatech-U4C6.git`
3. **Navegue até o diretório do projeto:** `cd Embarcatech-U4C6`
4. **Compile o projeto:** `cmake -B build && cmake --build build`
5. **Copie para o Pico:** Copie o arquivo `U4C6.uf2` da pasta `build` (gerada após a compilação) para o Raspberry Pi Pico. O programa iniciará automaticamente.

## Tratamento dos botões - Interrupções e Alarmes ⏱️

Os botões A e B foram inicializados como entradas em PULL UP e são monitorados por interrupções com uma função para o tratamento dessas interrupções. À medida que ocorre uma interrupção, a função de tratamento verifica qual o botão gerou o evento e qual o tipo de evento. Se o evento foi de FALL EDGE (borda de descida), significa que o botão foi pressionado e um alarme é gerado para ser disparado em 100ms (Tempo configurado para debounce). Se qualquer outro evento acontecer no mesmo botão, esse alarme é cancelado. Sendo assim, o alarme só é realmente disparado se o botão for pressionado e ficar 100ms sem sofrer qualquer alteração.

## 🔗 Link do Vídeo de Funcionamento:

https://drive.google.com/file/d/1118dtAJuiiKRs1i7EShtLsdd9D56enlQ/view?usp=drive_link

## 📞 Contato

- 👤 **Autor**: Kleber Marçal

- 📧 **E-mail**:kleber.sm@gmail.com

---
