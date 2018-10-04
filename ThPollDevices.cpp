#include "ThPollDevices.h"


ThPollDevices::ThPollDevices(modbus_t *m_modbus):m_modbus(m_modbus)
{
    work=true;
}

ThPollDevices::~ThPollDevices()
{
    //input.close();
    //output.close();
    /*modbus_close(m_modbus);
    modbus_free(m_modbus);
    m_modbus=NULL;*/
}

bool ThPollDevices::isRunning()
{
    return work;
}

void ThPollDevices::StopWorkerThread()
{
    work=false;
}

static inline void FlushBuffer(uint16_t *Arr, int size){

    for(int i=0;i<size;i++){
        Arr[i]=0;
    }
}

static inline void FillBySpace(QString* str, uint32_t pos)
{
    for(uint32_t i=0;i<pos;i++)
    {
        str->append("  ");
    }
}

void ThPollDevices::run()
{
    QString console_msg;

    if(work){
        return;
    }

    QString result;

    QString line;

    QStringList terms;

    typedef struct{
        uint32_t Address;
        uint8_t Opcode;
        uint16_t num;
        uint16_t TX[256];
        uint16_t RX[256];
        uint16_t FLAG_SUCCESS_REQ_MB=0;
        uint16_t FLAG_SUCCESS_FPGA=0;
    }FPGA_CMD;

    QList<FPGA_CMD> list_command;
    list_command.clear();
    int size_terms=0;
    QString ErrorParser;
    QString testline;

    do
    {



    } while (work);

    if(list_command.isEmpty()){
        emit sendMessage("There are no valid commands in the input file.");
        work=false;
        return;
    }

    sendProgressStatus(0);
    int i = 0;
    uint16_t data[10];
    int try_op;
    int req = -1;
    foreach(FPGA_CMD cmd, list_command)
    {
        if(!work){
            break;
        }

        try_op=10;
        req = sendModbusRequest(1, MODBUS_FC_READ_HOLDING_REGISTERS, 0, 1, data);
        Sleep(100);

        while((data[0]!=0)&&(try_op>0)&&work)//wait for KMK is busy
        {
            req = sendModbusRequest(1, MODBUS_FC_READ_HOLDING_REGISTERS, 0, 1, data);
            Sleep(100);
            try_op--;
        }
        sendModbusRequest(1, MODBUS_FC_WRITE_MULTIPLE_REGISTERS, 8, cmd.num, cmd.TX);


            memset(cmd.RX,0,cmd.num*sizeof(uint16_t));
            sendModbusRequest(1, MODBUS_FC_READ_INPUT_REGISTERS, 2, 1, data);
            cmd.RX[0] = data[0];
            console_msg = QString("---->Address 0x%1 Opcode 0xC0 RX:0x%2 ").arg(cmd.Address,0,16).arg(cmd.RX[0],0,16);
            console_msg.append(QString("\n MB_req_ok:%1  SPI_req_ok:%2").arg(cmd.FLAG_SUCCESS_REQ_MB>0?1:0).arg(cmd.FLAG_SUCCESS_FPGA));
            console_msg.append("\r\n");

            emit sendMessage(console_msg);
            break;


        sendProgressStatus(100*(i+1)/(list_command.size()));
        i++;
    }

    emit resultReady(result);
    work=false;

}


int ThPollDevices::sendModbusRequest(const int slave, const int func, const int addr, int num,  uint16_t* dest )
{
    if( m_modbus == NULL )
    {
        return -1;
    }
    int ret = -1;
    bool is16Bit=false;
    bool writeAccess=false;
    modbus_set_slave( m_modbus, slave );

    switch( func )
    {
        case MODBUS_FC_READ_COILS:
            //ret = modbus_read_bits( m_modbus, addr, num, dest );
            break;
        case MODBUS_FC_READ_DISCRETE_INPUTS:
            //ret = modbus_read_input_bits( m_modbus, addr, num, dest );
            break;
        case MODBUS_FC_READ_HOLDING_REGISTERS:
            ret = modbus_read_registers( m_modbus, addr, num, dest );
            is16Bit = true;
            break;
        case MODBUS_FC_READ_INPUT_REGISTERS:
            ret = modbus_read_input_registers( m_modbus, addr, num, dest );
            is16Bit = true;
            break;
       /* case MODBUS_FC_WRITE_SINGLE_COIL:
            ret = modbus_write_bit( m_modbus, addr,
                    ui->regTable->item( 0, DataColumn )->
                        text().toInt(0, 0) ? 1 : 0 );
            writeAccess = true;
            num = 1;
            break;*/

        case MODBUS_FC_WRITE_SINGLE_REGISTER:
            ret = modbus_write_register( m_modbus, addr, dest[0] );
            writeAccess = true;
            num = 1;
            break;

        /*case MODBUS_FC_WRITE_MULTIPLE_COILS:
        {
            uint8_t * data = new uint8_t[num];
            for( int i = 0; i < num; ++i )
            {
                data[i] = ui->regTable->item( i, DataColumn )->
                                text().toInt(0, 0);
            }
            ret = modbus_write_bits( m_modbus, addr, num, data );
            delete[] data;
            writeAccess = true;
            break;
        }*/

        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
        {
            ret = modbus_write_registers( m_modbus, addr, num, dest );
            writeAccess = true;
            break;
        }

        default:
            //QMessageBox::warning( this, tr( "Unimplemented function code" ), tr( "Function code %1 not implemented" ).arg( func ) );
            break;
    }

    if( ret == num )
    {
       return num;
    }
    else
    {
        if( ret < 0 )
        {
            if(
#ifdef WIN32
                    errno == WSAETIMEDOUT ||
#endif
                    errno == EIO
                                                                    )
            {
                emit sendMessage("I/O error: did not receive any data from slave.");
               //QMessageBox::critical( this, tr( "I/O error" ),
//                    tr( "I/O error: did not receive any data from slave." ) );
            }
            else
            {
                emit sendMessage(QString("Slave threw exception \"%1\" or function not implemented.").arg( modbus_strerror( errno ) ));
               // QMessageBox::critical( this, tr( "Protocol error" ),
                 //   tr( "Slave threw exception \"%1\" or "
                       // "function not implemented." ).
                          //      arg( modbus_strerror( errno ) ) );
            }
        }
        else
        {
            emit sendMessage("Number of registers returned does not match number of registers requested!");
           // QMessageBox::critical( this, tr( "Protocol error" ),
              //  tr( "Number of registers returned does not "
                 //   "match number of registers "
                        //    "requested!" ) );
        }
    }

    return -1;
}
