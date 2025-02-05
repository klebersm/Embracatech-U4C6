#include <stdio.h>
#include "pico/stdlib.h"

#include "U4C6.h"

static alarm_id_t btn_a_alm;
static alarm_id_t btn_b_alm;

void init_gpio() {
    uint ledMask = (0x01 << LED_R) | (0x01 << LED_G) | (0x01 << LED_B);
    gpio_init_mask(ledMask);
    gpio_set_dir_out_masked(ledMask);

    uint btnMask = (0x01 << BUTTON_A) | (0x01 << BUTTON_B);
    gpio_init_mask(btnMask);
    gpio_set_dir_in_masked(btnMask);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
}

uint64_t handle_btn_a(alarm_id_t id, void *user_data) {
    gpio_put(LED_G, !gpio_get(LED_G));
}

uint64_t handle_btn_b(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, !gpio_get(LED_B));
}

static void debounce(uint gpio, uint32_t events) {
    if(gpio == BUTTON_A) {
        cancel_alarm(btn_a_alm);
        if(events == 0x04) btn_a_alm = add_alarm_in_ms(DEBOUNCE_MS, handle_btn_a, NULL, false);
    }
    else if(gpio == BUTTON_B){
        cancel_alarm(btn_b_alm);
        if(events == 0x04) btn_b_alm = add_alarm_in_ms(DEBOUNCE_MS, handle_btn_b, NULL, false);
    }
}

int main()
{
    stdio_init_all();
    
    init_gpio();

    i2c_init(I2C_PORT, SSD1306_FREQ);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, SSD1306_ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    ssd1306_draw_string(&ssd, "CONECTE UART", 8, 10); // Desenha uma string
    ssd1306_send_data(&ssd);

    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("UART conectada com sucesso.\n");

    while (true) {
        ssd1306_rect(&ssd, 3, 3, 122, 58, true, false); // Desenha um retângulo
        ssd1306_send_data(&ssd); // Atualiza o display
        char c;
        if (scanf("%c", &c) == 1) {

        }
    }
}
