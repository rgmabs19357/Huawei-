

struct bq_bci_platform_data {
    int *battery_tmp_tbl;
    unsigned int tblsize;

    unsigned int monitoring_interval;

    unsigned int max_charger_currentmA;
    unsigned int max_charger_voltagemV;
    unsigned int termination_currentmA;

   unsigned int max_bat_voltagemV;
   unsigned int low_bat_voltagemV;
};


