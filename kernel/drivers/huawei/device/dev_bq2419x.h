
#define I2C_ADDR_BQ24192                       (0x6B)

struct bq2419x_platform_data {
    int max_charger_currentmA;
    int max_charger_voltagemV;
    int termination_currentmA;
    int max_cin_limit_currentmA;
    int gpio_cd;
    int gpio_otg;
    int gpio_int;
};
