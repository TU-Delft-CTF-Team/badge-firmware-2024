#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "black_box.hpp"
#include "morse_flag.hpp"
#include "morse.pio.h"


namespace BlackBox {

    static const uint32_t* control_chan_data = morse_flag;
    static int data_chan = 0;

    void init() {
        uint offset;
        uint sm = 0;

        offset = pio_add_program(pio0, &morse_program);
        morse_program_init(pio0, sm, offset, PICO_DEFAULT_LED_PIN);
        pio_sm_set_enabled(pio0, sm, true);

        int control_chan = dma_claim_unused_channel(true);
        data_chan = dma_claim_unused_channel(true);

        dma_channel_config c = dma_channel_get_default_config(control_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, false);
        channel_config_set_write_increment(&c, false);
        dma_channel_configure(
            control_chan,
            &c,
            &dma_hw->ch[data_chan].al3_read_addr_trig,
            &control_chan_data,
            1,
            false
        );

        c = dma_channel_get_default_config(data_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, true);
        channel_config_set_write_increment(&c, false);
        channel_config_set_dreq(&c, DREQ_PIO0_TX0);
        channel_config_set_chain_to(&c, control_chan);
        channel_config_set_irq_quiet(&c, true);
    
        dma_channel_configure(
            data_chan,
            &c,
            &pio0->txf[sm],
            NULL,
            transfer_count,
            false
        );

        // dma_start_channel_mask(1u << control_chan);
        dma_channel_start(control_chan);
    }
    
}
