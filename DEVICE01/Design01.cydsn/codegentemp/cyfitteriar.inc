#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar_trm.inc

/* UART_rx */
UART_rx__0__DM__MASK EQU 0x07
UART_rx__0__DM__SHIFT EQU 0
UART_rx__0__DR EQU CYREG_PRT4_DR
UART_rx__0__HSIOM EQU CYREG_HSIOM_PORT_SEL4
UART_rx__0__HSIOM_MASK EQU 0x0000000F
UART_rx__0__HSIOM_SHIFT EQU 0
UART_rx__0__INTCFG EQU CYREG_PRT4_INTCFG
UART_rx__0__INTSTAT EQU CYREG_PRT4_INTSTAT
UART_rx__0__MASK EQU 0x01
UART_rx__0__PC EQU CYREG_PRT4_PC
UART_rx__0__PC2 EQU CYREG_PRT4_PC2
UART_rx__0__PORT EQU 4
UART_rx__0__PS EQU CYREG_PRT4_PS
UART_rx__0__SHIFT EQU 0
UART_rx__DR EQU CYREG_PRT4_DR
UART_rx__INTCFG EQU CYREG_PRT4_INTCFG
UART_rx__INTSTAT EQU CYREG_PRT4_INTSTAT
UART_rx__MASK EQU 0x01
UART_rx__PC EQU CYREG_PRT4_PC
UART_rx__PC2 EQU CYREG_PRT4_PC2
UART_rx__PORT EQU 4
UART_rx__PS EQU CYREG_PRT4_PS
UART_rx__SHIFT EQU 0

/* UART_SCB */
UART_SCB__BIST_CONTROL EQU CYREG_SCB0_BIST_CONTROL
UART_SCB__BIST_DATA EQU CYREG_SCB0_BIST_DATA
UART_SCB__CTRL EQU CYREG_SCB0_CTRL
UART_SCB__EZ_DATA00 EQU CYREG_SCB0_EZ_DATA00
UART_SCB__EZ_DATA01 EQU CYREG_SCB0_EZ_DATA01
UART_SCB__EZ_DATA02 EQU CYREG_SCB0_EZ_DATA02
UART_SCB__EZ_DATA03 EQU CYREG_SCB0_EZ_DATA03
UART_SCB__EZ_DATA04 EQU CYREG_SCB0_EZ_DATA04
UART_SCB__EZ_DATA05 EQU CYREG_SCB0_EZ_DATA05
UART_SCB__EZ_DATA06 EQU CYREG_SCB0_EZ_DATA06
UART_SCB__EZ_DATA07 EQU CYREG_SCB0_EZ_DATA07
UART_SCB__EZ_DATA08 EQU CYREG_SCB0_EZ_DATA08
UART_SCB__EZ_DATA09 EQU CYREG_SCB0_EZ_DATA09
UART_SCB__EZ_DATA10 EQU CYREG_SCB0_EZ_DATA10
UART_SCB__EZ_DATA11 EQU CYREG_SCB0_EZ_DATA11
UART_SCB__EZ_DATA12 EQU CYREG_SCB0_EZ_DATA12
UART_SCB__EZ_DATA13 EQU CYREG_SCB0_EZ_DATA13
UART_SCB__EZ_DATA14 EQU CYREG_SCB0_EZ_DATA14
UART_SCB__EZ_DATA15 EQU CYREG_SCB0_EZ_DATA15
UART_SCB__EZ_DATA16 EQU CYREG_SCB0_EZ_DATA16
UART_SCB__EZ_DATA17 EQU CYREG_SCB0_EZ_DATA17
UART_SCB__EZ_DATA18 EQU CYREG_SCB0_EZ_DATA18
UART_SCB__EZ_DATA19 EQU CYREG_SCB0_EZ_DATA19
UART_SCB__EZ_DATA20 EQU CYREG_SCB0_EZ_DATA20
UART_SCB__EZ_DATA21 EQU CYREG_SCB0_EZ_DATA21
UART_SCB__EZ_DATA22 EQU CYREG_SCB0_EZ_DATA22
UART_SCB__EZ_DATA23 EQU CYREG_SCB0_EZ_DATA23
UART_SCB__EZ_DATA24 EQU CYREG_SCB0_EZ_DATA24
UART_SCB__EZ_DATA25 EQU CYREG_SCB0_EZ_DATA25
UART_SCB__EZ_DATA26 EQU CYREG_SCB0_EZ_DATA26
UART_SCB__EZ_DATA27 EQU CYREG_SCB0_EZ_DATA27
UART_SCB__EZ_DATA28 EQU CYREG_SCB0_EZ_DATA28
UART_SCB__EZ_DATA29 EQU CYREG_SCB0_EZ_DATA29
UART_SCB__EZ_DATA30 EQU CYREG_SCB0_EZ_DATA30
UART_SCB__EZ_DATA31 EQU CYREG_SCB0_EZ_DATA31
UART_SCB__I2C_CFG EQU CYREG_SCB0_I2C_CFG
UART_SCB__I2C_CTRL EQU CYREG_SCB0_I2C_CTRL
UART_SCB__I2C_M_CMD EQU CYREG_SCB0_I2C_M_CMD
UART_SCB__I2C_S_CMD EQU CYREG_SCB0_I2C_S_CMD
UART_SCB__I2C_STATUS EQU CYREG_SCB0_I2C_STATUS
UART_SCB__INTR_CAUSE EQU CYREG_SCB0_INTR_CAUSE
UART_SCB__INTR_I2C_EC EQU CYREG_SCB0_INTR_I2C_EC
UART_SCB__INTR_I2C_EC_MASK EQU CYREG_SCB0_INTR_I2C_EC_MASK
UART_SCB__INTR_I2C_EC_MASKED EQU CYREG_SCB0_INTR_I2C_EC_MASKED
UART_SCB__INTR_M EQU CYREG_SCB0_INTR_M
UART_SCB__INTR_M_MASK EQU CYREG_SCB0_INTR_M_MASK
UART_SCB__INTR_M_MASKED EQU CYREG_SCB0_INTR_M_MASKED
UART_SCB__INTR_M_SET EQU CYREG_SCB0_INTR_M_SET
UART_SCB__INTR_RX EQU CYREG_SCB0_INTR_RX
UART_SCB__INTR_RX_MASK EQU CYREG_SCB0_INTR_RX_MASK
UART_SCB__INTR_RX_MASKED EQU CYREG_SCB0_INTR_RX_MASKED
UART_SCB__INTR_RX_SET EQU CYREG_SCB0_INTR_RX_SET
UART_SCB__INTR_S EQU CYREG_SCB0_INTR_S
UART_SCB__INTR_S_MASK EQU CYREG_SCB0_INTR_S_MASK
UART_SCB__INTR_S_MASKED EQU CYREG_SCB0_INTR_S_MASKED
UART_SCB__INTR_S_SET EQU CYREG_SCB0_INTR_S_SET
UART_SCB__INTR_SPI_EC EQU CYREG_SCB0_INTR_SPI_EC
UART_SCB__INTR_SPI_EC_MASK EQU CYREG_SCB0_INTR_SPI_EC_MASK
UART_SCB__INTR_SPI_EC_MASKED EQU CYREG_SCB0_INTR_SPI_EC_MASKED
UART_SCB__INTR_TX EQU CYREG_SCB0_INTR_TX
UART_SCB__INTR_TX_MASK EQU CYREG_SCB0_INTR_TX_MASK
UART_SCB__INTR_TX_MASKED EQU CYREG_SCB0_INTR_TX_MASKED
UART_SCB__INTR_TX_SET EQU CYREG_SCB0_INTR_TX_SET
UART_SCB__RX_CTRL EQU CYREG_SCB0_RX_CTRL
UART_SCB__RX_FIFO_CTRL EQU CYREG_SCB0_RX_FIFO_CTRL
UART_SCB__RX_FIFO_RD EQU CYREG_SCB0_RX_FIFO_RD
UART_SCB__RX_FIFO_RD_SILENT EQU CYREG_SCB0_RX_FIFO_RD_SILENT
UART_SCB__RX_FIFO_STATUS EQU CYREG_SCB0_RX_FIFO_STATUS
UART_SCB__RX_MATCH EQU CYREG_SCB0_RX_MATCH
UART_SCB__SPI_CTRL EQU CYREG_SCB0_SPI_CTRL
UART_SCB__SPI_STATUS EQU CYREG_SCB0_SPI_STATUS
UART_SCB__SS0_POSISTION EQU 0
UART_SCB__SS1_POSISTION EQU 1
UART_SCB__SS2_POSISTION EQU 2
UART_SCB__SS3_POSISTION EQU 3
UART_SCB__STATUS EQU CYREG_SCB0_STATUS
UART_SCB__TX_CTRL EQU CYREG_SCB0_TX_CTRL
UART_SCB__TX_FIFO_CTRL EQU CYREG_SCB0_TX_FIFO_CTRL
UART_SCB__TX_FIFO_STATUS EQU CYREG_SCB0_TX_FIFO_STATUS
UART_SCB__TX_FIFO_WR EQU CYREG_SCB0_TX_FIFO_WR
UART_SCB__UART_CTRL EQU CYREG_SCB0_UART_CTRL
UART_SCB__UART_RX_CTRL EQU CYREG_SCB0_UART_RX_CTRL
UART_SCB__UART_RX_STATUS EQU CYREG_SCB0_UART_RX_STATUS
UART_SCB__UART_TX_CTRL EQU CYREG_SCB0_UART_TX_CTRL

/* UART_SCB_IRQ */
UART_SCB_IRQ__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
UART_SCB_IRQ__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
UART_SCB_IRQ__INTC_MASK EQU 0x400
UART_SCB_IRQ__INTC_NUMBER EQU 10
UART_SCB_IRQ__INTC_PRIOR_MASK EQU 0xC00000
UART_SCB_IRQ__INTC_PRIOR_NUM EQU 3
UART_SCB_IRQ__INTC_PRIOR_REG EQU CYREG_CM0_IPR2
UART_SCB_IRQ__INTC_SET_EN_REG EQU CYREG_CM0_ISER
UART_SCB_IRQ__INTC_SET_PD_REG EQU CYREG_CM0_ISPR

/* UART_SCBCLK */
UART_SCBCLK__DIVIDER_MASK EQU 0x0000FFFF
UART_SCBCLK__ENABLE EQU CYREG_CLK_DIVIDER_A00
UART_SCBCLK__ENABLE_MASK EQU 0x80000000
UART_SCBCLK__MASK EQU 0x80000000
UART_SCBCLK__REGISTER EQU CYREG_CLK_DIVIDER_A00

/* UART_tx */
UART_tx__0__DM__MASK EQU 0x38
UART_tx__0__DM__SHIFT EQU 3
UART_tx__0__DR EQU CYREG_PRT4_DR
UART_tx__0__HSIOM EQU CYREG_HSIOM_PORT_SEL4
UART_tx__0__HSIOM_MASK EQU 0x000000F0
UART_tx__0__HSIOM_SHIFT EQU 4
UART_tx__0__INTCFG EQU CYREG_PRT4_INTCFG
UART_tx__0__INTSTAT EQU CYREG_PRT4_INTSTAT
UART_tx__0__MASK EQU 0x02
UART_tx__0__PC EQU CYREG_PRT4_PC
UART_tx__0__PC2 EQU CYREG_PRT4_PC2
UART_tx__0__PORT EQU 4
UART_tx__0__PS EQU CYREG_PRT4_PS
UART_tx__0__SHIFT EQU 1
UART_tx__DR EQU CYREG_PRT4_DR
UART_tx__INTCFG EQU CYREG_PRT4_INTCFG
UART_tx__INTSTAT EQU CYREG_PRT4_INTSTAT
UART_tx__MASK EQU 0x02
UART_tx__PC EQU CYREG_PRT4_PC
UART_tx__PC2 EQU CYREG_PRT4_PC2
UART_tx__PORT EQU 4
UART_tx__PS EQU CYREG_PRT4_PS
UART_tx__SHIFT EQU 1

/* InputPin */
InputPin__0__DM__MASK EQU 0x38
InputPin__0__DM__SHIFT EQU 3
InputPin__0__DR EQU CYREG_PRT0_DR
InputPin__0__HSIOM EQU CYREG_HSIOM_PORT_SEL0
InputPin__0__HSIOM_MASK EQU 0x000000F0
InputPin__0__HSIOM_SHIFT EQU 4
InputPin__0__INTCFG EQU CYREG_PRT0_INTCFG
InputPin__0__INTSTAT EQU CYREG_PRT0_INTSTAT
InputPin__0__MASK EQU 0x02
InputPin__0__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
InputPin__0__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
InputPin__0__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
InputPin__0__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
InputPin__0__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
InputPin__0__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
InputPin__0__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
InputPin__0__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
InputPin__0__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
InputPin__0__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
InputPin__0__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
InputPin__0__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
InputPin__0__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
InputPin__0__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
InputPin__0__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
InputPin__0__PC EQU CYREG_PRT0_PC
InputPin__0__PC2 EQU CYREG_PRT0_PC2
InputPin__0__PORT EQU 0
InputPin__0__PS EQU CYREG_PRT0_PS
InputPin__0__SHIFT EQU 1
InputPin__DR EQU CYREG_PRT0_DR
InputPin__INTCFG EQU CYREG_PRT0_INTCFG
InputPin__INTSTAT EQU CYREG_PRT0_INTSTAT
InputPin__MASK EQU 0x02
InputPin__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
InputPin__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
InputPin__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
InputPin__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
InputPin__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
InputPin__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
InputPin__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
InputPin__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
InputPin__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
InputPin__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
InputPin__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
InputPin__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
InputPin__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
InputPin__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
InputPin__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
InputPin__PC EQU CYREG_PRT0_PC
InputPin__PC2 EQU CYREG_PRT0_PC2
InputPin__PORT EQU 0
InputPin__PS EQU CYREG_PRT0_PS
InputPin__SHIFT EQU 1
InputPin__SNAP EQU CYREG_PRT0_INTSTAT

/* OutputPinSW */
OutputPinSW__0__DM__MASK EQU 0x38000
OutputPinSW__0__DM__SHIFT EQU 15
OutputPinSW__0__DR EQU CYREG_PRT2_DR
OutputPinSW__0__HSIOM EQU CYREG_HSIOM_PORT_SEL2
OutputPinSW__0__HSIOM_MASK EQU 0x00F00000
OutputPinSW__0__HSIOM_SHIFT EQU 20
OutputPinSW__0__INTCFG EQU CYREG_PRT2_INTCFG
OutputPinSW__0__INTSTAT EQU CYREG_PRT2_INTSTAT
OutputPinSW__0__MASK EQU 0x20
OutputPinSW__0__PA__CFG0 EQU CYREG_UDB_PA2_CFG0
OutputPinSW__0__PA__CFG1 EQU CYREG_UDB_PA2_CFG1
OutputPinSW__0__PA__CFG10 EQU CYREG_UDB_PA2_CFG10
OutputPinSW__0__PA__CFG11 EQU CYREG_UDB_PA2_CFG11
OutputPinSW__0__PA__CFG12 EQU CYREG_UDB_PA2_CFG12
OutputPinSW__0__PA__CFG13 EQU CYREG_UDB_PA2_CFG13
OutputPinSW__0__PA__CFG14 EQU CYREG_UDB_PA2_CFG14
OutputPinSW__0__PA__CFG2 EQU CYREG_UDB_PA2_CFG2
OutputPinSW__0__PA__CFG3 EQU CYREG_UDB_PA2_CFG3
OutputPinSW__0__PA__CFG4 EQU CYREG_UDB_PA2_CFG4
OutputPinSW__0__PA__CFG5 EQU CYREG_UDB_PA2_CFG5
OutputPinSW__0__PA__CFG6 EQU CYREG_UDB_PA2_CFG6
OutputPinSW__0__PA__CFG7 EQU CYREG_UDB_PA2_CFG7
OutputPinSW__0__PA__CFG8 EQU CYREG_UDB_PA2_CFG8
OutputPinSW__0__PA__CFG9 EQU CYREG_UDB_PA2_CFG9
OutputPinSW__0__PC EQU CYREG_PRT2_PC
OutputPinSW__0__PC2 EQU CYREG_PRT2_PC2
OutputPinSW__0__PORT EQU 2
OutputPinSW__0__PS EQU CYREG_PRT2_PS
OutputPinSW__0__SHIFT EQU 5
OutputPinSW__DR EQU CYREG_PRT2_DR
OutputPinSW__INTCFG EQU CYREG_PRT2_INTCFG
OutputPinSW__INTSTAT EQU CYREG_PRT2_INTSTAT
OutputPinSW__MASK EQU 0x20
OutputPinSW__PA__CFG0 EQU CYREG_UDB_PA2_CFG0
OutputPinSW__PA__CFG1 EQU CYREG_UDB_PA2_CFG1
OutputPinSW__PA__CFG10 EQU CYREG_UDB_PA2_CFG10
OutputPinSW__PA__CFG11 EQU CYREG_UDB_PA2_CFG11
OutputPinSW__PA__CFG12 EQU CYREG_UDB_PA2_CFG12
OutputPinSW__PA__CFG13 EQU CYREG_UDB_PA2_CFG13
OutputPinSW__PA__CFG14 EQU CYREG_UDB_PA2_CFG14
OutputPinSW__PA__CFG2 EQU CYREG_UDB_PA2_CFG2
OutputPinSW__PA__CFG3 EQU CYREG_UDB_PA2_CFG3
OutputPinSW__PA__CFG4 EQU CYREG_UDB_PA2_CFG4
OutputPinSW__PA__CFG5 EQU CYREG_UDB_PA2_CFG5
OutputPinSW__PA__CFG6 EQU CYREG_UDB_PA2_CFG6
OutputPinSW__PA__CFG7 EQU CYREG_UDB_PA2_CFG7
OutputPinSW__PA__CFG8 EQU CYREG_UDB_PA2_CFG8
OutputPinSW__PA__CFG9 EQU CYREG_UDB_PA2_CFG9
OutputPinSW__PC EQU CYREG_PRT2_PC
OutputPinSW__PC2 EQU CYREG_PRT2_PC2
OutputPinSW__PORT EQU 2
OutputPinSW__PS EQU CYREG_PRT2_PS
OutputPinSW__SHIFT EQU 5

/* InputInterrupt */
InputInterrupt__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
InputInterrupt__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
InputInterrupt__INTC_MASK EQU 0x01
InputInterrupt__INTC_NUMBER EQU 0
InputInterrupt__INTC_PRIOR_MASK EQU 0xC0
InputInterrupt__INTC_PRIOR_NUM EQU 3
InputInterrupt__INTC_PRIOR_REG EQU CYREG_CM0_IPR0
InputInterrupt__INTC_SET_EN_REG EQU CYREG_CM0_ISER
InputInterrupt__INTC_SET_PD_REG EQU CYREG_CM0_ISPR

/* Miscellaneous */
CYDEV_BCLK__HFCLK__HZ EQU 24000000
CYDEV_BCLK__HFCLK__KHZ EQU 24000
CYDEV_BCLK__HFCLK__MHZ EQU 24
CYDEV_BCLK__SYSCLK__HZ EQU 24000000
CYDEV_BCLK__SYSCLK__KHZ EQU 24000
CYDEV_BCLK__SYSCLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 18
CYDEV_CHIP_DIE_PSOC4A EQU 10
CYDEV_CHIP_DIE_PSOC5LP EQU 17
CYDEV_CHIP_DIE_TMA4 EQU 2
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC4
CYDEV_CHIP_JTAG_ID EQU 0x04B61193
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 10
CYDEV_CHIP_MEMBER_4C EQU 15
CYDEV_CHIP_MEMBER_4D EQU 6
CYDEV_CHIP_MEMBER_4E EQU 4
CYDEV_CHIP_MEMBER_4F EQU 11
CYDEV_CHIP_MEMBER_4G EQU 2
CYDEV_CHIP_MEMBER_4H EQU 9
CYDEV_CHIP_MEMBER_4I EQU 14
CYDEV_CHIP_MEMBER_4J EQU 7
CYDEV_CHIP_MEMBER_4K EQU 8
CYDEV_CHIP_MEMBER_4L EQU 13
CYDEV_CHIP_MEMBER_4M EQU 12
CYDEV_CHIP_MEMBER_4N EQU 5
CYDEV_CHIP_MEMBER_4U EQU 3
CYDEV_CHIP_MEMBER_5A EQU 17
CYDEV_CHIP_MEMBER_5B EQU 16
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_4A
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4C_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_4A_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_READ_ACCELERATOR EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_PROTECT_KILL EQU 4
CYDEV_DEBUG_PROTECT_OPEN EQU 1
CYDEV_DEBUG_PROTECT EQU CYDEV_DEBUG_PROTECT_OPEN
CYDEV_DEBUG_PROTECT_PROTECTED EQU 2
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DFT_SELECT_CLK0 EQU 1
CYDEV_DFT_SELECT_CLK1 EQU 2
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_IMO_TRIMMED_BY_USB EQU 0
CYDEV_IMO_TRIMMED_BY_WCO EQU 0
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_STACK_SIZE EQU 0x0400
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 1
CYDEV_VDDA_MV EQU 3300
CYDEV_VDDD_MV EQU 3300
CYDEV_WDT_GENERATE_ISR EQU 1
CYIPBLOCK_M0S8_CTBM_VERSION EQU 0
CYIPBLOCK_m0s8cpuss_VERSION EQU 0
CYIPBLOCK_m0s8csd_VERSION EQU 0
CYIPBLOCK_m0s8gpio2_VERSION EQU 0
CYIPBLOCK_m0s8hsiom4a_VERSION EQU 0
CYIPBLOCK_m0s8lcd_VERSION EQU 0
CYIPBLOCK_m0s8lpcomp_VERSION EQU 0
CYIPBLOCK_m0s8pclk_VERSION EQU 0
CYIPBLOCK_m0s8sar_VERSION EQU 0
CYIPBLOCK_m0s8scb_VERSION EQU 0
CYIPBLOCK_m0s8srssv2_VERSION EQU 1
CYIPBLOCK_m0s8tcpwm_VERSION EQU 0
CYIPBLOCK_m0s8udbif_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 2
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */