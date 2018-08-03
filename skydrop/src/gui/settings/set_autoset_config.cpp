#include "set_autoset_config.h"

#include "../pages.h"
#include "../gui_list.h"
#include "../gui_value.h"
#include "../../fc/fc.h"




void gui_set_autoset_config_init()
{
    gui_list_set(gui_set_autoset_config_item, gui_set_autoset_config_action, 3, GUI_SET_AUTOSET);
}

void gui_set_autoset_config_stop() {}

void gui_set_autoset_config_loop()
{
    gui_list_draw();
}

void gui_set_autoset_config_irqh(uint8_t type, uint8_t * buff)
{
    gui_list_irqh(type, buff);
}


void gui_set_autoset_config_circling_avg_cb(float val)
{
    gui_switch_task(GUI_SET_AUTOSET_CONFIG);

    config.gui.page_circling_average = sec_to_mul(val);
    eeprom_busy_wait();
    eeprom_update_float(&config_ee.gui.page_circling_average, config.gui.page_circling_average);
}

void gui_set_autoset_config_circling_thold_cb(float val)
{
    gui_switch_task(GUI_SET_AUTOSET_CONFIG);

    config.gui.page_cirlcing_thold = val;
    eeprom_busy_wait();
    eeprom_update_byte(&config_ee.gui.page_cirlcing_thold, config.gui.page_cirlcing_thold);
}

void gui_set_autoset_config_acro_thold_cb(float val)
{
    gui_switch_task(GUI_SET_AUTOSET_CONFIG);

    config.gui.page_acro_thold = val * 10.0;
    eeprom_busy_wait();
    eeprom_update_block((void *)&config_ee.gui.page_acro_thold, (void *)config.gui.page_acro_thold, sizeof(int8_t));
}

void gui_set_autoset_config_action(uint8_t index)
{
    switch (index)
    {
        case (0):
            gui_value_conf_P(PSTR("Circling avg."), GUI_VAL_NUMBER, PSTR("%0.0f sec"), mul_to_sec(config.gui.page_circling_average), 5, 60, 1, gui_set_autoset_config_circling_avg_cb);
            gui_switch_task(GUI_SET_VAL);
        break;

        case (1):
            gui_value_conf_P(PSTR("Circling thold."), GUI_VAL_NUMBER, PSTR("%0.0f deg/s"), config.gui.page_cirlcing_thold, 5, 60, 1, gui_set_autoset_config_circling_thold_cb);
            gui_switch_task(GUI_SET_VAL);
        break;

        case (2):
            gui_value_conf_P(PSTR("Acro thold."), GUI_VAL_NUMBER, PSTR("%0.1f m/s"), config.gui.page_acro_thold / 10.0, 10, -10, 0.5, gui_set_autoset_config_acro_thold_cb);
            gui_switch_task(GUI_SET_VAL);
        break;

    }
}

void gui_set_autoset_config_item(uint8_t index, char * text, uint8_t * flags, char * sub_text)
{
    switch (index)
    {
        case (0):
            strcpy_P(text, PSTR("Circling avg."));
            sprintf_P(sub_text, PSTR("%d s"), mul_to_sec(config.gui.page_circling_average));
            *flags |= GUI_LIST_SUB_TEXT;
        break;

        case (1):
            strcpy_P(text, PSTR("Circling thold."));
            sprintf_P(sub_text, PSTR("%d deg/s"), config.gui.page_cirlcing_thold);
            *flags |= GUI_LIST_SUB_TEXT;
        break;

        case (2):
            strcpy_P(text, PSTR("Acro thold."));
            sprintf_P(sub_text, PSTR("%0.1f m/s"), config.gui.page_acro_thold / 10.0);
            *flags |= GUI_LIST_SUB_TEXT;
        break;
    }
}
