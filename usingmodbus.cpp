#include "usingmodbus.h"

UsingModBus::UsingModBus(QObject *parent, modbus_t * m_modbus) : QObject(parent), m_modbus(m_modbus)
{

}

void UsingModBus::sendModbusRequest(const int slave, const int func, const int addr, int num,  uint16_t* dest )
{
    if( m_modbus == NULL )
    {
        return;
    }
    int ret = -1;
    bool writeAccess = false;
    modbus_set_slave( m_modbus, slave);
    const int value = dest[0];
    uint8_t* dest8 = (uint8_t*)dest;

    switch( func )
    {
        case MODBUS_FC_READ_COILS:
            ret = modbus_read_bits( m_modbus, addr, num, dest8 );
            break;
        case MODBUS_FC_READ_DISCRETE_INPUTS:
            ret = modbus_read_bits( m_modbus, addr, num, dest8 );
            break;
        case MODBUS_FC_READ_HOLDING_REGISTERS:
            ret = modbus_read_registers( m_modbus, addr, num, dest );

            break;
        case MODBUS_FC_READ_INPUT_REGISTERS:
            ret = modbus_read_input_registers( m_modbus, addr, num, dest );

            break;
        case MODBUS_FC_WRITE_SINGLE_COIL:
            ret = modbus_read_bits( m_modbus, addr, num, dest8 );
            break;
        case MODBUS_FC_WRITE_SINGLE_REGISTER:
            ret = modbus_write_register( m_modbus, addr, value);
            writeAccess = true;
            num = 1;
            break;

        case MODBUS_FC_WRITE_MULTIPLE_COILS:
        {
            ret = modbus_write_bits( m_modbus, addr, num, dest8 );
            writeAccess = true;

            break;
        }
        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
        {
            ret = modbus_write_registers( m_modbus, addr, num, dest );

            writeAccess = true;
            break;
        }

        default:
            break;
    }

    if( ret == num  )
    {
        if( writeAccess )
        {

        }
    }
    else
    {
        if( ret < 0 )
        {
            if((errno == WSAETIMEDOUT) || (errno == EIO))
            {
                /*ui->Console->append("I/O error: did not receive any data from slave.");*/
            }
            else
            {
               /*ui->Console->append(QString("Slave threw exception \"%1\" or "
               "function not implemented.").arg(modbus_strerror(errno)));*/
            }
        }
        else
        {
           /*ui->Console->append("ModBusError:Number of registers returned does not "
            "match number of registers "
            "requested!");*/
        }
    }
}
