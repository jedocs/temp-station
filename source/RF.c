#include "include\define.h"

// rf input/output buffers:
unsigned char RxPacket[PAYLOAD_LEN]; // Receive data puffer (payload only)
unsigned char TxPacket[TXBUF_LEN]; // Transmit data puffer
unsigned char TxPacketPtr; // Next byte to send
unsigned char RxPacketPtr; // Next byte to send
unsigned char RxPacketLen;
BOOL hasPacket;

// IA4420 SPI commands:
unsigned int Power_management_cmd = 0x8201; // Everything off, uC clk disabled   Power_management_cmd;
unsigned int Receiver_control_cmd = 0x9481; // BW=135kHz, DRSSI=-97dBm, pin8=VDI, fast VDI   81      Receiver_control_cmd;
unsigned int Txreg_write_cmd = 0xB800; //Txreg_write_cmd;
unsigned int FIFO_cmd = 0xCA81; // Sync. latch cleared, limit=8bits, disable sensitive reset    FIFO_cmd;
unsigned int Data_filter_cmd = 0xC22C; // Digital LPF (default)    Data_filter_cmd;
unsigned int AFC_cmd = 0xC4F7; // Auto AFC (default)   AFC_cmd;
unsigned int Frequency_cmd = 0xA7D0; // (Fo=915.000MHz (default))?????   870.000    Frequency_cmd;
unsigned int Data_rate_cmd = 0xC623; // 9579Baud (default)   Data_rate_cmd;
unsigned int Transmitter_control_cmd = 0x9850; // df=75kHz, Pmax, normal modulation polarity  Transmitter_control_cmd;
unsigned int Configuration_cmd = 0x8007 | FREQ_Band; // Cload=12pF; TX registers, FIFO are disabled  Configuration_cmd;
char jooin[10] = "qwe";

WORD rcrc, ccrc;

//================================================================7
// HW SPI write

void SPIPut(unsigned char v) {
    unsigned char i;
    IFS0bits.SPI1IF = 0;
    i = SPI1BUF;
    SPI1BUF = v;
    while (IFS0bits.SPI1IF == 0) {
    }
}

//*********************************************************************

unsigned char SPIGet(void) {
    SPIPut(0x00);
    return SPI1BUF;
}

// Send SPI command to the rf chip                              // send 16-bit SPI command with NSEL control
//--------------------------------------------------------------

void send_cmd(unsigned int spicmd) {
    NSEL = 0;
    SPIPut(spicmd >> 8);
    SPIPut(spicmd);
    NSEL = 1;
}

//==============================================================
// initialization
//==============================================================

void RF_init(void) {
    unsigned int ch;
    SDIdir = 1;
    SDOdir = 0;
    SCKdir = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;
    SPI_SDI = 1;

    RxPacketLen = 0;
    RxPacketPtr = 0;
    hasPacket = FALSE;

    //----  configuring the RF link --------------------------------
    ch = 7; //1340
    Frequency_cmd = (0xA000 + FREQ_start + ((unsigned int) ch * FREQ_step));
    send_cmd(0xCC77); // PLL setting cmd. HOPE RF datasheet!!!!!!!!!!!!!!!!!!!!!!!!
    send_cmd(FIFO_cmd);
    send_cmd(FIFO_cmd | 0x0002); // enable synchron latch
    send_cmd(Configuration_cmd);
    send_cmd(Frequency_cmd);
    send_cmd(Power_management_cmd);
    send_cmd(Receiver_control_cmd);
    send_cmd(Transmitter_control_cmd);

    // antenna tuning on startup
    send_cmd(Power_management_cmd | 0x0020); // turn on the transmitter
    DelayMs(5); // ant.tuning time (~100us) + Xosc starup time (5ms)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // end of antenna tuning
    send_cmd(Power_management_cmd | 0x0080); // turn off transmitter, turn on receiver
    send_cmd(Configuration_cmd | 0x0040); // enable the FIFO
    send_cmd(FIFO_cmd);
    send_cmd(FIFO_cmd | 0x0002); // enable synchron latch
    send_cmd(0x0000); // read status byte (read ITs)


    //send_cmd(Power_management_cmd);                     // **********************************************************************************!!!!!!


    IFS1bits.INT2IF = 0;
    IEC1bits.INT2IE = 1;
}

/*********************************************************************
 * Function:        void HighISR(void)
 ********************************************************************/

void _ISRFAST __attribute__((interrupt, auto_psv)) _INT2Interrupt(void) {
    if (IEC1bits.INT2IE && IFS1bits.INT2IF) {

        NSEL = 0; // Sorrend fontos!!!!!!! (nsel, sdidir, spi_sdi) (késleltetés miatt?)
        Nop(); //kell !!!!
        
        if (SPI_SDI) // There is data in RX FIFO
        {
            BYTE RxPacketPtr, tmpPacketLen;
            WORD counter, received_crc, calculated_crc;
            NSEL = 1;
            NFFS = 0; // FIFO selected
            tmpPacketLen = SPIGet();

            if (tmpPacketLen >= PAYLOAD_LEN || tmpPacketLen == 0 || hasPacket) {
IGNORE_HERE:
                NFFS = 1; // bad packet len received
                send_cmd(Power_management_cmd); // turn off the transmitter and receiver
                send_cmd(FIFO_cmd); // reset FIFO
                send_cmd(Configuration_cmd); // disable FIFO, TX_latch
                send_cmd(Configuration_cmd | 0x0040); // enable FIFO
                send_cmd(Power_management_cmd | 0x0080); // turn on receiver
                send_cmd(FIFO_cmd | 0x0002); // FIFO synchron latch re-enabled
                hasPacket=FALSE;
                goto RETURN_HERE;
            }

            RxPacketLen = tmpPacketLen;
            NFFS = 1;
            RxPacketPtr = 0;
            counter = 0;

            while (1) {
                if (counter++ == 0xFFFF) {
                    goto IGNORE_HERE;
                } else if (FFIT == 1) {
                    NFFS = 0;
                    counter = 0;
                    RxPacket[RxPacketPtr++] = SPIGet();

                    if (RxPacketPtr >= RxPacketLen) {
                        RxPacket[RxPacketPtr++] = 0;
                        RxPacket[RxPacketPtr++] = 0;
                        NFFS = 1;
                        send_cmd(FIFO_cmd);

                        RxPacketLen -= 2; // do not count CRC
                        received_crc = ((WORD) RxPacket[RxPacketLen + 1])+(((WORD) RxPacket[RxPacketLen]) << 8);
                        calculated_crc = CRC16((BYTE *) RxPacket, RxPacketLen); // CRC_HW_calculateB((BYTE *) RxPacket, RxPacketLen);

                        if (received_crc != calculated_crc) {
                            RxPacketPtr = 0;
                            RxPacketLen = 0;
                            send_cmd(FIFO_cmd | 0x0002); // FIFO synchron latch re-enable
                            goto IGNORE_HERE;
                        }
                        send_cmd(FIFO_cmd | 0x0002);
                        hasPacket = TRUE;
//LED=1;
                        goto RETURN_HERE;
                    }
                    NFFS = 1;
                }
            }
        } else // read the rest of the interrupts
        {
            SPIGet();
            NSEL = 1;
        }
RETURN_HERE:
          IFS1bits.INT2IF = 0;
    }
}

/*********************************************************************
 * BOOL TxPacket(BYTE TxPacketLen)
 *
 * Overview:
 *              This function send the packet in the buffer TxPacket
 ********************************************************************/
void Tx(BYTE TxPacketLen) {

    WORD crc;
    BYTE TxPacketPtr, synCount;
    LED = 1;

    IEC1bits.INT2IE = 0;

    if (TxPacketLen + 2 > PACKET_LEN) {
        TxPacketLen = (PACKET_LEN - 2);
    }

    crc = CRC16(TxPacket, TxPacketLen);
    TxPacket[TxPacketLen++] = (crc >> 8);
    TxPacket[TxPacketLen++] = crc;

    // Turn off receiver, enable the TX register
    send_cmd(Power_management_cmd);
    send_cmd(Configuration_cmd | 0x0080);

    // enable transmitter
    send_cmd(Power_management_cmd | 0x0020);

    DelayMs(1); //?????????????????????????????????????????????

    TxPacketPtr = 0;
    synCount = 0;

    NSEL = 0;

    SPIPut(0xB8); // FIFO write
    SPIPut(0xAA); // 3rd preamble

    while (TxPacketPtr < TxPacketLen + 2) // 2 dummy byte
    {
        if (SPI_SDI == 1) {
            if (TxPacketPtr == 0 && synCount < 3) {
                switch (synCount) {
                    case 0:
                        SPIPut(0x2D); // first syn byte
                        break;
                    case 1:
                        SPIPut(0xD4); // second syn byte
                        break;
                    case 2:
                        SPIPut(TxPacketLen);
                        break;
                    default:
                        break;
                }
                synCount++;
            } else {
                SPIPut(TxPacket[TxPacketPtr]);
                TxPacketPtr++;
            }
        }
    }
    NSEL = 1;

    // Turn off the transmitter, disable the Tx register
    send_cmd(Power_management_cmd | 0x0080);
    send_cmd(Configuration_cmd | 0x0040);
    send_cmd(FIFO_cmd | 0x0002);

    //	status = SPIGet();                     //  clock pulse to reset the IT latches ???????????????????????????????????????
    //status = SPIGet();                     //  clock pulse to reset the IT latches ???????????????????????????????????????

    IEC1bits.INT2IE = 1;
    LED = 0;
}

char RF_join(void) {
    unsigned int error = 0, i;

    TxPacket[0] = (HELYISEG | 0b10100000);
    Tx(1);

    for (i = 0; i < 65535; i++) if (hasPacket) break; //wait until reply

    if (!hasPacket || (RxPacketLen != 8) || (RxPacket[0] != (0b01010000 | HELYISEG))) {
        //error = 1; // or timeout is reached
        if (RxPacketLen != 8) error += 4;
        if (RxPacket[0] != (0b01010000 | HELYISEG)) error += 2;
        if (!hasPacket) error += 1;
        return error;
    }
    return 0;

}