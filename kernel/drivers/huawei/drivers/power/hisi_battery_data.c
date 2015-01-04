#include <linux/string.h>
#include "hisi_battery_data.h"
#include "auto-generate/hisi_battery_data_array.c"


#define BAT_DATA_ARRY_ALL_SIZE sizeof(bat_data_array_all)/sizeof(bat_data_array_all[0])


static struct hisi_smartstar_product_index_map product_index_map[] = {
    {"EDGE_PLUS", SS_PRODUCT_INDEX_0},
    {"OSCAR", SS_PRODUCT_INDEX_1},
    {"SOPHIA", SS_PRODUCT_INDEX_2},
};


static int str2index(char *product_name)
{
    int i = 0;
    int index = SS_PRODUCT_INDEX_0;
    int array_size = sizeof(product_index_map)/sizeof(product_index_map[0]);

    for (i = 0; i < array_size; i++) {
		if (!strncmp(product_name, product_index_map[i].product_name, strlen(product_index_map[i].product_name))) {
            break;
        }
    }

    if (i < array_size) {
        index = product_index_map[i].index;
    }

    return index;
}


struct hisi_smartstar_coul_battery_data *get_battery_data(unsigned int id_voltage, char *product_name)
{
    int i = 0;
    int index = 0;
    p_bat_data_array pa = 0;

    /* check input */
    if (0 == product_name) {
        return 0;
    }

    /* get index of all_array */
    index = str2index(product_name);
    if ( index < SS_PRODUCT_INDEX_0 || index >= BAT_DATA_ARRY_ALL_SIZE) {
        return 0;
    }
    pa = bat_data_array_all[index];

    /* try to find battery data according to voltage */
    for (i = 1; (*pa)[i] != 0; i++) {
        if ((id_voltage >= (*pa)[i]->id_voltage_min)
            && (id_voltage <= (*pa)[i]->id_voltage_max)) {
            break;
        }
    }

    /* if not found, return default data */
    if (0 == (*pa)[i]) {
        return (*pa)[0];
    }
    else {
        return (*pa)[i];
    }
}


